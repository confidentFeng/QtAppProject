#ifndef APPINIT_H
#define APPINIT_H

#include <QObject>
#include <QApplication>
#include <QFile>
#include <QWidget>
#include <QMouseEvent>
#include <QMutex>
#include "src/Util/AppConfig.h"

// 全局程序初始化类 AppInit：用来做一些程序启动后的初始化处理 （单例模式，线程安全）
class AppInit : public QObject
{
    Q_OBJECT
public:
    static AppInit *Instance();
    void start();

protected:
    bool eventFilter(QObject *obj, QEvent *evt);

private:
    explicit AppInit(QObject *parent = 0);

    static AppInit *m_appInit;
};

#endif // APPINIT_H
