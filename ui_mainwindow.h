/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "pieceslist.h"
#include "puzzlewidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionClose;
    QAction *actionUndo;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    PiecesList *piecesList;
    PuzzleWidget *dropArea;
    QVBoxLayout *verticalLayout_3;
    QPushButton *generateButton;
    QLabel *commandArea;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuFile;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(868, 559);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QStringLiteral("actionUndo"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        piecesList = new PiecesList(centralWidget);
        piecesList->setObjectName(QStringLiteral("piecesList"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(piecesList->sizePolicy().hasHeightForWidth());
        piecesList->setSizePolicy(sizePolicy);
        piecesList->setMinimumSize(QSize(150, 0));
        piecesList->setMaximumSize(QSize(150, 16777215));
        piecesList->viewport()->setProperty("cursor", QVariant(QCursor(Qt::OpenHandCursor)));
        piecesList->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        piecesList->setResizeMode(QListView::Adjust);
        piecesList->setViewMode(QListView::IconMode);

        horizontalLayout->addWidget(piecesList);

        dropArea = new PuzzleWidget(centralWidget);
        dropArea->setObjectName(QStringLiteral("dropArea"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dropArea->sizePolicy().hasHeightForWidth());
        dropArea->setSizePolicy(sizePolicy1);
        dropArea->setMinimumSize(QSize(600, 400));
        dropArea->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        verticalLayout_3 = new QVBoxLayout(dropArea);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        generateButton = new QPushButton(dropArea);
        generateButton->setObjectName(QStringLiteral("generateButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(generateButton->sizePolicy().hasHeightForWidth());
        generateButton->setSizePolicy(sizePolicy2);
        generateButton->setMinimumSize(QSize(120, 40));
        generateButton->setMaximumSize(QSize(100, 40));
        generateButton->setAutoFillBackground(false);
        generateButton->setIconSize(QSize(120, 40));
        generateButton->setAutoRepeat(true);
        generateButton->setAutoDefault(false);
        generateButton->setDefault(true);

        verticalLayout_3->addWidget(generateButton, 0, Qt::AlignRight|Qt::AlignBottom);


        horizontalLayout->addWidget(dropArea);


        verticalLayout->addLayout(horizontalLayout);

        commandArea = new QLabel(centralWidget);
        commandArea->setObjectName(QStringLiteral("commandArea"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(commandArea->sizePolicy().hasHeightForWidth());
        commandArea->setSizePolicy(sizePolicy3);
        commandArea->setMinimumSize(QSize(0, 80));
        commandArea->setCursor(QCursor(Qt::IBeamCursor));
        commandArea->setAutoFillBackground(false);
        commandArea->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 255);\n"
"font: 10pt \"MS Shell Dlg 2\";"));
        commandArea->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        commandArea->setMargin(10);
        commandArea->setIndent(18);
        commandArea->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        verticalLayout->addWidget(commandArea);


        verticalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 868, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionClose);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionNew->setText(QApplication::translate("MainWindow", "&New puzzle", 0));
        actionNew->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0));
        actionClose->setText(QApplication::translate("MainWindow", "&Close", 0));
        actionUndo->setText(QApplication::translate("MainWindow", "&Undo", 0));
        generateButton->setText(QApplication::translate("MainWindow", "Generate Command", 0));
        commandArea->setText(QApplication::translate("MainWindow", ">$", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
