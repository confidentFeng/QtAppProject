#ifndef ARRANGEWND_H
#define ARRANGEWND_H

#include <QWidget>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include "NotifyManager.h"

class NotifyManager;

// 排列父界面，为什么要定义这个类，就是要同时作为NotifyWidget和NotifyCountWidget的父类，好让NotifyCountWidget始终在NotifyWidget的上方
class ArrangedWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ArrangedWidget(NotifyManager *manager, QWidget *parent = 0);
    void showArranged(int posIndex); // 根据通知在队列中的索引，来设置其的位置，相当于更新排序

signals:
    void visibleChanged(bool visible); // 界面可见状态改变的信号

protected:
    NotifyManager *m_manager;
    int m_posIndex;
};

#endif // ARRANGEWND_H
