#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mpvPlayer = new MpvPlayer(ui->playerWidget);
    m_isPlay = false;
    m_isRecord = false;

    connect(mpvPlayer, &MpvPlayer::mpv_palyEnd, this, &MainWindow::paltEnd_slot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 判断是否在播放
bool MainWindow::isPlay()
{
    return m_isPlay;
}

// 判断是否在录制
bool MainWindow::isRecord()
{
    return m_isRecord;
}

// 播放/停止
void MainWindow::on_playPushButton_clicked()
{
    //QString videoName = "../mpvDemoModify/test.mp4";
    QString videoName = "rtsp://wowzaec2demo.streamlock.net/vod/mp4:BigBuckBunny_115k.mov";
    //QString videoName = "rtsp://172.10.1.198:8554/ch0";

    // 选择是否播放视频
    if (!isPlay())
    {
        m_isPlay = true;
        ui->playPushButton->setText("停止");

        mpvPlayer->play(videoName); // 播放视频
    }
    else
    {
        m_isPlay = false;
        ui->playPushButton->setText("播放");
        ui->pausePushButton->setText("暂停");

        mpvPlayer->setProperty("pause", "no");
        mpvPlayer->play(" "); // 播放空视频，代替停止播放
    }
}

// 暂停/恢复视频
void MainWindow::on_pausePushButton_clicked()
{
    // 有流在播放才可以暂停
    if (!isPlay())
    {
        QMessageBox::warning(this, tr("警告对话框"),tr("有流在播放才可以暂停！"), QMessageBox::Abort);
        return;
    }
    // 录制时不能暂停
    if (isRecord())
    {
        QMessageBox::warning(this, tr("警告对话框"),tr("录制中不能暂停！"), QMessageBox::Abort);
        return;
    }

    // 获得mpv播放器的"暂停"状态
    QString pasued = mpvPlayer->getProperty("pause");
    // 根据"暂停"状态来选择暂停还是播放
    if(pasued == "no")
    {
        ui->pausePushButton->setText("恢复");
        mpvPlayer->setProperty("pause", "yes");
    }
    else if(pasued == "yes")
    {
        ui->pausePushButton->setText("暂停");
        mpvPlayer->setProperty("pause", "no");
    }
}

void MainWindow::on_recordPushButton_clicked()
{
    // 有流播放时，才能录制
    if (!isPlay())
    {
        QMessageBox::warning(this, tr("警告对话框"),tr("有流播放时，才能录制！"), QMessageBox::Abort);
        return;
    }

    // 暂停时不能录制
    QString pasued = mpvPlayer->getProperty("pause");
    if (pasued == "yes")
    {
        QMessageBox::warning(this, tr("警告对话框"),tr("暂停时不能录制！"), QMessageBox::Abort);
        return;
    }

    if (!isRecord())
    {
        // 开始录制视频
        m_isRecord = true;
        ui->recordPushButton->setText("录像中");

        mpvPlayer->setProperty("stream-record", "./out.mp4");
    }
    else
    {
        // 停止录制
        m_isRecord = false;
        ui->recordPushButton->setText("录像");

        mpvPlayer->setProperty("stream-record", " ");
    }
}

// 接受播放结束信号的槽函数
void MainWindow::paltEnd_slot()
{
    m_isPlay = false;
    ui->playPushButton->setText("播放");
}
