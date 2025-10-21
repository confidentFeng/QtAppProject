#include "CustomLabTip.h"

CustomLabTip::CustomLabTip(QWidget *parent) : QLabel(parent)
{
    this->setObjectName("CustomLabTip");
    this->setFixedHeight(36);

    // 延时关闭定时器
    timerDelay = new QTimer(this);
    timerDelay->setInterval(1000);
    connect(timerDelay, &QTimer::timeout, [=]{
        m_secondsRemain--;
        if(m_secondsRemain == 0) {
            timerDelay->stop();
            this->close();
        }
    });
}

// 显示弹出提示框
void CustomLabTip::setTextPopup(const QString &text, const int &size, const int &remain)
{
    // 设置字体大小
    QFont font;
    font.setPointSize(size);
    this->setFont(font);
    // 设置字体颜色
    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::white);
    this->setPalette(pe);
    // 设置文本
    this->setText(text);

    // 获取文本长度，同时设置标签宽度和界面宽度
    QFontMetrics fm(font);
    int pixelsWide = fm.width(text);
    this->setFixedWidth(pixelsWide+ 24);
    this->move((parentWidget()->width()-width())/2, y());

    // 设置延时时间
    if(remain != 0) {
        m_secondsRemain = remain;
        timerDelay->start();
    }
}

// 显示事件
void CustomLabTip::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);

}

// 隐藏事件
void CustomLabTip::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event);
}
