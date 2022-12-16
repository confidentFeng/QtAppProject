#include "NotifyManager.h"

NotifyManager::NotifyManager(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(320, 600);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setObjectName("NotifyManager");

    // 创建一个子窗口，这个子窗口交给滚动区域
    QWidget* pSubWidget = new QWidget(this);

    // 创建滚动区域
    m_pScrollArea = new QScrollArea(this);
    m_pScrollArea->setFixedSize(width(), NOTIFY_HEIGHT);
    m_pScrollArea->setWidgetResizable(true); // 决定着滚动区域是否应调整子widget的大小
    m_pScrollArea->verticalScrollBar()->setSingleStep(NOTIFY_HEIGHT/3);  // 设置步长，每次滚动滚轮只上移或下移一个item
    m_pScrollArea->setWidget(pSubWidget); // 子widget可以使用QScrollArea::setWidget(QWidget *widget)来指定
    m_pScrollArea->move(QPoint(0, height() - NOTIFY_HEIGHT));

    // 给子窗口设置一个垂直布局，方便动态添加通知
    m_pLayoutSub = new QVBoxLayout(pSubWidget);
    m_pLayoutSub->setSpacing(NOTIFY_SPACE);
    m_pLayoutSub->setContentsMargins(0,0,0,0);
    m_pLayoutSub->addStretch();

    // 初始化队列的通知数目界面
    m_pNotifyCntWidget = new NotifyCountWidget(this);
    m_pNotifyCntWidget->hide();

    // 显示队列的通知数目的定时器
    m_pTimerCnt = new QTimer(this);
    m_pTimerCnt->setSingleShot(true);
    m_pTimerCnt->setInterval(3000);
    connect(m_pTimerCnt, &QTimer::timeout, [=]{
        m_pNotifyCntWidget->hide();
        m_pNotifyCntWidget->isStartAnim(false); // 结束动画
    });

    // 队列定时器
    m_pTimerQueue = new QTimer(this);
    m_pTimerQueue->setInterval(500);
    m_pTimerQueue->start();
    connect(m_pTimerQueue, &QTimer::timeout, [=]{
        showQueueNotify();
    });
}

// 通知入队
void NotifyManager::notifyEnqueue(const QString &title, const QString &body, const QVariantMap &data)
{
    // 将标题栏和内容数据添加到队列中
    QVariantMap tmp = data;
    tmp.insert("title", title);
    tmp.insert("body", body);
    tmp.insert("icon", m_defaultIcon);
    m_dataQueue.enqueue(tmp);
}

// 显示队列中的通知
void NotifyManager::showQueueNotify()
{
    m_pTimerQueue->stop();

    // 如果通知数目超出限制，则显示"通知当前数目界面"
    if (m_notifyCount >= NOTIFY_MAX_COUNT || m_dataQueue.isEmpty()) {
        m_pTimerQueue->start();
        return;
    }

    // 创建并显示新的通知
    NotifyWidget *notifyWidget = new NotifyWidget(this); // 将管理员自身传给notifyWidget的m_manager
    notifyWidget->setData(m_dataQueue.dequeue()); // 设置数据队列的第一个数据(dequeue，删除队列第一个元素，并返回这个元素)
    m_pLayoutSub->insertWidget(0, notifyWidget);
    m_notifyCount++;

    // 显示新的通知时，摇晃动画
    animationShake(notifyWidget, 800, [=](){
        m_pTimerQueue->start();
    });

    // 通知销毁之后触发下面槽函数
    connect(notifyWidget, &QObject::destroyed, this, [this](){
        m_notifyCount--;
        // 更新滚动区域的高度
        updateAreaHeight();
    });

    // 更新滚动区域的高度
    updateAreaHeight();
}

// 更新滚动区域的高度
void NotifyManager::updateAreaHeight()
{
    // 布局最前面插入通知
    if(m_notifyCount < VIEW_ITEM) {
        m_pScrollArea->move(QPoint(0, height() - NOTIFY_HEIGHT*m_notifyCount));
        m_pScrollArea->setFixedHeight(NOTIFY_HEIGHT*m_notifyCount);
    }
    else {
        // 显示队列的通知数目
        showQueueCount();

        m_pScrollArea->setFixedHeight(NOTIFY_HEIGHT*(VIEW_ITEM-1) -10);
    }
}

// 设置默认图标
void NotifyManager::setDefaultIcon(const QString &defaultIcon)
{
    m_defaultIcon = defaultIcon;
}

// 设置通知数目界面的坐标
void NotifyManager::setCntWidgetPos(QPoint pos)
{
    m_pNotifyCntWidget->move(pos);
}

// 显示队列的通知数目
void NotifyManager::showQueueCount()
{
    m_pNotifyCntWidget->setCount(m_notifyCount);
    m_pNotifyCntWidget->show();
    m_pNotifyCntWidget->setWindowOpacity(0);
    animationOpacity(m_pNotifyCntWidget, 1, 1500, [this](){
        m_pNotifyCntWidget->isStartAnim(true);
    });

    m_pTimerCnt->start(3000); // 重新启动计时
}
