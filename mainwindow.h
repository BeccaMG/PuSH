#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "puzzlepiece.h"

class PuzzlePiece;
QT_BEGIN_NAMESPACE
class QListWidgetItem;
QT_END_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addPiece(PuzzlePiece *pieceItem, QPoint location);
    void add_piece_to_puzzle(PuzzlePiece *basePiece);
    static int const EXIT_CODE_REBOOT = -123456789;

private slots:
    void on_generateButton_clicked();
    void on_actionNew_triggered();
    void on_actionClose_triggered();

private:
    Ui::MainWindow *ui;    
};

#endif // MAINWINDOW_H
