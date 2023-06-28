/*** 如果运行异常退出，是因为没在输出目录拷贝动态链接库(libmpv.dll.a和mpv-1.dll) ***/
#ifndef MPVPLAYER_H
#define MPVPLAYER_H

#include <QWidget>
#include <QObject>
#include <QDebug>
#include <client.h> // MPV库头文件

class MpvPlayer : public QWidget
{
    Q_OBJECT

public:
    MpvPlayer(QWidget *parent);
    virtual ~MpvPlayer();

    void create_mvpPlayer(QWidget *videoWin); // 创建mvpPlayer
    void setProperty(const QString &name, const QString &value); // 设置mpv属性
    QString getProperty(const QString &name) const; // 获得mpv属性
    void play(QString filename); // 播放视频

private slots:
    void on_mpv_events(); // 这个槽函数由 wakeup()调用（通过mpv_events信号）

signals:
    void mpv_events(); // 触发on_mpv_events()槽函数的信号
    void mpv_palyEnd(); // 播放结束的信号

private:
    mpv_handle *mpv;

    void handle_mpv_event(mpv_event *event); // 处理mpv事件
};

#endif // MPVPLAYER_H
