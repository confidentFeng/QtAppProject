#ifndef QTEXAMPLE_H
#define QTEXAMPLE_H

// 如果运行异常退出，是因为没在输出目录拷贝动态链接库(libmpv.dll.a和mpv-1.dll)
#include <QMainWindow>
#include <QtGlobal>
#include <QFileDialog>
#include <QStatusBar>
#include <QMenuBar>
#include <QMenu>
#include <QGridLayout>
#include <QApplication>
#include <QTextEdit>

#include <clocale>
#include <sstream>
#include <stdexcept>

// MVP库头文件
#include <QJsonDocument>
#include <qthelper.hpp> // 该文件在最新的libmpv中已被弃用
#include <client.h>

class QTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_file_open(); // 打开文件
    void on_new_window(); // 新建窗口
    void on_mpv_events(); // 这个槽函数由 wakeup()调用（通过mpv_events信号）

signals:
    void mpv_events();

private:
    QWidget *mpv_container;
    mpv_handle *mpv;
    QTextEdit *log;

    void create_mvpPlayer(); // 创建mvpPlayer
    void handle_mpv_event(mpv_event *event); // 处理mpv事件

    void append_log(const QString &text); // 附加log
};

#endif // QTEXAMPLE_H
