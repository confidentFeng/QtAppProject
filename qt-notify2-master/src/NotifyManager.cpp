#include "NotifyManager.h"
#include "NotifyWidget.h" // NotifyWidget.h没有放到NotifyManager.h文件，是因为NotifyWidget.cpp也include了NotifyManager.h，为了能互相include才这么做

NotifyManager::NotifyManager(QObject *parent) : QObject(parent)
{
    m_maxCount = 5; // 可见的最大通知数目设置为5
    m_displayTime = 10000; // 显示时间默认设置为10秒，通知显示出来过了10秒之后隐藏并自动销毁
    m_animateTime = 300; // 动画时间设置为300ms
    m_spacing = 10; // 通知框之间的间距设置为10
    m_notifyWndSize = QSize(300, 60); // 通知框大小
    m_defaultIcon = ":/message.png"; // 默认图标
    m_styleSheets["default"] =
            "#notify-background {"
            "background: white;"
            "border-radius: 4px;"
            "}"
            "#notify-title{"
            "font-weight: bold;"
            "font-size: 14px;"
            "color: #333333;"
            "}"
            "#notify-body{"
            "font-size: 12px;"
            "color: #444444;"
            "}"
            "#notify-close-btn{ "
            "border: 0;"
            "color: #999999;"
            "}"
            "#notify-close-btn:hover{ "
            "background: #cccccc;"
            "}";
    m_isShowQueueCount = true; // 默认显示队列的通知数目

    // 传入边距以设置最下面的通知的右下角坐标
    this->setCornerMargins(10, 10);

    // 初始化队列的剩余通知数目界面
    m_notifyCount = new NotifyCountWidget(this);
}

// 弹出通知框
void NotifyManager::notify(const QString &title, const QString &body, const QVariantMap &data)
{
    // 将标题栏和内容数据添加到队列中
    QVariantMap tmp = data;
    tmp.insert("title", title);
    tmp.insert("body", body);
    m_dataQueue.enqueue(tmp);

    // 显示下一条通知
    showNext();
}

// 设置通知框的最大数目
void NotifyManager::setMaxCount(int count)
{
    m_maxCount = count;
}

// 获取通知框显示时间
int NotifyManager::displayTime() const
{
    return m_displayTime;
}

// 设置通知框显示时间
void NotifyManager::setDisplayTime(int displayTime)
{
    m_displayTime = displayTime;
}

// 获取动画时间
int NotifyManager::animateTime() const
{
    return m_animateTime;
}

// 设置动画时间
void NotifyManager::setAnimateTime(int animateTime)
{
    m_animateTime = animateTime;
}

// 获取通知栏之间的间距
int NotifyManager::spacing() const
{
    return m_spacing;
}

// 设置通知栏之间的间距
void NotifyManager::setSpacing(int spacing)
{
    m_spacing = spacing;
}

// 获取最下面的通知的右下角坐标
QPoint NotifyManager::cornerPos() const
{
    return m_cornerPos;
}

// 传入边距以设置最下面的通知的右下角坐标
void NotifyManager::setCornerMargins(int right, int bottom)
{
    QRect desktopRect = QApplication::primaryScreen()->availableGeometry();
    QPoint bottomRignt = desktopRect.bottomRight();
    m_cornerPos = QPoint(bottomRignt.x() - right, bottomRignt.y() - bottom);
}

// 获取通知框的尺寸
QSize NotifyManager::notifyWndSize() const
{
    return m_notifyWndSize;
}

// 设置通知框的尺寸
void NotifyManager::setNotifyWndSize(int width, int height)
{
    m_notifyWndSize = QSize(width, height);
}

// 获取默认图标的路径
QString NotifyManager::defaultIcon() const
{
    return m_defaultIcon;
}

// 设置默认图标
void NotifyManager::setDefaultIcon(const QString &defaultIcon)
{
    m_defaultIcon = defaultIcon;
}

// 获取指定theme的样式
QString NotifyManager::styleSheet(const QString &theme) const
{
    if (!m_styleSheets.contains(theme))
        return m_styleSheets.value("default");

    return m_styleSheets.value(theme);
}

// 设置指定theme的样式
void NotifyManager::setStyleSheet(const QString &styleSheet, const QString &theme)
{
    m_styleSheets[theme] = styleSheet;
}

// 设置是否显示队列的通知数目
void NotifyManager::setShowQueueCount(bool isShowQueueCount)
{
    m_isShowQueueCount = isShowQueueCount;

    if (!m_isShowQueueCount)
        m_notifyCount->showArranged(0);
}

// 显示下一条通知
void NotifyManager::showNext()
{
    // 如果通知数目超出限制，则显示"通知当前数目界面"
    if (m_notifyList.size() >= m_maxCount || m_dataQueue.isEmpty())
    {
        showQueueCount();
        return;
    }

    // 创建并显示新的通知框
    NotifyWidget *notifyWidget = new NotifyWidget(this); // 将管理员自身传给notifyWidget的m_manager
    m_notifyList.append(notifyWidget); // 添加到通知框列表
    notifyWidget->showArranged(m_notifyList.size()); // 设置新通知的显示位置
    notifyWidget->setData(m_dataQueue.dequeue()); // 设置数据队列的第一个数据(dequeue，删除队列第一个元素，并返回这个元素)
    showQueueCount(); // 显示队列的剩余通知数目

    // 通知过了displayTime时间之后隐藏之后销毁，然后触发下面槽函数
    connect(notifyWidget, &QObject::destroyed, this, [notifyWidget, this](){
        // 找到被销毁的通知在队列中的索引，然后移除该通知
        int index = m_notifyList.indexOf(notifyWidget);
        m_notifyList.removeAt(index);

        // 旧消息被移出后，就要显示通知队列中的下一个新消息，并排序
        for (; index<m_notifyList.size(); index++)
            m_notifyList[index]->showArranged(index+1);

        // 这里是为了实现周期提示功能，一般不用到，可以注释
        QTimer::singleShot(m_animateTime, this, [this](){
            showNext();
        });
    });
}

// 显示队列的剩余通知数目
void NotifyManager::showQueueCount()
{
    // 判断是否允许显示队列的剩余通知数目
    if (!m_isShowQueueCount)
        return;

    // 数据队列大于0，说明还有未显示的剩余通知，则显示数目；否则隐藏"剩余通知数目"
    if (!m_dataQueue.isEmpty())
    {
        m_notifyCount->showArranged(m_maxCount+1);
        m_notifyCount->setCount(m_dataQueue.size());
    }
    else {
        m_notifyCount->showArranged(0);
    }
}
