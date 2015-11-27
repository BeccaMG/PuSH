#include "puzzlewidget.h"

#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>
#include <QMessageBox>
#include <QMenu>
#include <QWidgetAction>
#include <QInputDialog>
#include <QDir>

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

PuzzleWidget::PuzzleWidget(QWidget *parent)
    : QWidget(parent), m_ImageSize(300)
{
    setAcceptDrops(true);

    m_pContextMenu = new QMenu();

    setContextMenuPolicy(Qt::CustomContextMenu);

    m_pActionDelete = m_pContextMenu->addAction("Delete piece");
    m_pActionSetText = m_pContextMenu->addAction("Change piece text...");

    connect(this,
            SIGNAL(customContextMenuRequested(const QPoint)),this,
            SLOT(contextMenuRequested(QPoint)));
    connect(m_pActionDelete,
            SIGNAL(triggered()), this,
            SLOT(deletePieceAt()));
    connect(m_pActionSetText,
            SIGNAL(triggered()), this,
            SLOT(changeTextPieceAt()));
}

void PuzzleWidget::clear()
{
    pieceLocations.clear();
    piecePixmaps.clear();
    pieceRects.clear();
    pieceTexts.clear();
    piecePointers.clear();
    highlightedRect = QRect();

    update();
}

void PuzzleWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("puzzle-piece"))
        event->accept();
    else
        event->ignore();
}

void PuzzleWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    QRect updateRect = highlightedRect;
    highlightedRect = QRect();
    update(updateRect);
    event->accept();
}

void PuzzleWidget::dragMoveEvent(QDragMoveEvent *event)
{
    QRect updateRect = highlightedRect.united(targetSquare(event->pos()));

    if (event->mimeData()->hasFormat("puzzle-piece")
        && findPiece(targetSquare(event->pos())) == -1) {

        highlightedRect = targetSquare(event->pos());
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        highlightedRect = QRect();
        event->ignore();
    }

    update(updateRect);
}

void PuzzleWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("puzzle-piece")
        && findPiece(targetSquare(event->pos())) == -1) {

        QByteArray pieceData = event->mimeData()->data("puzzle-piece");
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        QRect square = targetSquare(event->pos());
        QPixmap pixmap;
        QPoint location;
        QString text;

        dataStream >> pixmap >> location >> text;

        PuzzlePiece* newPiece;
        if (draggingExistingPiece == NULL) {
            newPiece = pieceByType(text);
        } else {
            newPiece = draggingExistingPiece;
            draggingExistingPiece = NULL;
        }

        if (!checkPuzzleMatch(newPiece, square)) {
            highlightedRect = QRect();
            QRect updateRect = highlightedRect.united(targetSquare(event->pos()));            
            event->ignore();
            update(updateRect);
            return;
        }        

        pieceLocations.append(location);
        piecePixmaps.append(pixmap);
        pieceRects.append(square);
        pieceTexts.append(text);
        piecePointers.append(newPiece);

        highlightedRect = QRect();
        update(square);

        event->setDropAction(Qt::MoveAction);
        event->accept();

    } else {
        highlightedRect = QRect();
        event->ignore();
    }
}

int PuzzleWidget::findPiece(const QRect &pieceRect) const
{
    for (int i = 0; i < pieceRects.size(); ++i) {
        if (pieceRect == pieceRects[i])
            return i;
    }
    return -1;
}

void PuzzleWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        event->ignore();
        return;
    }

    QRect square = targetSquare(event->pos());
    int found = findPiece(square);

    if (found == -1)
        return;

    QPoint location = pieceLocations[found];
    QPixmap pixmap = piecePixmaps[found];
    QString text = pieceTexts[found];
    draggingExistingPiece = piecePointers[found];
    PuzzlePiece *auxPiece = piecePointers[found];

    pieceLocations.removeAt(found);
    piecePixmaps.removeAt(found);
    pieceRects.removeAt(found);
    pieceTexts.removeAt(found);
    piecePointers.removeAt(found);

    update(square);

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);

    dataStream << pixmap << location << text;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("puzzle-piece", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(event->pos() - square.topLeft());
    drag->setPixmap(pixmap);

    if (!(drag->exec(Qt::MoveAction) == Qt::MoveAction)) {
        pieceLocations.insert(found, location);
        piecePixmaps.insert(found, pixmap);
        pieceRects.insert(found, square);
        pieceTexts.insert(found, text);
        if (draggingExistingPiece == NULL) {
            piecePointers.insert(found, auxPiece);
        } else {
            piecePointers.insert(found, draggingExistingPiece);
        }
        update(targetSquare(event->pos()));
    }
}

void PuzzleWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);

    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(event->rect(), Qt::white);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

    if (highlightedRect.isValid()) {
        painter.setBrush(QColor("#66CCFF"));
        painter.setPen(Qt::NoPen);
        painter.drawRect(highlightedRect.adjusted(0, 0, -1, -1));
    }

    for (int i = 0; i < pieceRects.size(); ++i) {
        painter.drawPixmap(pieceRects[i], piecePixmaps[i]);
        painter.drawText(pieceRects[i], Qt::AlignCenter,
                         piecePointers[i]->g_Text->text());
    }
    painter.end();
}

const QRect PuzzleWidget::targetSquare(const QPoint &position) const
{
    return QRect(position.x()/pieceSize() * pieceSize(),
                 position.y()/pieceSize() * pieceSize(),
                 pieceSize(),
                 pieceSize());
}

int PuzzleWidget::pieceSize() const
{
    return m_ImageSize / 3;
}

int PuzzleWidget::imageSize() const
{
    return m_ImageSize;
}

