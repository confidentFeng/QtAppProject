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
#include <QDebug>

#include <clocale>
#include <sstream>
#include <stdexcept>
#include "qtexample.h"

// 唤醒函数
static void wakeup(void *ctx)
{
    // 此回调可从任何mpv线程调用（但也可以从调用mpv API的线程递归地返回）
    // 只是需要通知要唤醒的Qt GUI线程（以便它可以使用mpv_wait_event（）），并尽快返回
    MainWindow *mainwindow = (MainWindow *)ctx;
    emit mainwindow->mpv_events();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // 设置主窗口标题名称和最小尺寸
    setWindowTitle("Qt embedding demo");
    setMinimumSize(640, 480);

    // 添加菜单栏
    QMenu *menu = menuBar()->addMenu(tr("&File"));
    QAction *on_open = new QAction(tr("&Open"), this);
    on_open->setShortcuts(QKeySequence::Open);
    on_open->setStatusTip(tr("Open a file"));
    connect(on_open, &QAction::triggered, this, &MainWindow::on_file_open);
    menu->addAction(on_open);
    // 添加菜单栏Action
    QAction *on_new = new QAction(tr("&New window"), this);
    connect(on_new, &QAction::triggered, this, &MainWindow::on_new_window);
    menu->addAction(on_new);
    // 返回主窗口的状态栏（不存在则创建一个空的状态栏）
    statusBar();

    // 同时创建log窗口
    QMainWindow *log_window = new QMainWindow(this);
    log = new QTextEdit(log_window);
    log->setReadOnly(true);
    log_window->setCentralWidget(log);
    log_window->setWindowTitle("mpv log window");
    log_window->setMinimumSize(500, 50);
    log_window->show();

    // 创建mvpPlayer
    create_mvpPlayer();
}

// 处理mpv事件
void MainWindow::handle_mpv_event(mpv_event *event)
{
    switch (event->event_id)
    {
        case MPV_EVENT_PROPERTY_CHANGE:
        {
            mpv_event_property *prop = (mpv_event_property *)event->data;

            // 状态栏显示播放时间
            if (strcmp(prop->name, "time-pos") == 0)
            {

                if (prop->format == MPV_FORMAT_DOUBLE)
                {
                    double time = *(double *)prop->data;
                    std::stringstream ss;
                    ss << "At: " << time;
                    statusBar()->showMessage(QString::fromStdString(ss.str()));
                }
                else if (prop->format == MPV_FORMAT_NONE)
                {
                    //该属性不可用，可能意味着播放已停止
                    statusBar()->showMessage("");
                }
            }
            else if (strcmp(prop->name, "chapter-list") == 0 ||
                       strcmp(prop->name, "track-list") == 0)
            {
                // 出于演示目的，将属性作为JSON转储
                if (prop->format == MPV_FORMAT_NODE)
                {
                    QVariant v = mpv::qt::node_to_variant((mpv_node *)prop->data);
                    // 使用JSON支持，可轻松打印mpv_node内容。
                    QJsonDocument d = QJsonDocument::fromVariant(v);
                    append_log("Change property " + QString(prop->name) + ":\n");
                    append_log(d.toJson().data());
                }
            }
            break;
        }
        case MPV_EVENT_VIDEO_RECONFIG:
        {
            // 检索新的视频大小
            int64_t w, h;
            if (mpv_get_property(mpv, "dwidth", MPV_FORMAT_INT64, &w) >= 0 &&
                mpv_get_property(mpv, "dheight", MPV_FORMAT_INT64, &h) >= 0 &&
                w > 0 && h > 0)
            {
                // 请注意，MPV_EVENT_VIDEO_RECONFIG事件不一定表示要调整大小，如果尺寸确实发生了变化，
                // 您应该检查一下视频。如果视频不合适，mpv本身会将视频缩放，放大到container大小
                std::stringstream ss;
                ss << "Reconfig: " << w << " " << h;
                statusBar()->showMessage(QString::fromStdString(ss.str()));
            }
            break;
        }
        case MPV_EVENT_LOG_MESSAGE:
        {
            struct mpv_event_log_message *msg = (struct mpv_event_log_message *)event->data;
            std::stringstream ss;
            ss << "[" << msg->prefix << "] " << msg->level << ": " << msg->text;
            append_log(QString::fromStdString(ss.str()));
            break;
        }
        case MPV_EVENT_SHUTDOWN:
        {
            mpv_terminate_destroy(mpv);
            mpv = NULL;
            break;
        }
        default: ;
    }
}

