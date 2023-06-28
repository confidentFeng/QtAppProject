/********************************************************************************
** Form generated from reading UI file 'showmap.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWMAP_H
#define UI_SHOWMAP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShowMap
{
public:
    QLabel *currentMapLabel;
    QPushButton *cancelButton;
    QPushButton *resetBoardButton;
    QPushButton *addBoardButton;
    QPushButton *okButton;
    QPushButton *lessBoardButton;
    QLabel *mapIndexLabel;
    QGroupBox *cruiseGroupBox;
    QPushButton *addItemButton;
    QPushButton *lessItemButton;
    QListWidget *listWidget;
    QPushButton *cruiseGroupBox_returnBtn;
    QLabel *cruiseLabel;
    QGroupBox *groupBox;
    QPushButton *autoButton;
    QPushButton *manualButton;

    void setupUi(QWidget *ShowMap)
    {
        if (ShowMap->objectName().isEmpty())
            ShowMap->setObjectName(QStringLiteral("ShowMap"));
        ShowMap->resize(1024, 768);
        currentMapLabel = new QLabel(ShowMap);
        currentMapLabel->setObjectName(QStringLiteral("currentMapLabel"));
        currentMapLabel->setGeometry(QRect(0, 110, 141, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("A\346\200\235\346\272\220\351\273\221\344\275\223\342\200\22405"));
        font.setPointSize(22);
        currentMapLabel->setFont(font);
        cancelButton = new QPushButton(ShowMap);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setGeometry(QRect(540, 658, 200, 60));
        QFont font1;
        font1.setFamily(QString::fromUtf8("A\346\200\235\346\272\220\351\273\221\344\275\223\342\200\22404"));
        font1.setPointSize(20);
        cancelButton->setFont(font1);
        cancelButton->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/new/prefix1/image/cancel.png)}\n"
"QPushButton:hover{border-image: url(:/new/prefix1/image/cancel.png)}\n"
"QPushButton:pressed{border-image: url(:/new/prefix1/image/cancel1.png)}"));
        resetBoardButton = new QPushButton(ShowMap);
        resetBoardButton->setObjectName(QStringLiteral("resetBoardButton"));
        resetBoardButton->setGeometry(QRect(914, 344, 70, 90));
        resetBoardButton->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/new/prefix1/image/reset.png)}\n"
"QPushButton:hover{border-image: url(:/new/prefix1/image/reset.png)}\n"
"QPushButton:pressed{border-image: url(:/new/prefix1/image/reset1.png)}"));
        addBoardButton = new QPushButton(ShowMap);
        addBoardButton->setObjectName(QStringLiteral("addBoardButton"));
        addBoardButton->setGeometry(QRect(914, 166, 70, 91));
        addBoardButton->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/new/prefix1/image/add.png)}\n"
"QPushButton:hover{border-image: url(:/new/prefix1/image/add.png)}\n"
"QPushButton:pressed{border-image: url(:/new/prefix1/image/add1.png)}"));
        okButton = new QPushButton(ShowMap);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setGeometry(QRect(250, 658, 200, 60));
        okButton->setFont(font1);
        okButton->setAutoFillBackground(false);
        okButton->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/new/prefix1/image/ok.png)}\n"
"QPushButton:hover{border-image: url(:/new/prefix1/image/ok.png)}\n"
"QPushButton:pressed{border-image: url(:/new/prefix1/image/ok1.png)}"));
        lessBoardButton = new QPushButton(ShowMap);
        lessBoardButton->setObjectName(QStringLiteral("lessBoardButton"));
        lessBoardButton->setGeometry(QRect(914, 255, 70, 91));
        lessBoardButton->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/new/prefix1/image/less.png)}\n"
"QPushButton:hover{border-image: url(:/new/prefix1/image/less.png)}\n"
"QPushButton:pressed{border-image: url(:/new/prefix1/image/less1.png)}"));
        mapIndexLabel = new QLabel(ShowMap);
        mapIndexLabel->setObjectName(QStringLiteral("mapIndexLabel"));
        mapIndexLabel->setGeometry(QRect(140, 110, 141, 41));
        mapIndexLabel->setFont(font);
        cruiseGroupBox = new QGroupBox(ShowMap);
        cruiseGroupBox->setObjectName(QStringLiteral("cruiseGroupBox"));
        cruiseGroupBox->setGeometry(QRect(485, 174, 296, 386));
        cruiseGroupBox->setStyleSheet(QLatin1String("#cruiseGroupBox\n"
"{\n"
"	border-image: url(:/new/prefix1/image/group4.png);\n"
"}"));
        addItemButton = new QPushButton(cruiseGroupBox);
        addItemButton->setObjectName(QStringLiteral("addItemButton"));
        addItemButton->setGeometry(QRect(30, 325, 75, 31));
        QFont font2;
        font2.setFamily(QString::fromUtf8("A\346\200\235\346\272\220\351\273\221\344\275\223\342\200\22404"));
        font2.setPointSize(16);
        addItemButton->setFont(font2);
        addItemButton->setStyleSheet(QStringLiteral("background-color:transparent;"));
        addItemButton->setFlat(true);
        lessItemButton = new QPushButton(cruiseGroupBox);
        lessItemButton->setObjectName(QStringLiteral("lessItemButton"));
        lessItemButton->setGeometry(QRect(170, 325, 75, 31));
        lessItemButton->setFont(font2);
        lessItemButton->setStyleSheet(QStringLiteral("background-color:transparent;"));
        lessItemButton->setFlat(true);
        listWidget = new QListWidget(cruiseGroupBox);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(12, 80, 258, 231));
        QFont font3;
        font3.setFamily(QString::fromUtf8("A\346\200\235\346\272\220\351\273\221\344\275\223\342\200\22405"));
        font3.setPointSize(20);
        listWidget->setFont(font3);
        listWidget->setFrameShape(QFrame::NoFrame);
        listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget->setAlternatingRowColors(true);
        cruiseGroupBox_returnBtn = new QPushButton(cruiseGroupBox);
        cruiseGroupBox_returnBtn->setObjectName(QStringLiteral("cruiseGroupBox_returnBtn"));
        cruiseGroupBox_returnBtn->setGeometry(QRect(20, 30, 18, 29));
        cruiseGroupBox_returnBtn->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/image//return.png);"));
        cruiseLabel = new QLabel(cruiseGroupBox);
        cruiseLabel->setObjectName(QStringLiteral("cruiseLabel"));
        cruiseLabel->setGeometry(QRect(100, 30, 81, 41));
        cruiseLabel->setFont(font3);
        groupBox = new QGroupBox(ShowMap);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(40, 190, 161, 304));
        groupBox->setStyleSheet(QLatin1String("#groupBox\n"
"{\n"
"	border-image: url(:/new/prefix1/image/group.png);\n"
"}"));
        autoButton = new QPushButton(groupBox);
        autoButton->setObjectName(QStringLiteral("autoButton"));
        autoButton->setGeometry(QRect(9, 10, 141, 134));
        autoButton->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/new/prefix1/image/aout.png)}\n"
"QPushButton:hover{border-image: url(:/new/prefix1/image/aout.png)}\n"
"QPushButton:pressed{border-image: url(:/new/prefix1/image/aout1.png)}"));
        manualButton = new QPushButton(groupBox);
        manualButton->setObjectName(QStringLiteral("manualButton"));
        manualButton->setGeometry(QRect(9, 140, 141, 141));
        manualButton->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/new/prefix1/image/manual.png)}\n"
"QPushButton:hover{border-image: url(:/new/prefix1/image/manual.png)}\n"
"QPushButton:pressed{border-image: url(:/new/prefix1/image/manual1.png)}"));

        retranslateUi(ShowMap);

        QMetaObject::connectSlotsByName(ShowMap);
    } // setupUi

    void retranslateUi(QWidget *ShowMap)
    {
        ShowMap->setWindowTitle(QApplication::translate("ShowMap", "ShowMap", Q_NULLPTR));
        currentMapLabel->setText(QApplication::translate("ShowMap", "\345\275\223\345\211\215\345\234\260\345\233\276\357\274\232", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("ShowMap", "\345\217\226\346\266\210", Q_NULLPTR));
        resetBoardButton->setText(QString());
        addBoardButton->setText(QString());
        okButton->setText(QApplication::translate("ShowMap", "\347\241\256\345\256\232", Q_NULLPTR));
        lessBoardButton->setText(QString());
        mapIndexLabel->setText(QApplication::translate("ShowMap", "332", Q_NULLPTR));
        cruiseGroupBox->setTitle(QString());
        addItemButton->setText(QApplication::translate("ShowMap", "\346\267\273\345\212\240\347\202\271", Q_NULLPTR));
        lessItemButton->setText(QApplication::translate("ShowMap", "\345\210\240\351\231\244\347\202\271", Q_NULLPTR));
        cruiseGroupBox_returnBtn->setText(QString());
        cruiseLabel->setText(QApplication::translate("ShowMap", "\345\267\241\350\210\252\347\202\271", Q_NULLPTR));
        groupBox->setTitle(QString());
        autoButton->setText(QString());
        manualButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ShowMap: public Ui_ShowMap {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWMAP_H
