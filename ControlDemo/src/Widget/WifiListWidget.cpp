#include "WifiListWidget.h"

WifiListWidget::WifiListWidget(QWidget *parent)
    : QWidget(parent)
{
    // 界面初始化
    //this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setFixedSize(320, ITEM_HEIGHT*ITEM_MAX_COUNT+52);
    this->setFocusPolicy(Qt::StrongFocus);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("WifiListWidget");

    // 初始化QTableView
    initTableView();

    // 初始化按钮
    m_pBtnRemove = new QPushButton;
    m_pBtnAdd = new QPushButton;
    m_pBtnRemove->setObjectName("Common_BtnBlue");
    m_pBtnAdd->setObjectName("Common_BtnBlue");
    m_pBtnRemove->setFixedSize(86, 32);
    m_pBtnAdd->setFixedSize(86, 32);
    m_pBtnRemove->setText("移除");
    m_pBtnAdd->setText("添加");
    connect(m_pBtnRemove, &QPushButton::clicked, [=]{
        m_pMyTableView->getModel()->removeRow(m_pMyTableView->getModel()->rowCount() - 1);
    });
    connect(m_pBtnAdd, &QPushButton::clicked, [=]{
        addItem("Wifi");
    });

    // 按钮布局
    QHBoxLayout *pLayoutBtn= new QHBoxLayout;
    pLayoutBtn->addStretch();
    pLayoutBtn->addWidget(m_pBtnRemove);
    pLayoutBtn->addStretch();
    pLayoutBtn->addWidget(m_pBtnAdd);
    pLayoutBtn->addStretch();
    pLayoutBtn->setSpacing(0);
    pLayoutBtn->setMargin(0);
    // 主布局
    QVBoxLayout *pLayoutMain = new QVBoxLayout(this);
    pLayoutMain->addWidget(m_pMyTableView);
    pLayoutMain->addStretch();
    pLayoutMain->addLayout(pLayoutBtn);
    pLayoutMain->addSpacing(10);
    pLayoutMain->setSpacing(0);
    pLayoutMain->setMargin(0);

    // 1. 查找出已连接wifi的名称
    QString strCmdCon = AppCommon::Get().ExecuteCmd("netsh wlan show interface");
    QStringList strListCon = strCmdCon.split("\r\n");
    QString strConWifiName = "null"; // 避免列表中有名称为""的wifi
    if (strListCon.size() > 15) // 有连接wifi的话，输出行数会有24行，否则只有14行
    {
        QStringList strListWifiName = strListCon[19].split(": ");
        strConWifiName = strListWifiName[1].remove(" ");
    }

    // 2. 提取出所有wifi的名称，并在已连接wifi一项"打勾"
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
            addItem(strListWifi[1]);
            index++;
        }
    }

#ifndef Q_OS_WIN
    // 设置数据
    QStringList strList = {"wif1", "wif2", "wif3", "wif4", "wif5", "wif6", "wif7", "wifi8"};
    // 添加项
    for (auto item : strList)
        addItem(item);
#endif
}

