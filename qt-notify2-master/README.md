# qt-notify2

### 介绍
qt-notify功能增强、全新实现版本，原版 https://gitee.com/cassfrontend/qt-notify

![](./screenshot.gif)

### 较原版增强功能

1.  超出最大显示数时，将显示闪烁消息图标和队列中的数量
2.  消息主体不限于单行，改为多行显示，仍支持自动截短加省略号
3.  点击消息不限于按URL链接处理，可自行通过信号连接显示详细信息界面
4.  支持多主题样式管理，不同的情景使用不同样式
5.  支持各条消息单独定义显示时间
6.  消息提示框加阴影效果
7.  提示框右键关闭
8.  改进的示例代码

### 接口改进

1.  更精简的主体代码
2.  所有可配置项都改为函数接口，包括显示时间、动画时间、窗口大小、位置间隔、默认图标、主题样式、是否显示超出消息数
3.  提示消息不限于标题、主体、图标、链接4项数据，使用自定义data（QVariantMap）扩展
4.  图标、链接可省略，可使用默认图标，也可在data中传入icon、url等
5.  通过data接口可以自定义单条消息使用的主题样式、显示时间
6.  点击提示，通过信号notifyDetail传出，连接后可自行处理

### 使用说明

在pro工程中包含qtnotify2.pri
```makefile
include($$PWD/../src/qtnotify2.pri)
```

```c++
// 包含头文件
#include "notifymanager.h"

// 可建立全局实例
NotifyManager *manager = new NotifyManager(this);

// 可选修改默认参数
manager->setMaxCount(3); // 最大显示消息数，默认5
manager->setDisplayTime(5000); // 显示时间，默认10000（毫秒）
manager->setAnimateTime(500); // 动画时间，默认300（毫秒）
manager->setSpacing(5); // 消息框间距，默认10px
manager->setCornerMargins(20, 20); // 右下角边距，默认10, 10
manager->setNotifyWndSize(300, 75); // 消息框大小，默认300, 60
manager->setDefaultIcon(":/message.png"); // 消息图标，默认":/message.png"
manager->setShowQueueCount(true); // 是否显示超出最大数未显示的消息数量，默认true
manager->setStyleSheet("#notify-background {....", "自定义主题名称"); // 添加自定义主题样式表，默认样式主题名为default

// 基本用法
manager->notify("消息标题", "消息主体");

// 追加扩展数据
QVariantMap data;
data["icon"] = ":/messageXXX.png"; // 自定义消息图标，也可传入QPixmap
//data["icon"] = QPixmap(xxx);
data["name"] = "张三";
data["location"] = "XX市XX路";
data["money"] = 30.59;
data["theme"] = "black"; // 自定义主题样式，除默认样式，其它需预先添加后使用
// 也可直接自定义样式表如下
// data["styleSheet"] = "#notify-background {...."
data["displayTime"] = 30*1000; // 自定义显示时间（毫秒）
manager->notify("支付信息", "XXX商家XXX商品", data);

// 点击消息处理
QObject::connect(manager, &NotifyManager::notifyDetail, this, [this](const QVariantMap &data){
    QMessageBox::information(this, data.value("title").toString(), data.value("body").toString());
});
```
