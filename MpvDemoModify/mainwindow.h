#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "mpvplayer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_playPushButton_clicked(); // 播放/停止
    void on_pausePushButton_clicked(); // 暂停/恢复视频
    void paltEnd_slot(); // 接受播放结束信号的槽函数

    void on_recordPushButton_clicked();

private:
    Ui::MainWindow *ui;

    bool isPlay(); // 判断是否在播放
    bool isRecord(); // 判断是否在录制

    MpvPlayer *mpvPlayer;
    bool m_isPlay;
    bool m_isRecord;
};

#endif // MAINWINDOW_H
