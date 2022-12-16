#ifndef NOTIFYWND_H
#define NOTIFYWND_H

#include <QtCore>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPropertyAnimation>

// 透明度改变动画（windowOpacity属性只能对顶级窗口使用，例如Qt::Tool窗口，对普通控件这些无效）
template<typename func>
static inline void animationOpacity(QWidget *target, const QVariant &endValue, int duration, func onFinished = nullptr)
{
    QPropertyAnimation *pAnimation = new QPropertyAnimation(target, "windowOpacity", target);
    pAnimation->setStartValue(target->property("windowOpacity"));
    pAnimation->setEndValue(endValue);
    pAnimation->setDuration(duration);
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    QObject::connect(pAnimation, &QPropertyAnimation::finished, target, onFinished);
}

// 摇晃动画
template<typename func>
static inline void animationShake(QWidget *target, int duration, func onFinished = nullptr)
{
    int distance = 5;
    QPropertyAnimation *pAnimation = new QPropertyAnimation(target, "geometry");
    pAnimation->setDuration(duration);
    pAnimation->setKeyValueAt(0, target->rect().adjusted(-distance, distance, 0, 0)); // 设置动画结束位置及其大小
    pAnimation->setKeyValueAt(0.1, target->rect().adjusted(distance, -distance, 0, 0));
    pAnimation->setKeyValueAt(0.2, target->rect().adjusted(-distance, distance, 0, 0));
    pAnimation->setKeyValueAt(0.3, target->rect().adjusted(distance, -distance, 0, 0));
    pAnimation->setKeyValueAt(0.4, target->rect().adjusted(-distance, distance, 0, 0));
    pAnimation->setKeyValueAt(0.5, target->rect().adjusted(distance, -distance, 0, 0));
    pAnimation->setKeyValueAt(0.6, target->rect().adjusted(-distance, distance, 0, 0));
    pAnimation->setKeyValueAt(0.7, target->rect().adjusted(distance, -distance, 0, 0));
    pAnimation->setKeyValueAt(0.8, target->rect().adjusted(-distance, distance, 0, 0));
    pAnimation->setKeyValueAt(0.9, target->rect().adjusted(distance, -distance, 0, 0));
    pAnimation->setKeyValueAt(1, target->rect().adjusted(0, 0, 0, 0));
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    QObject::connect(pAnimation, &QPropertyAnimation::finished, target, onFinished);
}

// 移动向右消失动画
template<typename func>
static inline void animationMove(QWidget *target, int duration, int distance, func onFinished = nullptr)
{
    QPropertyAnimation *pAnimation = new QPropertyAnimation(target, "pos");
    pAnimation->setDuration(duration);
    pAnimation->setStartValue(target->pos());
    pAnimation->setEndValue(target->pos() + QPoint(distance, 0));
    pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    QObject::connect(pAnimation, &QPropertyAnimation::finished, target, onFinished);
}

// 通知
class NotifyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NotifyWidget(QWidget *parent = 0);
    void setData(const QVariantMap &data); // 设置数据

private:
    QVariantMap m_data; // 存放数据的map
    QLabel *m_pLabIcon; // 图标标签
    QLabel *m_pLabTitle; // 标题标签
    QLabel *m_pLabBody; // 内容标签
    QPushButton *m_pBtnClose; // 关闭按钮
};

// 队列的通知数目界面
class NotifyCountWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NotifyCountWidget(QWidget *parent = nullptr);
    void setCount(int count); // 设置通知数目
    void isStartAnim(bool isStartAnim); // 是否开启动画

private:
    QLabel *m_pLabIcon;
    QLabel *m_pLabCount;
    QPropertyAnimation *m_pFlickerAnim;
};

#endif // NOTIFYWND_H
