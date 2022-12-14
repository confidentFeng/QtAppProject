#ifndef NOTIFYWND_H
#define NOTIFYWND_H


#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>
#include <QGraphicsDropShadowEffect>
#include "ArrangedWidget.h"

// 通知框
class NotifyWidget : public ArrangedWidget
{
    Q_OBJECT

public:
    explicit NotifyWidget(NotifyManager *manager, QWidget *parent = 0);

    QVariantMap data() const; // 获取数据
    void setData(const QVariantMap &data); // 设置数据

private:
    QVariantMap m_data; // 存放数据的map
    QFrame *m_pFrameBack; // 背景界面
    QLabel *m_pLabIcon; // 图标标签
    QLabel *m_pLabTitle; // 标题标签
    QLabel *m_pLabBody; // 内容标签
    QPushButton *m_pBtnClose; // 关闭按钮
};

// 队列中的剩余通知数目
class NotifyCountWidget : public ArrangedWidget
{
    Q_OBJECT

public:
    explicit NotifyCountWidget(NotifyManager *manager, QWidget *parent = 0);
    void setCount(int count); // 设置剩余通知数目

private:
    QLabel *m_pLabIcon;
    QLabel *m_pLabCount;
    QPropertyAnimation *flickerAnim;
};

#endif // NOTIFYWND_H
