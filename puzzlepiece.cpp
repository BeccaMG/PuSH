#include "puzzlepiece.h"

#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>

PuzzlePiece::PuzzlePiece(QListWidget *parent)
    : QListWidgetItem(parent)
{
    g_Piece = new QLabel(parent);
    g_Text = new QLabel(parent);
}

QString PuzzlePiece::getPieceText(int *total)
{
    std::string puzzleType = pieceText.toStdString();
    QString result = " ";
    (*total)++;

    if (puzzleType == "process") {
        result += g_Text->text();
        if (leftPiece != NULL &&
                leftPiece->pieceText.toStdString() != "|") {
            result += leftPiece->getPieceText(total);
        }
        if (downPiece != NULL) {
            result += downPiece->getPieceText(total);
        }
        if (rightPiece != NULL) {
            result += rightPiece->getPieceText(total);
        }
    }
    if (puzzleType == "|") {
        result += pieceText;
        if (rightPiece != NULL) {
            result += rightPiece->getPieceText(total);
        }
    }
    if (puzzleType == "inFile") {
        result += "< " + g_Text->text();
    }
    if (puzzleType == "outFile") {
        result += "> " + g_Text->text();
    }
    if (puzzleType == "err_file") {
        result += "2> " + g_Text->text();
    }
    return result;
}

void PuzzlePiece::processPiece()
{
    pieceText = "process";
    g_Text->setText(pieceText);
    g_Piece->setPixmap(QPixmap(":/images/images/process.png"));
    upSide = -1;
    downSide = 2;
    leftSide = 0;
    rightSide = 1;
}

void PuzzlePiece::pipePiece()
{
    pieceText = "|";
    g_Text->setText(pieceText);
    g_Piece->setPixmap(QPixmap(":/images/images/pipe.png"));
    upSide = -1;
    downSide = -1;
    leftSide = 1;
    rightSide = 0;
}

void PuzzlePiece::inputFilePiece()
{
    pieceText = "inFile";
    g_Text->setText(pieceText);
    g_Piece->setPixmap(QPixmap(":/images/images/in_file.png"));
    upSide = -1;
    downSide = -1;
    leftSide = -1;
    rightSide = 0;
}

void PuzzlePiece::outputFilePiece()
{
    pieceText = "outFile";
    g_Text->setText(pieceText);
    g_Piece->setPixmap(QPixmap(":/images/images/out_file.png"));
    upSide = -1;
    downSide = -1;
    leftSide = 1;
    rightSide = -1;
}

void PuzzlePiece::errorFilePiece()
{
    pieceText = "err_file";
    g_Text->setText(pieceText);
    g_Piece->setPixmap(QPixmap(":/images/images/err_file.png"));
    upSide = 2;
    downSide = -1;
    leftSide = -1;
    rightSide = -1;
}

void PuzzlePiece::clearLinks()
{
    if (upPiece != NULL) {
        upPiece->downPiece = NULL;
        upPiece = NULL;
    }
    if (downPiece != NULL) {
        downPiece->upPiece = NULL;
        downPiece = NULL;
    }
    if (leftPiece != NULL) {
        leftPiece->rightPiece = NULL;
        leftPiece = NULL;
    }
    if (rightPiece != NULL) {
        rightPiece->leftPiece = NULL;
        rightPiece = NULL;
    }
}
