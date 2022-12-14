#include "ArrangedWidget.h"

// 动画
static QPropertyAnimation *propertyAnimationOnTarget(QObject *target, const QByteArray &propertyName, const QVariant &endValue, int duration)
{
    QPropertyAnimation *animation = new QPropertyAnimation(target, propertyName, target);
    animation->setStartValue(target->property(propertyName));
    animation->setEndValue(endValue);
    animation->setDuration(duration);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    return animation;
}

// 动画模板
template<typename func>
static inline void propertyAnimationOnTarget(QObject *target, const QByteArray &propertyName, const QVariant &endValue, int duration, func onFinished)
{
    QPropertyAnimation *animation = propertyAnimationOnTarget(target, propertyName, endValue, duration);
    QObject::connect(animation, &QPropertyAnimation::finished, target, onFinished);
}

ArrangedWidget::ArrangedWidget (NotifyManager *manager, QWidget *parent)
    : QWidget(parent)
{
    // 初始化界面
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint); // 必须设置为Qt::Tools
    this->setAttribute(Qt::WA_NoSystemBackground, true);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setFixedSize(manager->notifyWndSize());

    // 初始化成员变量
    m_manager = manager; // NotifyWidget创建的时候传入
    m_posIndex = 0;

    // manager销毁，界面也跟着销毁
    connect(manager, &QObject::destroyed, this, &QObject::deleteLater);
}

// 根据通知在队列中的索引，来设置其的位置，相当于更新排序
void ArrangedWidget::showArranged(int posIndex)
{
    if (m_posIndex == posIndex)
        return;

    m_posIndex = posIndex;

    // 索引小于等于0，则隐藏
    if (posIndex <= 0)
    {
        // 如果已经隐藏，则返回
        if (!isVisible())
            return;

        // 隐藏动画
        propertyAnimationOnTarget(this, "windowOpacity", 0, m_manager->animateTime(), [this]() {
            this->hide();
            emit visibleChanged(false); // 隐藏信号
        });

        return;
    }

    // 计算提醒框的位置
    QSize wndsize = m_manager->notifyWndSize();
    QSize offset = QSize(wndsize.width(), wndsize.height()*posIndex + m_manager->spacing()*(posIndex-1));
    QPoint pos = m_manager->cornerPos() - QPoint(offset.width(), offset.height());

    // 如果原先是隐藏的，现在显示
    if (!isVisible())
    {
        this->show();
        this->move(pos);
        this->setWindowOpacity(0);
        propertyAnimationOnTarget(this, "windowOpacity", 1, m_manager->animateTime(), [this](){
            emit visibleChanged(true);
        });
    }
    else // 否则，移动位置
    {
        propertyAnimationOnTarget(this, "pos", pos, m_manager->animateTime());
    }
}
