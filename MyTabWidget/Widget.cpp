#include "Widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // 界面初始化
    this->setFixedSize(320, 200);
    this->setFocusPolicy(Qt::StrongFocus);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("MeetUserList");

    // 初始化选项卡界面
    m_pTabWidget = new QTabWidget(this);
    m_pTabWidget->setFixedSize(width(), height());
    m_pTabWidget->tabBar()->setStyle(new CustomTabStyle); // 实现TabBar的文本左对齐
    m_pTabWidget->setTabsClosable(true);  // 将关闭按钮自动添加到每个选项卡
    m_pTabWidget->setMovable(true); // 设置用户是否可以在选项卡栏区域内移动选项卡，默认为false

    // 初始化子界面1
    m_pWidget1 = new QWidget;
    QFormLayout *pFormLayout = new QFormLayout(m_pWidget1);
    pFormLayout->addRow("姓名", new QLineEdit());
    pFormLayout->addRow("地址", new QLineEdit());

    // 初始化子界面2
    m_pWidget2 = new QWidget;
    QHBoxLayout *pHBoxLayout2 = new QHBoxLayout(m_pWidget2);
    pHBoxLayout2->addWidget(new QRadioButton("男"));
    pHBoxLayout2->addWidget(new QRadioButton("女"));

    // 初始化子界面3
    m_pWidget3 = new QWidget;
    QHBoxLayout *pHBoxLayout3 = new QHBoxLayout(m_pWidget3);
    pHBoxLayout3->addWidget(new QCheckBox("物理"));
    pHBoxLayout3->addWidget(new QCheckBox("化学"));

    // 添加各子界面
    m_pTabWidget->addTab(m_pWidget1, "联系方式");
    m_pTabWidget->addTab(m_pWidget2, "个人信息");
    m_pTabWidget->addTab(m_pWidget3, "科目");

    // 当点击第参数个选项卡的关闭按钮的时候，发出信号
    connect(m_pTabWidget->tabBar(), &QTabBar::tabCloseRequested, [=](int index){
        if (index == -1)
            return;

        // 移除Tab
        m_pTabWidget->removeTab(index);
    });

    // 当双击第参数个选项卡的时候，发出信号
    connect(m_pTabWidget->tabBar(), &QTabBar::tabBarDoubleClicked, [=](int index){
        if (index == -1)
            return;

        // 移除Tab
        m_pTabWidget->removeTab(index);
    });
}
