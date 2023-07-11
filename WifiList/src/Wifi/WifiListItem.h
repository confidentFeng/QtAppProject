#ifndef WIFILISTITEM_H
#define WIFILISTITEM_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRegExpValidator>
#include "XmlHelper.h"
#include "src/Control/FlatUI.h"
#include "src/Util/def.h"
#include "src/Util/AppCommon.h"
#include "src/Control/CustomEditPasswd.h"
#include "src/Widget/LoadingWidget.h"

#define WIFI_LIST_WIDTH 360
#define WIFI_ITEM_HEIGHT 50

enum WifiState {
    Unchecked = 0,
    Checked,
    Edit,
    Connecting,
    Connected
};

class WifiListItem : public QWidget
{
    Q_OBJECT
public:
    explicit WifiListItem(QWidget *parent = nullptr);
    void setState(WifiState wifiState); // 设置状态
    WifiState getState(); // 获取状态
    void setWifiName(const QString &name); // 设置wifi名称

private:
    void initSigSlot(); // 初始化信号槽

    QLabel *m_pLabIcon; // 图标标签
    QLabel *m_pLabName; // 名称标签

    QCheckBox *m_pCheckBox; // 勾选框
    QPushButton *m_pBtnWifi; // wifi按钮
    QWidget *m_pWidgetCheck; // 勾选框Widget

    QLabel *m_pLabEditTip; // 编辑框提示文本标签
    CustomEditPasswd *m_pEditPasswd; // wifi密码编辑框
    QLabel *m_pLabErrorTip; // 错误提示文本标签
    QPushButton *m_pBtnNext; // 下一步按钮
    QPushButton *m_pBtnCancel; // 取消按钮
    QWidget *m_pWidgetEdit; // 编辑框Widget

    LoadingWidget *m_pLoadingWidget; // 加载界面
    QLabel *m_pLabVerify; // 验证标签
    QPushButton *m_pBtnConCancel; // 连接取消按钮
    QWidget *m_pWidgetConnecting; // 连接中Widget

    QPushButton *m_pBtnLProperty; // 属性按钮
    QPushButton *m_pBtnDisconect; // 断开连接按钮
    QWidget *m_pWidgetConnected; // 断开连接Widget

    WifiState m_wifiState = Checked; // 当前状态
};

#endif // WIFILISTITEM_H
