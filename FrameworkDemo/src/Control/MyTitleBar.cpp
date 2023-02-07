#include "MyTitleBar.h"

MyTitleBar::MyTitleBar(QWidget *parent) : QWidget(parent)
{
    // 界面初始化
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("MyTitleBar");

    // 窗口部件初始化
    m_pLabTitle = new QLabel;
    m_pBtnClose = new QPushButton;
    m_pLabTitle->setObjectName("Common_14pxText");
    m_pBtnClose->setObjectName("MyTitleBar_BtnClose");
    m_pBtnClose->setFixedSize(30, 30);
    m_pBtnClose->setCursor(QCursor(QPixmap(":/Image/Util/icon_cursorHand.png")));

    // 主布局
    QHBoxLayout *pHLayoutMain = new QHBoxLayout(this);
    pHLayoutMain->addSpacing(20);
    pHLayoutMain->addWidget(m_pLabTitle);
    pHLayoutMain->addStretch();
    pHLayoutMain->addWidget(m_pBtnClose);
    pHLayoutMain->setMargin(0);

    // 关闭按钮
    connect(m_pBtnClose, &QPushButton::clicked, [=]() {
        emit sigClose();
    });
}

// 设置标题名称
void MyTitleBar::setTitleName(const QString &sText)
{
    m_pLabTitle->setText(sText);
}

// 获取标题名称
QString MyTitleBar::getTitleName()
{
    return m_pLabTitle->text();
}

// 隐藏关闭按钮
void MyTitleBar::hideCloseBtn(const bool &isHide)
{
    if(isHide)
        m_pBtnClose->hide();
    else
        m_pBtnClose->show();
}
