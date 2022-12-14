#ifndef NOTIFYMANAGER_H
#define NOTIFYMANAGER_H

#include <QtCore>
#include <QApplication>
#include <QScreen>

class NotifyWidget;
class NotifyCountWidget;
class NotifyManager : public QObject
{
    Q_OBJECT

public:
    explicit NotifyManager( QObject *parent = 0);
    void notify(const QString &title, const QString &body, const QVariantMap &data = QVariantMap()); // 弹出通知框
    void setMaxCount(int count); // 设置通知框的最大数目
    int displayTime() const; // 获取通知框显示时间
    void setDisplayTime(int displayTime); // 设置通知框显示时间
    int animateTime() const; // 获取动画时间
    void setAnimateTime(int animateTime); // 设置动画时间
    int spacing() const; // 获取通知框之间的间距
    void setSpacing(int spacing); // 设置通知框之间的间距
    QPoint cornerPos() const; // 获取最下面的通知框的右下角坐标
    void setCornerMargins(int right, int bottom); // 传入边距以设置最下面的通知的右下角坐标
    QSize notifyWndSize() const; // 获取通知框的尺寸
    void setNotifyWndSize(int width, int height); // 设置通知框的尺寸
    QString defaultIcon() const; // 获取默认图标的路径
    void setDefaultIcon(const QString &defaultIcon); // 设置默认图标
    QString styleSheet(const QString &theme = "default") const; // 获取指定theme的样式
    void setStyleSheet(const QString &styleSheet, const QString &theme = "default"); // 设置指定theme的样式

    void setShowQueueCount(bool isShowQueueCount); // 设置是否显示队列的通知数目

signals:
    void notifyDetail(const QVariantMap &data);

private:
    void showNext(); // 显示下一条通知
    void showQueueCount(); // 显示队列的通知数目

    QQueue<QVariantMap> m_dataQueue; // 存放标题栏和内容数据的队列
    QList<NotifyWidget *> m_notifyList; // 通知框列表
    NotifyCountWidget *m_notifyCount; // 队列的剩余通知数目界面

    int m_maxCount; // 通知框的最大数目
    bool m_isShowQueueCount; // 是否显示队列的剩余通知数目
    int m_displayTime; // 通知框显示时间
    int m_animateTime; // 动画时间
    int m_spacing; // 通知框之间的间距
    QPoint m_cornerPos; // 最下面的通知框的右下角坐标
    QSize m_notifyWndSize; // 通知框的尺寸
    QString m_defaultIcon; // 默认图标
    QMap<QString, QString> m_styleSheets; // 存放多个theme的样式的map
};

#endif // NOTIFYMANAGER_H
