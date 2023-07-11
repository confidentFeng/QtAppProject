#include "WifiList.h"

WifiList::WifiList(QWidget *parent) : QWidget(parent)
{
    // 界面初始化
    //this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setFixedSize(360, WIFI_ITEM_HEIGHT*10);
    this->setFocusPolicy(Qt::StrongFocus);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("WifiList");
    this->setProperty("canMove", true);
    this->setStyleSheet("QWidget#WifiList{background: #3c3c3c;}");

    // 初始化列表
    initListWidget();

    // 主布局
    QVBoxLayout* pLayoutMain = new QVBoxLayout(this);
    pLayoutMain->addWidget(m_pListWidget);
    pLayoutMain->addStretch();
    pLayoutMain->setSpacing(0);
    pLayoutMain->setMargin(0);

    // 获取wifi名称列表，添加到QListWidget列表中
    for(auto item : getdWifiList()) {
        addListItem(item);
    }
}

// 初始化列表
void WifiList::initListWidget()
{
    // 滚动列表初始化
    m_pListWidget = new QListWidget;
    m_pListWidget->setObjectName("WifiList_ListWidget");
    m_pListWidget->setFixedSize(width(), WIFI_ITEM_HEIGHT*10); // 136是item的高度，可见区域只显示4个item
    m_pListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 屏蔽水平滑动条
    m_pListWidget->setVerticalScrollMode(QListWidget::ScrollPerPixel); // 垂直滚动条设置为像素滚动
    m_pListWidget->verticalScrollBar()->setSingleStep(WIFI_ITEM_HEIGHT/3);  // 设置步长，每次滚动滚轮只上移或下移一个item
    m_pListWidget->verticalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
    FlatUI::setScrollBarQss(m_pListWidget->verticalScrollBar(), 0, 6, 12, "#3c3c3c", "#4d4d4d", "#7a7a7a", "#a6a6a6");
    m_pListWidget->installEventFilter(this);
    m_pListWidget->viewport()->installEventFilter(this);    //视图添加事件过滤器

#ifndef Q_OS_WIN
    // 设置数据
    QStringList strList = {"wif1", "wif2", "wif3", "wif4", "wif5", "wif6", "wif7", "wifi8"};
    // 添加项
    for (auto item : strList)
        addListItem(item);
#endif

    // 列表-信号槽连接
    connect(m_pListWidget, SIGNAL(itemPressed(QListWidgetItem *)), this, SLOT(slotItemPressed(QListWidgetItem *)));
    connect(m_pListWidget, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), \
            this, SLOT(slotCurrentItemChanged(QListWidgetItem *, QListWidgetItem *)));
}

// 添加自定义列表项
void WifiList::addListItem(const QString &name)
{
    WifiListItem *pListItem = new WifiListItem;
    pListItem->setWifiName(name);
    QListWidgetItem *item = new QListWidgetItem(m_pListWidget);
    m_pListWidget->setItemWidget(item, pListItem);
    item->setSizeHint(QSize(242, WIFI_ITEM_HEIGHT)); // 每次改变Item的高度
    m_pListWidget->addItem(item);
}

// 获取wifi名称列表
QStringList WifiList::getdWifiList()
{
    QStringList wifiList;

    // 提取出所有wifi的名称
    int index = 0;
    QString strCmdOut = AppCommon::Get().ExecuteCmd("netsh wlan show networks");
    QStringList strListOut = strCmdOut.split("\r\n");
    for (int i = 0; i < strListOut.size(); i++)
    {
        if (strListOut[i].contains("SSID"))
        {
            QStringList strListWifi = strListOut[i].split(" : ");

            // 去掉名称为""的wifi
            if (strListWifi[1] == "")
                continue;
            // 去掉名称乱码（实际是中文）的wifi
            if (strListWifi[1].contains(QRegExp("[\\x4e00-\\x9fa5]+")))
                continue;
            // 去掉长度过长的wifi
            if (strListWifi[1].length() > 24)
                continue;

            // 添加项
            wifiList.append(strListWifi[1]);
            index++;
        }
    }

    return wifiList;
}

// 获取已连接的wifi名称
QString WifiList::getConectedWifi()
{
    // 查找出已连接wifi的名称
    QString strCmdCon = AppCommon::Get().ExecuteCmd("netsh wlan show interface");
    QStringList strListCon = strCmdCon.split("\r\n");
    QString strConWifiName = "null"; // 避免列表中有名称为""的wifi
    if (strListCon.size() > 15) // 有连接wifi的话，输出行数会有24行，否则只有14行
    {
        QStringList strListWifiName = strListCon[19].split(": ");
        strConWifiName = strListWifiName[1].remove(" ");
    }

    return strConWifiName;
}

// item按下槽函数
void WifiList::slotItemPressed(QListWidgetItem *item)
{
    if ( item == nullptr )
        return ;

    qDebug() << "11111111111111111 " << m_pListWidget->currentRow();

//    QWidget *pVideoItem = m_pListWidget->itemWidget(item);
//    WifiListItem *pListItem = (WifiListItem*)(pVideoItem);
//    pListItem->setFixedSize(242, WIFI_ITEM_HEIGHT+90);
//    pVideoItem->setFixedSize(242, WIFI_ITEM_HEIGHT+90);

//    item->setSizeHint(QSize(242, WIFI_ITEM_HEIGHT+90));

//    pListItem->setState(Checked);

//    item->setSizeHint(QSize(242, WIFI_ITEM_HEIGHT+90));
}

// 当前item改变槽函数(包括上下键操作也触发)
void WifiList::slotCurrentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        return;

    qDebug() << "slotCurrentItemChanged " << m_pListWidget->currentRow();

    if ( previous ){
        QWidget *pItemPre = m_pListWidget->itemWidget(previous);
        WifiListItem *pListItemPre = (WifiListItem*)(pItemPre);
//        if(pListItemPre->getState() == Connected)
//            pListItemPre->setState(pListItemPre->getState());
//        else
            pListItemPre->setState(Unchecked);

        previous->setSizeHint(QSize(242, WIFI_ITEM_HEIGHT));
    }
    if ( current ){
        QWidget *pItemCur = m_pListWidget->itemWidget(current);
        WifiListItem *pListItemCur = (WifiListItem*)(pItemCur);
        pListItemCur->setState(pListItemCur->getState());

        current->setSizeHint(QSize(242, WIFI_ITEM_HEIGHT*3));
    }
}
