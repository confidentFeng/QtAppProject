#include "Widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // 初始化界面
    this->setFixedSize(800, 600);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    // 初始化标签
    m_pLabTest = new QLabel;
    m_pLabTest->setText("测试文本");

    // 初始化按钮
    m_pBtnTest = new QPushButton;
    m_pBtnTest->setObjectName("Common_BtnBlue");
    m_pBtnTest->setFixedSize(60, 32);
    m_pBtnTest->setText("按钮");

    // 初始化编辑框
    m_pLineEdit = new QLineEdit;
    m_pLineEdit->setFixedSize(150, 30);
    m_pLineEdit->setText("这是编辑框");

    // 初始化勾选框
    m_pCheckBox = new QCheckBox(this);

    // 初始化滑动条
    m_pSlider = new QSlider;
    m_pSlider->setOrientation(Qt::Horizontal);  // 水平方向
    m_pSlider->setMinimum(0);  // 最小值
    m_pSlider->setMaximum(100);  // 最大值
    m_pSlider->setSingleStep(10);  // 步长
    m_pSlider->setFixedWidth(500); // 设置固定宽度，高度由样式表设置
    m_pSlider->setValue(50);

    // 初始化滚动条
    m_pScrollBar = new QScrollBar;
    m_pScrollBar->setOrientation(Qt::Vertical);  // 垂直方向
    m_pScrollBar->setMinimum(0);  // 最小值
    m_pScrollBar->setMaximum(100);  // 最大值
    m_pScrollBar->setSingleStep(10);  // 步长
    m_pScrollBar->setFixedHeight(500); // 设置固定高度，宽度由样式表设置

    // 初始化进度条
    m_pProBar = new QProgressBar;
    m_pProBar->setRange(0, 100); // 设置进度条最小值和最大值(取值范围)
    m_pProBar->setValue(40);  // 设置当前的运行值
    m_pProBar->setOrientation(Qt::Horizontal);  // 水平方向
    m_pProBar->setTextVisible(false); // 隐藏进度条文本
    m_pProBar->setFixedSize(500, 16);   // 进度条固定大小
    m_pProBar->setInvertedAppearance(false); // true:反方向  false:正方向

    // 标签、按钮布局
    QHBoxLayout *pHLayoutLabel = new QHBoxLayout;
    pHLayoutLabel->addStretch();
    pHLayoutLabel->addWidget(m_pLabTest);
    pHLayoutLabel->addSpacing(24);
    pHLayoutLabel->addWidget(m_pBtnTest);
    pHLayoutLabel->addSpacing(24);
    pHLayoutLabel->addWidget(m_pLineEdit);
    pHLayoutLabel->addSpacing(24);
    pHLayoutLabel->addWidget(m_pCheckBox);
    pHLayoutLabel->addStretch();
    pHLayoutLabel->setSpacing(0);
    // 左侧垂直布局
    QVBoxLayout *pVLayoutLeft = new QVBoxLayout;
    pVLayoutLeft->addSpacing(64);
    pVLayoutLeft->addLayout(pHLayoutLabel);
    pVLayoutLeft->addSpacing(64);
    pVLayoutLeft->addWidget(m_pSlider, 0, Qt::AlignHCenter);
    pVLayoutLeft->addSpacing(64);
    pVLayoutLeft->addWidget(m_pProBar, 0, Qt::AlignHCenter);
    pVLayoutLeft->addStretch();
    pVLayoutLeft->setSpacing(0);
    pVLayoutLeft->setMargin(0);
    // 主布局
    QHBoxLayout *pLayoutMain = new QHBoxLayout(this);
    pLayoutMain->addStretch();
    pLayoutMain->addLayout(pVLayoutLeft);
    pLayoutMain->addStretch();
    pLayoutMain->addWidget(m_pScrollBar);
    pLayoutMain->addStretch();
    pLayoutMain->setSpacing(0);
    pLayoutMain->setMargin(0);
}

Widget::~Widget()
{
}

