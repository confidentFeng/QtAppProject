#include "FlatUiWidget.h"

FlatUiWidget::FlatUiWidget(QWidget *parent) : QWidget(parent)
{
    // 初始化主界面
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setFixedSize(STACK_WIDTH, STACK_HEIGHT);
    this->setObjectName("FlatUiWidget");

    // 按钮
    m_pBtn1 = new QPushButton;
    m_pBtn2 = new QPushButton;
    m_pBtn3 = new QPushButton;
    m_pBtn4 = new QPushButton;
    m_pBtn1->setFixedSize(150, 36);
    m_pBtn2->setFixedSize(150, 36);
    m_pBtn3->setFixedSize(150, 36);
    m_pBtn4->setFixedSize(150, 36);
    FlatUI::setPushButtonQss(m_pBtn1);
    FlatUI::setPushButtonQss(m_pBtn2, 8, 14, "#1ABC9C", "#E6F8F5", "#2EE1C1", "#FFFFFF", "#16A086", "#A7EEE6");
    FlatUI::setPushButtonQss(m_pBtn3, 8, 14, "#3498DB", "#FFFFFF", "#5DACE4", "#E5FEFF", "#2483C7", "#A0DAFB");
    FlatUI::setPushButtonQss(m_pBtn4, 8, 14, "#E74C3C", "#FFFFFF", "#EC7064", "#FFF5E7", "#DC2D1A", "#F5A996");
    // 按钮分组框
    m_pGroupBtn = new QGroupBox;
    m_pGroupBtn->setFixedHeight(80);
    // 按钮分组框布局
    QHBoxLayout *pLayoutBtn = new QHBoxLayout(m_pGroupBtn);
    pLayoutBtn->addStretch();
    pLayoutBtn->addWidget(m_pBtn1);
    pLayoutBtn->addStretch();
    pLayoutBtn->addWidget(m_pBtn2);
    pLayoutBtn->addStretch();
    pLayoutBtn->addWidget(m_pBtn3);
    pLayoutBtn->addStretch();
    pLayoutBtn->addWidget(m_pBtn4);
    pLayoutBtn->addStretch();
    pLayoutBtn->setSpacing(0);
    pLayoutBtn->setMargin(0);

    // 编辑框
    m_pEdit1 = new QLineEdit;
    m_pEdit2 = new QLineEdit;
    m_pEdit3 = new QLineEdit;
    m_pEdit4 = new QLineEdit;
    m_pEdit1->setFixedSize(150, 36);
    m_pEdit2->setFixedSize(150, 36);
    m_pEdit3->setFixedSize(150, 36);
    m_pEdit4->setFixedSize(150, 36);
    FlatUI::setLineEditQss(m_pEdit1);
    FlatUI::setLineEditQss(m_pEdit2, 5, 14, "#1ABC9C", 2, "#DCE4EC", "#1ABC9C");
    FlatUI::setLineEditQss(m_pEdit3, 3, 14, "#3498DB", 1, "#DCE4EC", "#3498DB");
    FlatUI::setLineEditQss(m_pEdit4, 3, 14, "#E74C3C", 1, "#DCE4EC", "#E74C3C");
    // 编辑框分组框
    m_pGroupEdit = new QGroupBox;
    m_pGroupEdit->setFixedHeight(80);
    // 编辑框分组框布局
    QHBoxLayout *pLayoutEdit = new QHBoxLayout(m_pGroupEdit);
    pLayoutEdit->addStretch();
    pLayoutEdit->addWidget(m_pEdit1);
    pLayoutEdit->addStretch();
    pLayoutEdit->addWidget(m_pEdit2);
    pLayoutEdit->addStretch();
    pLayoutEdit->addWidget(m_pEdit3);
    pLayoutEdit->addStretch();
    pLayoutEdit->addWidget(m_pEdit4);
    pLayoutEdit->addStretch();
    pLayoutEdit->setSpacing(0);
    pLayoutEdit->setMargin(0);

    // 勾选框
    m_pCheckBox1 = new QCheckBox(this);
    m_pCheckBox2 = new QCheckBox(this);
    m_pCheckBox3 = new QCheckBox(this);
    m_pCheckBox4 = new QCheckBox(this);
    // 勾选框分组框
    m_pGroupCheck = new QGroupBox;
    m_pGroupCheck->setFixedHeight(80);
    // 勾选框布局
    QHBoxLayout *pLayoutCheckBox = new QHBoxLayout(m_pGroupCheck);
    pLayoutCheckBox->addStretch();
    pLayoutCheckBox->addWidget(m_pCheckBox1);
    pLayoutCheckBox->addStretch();
    pLayoutCheckBox->addWidget(m_pCheckBox2);
    pLayoutCheckBox->addStretch();
    pLayoutCheckBox->addWidget(m_pCheckBox3);
    pLayoutCheckBox->addStretch();
    pLayoutCheckBox->addWidget(m_pCheckBox4);
    pLayoutCheckBox->addStretch();
    pLayoutCheckBox->setSpacing(0);
    pLayoutCheckBox->setMargin(0);

    // 单选框
    m_pRadioBtn1 = new QRadioButton;
    m_pRadioBtn2 = new QRadioButton;
    m_pRadioBtn3 = new QRadioButton;
    m_pRadioBtn4 = new QRadioButton;
    // 设置样式表
    FlatUI::setRadioButtonQss(m_pRadioBtn1);
    FlatUI::setRadioButtonQss(m_pRadioBtn2, 8, "#D7DBDE", "#1ABC9C");
    FlatUI::setRadioButtonQss(m_pRadioBtn3, 8, "#D7DBDE", "#3498DB");
    FlatUI::setRadioButtonQss(m_pRadioBtn4, 8, "#D7DBDE", "#E74C3C");
    // 单选框分组框
    m_pGroupRadioBtn = new QGroupBox;
    m_pGroupRadioBtn->setFixedHeight(80);
    // 单选框布局
    QHBoxLayout *pLayoutRadioBtn = new QHBoxLayout(m_pGroupRadioBtn);
    pLayoutRadioBtn->addStretch();
    pLayoutRadioBtn->addWidget(m_pRadioBtn1);
    pLayoutRadioBtn->addStretch();
    pLayoutRadioBtn->addWidget(m_pRadioBtn2);
    pLayoutRadioBtn->addStretch();
    pLayoutRadioBtn->addWidget(m_pRadioBtn3);
    pLayoutRadioBtn->addStretch();
    pLayoutRadioBtn->addWidget(m_pRadioBtn4);
    pLayoutRadioBtn->addStretch();
    pLayoutRadioBtn->setSpacing(0);
    pLayoutRadioBtn->setMargin(0);

    // 初始化进度条1
    m_pProBar1 = new QProgressBar;
    m_pProBar1->setRange(0, 100); // 设置进度条最小值和最大值(取值范围)
    m_pProBar1->setValue(50);  // 设置当前的运行值
    m_pProBar1->setOrientation(Qt::Horizontal);  // 水平方向
    //m_pProBar1->setTextVisible(false); // 隐藏进度条文本（会导致与滑动条的值同步有点问题）
    m_pProBar1->setFixedSize(300, 16);   // 进度条固定大小
    m_pProBar1->setInvertedAppearance(false); // true:反方向  false:正方向
    // 初始化进度条2
    m_pProBar2 = new QProgressBar;
    m_pProBar2->setRange(0, 100); // 设置进度条最小值和最大值(取值范围)
    m_pProBar2->setValue(50);  // 设置当前的运行值
    m_pProBar2->setOrientation(Qt::Horizontal);  // 水平方向
    //m_pProBar2->setTextVisible(false); // 隐藏进度条文本
    m_pProBar2->setFixedSize(300, 16);   // 进度条固定大小
    m_pProBar2->setInvertedAppearance(false); // true:反方向  false:正方向
    // 初始化滑动条1
    m_pSlider1 = new QSlider;
    m_pSlider1->setOrientation(Qt::Horizontal);  // 水平方向
    m_pSlider1->setMinimum(0);  // 最小值
    m_pSlider1->setMaximum(100);  // 最大值
    m_pSlider1->setSingleStep(1);  // 步长
    m_pSlider1->setFixedWidth(300); // 设置固定宽度，高度由样式表设置
    m_pSlider1->setValue(50);
    // 初始化数字滑动条2
    m_pSlider2 = new QSlider;
    m_pSlider2->setOrientation(Qt::Horizontal);  // 水平方向
    m_pSlider2->setMinimum(0);  // 最小值
    m_pSlider2->setMaximum(100);  // 最大值
    m_pSlider2->setSingleStep(1);  // 步长
    m_pSlider2->setFixedWidth(300); // 设置固定宽度，高度由样式表设置
    m_pSlider2->setValue(50);
    // 设置样式表
    FlatUI::setProgressQss(m_pProBar1);
    FlatUI::setProgressQss(m_pProBar2, 8, 5, 9, "#E8EDF2", "#1ABC9C");
    FlatUI::setSliderQss(m_pSlider1);
    FlatUI::setSliderQss(m_pSlider2, 10, "#E8EDF2", "#E74C3C", "#E74C3C");
    // 分组框
    m_pGroupSlider = new QGroupBox;
    m_pGroupSlider->setFixedHeight(80);
    // 布局
    QGridLayout *pLayoutSlider = new QGridLayout(m_pGroupSlider);
    pLayoutSlider->addWidget(m_pProBar1, 0, 0);
    pLayoutSlider->addWidget(m_pProBar2, 0, 1);
    pLayoutSlider->addWidget(m_pSlider1, 1, 0);
    pLayoutSlider->addWidget(m_pSlider2, 1, 1);
    pLayoutSlider->setAlignment(Qt::AlignHCenter);
    pLayoutSlider->setSpacing(16);
    pLayoutSlider->setMargin(0);

    // 滚动条
    m_pScrollBar = new QScrollBar;
    m_pScrollBar->setOrientation(Qt::Horizontal);  // 水平方向
    m_pScrollBar->setMinimum(0);  // 最小值
    m_pScrollBar->setMaximum(300);  // 最大值
    m_pScrollBar->setSingleStep(10);  // 步长
    m_pScrollBar->setFixedWidth(600); // 设置固定高度，宽度由样式表设置
    FlatUI::setScrollBarQss(m_pScrollBar, 8, 120, 20, "#606060", "#34495E", "#1ABC9C", "#E74C3C");
    // 滚动条分组框
    m_pGroupScrollBar = new QGroupBox;
    m_pGroupScrollBar->setFixedHeight(80);
    // 滚动条布局
    QVBoxLayout *pLayoutScrollBar = new QVBoxLayout(m_pGroupScrollBar);
    pLayoutScrollBar->addStretch();
    pLayoutScrollBar->addWidget(m_pScrollBar);
    pLayoutScrollBar->addStretch();
    pLayoutScrollBar->setSpacing(0);
    pLayoutScrollBar->setContentsMargins(32, 0, 12, 0);

    // 主布局
    QVBoxLayout *pLayoutMain = new QVBoxLayout(this);
    pLayoutMain->addStretch();
    pLayoutMain->addWidget(m_pGroupBtn);
    pLayoutMain->addStretch();
    pLayoutMain->addWidget(m_pGroupEdit);
    pLayoutMain->addStretch();
    pLayoutMain->addWidget(m_pGroupCheck);
    pLayoutMain->addStretch();
    pLayoutMain->addWidget(m_pGroupRadioBtn);
    pLayoutMain->addStretch();
    pLayoutMain->addWidget(m_pGroupSlider);
    pLayoutMain->addStretch();
    pLayoutMain->addWidget(m_pGroupScrollBar);
    pLayoutMain->addStretch();
    pLayoutMain->setSpacing(0);
    pLayoutMain->setContentsMargins(12, 0, 12, 0);

    // 统一设置需要被翻译的文本
    translateUI();

    // 滑动条信号槽
//    connect(m_pSlider1, &QSlider::valueChanged, [=](int value) {
//        //m_pSlider->setValue(value);
//        m_pProBar1->setValue(value);
//    });
//    connect(m_pSlider2, &QSlider::valueChanged, [=](int value) {
//        //m_pCustomSliderNum->setValue(value);
//        m_pProBar2->setValue(value);
//    });

    connect(m_pSlider1, SIGNAL(valueChanged(int)), m_pProBar1, SLOT(setValue(int)));
    connect(m_pSlider2, SIGNAL(valueChanged(int)), m_pProBar2, SLOT(setValue(int)));
}

// 统一设置需要被翻译的文本
void FlatUiWidget::translateUI()
{
    m_pBtn1->setText(tr("测试文本"));
    m_pBtn2->setText(tr("测试文本"));
    m_pBtn3->setText(tr("测试文本"));
    m_pBtn4->setText(tr("测试文本"));
    m_pGroupBtn->setTitle(tr("按钮"));

    m_pGroupEdit->setTitle(tr("编辑框"));
    m_pGroupCheck->setTitle(tr("勾选框"));
    m_pGroupRadioBtn->setTitle(tr("单选框"));
    m_pGroupSlider->setTitle(tr("滑动条与进度条"));
    m_pGroupScrollBar->setTitle(tr("滚动条"));
}
