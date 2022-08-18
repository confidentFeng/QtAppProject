#include "MainWidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    // 初始化界面
    this->setFixedSize(800, 600);
    //this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    // 初始化颜色选择界面
    m_pColorSelWidget = new ColorSelWidget;

    // 初始化窗口部件
    m_pBtnClor = new QPushButton;
    m_pBtnClor->setFixedSize(76, 24);
    m_pBtnClor->setText("颜色");
    connect(m_pBtnClor, &QPushButton::clicked, [=]{
        m_pColorSelWidget->showDialog();
    });

    // 主布局
    QVBoxLayout *pLayoutMain = new QVBoxLayout(this);
    pLayoutMain->addStretch();
    pLayoutMain->addWidget(m_pBtnClor, 0, Qt::AlignCenter);
    pLayoutMain->addStretch();
    pLayoutMain->setMargin(0);
}

MainWidget::~MainWidget()
{
}

