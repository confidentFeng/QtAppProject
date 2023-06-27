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
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *manageAction;
    QAction *chartAction;
    QAction *quitAction;
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *managePage;
    QLabel *label;
    QToolBox *toolBox;
    QWidget *page_4;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QComboBox *sellFactoryComboBox;
    QComboBox *sellBrandComboBox;
    QLineEdit *sellPriceLineEdit;
    QSpinBox *sellNumSpinBox;
    QLabel *label_7;
    QLabel *sellLastNumLabel;
    QLabel *label_9;
    QLineEdit *sellSumLineEdit;
    QPushButton *sellOkBtn;
    QPushButton *sellCancelBtn;
    QWidget *page_5;
    QListWidget *dailyList;
    QWidget *page_2;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(750, 500);
        manageAction = new QAction(MainWindow);
        manageAction->setObjectName(QString::fromUtf8("manageAction"));
        chartAction = new QAction(MainWindow);
        chartAction->setObjectName(QString::fromUtf8("chartAction"));
        quitAction = new QAction(MainWindow);
        quitAction->setObjectName(QString::fromUtf8("quitAction"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(10, 20, 700, 410));
        managePage = new QWidget();
        managePage->setObjectName(QString::fromUtf8("managePage"));
        label = new QLabel(managePage);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 10, 641, 31));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label->setFrameShape(QFrame::StyledPanel);
        label->setAlignment(Qt::AlignCenter);
        toolBox = new QToolBox(managePage);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        toolBox->setGeometry(QRect(30, 50, 301, 321));
        toolBox->setFrameShape(QFrame::StyledPanel);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        page_4->setGeometry(QRect(0, 0, 299, 267));
        label_2 = new QLabel(page_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 10, 41, 20));
        label_3 = new QLabel(page_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 50, 54, 20));
        label_4 = new QLabel(page_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 90, 31, 20));
        label_5 = new QLabel(page_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 130, 54, 12));
        label_6 = new QLabel(page_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 170, 31, 16));
        sellFactoryComboBox = new QComboBox(page_4);
        sellFactoryComboBox->setObjectName(QString::fromUtf8("sellFactoryComboBox"));
        sellFactoryComboBox->setGeometry(QRect(60, 10, 101, 22));
        sellBrandComboBox = new QComboBox(page_4);
        sellBrandComboBox->setObjectName(QString::fromUtf8("sellBrandComboBox"));
        sellBrandComboBox->setGeometry(QRect(60, 50, 101, 22));
        sellPriceLineEdit = new QLineEdit(page_4);
        sellPriceLineEdit->setObjectName(QString::fromUtf8("sellPriceLineEdit"));
        sellPriceLineEdit->setGeometry(QRect(60, 90, 113, 20));
        sellNumSpinBox = new QSpinBox(page_4);
        sellNumSpinBox->setObjectName(QString::fromUtf8("sellNumSpinBox"));
        sellNumSpinBox->setGeometry(QRect(60, 130, 42, 22));
        label_7 = new QLabel(page_4);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(180, 90, 21, 16));
        sellLastNumLabel = new QLabel(page_4);
        sellLastNumLabel->setObjectName(QString::fromUtf8("sellLastNumLabel"));
        sellLastNumLabel->setGeometry(QRect(110, 130, 81, 16));
        label_9 = new QLabel(page_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(180, 170, 21, 16));
        sellSumLineEdit = new QLineEdit(page_4);
        sellSumLineEdit->setObjectName(QString::fromUtf8("sellSumLineEdit"));
        sellSumLineEdit->setGeometry(QRect(60, 170, 111, 20));
        sellOkBtn = new QPushButton(page_4);
        sellOkBtn->setObjectName(QString::fromUtf8("sellOkBtn"));
        sellOkBtn->setGeometry(QRect(50, 220, 75, 23));
        sellCancelBtn = new QPushButton(page_4);
        sellCancelBtn->setObjectName(QString::fromUtf8("sellCancelBtn"));
        sellCancelBtn->setGeometry(QRect(170, 220, 75, 23));
        toolBox->addItem(page_4, QString::fromUtf8("\345\207\272\345\224\256\350\275\246\350\276\206"));
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        page_5->setGeometry(QRect(0, 0, 299, 267));
        toolBox->addItem(page_5, QString::fromUtf8("Page 2"));
        dailyList = new QListWidget(managePage);
        dailyList->setObjectName(QString::fromUtf8("dailyList"));
        dailyList->setGeometry(QRect(360, 51, 301, 321));
        stackedWidget->addWidget(managePage);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        stackedWidget->addWidget(page_2);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 750, 23));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menu->addAction(manageAction);
        menu->addAction(chartAction);
        menu->addSeparator();
        menu->addAction(quitAction);

        retranslateUi(MainWindow);

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\346\261\275\350\275\246\351\224\200\345\224\256\347\256\241\347\220\206\347\263\273\347\273\237", nullptr));
        manageAction->setText(QApplication::translate("MainWindow", "\345\223\201\347\211\214\350\275\246\347\256\241\347\220\206", nullptr));
#ifndef QT_NO_SHORTCUT
        manageAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+M", nullptr));
#endif // QT_NO_SHORTCUT
        chartAction->setText(QApplication::translate("MainWindow", "\351\224\200\345\224\256\347\273\237\350\256\241", nullptr));
#ifndef QT_NO_SHORTCUT
        chartAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", nullptr));
#endif // QT_NO_SHORTCUT
        quitAction->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
#ifndef QT_NO_SHORTCUT
        quitAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_NO_SHORTCUT
        label->setText(QApplication::translate("MainWindow", "\345\223\201\347\211\214\350\275\246\347\256\241\347\220\206", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\345\216\202\345\256\266\357\274\232", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\345\223\201\347\211\214\357\274\232", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "\346\212\245\344\273\267\357\274\232", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "\346\225\260\351\207\217\357\274\232", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "\351\207\221\351\242\235\357\274\232", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "\344\270\207", nullptr));
        sellLastNumLabel->setText(QApplication::translate("MainWindow", "\345\211\251\344\275\231\346\225\260\351\207\217\357\274\2320", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "\344\270\207", nullptr));
        sellOkBtn->setText(QApplication::translate("MainWindow", "\347\241\256\345\256\232", nullptr));
        sellCancelBtn->setText(QApplication::translate("MainWindow", "\345\217\226\346\266\210", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_4), QApplication::translate("MainWindow", "\345\207\272\345\224\256\350\275\246\350\276\206", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_5), QApplication::translate("MainWindow", "Page 2", nullptr));
        menu->setTitle(QApplication::translate("MainWindow", "\351\224\200\345\224\256\347\256\241\347\220\206", nullptr));
        menu_2->setTitle(QApplication::translate("MainWindow", "\344\277\256\346\224\271\345\257\206\347\240\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
