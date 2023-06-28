#include "mpvplayer.h"

// 唤醒函数
static void wakeup(void *ctx)
{
    // 此回调可从任何mpv线程调用（但也可以从调用mpv API的线程递归地返回）
    // 只是需要通知要唤醒的Qt GUI线程（以便它可以使用mpv_wait_event（）），并尽快返回
    MpvPlayer *mvpPlayer = (MpvPlayer *)ctx;
    emit mvpPlayer->mpv_events();
}

MpvPlayer::MpvPlayer(QWidget *parent) :
    QWidget(parent)
{
    // 创建mvpPlayer
    create_mvpPlayer(parent);
}

MpvPlayer::~MpvPlayer()
{
    if (mpv)
        mpv_terminate_destroy(mpv);
}

// 创建mvpPlayer
void MpvPlayer::create_mvpPlayer(QWidget *videoWin)
{
    // 创建mpv实例
    mpv = mpv_create();
    if (!mpv)
        throw std::runtime_error("can't create mpv instance");

    // 将视频子窗口的窗口ID传递给mpv wid选项
    int64_t wid = videoWin->winId();
    mpv_set_option(mpv, "wid", MPV_FORMAT_INT64, &wid);

    // 让我们通过MPV_EVENT_PROPERTY_CHANGE接收属性更改事件，如果这属性更改了
    mpv_observe_property(mpv, 0, "time-pos", MPV_FORMAT_DOUBLE);

    // 从这里开始，将调用唤醒功能。 回调可以来自任何线程，因此我们使用QueuedConnection机制以线程安全的方式中继唤醒
    connect(this, &MpvPlayer::mpv_events, this, &MpvPlayer::on_mpv_events,
            Qt::QueuedConnection);
    mpv_set_wakeup_callback(mpv, wakeup, this);

    // 判断mpv实例是否成功初始化
    if (mpv_initialize(mpv) < 0)
        throw std::runtime_error("mpv failed to initialize");
}

// 设置mpv属性
void MpvPlayer::setProperty(const QString &name, const QString &value)
{
    mpv_set_option_string(mpv, name.toLatin1().data(), value.toLatin1().data());
}

// 获得mpv属性
QString MpvPlayer::getProperty(const QString &name) const
{
    return (QString)mpv_get_property_string(mpv, name.toLatin1().data());
}

// 播放视频
void MpvPlayer::play(QString filename)
{
    if (mpv)
    {
        const QByteArray c_filename = filename.toUtf8();
        const char *args[] = {"loadfile", c_filename.data(), NULL};
        // 与mpv_command相同，但异步运行命令来避免阻塞，直到进程终止
        mpv_command_async(mpv, 0, args);
    }
}

// 这个槽函数由 wakeup()调用（通过mpv_events信号）
void MpvPlayer::on_mpv_events()
{
    // 处理所有事件，直到事件队列为空
    while (mpv)
    {
        mpv_event *event = mpv_wait_event(mpv, 0);
        if (event->event_id == MPV_EVENT_NONE)
            break;
        handle_mpv_event(event);
    }
}

// 处理mpv事件
void MpvPlayer::handle_mpv_event(mpv_event *event)
{
    switch (event->event_id)
    {
        // 属性改变事件发生
        case MPV_EVENT_PROPERTY_CHANGE:
        {
            mpv_event_property *prop = (mpv_event_property *)event->data;

            if (strcmp(prop->name, "time-pos") == 0)
            {
                if (prop->format == MPV_FORMAT_DOUBLE)
                {
                    // 获得播放时间
                    //double time = *(double *)prop->data;
                    //qDebug() << "播放时间: " << QString::number(time, 10, 2);
                }
                else if (prop->format == MPV_FORMAT_NONE)
                {
                    // 该属性不可用，可能意味着播放已停止
                    emit mpv_palyEnd();
                    qDebug() << "播放结束";
                }
            }
        }
        break;

        // palyer退出事件发生
        case MPV_EVENT_SHUTDOWN:
        {
            mpv_terminate_destroy(mpv);
            mpv = NULL;
        }
        break;

        default: ;
    }
}
