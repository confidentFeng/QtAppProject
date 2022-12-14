#include "Widget.h"

// 内容列表
const QStringList g_notifies = {
    "我从来不相信什么懒洋洋的自由，我向往的自由是通过勤奋和努力实现的更广阔的人生，那样的自由才是珍贵的、有价值的。",
    "我相信一万小时定律，我从来不相信天上掉馅饼的灵感和坐等的成就。",
    "做一个自由又自律的人，靠势必实现的决心认真地活着。",
    "你的脸上云淡风轻，谁也不知道你的牙咬得有多紧。",
    "你走路带着风，谁也不知道你膝盖上仍有曾摔伤的淤青。",
    "你笑得没心没肺，没人知道你哭起来只能无声落泪。",
    "要让人觉得毫不费力，只能背后极其努力。",
    "我们没有改变不了的未来，只有不想改变的过去。",
    "如果逃避眼前的现实，越是逃，就越是会陷入痛苦的境地。",
    "要有面对问题的勇气，渡过这个困境的话，应该就能一点点地解决问题。感激遇到的所有人吧。",
    "虽然晚了点，依靠自己的力量前进吧。为了开始新的人生。"
};

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    // 初始化界面
    this->resize(300,80);
    this->setWindowTitle(tr("浮动提示框"));

    // 初始化窗口部件
    QPushButton * button1 = new QPushButton(tr("提示1"), this);
    QPushButton * button100 = new QPushButton(tr("提示100"), this);
    QPushButton * buttonDate = new QPushButton(tr("日期"), this);
    QPushButton * buttonblack = new QPushButton(tr("提示(黑色样式)"), this);
    QPushButton * button15s = new QPushButton(tr("提示(15秒)"), this);
    QPushButton * buttonTimer = new QPushButton(tr("开始周期提示"), this);
    QDoubleSpinBox * spinBoxTime = new QDoubleSpinBox(this);
    buttonTimer->setCheckable(true);
    spinBoxTime->setSuffix(tr("秒"));
    spinBoxTime->setSingleStep(0.1);

    // 主布局
    QVBoxLayout *pLayoutMain = new QVBoxLayout(this);
    pLayoutMain->addWidget(button1);
    pLayoutMain->addWidget(button100);
    pLayoutMain->addWidget(buttonDate);
    pLayoutMain->addWidget(buttonblack);
    pLayoutMain->addWidget(button15s);
    pLayoutMain->addWidget(buttonTimer);
    pLayoutMain->addWidget(spinBoxTime);

    // 初始化通知管理器
    NotifyManager *manager = new NotifyManager(this);
    manager->setMaxCount(5);
    manager->setDisplayTime(5000);
    manager->setNotifyWndSize(300, 80);
    manager->setStyleSheet("#notify-background {"
                           "background: black;"
                           "}"
                           "#notify-title{"
                           "font: bold 14px 黑体;"
                           "color: #eeeeee;"
                           "}"
                           "#notify-body{"
                           "font: 12px 黑体;"
                           "color: #dddddd;"
                           "}"
                           "#notify-close-btn{ "
                           "border: 0;"
                           "color: #999999;"
                           "}"
                           "#notify-close-btn:hover{ "
                           "background: #444444;"
                           "}", "black");

    int count = 1;
    srand(QDateTime::currentMSecsSinceEpoch());

    // 初始化信号槽连接
    QObject::connect(button1, &QPushButton::clicked, manager, [manager, &count]() {
        // 弹出一个消息框
        QString text = g_notifies[rand()%g_notifies.size()];
        manager->notify(tr("新消息%1").arg(count++), text);
    });
    QObject::connect(button100, &QPushButton::clicked, manager, [button1]() {
        // 弹出100个消息框
        for (int i=0; i<100; i++)
            button1->click();
    });
    QObject::connect(buttonDate, &QPushButton::clicked, manager, [manager]() {
        // 弹出一个消息框
        QString text = g_notifies[rand()%g_notifies.size()];
        manager->notify(tr("今天 %1").arg(QDateTime::currentDateTime().toString("hh:mm")), text);
    });
    QObject::connect(buttonblack, &QPushButton::clicked, manager, [manager, &count]() {
        // 弹出一个消息框，样式设置为黑色样式
        QVariantMap data;
        data["theme"] = "black";
        QString text = g_notifies[rand()%g_notifies.size()];
        manager->notify(tr("黑色样式消息%1").arg(count++), text, data);
    });
    QObject::connect(button15s, &QPushButton::clicked, manager, [manager, &count]() {
        // 弹出一个消息框，displayTime设置为15秒
        QVariantMap data;
        data["displayTime"] = 15*1000;
        QString text = g_notifies[rand()%g_notifies.size()];
        manager->notify(tr("15秒消息%1").arg(count++), text, data);
    });

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, button1, &QPushButton::click);
    QObject::connect(spinBoxTime, QOverload<double>::of(&QDoubleSpinBox::valueChanged), &timer, [&timer](double value){
        timer.setInterval(value*1000);
    });
    QObject::connect(buttonTimer, &QPushButton::clicked, &timer, [&timer](bool checked){
        if (checked) timer.start();
        else timer.stop();
    });

    QObject::connect(manager, &NotifyManager::notifyDetail, [](const QVariantMap &data){
        QMessageBox msgbox(QMessageBox::Information, tr("新消息"), data.value("title").toString());
        msgbox.setDetailedText(data.value("body").toString());
        msgbox.findChild<QDialogButtonBox*>()->setMinimumWidth(500);
        msgbox.exec();
    });

    spinBoxTime->setValue(0.5);
}
