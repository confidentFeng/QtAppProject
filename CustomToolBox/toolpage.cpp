#include "ToolPage.h"

ToolPage::ToolPage(QWidget *parent) : QWidget(parent)
{
    // 初始化主界面
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setFixedWidth(362-10); // 10为QScrollArea的滚动条宽度
    this->setObjectName("ToolPage");

    // 折叠按钮
    m_pBtnFold = new QPushButton;
    m_pBtnFold->setObjectName("ToolPage_BtnFold");
    m_pBtnFold->setCheckable(true);
    m_pBtnFold->setChecked(true);
    m_pBtnFold->setFixedSize(width(), 30);
    // 图标标签
    m_pLabIcon = new QLabel;
    m_pLabIcon->setFixedSize(20, 20);
    m_pLabIcon->setPixmap(QPixmap(":/img/down-arrow.png").scaled(m_pLabIcon->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    // 折叠按钮布局
    QHBoxLayout *layout = new QHBoxLayout(m_pBtnFold);
    layout->addStretch();
    layout->addWidget(m_pLabIcon);
    layout->setSpacing(0);
    layout->setMargin(0);

    // 内容子界面
    m_pWidgetContent = new QWidget;
    m_pWidgetContent->setObjectName("ToolPage_WidgetContent");
    // 内容子界面布局
    m_pLayoutContent = new QVBoxLayout(m_pWidgetContent);
    m_pLayoutContent->setSpacing(0);
    m_pLayoutContent->setMargin(0);

    // 主布局
    QVBoxLayout *pLayoutMain = new QVBoxLayout(this);
    pLayoutMain->addWidget(m_pBtnFold);
    pLayoutMain->addWidget(m_pWidgetContent);
    pLayoutMain->setSpacing(0);
    pLayoutMain->setMargin(0);

    // 信号槽连接
    connect(m_pBtnFold, &QPushButton::clicked, [=]{
        if (m_bIsExpanded) {
            this->collapse();
        } else {
            this->expand();
        }
    });
}

// 添加界面
void ToolPage::addWidget(const QString &title, QWidget *widget)
{
    m_pBtnFold->setText(title);
    m_pLayoutContent->addWidget(widget);
}

void ToolPage::expand()
{
    m_pWidgetContent->show();
    m_bIsExpanded = true;

    m_pLabIcon->setPixmap(QPixmap(":/img/down-arrow.png").scaled(m_pLabIcon->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void ToolPage::collapse()
{
    m_pWidgetContent->hide();
    m_bIsExpanded = false;

    m_pLabIcon->setPixmap(QPixmap(":/img/left-arrow.png").scaled(m_pLabIcon->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}