// 这个槽函数由 wakeup()调用（通过mpv_events信号）
void MainWindow::on_mpv_events()
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

// 打开文件
void MainWindow::on_file_open()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open file");
    if (mpv)
    {
        const QByteArray c_filename = filename.toUtf8();
        const char *args[] = {"loadfile", c_filename.data(), NULL};
        // 与mpv_command相同，但异步运行命令（调用mpv渲染API线程）
        mpv_command_async(mpv, 0, args);
    }
}

// 新建窗口
void MainWindow::on_new_window()
{
    // 新建个MainWindow实例
    (new MainWindow())->show();
}

// 附加log
void MainWindow::append_log(const QString &text)
{
    QTextCursor cursor = log->textCursor();
    cursor.movePosition(QTextCursor::End);
    cursor.insertText(text);
    log->setTextCursor(cursor);
}

// --stream-record   https://mpv.io/manual/master/
// 创建mvpPlayer
void MainWindow::create_mvpPlayer()
{
    // 创建mpv实例
    mpv = mpv_create();
    if (!mpv)
        throw std::runtime_error("can't create mpv instance");

    // 创建一个视频子窗口(mpv_container)来播放视频
    mpv_container = new QWidget(this);
    setCentralWidget(mpv_container);
    mpv_container->setAttribute(Qt::WA_DontCreateNativeAncestors);
    mpv_container->setAttribute(Qt::WA_NativeWindow);
    // 然后将窗口ID传递给mpv wid选项
    int64_t wid = mpv_container->winId();
    mpv_set_option(mpv, "wid", MPV_FORMAT_INT64, &wid);

    // 启用默认绑定，因为我们很懒。 通常，播放者使用mpv作为后端将实现其自己的键绑定
    mpv_set_option_string(mpv, "input-default-bindings", "yes");

    // 启用键盘输入在X11 Window上。
    mpv_set_option_string(mpv, "input-vo-keyboard", "yes");

    // 让我们通过MPV_EVENT_PROPERTY_CHANGE接收属性更改事件，如果这属性更改了
    mpv_observe_property(mpv, 0, "time-pos", MPV_FORMAT_DOUBLE);

    mpv_observe_property(mpv, 0, "track-list", MPV_FORMAT_NODE);
    mpv_observe_property(mpv, 0, "chapter-list", MPV_FORMAT_NODE);

    // 请求级别为"info"或更高级别的日志消息。它们以MPV_EVENT_LOG_MESSAGE的形式接收
    mpv_request_log_messages(mpv, "info");

    // 从这里开始，将调用唤醒功能。 回调可以来自任何线程，因此我们使用QueuedConnection机制以线程安全的方式中继唤醒
    connect(this, &MainWindow::mpv_events, this, &MainWindow::on_mpv_events,
            Qt::QueuedConnection);
    mpv_set_wakeup_callback(mpv, wakeup, this);

    // 判断mpv实例是否成功初始化
    if (mpv_initialize(mpv) < 0)
        throw std::runtime_error("mpv failed to initialize");
}

MainWindow::~MainWindow()
{
    if (mpv)
        mpv_terminate_destroy(mpv);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Qt在QApplication构造函数中设置了locale，但是libmpv需要将LC_NUMERIC类别设置为“ C”，因此将其改回。
    std::setlocale(LC_NUMERIC, "C");

    MainWindow w;
    w.show();

    return a.exec();
}
