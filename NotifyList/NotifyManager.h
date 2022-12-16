#ifndef NOTIFYMANAGER_H
#define NOTIFYMANAGER_H

#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include "NotifyWidget.h"

#define NOTIFY_MAX_COUNT 20 // 最大通知数目
#define NOTIFY_SPACE 12 // 每个通知之间的间距
#define NOTIFY_HEIGHT (81+12) // 每个通知item的高度（等于通知的高度+通知之间的间距）
#define VIEW_ITEM 6 // QScrollArea可见区域内的通知数目

class NotifyManager : public QWidget
{
    Q_OBJECT

public:
    explicit NotifyManager( QWidget *parent = nullptr);
    void notifyEnqueue(const QString &title, const QString &body, const QVariantMap &data = QVariantMap()); // 通知入队
    void showQueueCount(); // 显示队列的通知数目
    void setDefaultIcon(const QString &defaultIcon); // 设置默认图标
    void setCntWidgetPos(QPoint pos); // 设置通知数目界面的坐标

private:
    void showQueueNotify(); // 显示队列中的通知
    void updateAreaHeight(); // 更新滚动区域的高度

    NotifyCountWidget *m_pNotifyCntWidget; // 队列的通知数目界面
    QScrollArea* m_pScrollArea;
    QVBoxLayout* m_pLayoutSub;

    QQueue<QVariantMap> m_dataQueue; // 数据队列
    QString m_defaultIcon; // 默认图标
    QMap<QString, QString> m_styleSheets; // 存放多个theme的样式的map
    QTimer *m_pTimerCnt;
    QTimer *m_pTimerQueue; // 队列定时器
    int m_notifyCount = 0; // 通知数目
};

#endif // NOTIFYMANAGER_H