// 初始化QTableView
void WifiListWidget::initTableView()
{
    // 初始化tableWidget
    m_pMyTableView = new MyTableView;
    m_pMyTableView->setFixedSize(width(), ITEM_HEIGHT*ITEM_MAX_COUNT);
    m_pMyTableView->setObjectName("WifiListWidget_myTableView");
    m_pMyTableView->horizontalHeader()->setVisible(false); // 隐藏表头
    m_pMyTableView->verticalHeader()->setHidden(true); // 隐藏默认行号
    m_pMyTableView->setShowGrid(false);
    m_pMyTableView->setEditTriggers(QAbstractItemView::NoEditTriggers); // 设置不可编辑
    m_pMyTableView->verticalScrollBar()->setSingleStep(ITEM_HEIGHT/3); // 设置滚动条步长（要先设置为像素滚动，才能生效）
    m_pMyTableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter); // 设置表头为左对齐
    m_pMyTableView->verticalHeader()->setMinimumSectionSize(ITEM_HEIGHT); // linux下默认最小高度为MEET_ITEM_HEIGHT，所以这里要修改下
    m_pMyTableView->verticalHeader()->setDefaultSectionSize(ITEM_HEIGHT);
    m_pMyTableView->setIconSize(QSize(20, 20)); // 设置icon尺寸大小（否则显示的图标尺寸很小，即使实际图片文件很大）
    m_pMyTableView->setDragEnabled(false);         // 此处添加拖拽的话会生成两个item
    m_pMyTableView->setSelectionBehavior(QAbstractItemView::SelectRows); // 设置选中行
    m_pMyTableView->setSelectionMode(QAbstractItemView::ExtendedSelection); // 设置多选属性，可通过鼠标拖拽、按下Ctrl或Shift键操作多选
    m_pMyTableView->setMouseTracking(true); // 必须要有，否则无法实现hover变色
    m_pMyTableView->setHoverColor(QColor(0,147,221,50)); // 设置悬浮颜色
    m_pMyTableView->setStyle(new TableItemSpaceStyleName); // 设置单元格内边距

    // 复选框改变也会触发itemChanged信号
    connect(m_pMyTableView->getModel(), &QStandardItemModel::itemChanged, [=](QStandardItem *item) {
        // 实时获取选中的复选框数目
        int checkedCount = 0;
        for(int i=0; i < m_pMyTableView->getModel()->rowCount(); i++)
            if(m_pMyTableView->getModel()->item(i, 0)->isEnabled() &&
               Qt::Checked == m_pMyTableView->getModel()->index(i, 0).data(Qt::CheckStateRole))
                checkedCount++;
        //qDebug() << "QStandardItemModel::itemChanged: " << checkedCount;

        // 复选框选中时，同时选中当前行
        m_pMyTableView->selectRow(item->index().row());
    });

    // 创建多个动作
    m_actionAdd = new QAction;
    m_actionDel = new QAction;
    m_actionAdd->setText(tr("添加数据"));
    m_actionDel->setText(tr("删除数据"));
    // 创建右键菜单
    m_popMenu = new QMenu(m_pMyTableView);
    m_popMenu->addAction(m_actionAdd);
    m_popMenu->addAction(m_actionDel);
    // QAction绑定槽函数，当点击QAction时触发
    connect(m_actionAdd, &QAction::triggered, [=] {
        addItem("王五");
    });
    connect(m_actionDel, &QAction::triggered, [=] {
        m_pMyTableView->getModel()->removeRow(m_pMyTableView->currentIndex().row());
    });
    // m_pMyTableView设置可弹出右键菜单
    m_pMyTableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_pMyTableView, &QTableView::customContextMenuRequested, [=] {
        // 检测是否有选中项 && 选中项是否有效
        if (m_pMyTableView->selectionModel()->hasSelection() && m_pMyTableView->currentIndex().isValid())
            m_popMenu->exec(QCursor::pos());
    });

    // 鼠标双击超时检测定时器
    m_pTimerMouseOut = new QTimer(this);
    m_pTimerMouseOut->setSingleShot(true);
    connect(m_pTimerMouseOut, &QTimer::timeout, [=]{
        m_nCntDouble = 0;
        m_pTimerMouseOut->stop();
        m_userClicked = "";
    });

    // 双击
    connect(m_pMyTableView, &QTableView::clicked, [=](const QModelIndex &index){
        QString curText = m_pMyTableView->getModel()->item(index.row(), 0)->text();

        if(m_userClicked != curText)
            m_pTimerMouseOut->start(400);
        m_nCntDouble++;
        if(m_nCntDouble >= 2) {
            m_nCntDouble = 0;
            m_pTimerMouseOut->stop();

            // 如果item已被禁用，则返回
            if(!m_pMyTableView->getModel()->item(index.row(), 0)->isEnabled())
                return;

            // 如果两次点击的用户名都相同
            if(m_userClicked == curText) {
                qDebug() << "double clicked Success";
                // 进行双击操作
            }

            m_userClicked = "";
            return;
        }

        m_userClicked = curText;
    });
}

