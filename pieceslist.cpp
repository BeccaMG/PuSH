#include "pieceslist.h"

#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>

PiecesList::PiecesList(QWidget *parent)
    : QListWidget(parent), m_PieceSize(100)
{
    setDragEnabled(true);
    setViewMode(QListView::IconMode);
    setIconSize(QSize(m_PieceSize, m_PieceSize));
    setSpacing(10);
    setDropIndicatorShown(true);
}

void PiecesList::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("puzzle-piece"))
        event->accept();
    else
        event->ignore();
}

void PiecesList::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("puzzle-piece")) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        event->ignore();
    }
}

void PiecesList::dropEvent(QDropEvent *event)
{
        event->ignore();
}

// Drag a piece from the list
void PiecesList::startDrag(Qt::DropActions /*supportedActions*/)
{
    QListWidgetItem *originalItem = currentItem();
    QListWidgetItem *item = originalItem->clone();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    QPixmap pixmap = qvariant_cast<QPixmap>(item->data(Qt::UserRole));
    QPoint location = item->data(Qt::UserRole+1).toPoint();
    QString text = item->data(Qt::UserRole+2).toString();

    dataStream << pixmap << location << text;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("puzzle-piece", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(QPoint(pixmap.width()/2, pixmap.height()/2));
    drag->setPixmap(pixmap);

    if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
        delete takeItem(row(item));
}
