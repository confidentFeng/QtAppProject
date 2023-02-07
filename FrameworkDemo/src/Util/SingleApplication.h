#ifndef GLOBALAPPLICATION_H
#define GLOBALAPPLICATION_H

#include <QApplication>
#include <QWidget>
#include <QLocalServer>
#include <QLocalSocket>
#include <QFileInfo>
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>
#include "src/Util/AppEvent.h"

#define TIME_OUT (500) // 500ms

// 实现单例程序，并实现全局事件过滤函数notify()
class SingleApplication : public QApplication
{
    Q_OBJECT

public:
    SingleApplication(int&argc,char **argv);
    ~SingleApplication();
    bool isRunning(); // 是否已經有实例在运行
    QWidget *w; // MainWindow指针
    bool notify(QObject*, QEvent *event); // 全局事件过滤函数

signals:
    void sigShowGet(); // 拖拽子界面显示的信号

private slots:
    void _newLocalConnection(); // 有新连接时触发

private:    
    void _initLocalConnection(); // 初始化本地连接
    void _newLocalServer(); // 创建服务端
    void _activateWindow(); // 激活窗口

    bool _isRunning; // 是否已經有实例在运行
    QLocalServer *_localServer; // 本地socket Server
    QString _serverName; // 服务名称
};

#endif //  GLOBALAPPLICATION_H
