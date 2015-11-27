#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtWidgets>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(tr("PUSH - PUzzle SHell"));

    PuzzlePiece *newPiece = new PuzzlePiece();
    newPiece->processPiece();
    addPiece(newPiece, QPoint(0, 0));

    newPiece = new PuzzlePiece();
    newPiece->pipePiece();
    addPiece(newPiece, QPoint(1, 1));

    newPiece = new PuzzlePiece();
    newPiece->inputFilePiece();
    addPiece(newPiece, QPoint(0, 0));

    newPiece = new PuzzlePiece();
    newPiece->outputFilePiece();
    addPiece(newPiece, QPoint(0, 0));

    newPiece = new PuzzlePiece();
    newPiece->errorFilePiece();
    addPiece(newPiece, QPoint(0, 0));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addPiece(PuzzlePiece *pieceItem, QPoint location)
{
    const QPixmap *g_Piece = pieceItem->g_Piece->pixmap();
    pieceItem->setIcon(QIcon(*g_Piece));
    pieceItem->setData(Qt::UserRole, QVariant(*g_Piece));
    pieceItem->setData(Qt::UserRole+1, location);
    pieceItem->setData(Qt::UserRole+2, pieceItem->pieceText);
    pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled);
    ui->piecesList->addItem(pieceItem);
}

void MainWindow::on_generateButton_clicked()
{    
    ui->commandArea->setText(ui->dropArea->generateCommand());
}

void MainWindow::on_actionNew_triggered()
{
    qApp->exit(MainWindow::EXIT_CODE_REBOOT);
}

void MainWindow::on_actionClose_triggered()
{
    qApp->exit(0);
}
