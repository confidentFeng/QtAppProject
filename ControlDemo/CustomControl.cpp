#include "CustomControl.h"

CustomControl::CustomControl(QWidget *parent)
    : QWidget(parent)
{
    // 主界面初始化
    //this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(1280, 720);
    this->setStyleSheet("QWidget#MainWidget{background:transparent;}");

    // 创建数据显示列表
    QStringList list;
    list.append("标签");
    list.append("按钮");
    list.append("编辑框");
    list.append("勾选框与单选框");
    list.append("滑动条与进度条");
    // 创建QListView对象
    m_pListView = new QListView;
    m_pListView->setObjectName("MainWidget_ListView");
    m_pListView->setFixedSize(208, 150*list.count()+4); // 必须加上边框：4px
    m_pListView->setResizeMode(QListView::Adjust);
    m_pListView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // 使用数据列表创建数据显示模型
    QStringListModel *listmodel = new QStringListModel(list);
    m_pListView->setModel(listmodel); // 设置模型到listview上

    // 自定义标签界面
    m_pCustomLabWidget = new CustomLabWidget;
    // 自定义按钮界面
    m_pCustomBtnWidget = new CustomBtnWidget;
    // 自定义编辑框界面
    m_pCustomEidtWidget = new CustomEidtWidget;
    // 自定义勾选框界面
    m_pCustomCheckWidget = new CustomCheckWidget;
    // 自定义滑动条界面
    m_pCustomSliderWidget = new CustomSliderWidget;

    // 堆栈窗口
    m_pStackedWidget = new QStackedWidget;
    m_pStackedWidget->setFixedSize(STACK_WIDTH, STACK_HEIGHT);
    // 堆栈界面添加子界面
    m_pStackedWidget->addWidget(m_pCustomLabWidget);
    m_pStackedWidget->addWidget(m_pCustomBtnWidget);
    m_pStackedWidget->addWidget(m_pCustomEidtWidget);
    m_pStackedWidget->addWidget(m_pCustomCheckWidget);
    m_pStackedWidget->addWidget(m_pCustomSliderWidget);

    // 内容布局
    QHBoxLayout *pLayoutContent = new QHBoxLayout;
    pLayoutContent->addWidget(m_pListView, 0, Qt::AlignTop);
    pLayoutContent->addSpacing(16);
    pLayoutContent->addWidget(m_pStackedWidget);
    pLayoutContent->addStretch();
    pLayoutContent->setSpacing(0);
    pLayoutContent->setMargin(0);

    // 主布局
    QVBoxLayout *pLayoutMain = new QVBoxLayout(this);
    pLayoutMain->addLayout(pLayoutContent);
    pLayoutMain->addStretch();
    pLayoutMain->setSpacing(0);
    pLayoutMain->setMargin(0);

    // 信号槽连接
    connect(m_pListView, &QListView::clicked, [=](const QModelIndex &index) {
        m_pStackedWidget->setCurrentIndex(index.row());
    });
}