QString PuzzleWidget::generateCommand()
{
    if (pieceRects.size() > 0) {
        QString str = ">$";
        int minIndex = 0;
        QRect minPoint = pieceRects[minIndex];

        for (int i = 0; i < pieceRects.size(); i++)
        {
            if (piecePointers[i]->pieceText.toStdString() == "process")
            {
                minIndex = i;
                minPoint = pieceRects[i];
                break;
            }
        }
        // Find the process piece most to the left
        for (int i = 0; i < pieceRects.size(); i++)
        {
            if (pieceRects[i].left() <= minPoint.left()
                    && piecePointers[i]->pieceText.toStdString() == "process")
            {
                minIndex = i;
                minPoint = pieceRects[i];
            }
        }

        int *total = new int(0);

        if (piecePointers[minIndex]->pieceText.toStdString() == "process")
        {
            str = piecePointers[minIndex]->getPieceText(total);
            if (*total == piecePointers.size())
                return ">$" + str;
            QMessageBox msgBox;
            msgBox.setText("Incomplete or incoherent puzzle");
            msgBox.setInformativeText("Please put all the pieces together in order before generating the command.");
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();
        } else {
            QMessageBox msgBox;
            msgBox.setText("Incomplete or incoherent puzzle");
            msgBox.setInformativeText("Please put all the pieces together in order before generating the command.");
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.exec();
        }
    }
    return ">$";
}

PuzzlePiece* PuzzleWidget::pieceByType(QString text)
{
    std::string puzzleType = text.toStdString();
    PuzzlePiece *newPiece = new PuzzlePiece();

    if (puzzleType == "process") {
        newPiece->processPiece();
    }
    if (puzzleType == "|") {
        newPiece->pipePiece();
    }
    if (puzzleType == "inFile") {
        newPiece->inputFilePiece();
    }
    if (puzzleType == "outFile") {
        newPiece->outputFilePiece();
    }
    if (puzzleType == "err_file") {
        newPiece->errorFilePiece();
    }

    return newPiece;
}

bool PuzzleWidget::checkPuzzleMatch(PuzzlePiece *piece, QRect square)
{
    QPoint auxPointUp(square.left(), square.top()-1); // Up
    QPoint auxPointDown(square.left(), square.bottom()+1); // Down
    QPoint auxPointLeft(square.left()-1, square.top()); // Left
    QPoint auxPointRight(square.right()+1, square.top()); // Right

    if (hasValidPiece(piece, auxPointUp, UP)
            && hasValidPiece(piece, auxPointDown, DOWN)
            && hasValidPiece(piece, auxPointLeft, LEFT)
            && hasValidPiece(piece, auxPointRight, RIGHT))
        piece->clearLinks();

    return (hasValidPiece(piece, auxPointUp, UP)
            && hasValidPiece(piece, auxPointDown, DOWN)
            && hasValidPiece(piece, auxPointLeft, LEFT)
            && hasValidPiece(piece, auxPointRight, RIGHT));
}

bool PuzzleWidget::hasValidPiece(PuzzlePiece *piece, QPoint position, int side)
{
    int found = findPiece(targetSquare(position));
    PuzzlePiece *auxPiece;

    if (found == -1) // No piece means it is valid
        return true;

    auxPiece = piecePointers[found];

    if (side == UP) {
        if ((piece->upSide == auxPiece->downSide) && (piece->upSide != -1)) {
            piece->upPiece = auxPiece;
            auxPiece->downPiece = piece;
            return true;
        }
        return false;
    }
    if (side == DOWN) {
        if ((piece->downSide == auxPiece->upSide) && (piece->downSide != -1)) {
            piece->downPiece = auxPiece;
            auxPiece->upPiece = piece;
            return true;
        }
        return false;
    }
    if (side == LEFT) {
        if ((piece->leftSide == auxPiece->rightSide) && (piece->leftSide != -1)) {
            piece->leftPiece = auxPiece;
            auxPiece->rightPiece = piece;
            return true;
        }
        return false;
    }
    if (side == RIGHT) {
        if ((piece->rightSide == auxPiece->leftSide) && (piece->rightSide != -1)) {
            piece->rightPiece = auxPiece;
            auxPiece->leftPiece = piece;
            return true;
        }
        return false;
    }

    return false;
}

void PuzzleWidget::contextMenuRequested(QPoint point)
{
    QRect square = targetSquare(point);
    int found = findPiece(square);

    if (found == -1)
        return;

    pointRightClicked = point;
    m_pContextMenu->popup(mapToGlobal(point));
}

void PuzzleWidget::deletePieceAt()
{
    QRect square = targetSquare(pointRightClicked);
    int found = findPiece(square);

    QMessageBox msgBox;
    msgBox.setText("Deleting puzzle piece...");
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setInformativeText("Do you really want to delete this piece?");
    msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();

    if (ret == QMessageBox::Yes) {
        piecePointers[found]->clearLinks();
        pieceLocations.removeAt(found);
        piecePixmaps.removeAt(found);
        pieceRects.removeAt(found);
        pieceTexts.removeAt(found);
        piecePointers.removeAt(found);
    }
}

void PuzzleWidget::changeTextPieceAt()
{    
    QRect square = targetSquare(pointRightClicked);
    int found = findPiece(square);

    bool ok;
    QString text = QInputDialog::getText(this, tr("Changing piece text..."),
                                             tr("New piece text (this will not afect a pipe piece):"), QLineEdit::Normal,
                                             piecePointers[found]->g_Text->text(), &ok);

    if (piecePointers[found]->pieceText == "|")
        return;

    if (ok && !text.isEmpty())
            piecePointers[found]->g_Text->setText(text);
}
