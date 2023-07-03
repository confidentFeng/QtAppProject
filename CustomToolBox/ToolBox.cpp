#include "ToolBox.h"

ToolBox::ToolBox(QWidget *parent) : QWidget(parent),
    m_pLayoutContent(nullptr)
{
    // 初始化主界面
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setFixedSize(362, 535);
    this->setObjectName("ToolBox");

    // 内容布局，用于添加ToolPage
    m_pLayoutContent = new QVBoxLayout;
    m_pLayoutContent->setSpacing(0);
    m_pLayoutContent->setMargin(0);

    // 背景子界面
    m_pWidgetBack = new QWidget(); //子部件
    m_pWidgetBack->setFixedSize(width(), height());
    m_pWidgetBack->setObjectName("ToolBox_WidgetBack");
    // 背景子界面布局
    QVBoxLayout *vBoxLayout = new QVBoxLayout(m_pWidgetBack);
    vBoxLayout->addLayout(m_pLayoutContent);
    vBoxLayout->addStretch();
    vBoxLayout->setSpacing(0);
    vBoxLayout->setMargin(0);

    // 主布局
    QVBoxLayout *pLayoutMain = new QVBoxLayout(this);
    // 滚动区域
    m_pScrollArea = new QScrollArea(this) ;
    m_pScrollArea->setObjectName("ToolBox_ScrollArea");
    m_pScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 隐藏横向滚动条
    m_pScrollArea->setWidget(m_pWidgetBack); // 设置滚动部件
    pLayoutMain->addWidget(m_pScrollArea); // 添加QScrollArea布局
    pLayoutMain->setSpacing(0);
    pLayoutMain->setMargin(0);
}

void ToolBox::addWidget(const QString &title, QWidget *widget)
{
    ToolPage *page = new ToolPage(this);
    page->addWidget(title, widget);

    m_pLayoutContent->addWidget(page);
}