// 添加项
void WifiListWidget::addItem(QString name)
{
    // 准备数据模型
    QList<QStandardItem *> listItems;

    // 名称（包括勾选框）
    QStandardItem *pItemName = new QStandardItem(name);
    pItemName->setCheckable(true);
    pItemName->setCheckState(Qt::Unchecked);
    // 年龄
    QStandardItem *pItemAge = new QStandardItem("25");
    // 图标
    QStandardItem *pItemIcon = new QStandardItem(QIcon(":/Image/icon_camera_checked.png"), "");

    // 添加到数据模型
    listItems << pItemName << pItemAge << pItemIcon;
    m_pMyTableView->getModel()->appendRow(listItems); // 加载一行数据

    // 设置各列的宽度
    if(m_pMyTableView->getModel()->rowCount() > ITEM_MAX_COUNT)
        m_pMyTableView->setColumnWidth(0, 200-8);
    else
        m_pMyTableView->setColumnWidth(0, 200);
    m_pMyTableView->setColumnWidth(1, 60);
    m_pMyTableView->setColumnWidth(2, 60);
}

// 获取多选的item
void WifiListWidget::getMultiCheckItem()
{
    QStandardItemModel *standardModel = new QStandardItemModel(this);
    QItemSelectionModel  *selectModel = new QItemSelectionModel(standardModel);

    // 第一种方法： 通过 QItemSelectionModel
    if(!selectModel->hasSelection())
        return;
    QModelIndexList  modelList1 = selectModel->selectedIndexes();

   // 第二种方法:  通过tableView
    QModelIndexList modelList2 = m_pMyTableView->selectionModel()->selectedIndexes();
    foreach(QModelIndex index, modelList1)
    {
       QStandardItem *item = standardModel->itemFromIndex(index);
       QFont font = item->font();
       font.setBold(!font.bold());
       item->setFont(font);
    }
}

// 获取viewPort当前显示的可见的第一行
int WifiListWidget::getViewFirstNumber()
{
    return m_pMyTableView->verticalScrollBar()->value();
}

// 获取viewPort当前显示的可见的最后一行
int WifiListWidget::getViewLastNumber()
{
    return m_pMyTableView->verticalScrollBar()->value() + m_pMyTableView->verticalScrollBar()->pageStep();
}

// 键盘按下事件
void WifiListWidget::keyPressEvent(QKeyEvent *event)
{
    // 自定义实现QTableView的上下方向键功能
    if(event->key() == Qt::Key_Up) {
        int curRow = m_pMyTableView->currentIndex().row();
        curRow--;
        if(curRow < 0)
            curRow = m_pMyTableView->model()->rowCount()-1;
        QModelIndex nextIndex = m_pMyTableView->model()->index(curRow, 0);
        m_pMyTableView->setCurrentIndex(nextIndex);

        return;
    }
    if(event->key() == Qt::Key_Down) {
        int curRow = m_pMyTableView->currentIndex().row();
        curRow++;
        if(curRow > m_pMyTableView->model()->rowCount()-1)
            curRow = 0;
        QModelIndex nextIndex = m_pMyTableView->model()->index(curRow, 0);
        m_pMyTableView->setCurrentIndex(nextIndex);

        return;
    }
    if(event->key() == Qt::Key_Home) { // Home键跳转到第一行
        QModelIndex nextIndex = m_pMyTableView->model()->index(0, 0);
        m_pMyTableView->setCurrentIndex(nextIndex);

        return;
    }
    if(event->key() == Qt::Key_End) { // End键跳转到最后一行
        QModelIndex nextIndex = m_pMyTableView->model()->index(m_pMyTableView->model()->rowCount()-1, 0);
        m_pMyTableView->setCurrentIndex(nextIndex);

        return;
    }
    if(event->key() == Qt::Key_PageUp) { // PageUp键向上翻页
        m_curScrollPos = m_pMyTableView->verticalScrollBar()->value();
        if(m_curScrollPos > 0)
            m_pMyTableView->verticalScrollBar()->setSliderPosition(m_curScrollPos - m_pageHeight);
        return;
    }
    if(event->key() == Qt::Key_PageDown) { // PageUp键向下翻页
        int maxValue = m_pMyTableView->verticalScrollBar()->maximum(); // 当前scroller最大显示值
        m_curScrollPos = m_pMyTableView->verticalScrollBar()->value(); // 获得当前scroller值
        if(m_curScrollPos < maxValue)
            m_pMyTableView->verticalScrollBar()->setSliderPosition(m_pageHeight + m_curScrollPos);
        return;
    }
    else
        event->ignore(); // 不加上这句，其它键盘事件会失效
}

