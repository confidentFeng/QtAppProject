/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *playPushButton;
    QWidget *playerWidget;
    QPushButton *pausePushButton;
    QPushButton *recordPushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(400, 300);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        playPushButton = new QPushButton(centralWidget);
        playPushButton->setObjectName(QString::fromUtf8("playPushButton"));
        playPushButton->setGeometry(QRect(140, 210, 75, 23));
        playerWidget = new QWidget(centralWidget);
        playerWidget->setObjectName(QString::fromUtf8("playerWidget"));
        playerWidget->setGeometry(QRect(50, 20, 301, 171));
        pausePushButton = new QPushButton(centralWidget);
        pausePushButton->setObjectName(QString::fromUtf8("pausePushButton"));
        pausePushButton->setGeometry(QRect(230, 210, 75, 23));
        recordPushButton = new QPushButton(centralWidget);
        recordPushButton->setObjectName(QString::fromUtf8("recordPushButton"));
        recordPushButton->setGeometry(QRect(50, 210, 75, 23));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        playPushButton->setText(QApplication::translate("MainWindow", "\346\222\255\346\224\276", nullptr));
        pausePushButton->setText(QApplication::translate("MainWindow", "\346\232\202\345\201\234", nullptr));
        recordPushButton->setText(QApplication::translate("MainWindow", "\345\275\225\345\210\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
