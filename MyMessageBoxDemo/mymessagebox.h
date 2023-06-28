/*
* Copyright (c) 2019,浙江智澜科技有限公司
* All rights reserved.
*
* 摘 要：实现消息对话框
*
* 当前版本：1.0
* 作 者：聂咸丰
* 完成日期：2019 年 9 月 4 日
*/
#ifndef MYMESSAGEBOX_H
#define MYMESSAGEBOX_H

#include <QWidget>
#include <QFile>
#include <QCloseEvent>
#include <QDebug>
#include "mytitlebar.h"

enum ChosseResult
{
    ID_OK = 0,						// 确定;
    ID_CANCEL						// 取消;
};

enum MessageType
{
    MESSAGE_INFORMATION = 0,		// 提示信息;
    MESSAGE_WARNNING,				// 提示警告;
    MESSAGE_QUESTION,				// 提示询问;
    MESSAGE_INPUT					// 提示输入框;
};

enum MessageButtonType
{
    BUTTON_OK = 0,					// 只有确定按钮;
    BUTTON_OK_AND_CANCEL,			// 确定、取消按钮;
    BUTTON_CLOSE					// 关闭按钮;
};

namespace Ui {
class MyMessageBox;
}

class MyMessageBox : public QWidget
{
    Q_OBJECT

public:
    explicit MyMessageBox(QWidget *parent = nullptr);
    ~MyMessageBox();

    // 自定义显示函数
    int showMyMessageBox(QWidget* parent, const QString &title,const QString &contentText , MessageType \
                                messageType, MessageButtonType messageButtonType , bool isModelWindow = false);

private slots:
    // 确定按钮-点击信号槽
    void on_okButton_clicked();
    // 取消按钮-点击槽函数
    void on_cancelButton_clicked();

private:
    Ui::MyMessageBox *ui;

    // 初始化标题栏
    void initTitleBar();
    // 设置标题内容
    void setWindowTitle(QString title, int titleFontSize = 10);
    // 设置提示内容
    void setContentText(QString contentText);
    // 设置对话框类型
    void setMessageType(MessageType messageType);
    // 设置按钮类型
    void setButtonType(MessageButtonType buttonType);
    // 加载本地样式文件：可以将样式直接写在文件中，程序运行时直接加载进来
    void loadStyleSheet(const QString &sheetName);
    // 关闭事件：在exec()方法中返回选择结果
    void closeEvent(QCloseEvent *event);
    // 因为QWidget没有exec()方法，所以需要自己定义来完成exec()方法
    int exec();

    MyTitleBar* m_titleBar; // 自定义标题栏
    bool m_isModalFlag; // 是否为模态窗口的标志位
    QEventLoop* m_eventLoop; // 事件循环
    ChosseResult m_chooseResult; // 用户选择的结果
};

#endif // MYMESSAGEBOX_H
