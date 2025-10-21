#include "CustomSliderWidget.h"

CustomSliderWidget::CustomSliderWidget(QWidget *parent) : QWidget(parent)
{
    // 初始化界面
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setFixedSize(STACK_WIDTH, STACK_HEIGHT);
    this->setObjectName("CustomBtnWidget");

    // 初始化数字滑动条
    m_pCustomSliderNum = new CustomSliderNum;
    m_pCustomSliderNum->setOrientation(Qt::Horizontal);  // 水平方向
    m_pCustomSliderNum->setMinimum(0);  // 最小值
    m_pCustomSliderNum->setMaximum(100);  // 最大值
    m_pCustomSliderNum->setSingleStep(1);  // 步长
    m_pCustomSliderNum->setFixedSize(500, 70); // 设置固定宽高，高度设置大一些，让数字显示出来
    m_pCustomSliderNum->setValue(50);
    // 初始化滑动条
    m_pSlider = new QSlider;
    m_pSlider->setOrientation(Qt::Horizontal);  // 水平方向
    m_pSlider->setMinimum(0);  // 最小值
    m_pSlider->setMaximum(100);  // 最大值
    m_pSlider->setSingleStep(1);  // 步长
    m_pSlider->setFixedWidth(500); // 设置固定宽度，高度由样式表设置
    m_pSlider->setValue(50);
    m_pSlider->setCursor(QCursor(QPixmap(CURSOR_HAND)));
    // 分组框
    m_pGroupSlider = new QGroupBox;
    m_pGroupSlider->setFixedSize(STACK_WIDTH-160, 140);
    m_pGroupSlider->setTitle(tr("滑动条"));
    // 布局
    QVBoxLayout *pLayoutSlider = new QVBoxLayout(m_pGroupSlider);
    pLayoutSlider->addStretch();
    pLayoutSlider->addWidget(m_pCustomSliderNum);
    pLayoutSlider->addStretch();
    pLayoutSlider->addWidget(m_pSlider);
    pLayoutSlider->addStretch();
    pLayoutSlider->setAlignment(Qt::AlignHCenter);
    pLayoutSlider->setSpacing(0);
    pLayoutSlider->setMargin(0);

    // 初始化进度条
    m_pProg = new QProgressBar;
    m_pProg->setRange(0, 100); // 设置进度条最小值和最大值(取值范围)
    m_pProg->setValue(50);  // 设置当前的运行值
    m_pProg->setOrientation(Qt::Horizontal);  // 水平方向
    m_pProg->setTextVisible(false); // 隐藏进度条文本
    m_pProg->setFixedSize(500, 16);   // 进度条固定大小
    m_pProg->setInvertedAppearance(false); // true:反方向  false:正方向
    // 初始化加载进度条
    m_pProgLoad = new QProgressBar;
    m_pProgLoad->setOrientation(Qt::Horizontal);  // 水平方向
    m_pProgLoad->setTextVisible(false); // 隐藏进度条文本
    m_pProgLoad->setFixedSize(500, 16);   // 进度条固定大小
    m_pProgLoad->setMinimum(0); // 将进度条控件的最大值、最小值都设置为0时，可以显示忙碌状态，从而替代百分比表示的进度
    m_pProgLoad->setMaximum(0);
    // 分组框
    m_pGroupProg = new QGroupBox;
    m_pGroupProg->setFixedSize(STACK_WIDTH-160, 140);
    m_pGroupProg->setTitle(tr("进度条"));
    // 布局
    QVBoxLayout *pLayoutProg = new QVBoxLayout(m_pGroupProg);
    pLayoutProg->addStretch();
    pLayoutProg->addWidget(m_pProg);
    pLayoutProg->addStretch();
    pLayoutProg->addWidget(m_pProgLoad);
    pLayoutProg->addStretch();
    pLayoutProg->setAlignment(Qt::AlignHCenter);
    pLayoutProg->setSpacing(0);
    pLayoutProg->setMargin(0);

    // 主布局
    QVBoxLayout *pLayoutMain = new QVBoxLayout(this);
    pLayoutMain->addStretch();
    pLayoutMain->addWidget(m_pGroupSlider, 0, Qt::AlignHCenter);
    pLayoutMain->addStretch();
    pLayoutMain->addWidget(m_pGroupProg, 0, Qt::AlignHCenter);
    pLayoutMain->addStretch();
    pLayoutMain->setSpacing(0);
    pLayoutMain->setMargin(0);
}
