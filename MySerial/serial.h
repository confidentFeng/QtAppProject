/*
* Copyright (c) 2019,fengMisaka
* All rights reserved.
*
* 摘 要：自定义串口类，与下位机通信，实现发送和接收串口数据
*
* 当前版本：1.0
* 作 者：fengMisaka
* 完成日期：2019 年 8 月 22 日
*/
#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QDebug>

class Serial:public QObject // 要继承QObject，才能使用 connect() 函数
{
    Q_OBJECT

public:
    Serial();
    QStringList scanSerial(); // 扫描可用串口
    bool open(QString serialName, int baudRate); // 打开串口
    void close(); // 关闭串口
    void sendData(QByteArray &sendData); // 发送数据给下位机
    QByteArray getReadBuf(); // 获得读取数据缓冲区
    void clearReadBuf(); // 清除读取数据缓冲区
    QByteArray hexStringToByteArray(QString HexString); // 将16进制字符串转换为对应的字节序列

signals:
    void readSignal(); // 当下位机中有数据发送过来时就会触发这个信号，以提示其它类对象

public slots:
    void readData(); // 读取下位机发来数据

private:
    QSerialPort *m_serialPort; // 实例化一个指向串口的指针，可以用于访问串口
    QByteArray m_readBuf; // 存储下位机发来数据的缓冲区
};

#endif // SERIAL_H
