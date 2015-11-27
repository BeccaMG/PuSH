#ifndef PUZZLEWIDGET_H
#define PUZZLEWIDGET_H

#include <QList>
#include <QString>
#include <QPoint>
#include <QPixmap>
#include <QWidget>

#include "puzzlepiece.h"

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
class QMouseEvent;
QT_END_NAMESPACE

class PuzzleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PuzzleWidget(QWidget *parent = 0);
    void clear();

    int pieceSize() const;
    int imageSize() const;

    QString generateCommand();

protected:
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragLeaveEvent(QDragLeaveEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    int findPiece(const QRect &pieceRect) const;
    const QRect targetSquare(const QPoint &position) const;

    PuzzlePiece* pieceByType(QString text);
    bool checkPuzzleMatch(PuzzlePiece *piece, QRect square);
    bool hasValidPiece(PuzzlePiece *piece, QPoint position, int side);

    QList<QPixmap> piecePixmaps;
    QList<QRect> pieceRects;
    QList<QPoint> pieceLocations;
    QList<QString> pieceTexts;
    QList<PuzzlePiece*> piecePointers;

    QRect highlightedRect;

    PuzzlePiece* draggingExistingPiece = NULL;
    int m_ImageSize;

    std::list<PuzzlePiece*> puzzle;

    QMenu* m_pContextMenu;
    QAction* m_pActionDelete;
    QAction* m_pActionSetText;

    QPoint pointRightClicked;


private slots:
    void contextMenuRequested(QPoint point);
    void deletePieceAt();
    void changeTextPieceAt();
};

#endif // PUZZLEWIDGET_H
