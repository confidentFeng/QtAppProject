/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QTextEdit *recvTextEdit;
    QPushButton *sendButton;
    QTextEdit *sendTextEdit;
    QWidget *widget;
    QGridLayout *gridLayout;
    QComboBox *portComboBox;
    QComboBox *baudComboBox;
    QPushButton *openPortButton;
    QPushButton *clearTextButton;
    QPushButton *clearSendButton;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(400, 271);
        recvTextEdit = new QTextEdit(Widget);
        recvTextEdit->setObjectName(QString::fromUtf8("recvTextEdit"));
        recvTextEdit->setGeometry(QRect(10, 10, 290, 150));
        sendButton = new QPushButton(Widget);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setGeometry(QRect(310, 200, 75, 23));
        sendTextEdit = new QTextEdit(Widget);
        sendTextEdit->setObjectName(QString::fromUtf8("sendTextEdit"));
        sendTextEdit->setGeometry(QRect(10, 180, 291, 71));
        widget = new QWidget(Widget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(310, 10, 77, 135));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        portComboBox = new QComboBox(widget);
        portComboBox->setObjectName(QString::fromUtf8("portComboBox"));

        gridLayout->addWidget(portComboBox, 0, 0, 1, 1);

        baudComboBox = new QComboBox(widget);
        baudComboBox->addItem(QString());
        baudComboBox->addItem(QString());
        baudComboBox->addItem(QString());
        baudComboBox->addItem(QString());
        baudComboBox->addItem(QString());
        baudComboBox->addItem(QString());
        baudComboBox->addItem(QString());
        baudComboBox->addItem(QString());
        baudComboBox->setObjectName(QString::fromUtf8("baudComboBox"));

        gridLayout->addWidget(baudComboBox, 1, 0, 1, 1);

        openPortButton = new QPushButton(widget);
        openPortButton->setObjectName(QString::fromUtf8("openPortButton"));

        gridLayout->addWidget(openPortButton, 2, 0, 1, 1);

        clearTextButton = new QPushButton(widget);
        clearTextButton->setObjectName(QString::fromUtf8("clearTextButton"));

        gridLayout->addWidget(clearTextButton, 3, 0, 1, 1);

        clearSendButton = new QPushButton(widget);
        clearSendButton->setObjectName(QString::fromUtf8("clearSendButton"));

        gridLayout->addWidget(clearSendButton, 4, 0, 1, 1);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        sendButton->setText(QApplication::translate("Widget", "\345\217\221\351\200\201\346\225\260\346\215\256", nullptr));
        baudComboBox->setItemText(0, QApplication::translate("Widget", "4800", nullptr));
        baudComboBox->setItemText(1, QApplication::translate("Widget", "9600", nullptr));
        baudComboBox->setItemText(2, QApplication::translate("Widget", "19200", nullptr));
        baudComboBox->setItemText(3, QApplication::translate("Widget", "38400", nullptr));
        baudComboBox->setItemText(4, QApplication::translate("Widget", "57600", nullptr));
        baudComboBox->setItemText(5, QApplication::translate("Widget", "115200", nullptr));
        baudComboBox->setItemText(6, QApplication::translate("Widget", "128000", nullptr));
        baudComboBox->setItemText(7, QApplication::translate("Widget", "256000", nullptr));

        openPortButton->setText(QApplication::translate("Widget", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        clearTextButton->setText(QApplication::translate("Widget", "\346\270\205\351\231\244\346\226\207\346\234\254\346\241\206", nullptr));
        clearSendButton->setText(QApplication::translate("Widget", "\346\270\205\351\231\244\345\217\221\351\200\201\346\241\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
