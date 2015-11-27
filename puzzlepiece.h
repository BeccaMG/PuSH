#ifndef PUZZLEPIECE_H
#define PUZZLEPIECE_H

#include <QList>
#include <QPoint>
#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
class QMouseEvent;
QT_END_NAMESPACE

class PuzzlePiece : public QListWidgetItem
{

public:
    PuzzlePiece(QListWidget * parent = 0);

    QLabel *g_Piece;
    QLabel *g_Text;
    QString pieceText;

    PuzzlePiece *upPiece = NULL;
    PuzzlePiece *downPiece = NULL;
    PuzzlePiece *leftPiece = NULL;
    PuzzlePiece *rightPiece = NULL;

    int upSide;
    int downSide;
    int leftSide;
    int rightSide;

    QString getPieceText(int *total);

    void processPiece();
    void pipePiece();
    void inputFilePiece();
    void outputFilePiece();
    void errorFilePiece();

    void clearLinks();
};

#endif // PUZZLEPIECE_H
