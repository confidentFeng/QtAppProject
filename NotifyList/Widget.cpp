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

Widegt::Widegt(QWidget *parent)
    : QWidget(parent)
{
    // 初始化界面
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Widget);
    this->setFixedSize(600, 600);

    // 初始化窗口部件
    QPushButton * button1 = new QPushButton(tr("提示1"), this);
    QPushButton * button100 = new QPushButton(tr("提示100"), this);
    QPushButton * buttonDate = new QPushButton(tr("日期"), this);
    button1->setFixedSize(60, 32);
    button100->setFixedSize(60, 32);
    buttonDate->setFixedSize(60, 32);

    // 初始化通知管理器
    NotifyManager *pManager = new NotifyManager;
    pManager->setDefaultIcon(":/message.png"); // 设置默认图标
    pManager->setCntWidgetPos(this->pos() +(QPoint(936, 290)));

    // 按钮布局
    QVBoxLayout *pLayoutBtn = new QVBoxLayout();
    pLayoutBtn->addSpacing(32);
    pLayoutBtn->addWidget(button1);
    pLayoutBtn->addSpacing(12);
    pLayoutBtn->addWidget(button100);
    pLayoutBtn->addSpacing(12);
    pLayoutBtn->addWidget(buttonDate);
    pLayoutBtn->addStretch();
    // 主布局
    QHBoxLayout *pLayoutMain = new QHBoxLayout(this);
    pLayoutMain->addSpacing(24);
    pLayoutMain->addLayout(pLayoutBtn);
    pLayoutMain->addStretch();
    pLayoutMain->addWidget(pManager);
    pLayoutMain->setContentsMargins(0, 0, 0, 0);

    // 初始化信号槽连接
    QObject::connect(button1, &QPushButton::clicked, pManager, [=]() {
        static int count = 0;

        // 弹出一个消息框
        QString text = g_notifies[rand()%g_notifies.size()];
        pManager->notifyEnqueue(tr("新消息%1").arg(count++), text);
    });
    QObject::connect(button100, &QPushButton::clicked, pManager, [button1]() {
        // 弹出100个消息框
        for (int i=0; i<100; i++)
            button1->click();
    });
    QObject::connect(buttonDate, &QPushButton::clicked, pManager, [pManager]() {
        // 弹出一个消息框
        QString text = g_notifies[rand()%g_notifies.size()];
        pManager->notifyEnqueue(tr("今天 %1").arg(QDateTime::currentDateTime().toString("hh:mm")), text);
    });
}

Widegt::~Widegt()
{
}

