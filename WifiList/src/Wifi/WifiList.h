#ifndef WIFILIST_H
#define WIFILIST_H

#include <QWidget>
#include <QListWidget>
#include <QScrollBar>
#include "WifiListItem.h"
#include "src/Control/FlatUI.h"
#include "src/Util/AppInit.h"
#include "src/Util/AppCommon.h"

class WifiList : public QWidget
{
    Q_OBJECT
public:
    explicit WifiList(QWidget *parent = nullptr);

public slots:
    void slotItemPressed(QListWidgetItem *item); // item按下槽函数
    void slotCurrentItemChanged(QListWidgetItem *current, QListWidgetItem *previous); // 当前item改变槽函数

private:
    void initListWidget(); // 初始化列表
    void addListItem(const QString &name); // 添加自定义列表项
    QStringList getdWifiList(); // 获取wifi名称列表
    QString getConectedWifi(); // 获取已连接的wifi名称

    WifiListItem *m_pWifiListItem;

    QListWidget *m_pListWidget; // 视频列表
};

#endif // WIFILIST_H
