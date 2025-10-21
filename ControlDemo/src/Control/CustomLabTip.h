#ifndef MYTIPLABEL_H
#define MYTIPLABEL_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QVBoxLayout>
#include <QDebug>

// 自定义定时隐藏提示标签
class CustomLabTip : public QLabel
{
    Q_OBJECT
public:
    explicit CustomLabTip(QWidget *parent = nullptr);
    void setTextPopup(const QString &text, const int &size = 14, const int &remain = 0); // 显示弹出提示框

protected:
    void showEvent(QShowEvent *event); // 显示事件
    void hideEvent(QHideEvent *event); // 隐藏事件

private:
    QTimer *timerDelay; // 延时关闭定时器
    int m_secondsRemain = 60; // 离关闭前的剩余秒数
};

#endif // MYTIPLABEL_H
