#ifndef UTIL_H
#define UTIL_H

#include <QCoreApplication>
#include <QTime>
#include <QVariant>
#include <QFile>
#include <QMap>
#include <QApplication>
#include <QTimer>
#include <QProcess>
#include <QDebug>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

class AppCommon
{
public:
    static AppCommon& Get() {
        static AppCommon m_util;
        return m_util;
    }

    void sleep(unsigned long msec);
    void sleepEvent(unsigned long msec);

    void setMousePos(int x, int y); // 设置鼠标坐标

    uint16_t u8ToU16(uint8_t high, uint8_t low); // uint8转uint16
    QString u16ToU8(uint16_t &num); // uint16转uint8

    QString ExecuteCmd(const QString& strCmd); // 执行cmd命令

private:
    AppCommon();

    int optind;
    char *optarg;
    const char *opt_string = "vS:h?";
};

#endif // UTIL_H
