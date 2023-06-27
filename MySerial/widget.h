/*
* Copyright (c) 2019,fengMisaka
* All rights reserved.
*
* 摘 要：串口调试助手界面类，实现串口调试助手基本功能
*
* 当前版本：1.0
* 作 者：fengMisaka
* 完成日期：2019 年 8 月 22 日
*/
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include "serial.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_openPortButton_clicked(); // 打开串口按钮-点击槽函数
    void on_clearTextButton_clicked(); // 清除接收文本框按钮-点击槽函数
    void on_clearSendButton_clicked(); // 清除发送文本框按钮-点击槽函数
    void on_sendButton_clicked(); // 发送数据按钮-点击槽函数
    void readSerialData(); // 读取从自定义串口类获得的数据

private:
    Ui::Widget *ui;

    Serial *m_serial; // 自定义串口类对象指针
};

#endif // WIDGET_H
