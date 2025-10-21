#include "CustomCheckWidget.h"

CustomCheckWidget::CustomCheckWidget(QWidget *parent) : QWidget(parent)
{
    // 初始化界面
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setFixedSize(STACK_WIDTH, STACK_HEIGHT);
    this->setObjectName("CustomBtnWidget");

    // 勾选框1
    m_pCheckBox1 = new QCheckBox;
    m_pCheckBox1->setObjectName("CustomCheckWidget_CheckBox1");
    m_pCheckBox1->setCursor(QCursor(QPixmap(CURSOR_HAND)));
    // 勾选框2
    m_pCheckBox2 = new QCheckBox;
    m_pCheckBox2->setObjectName("CustomCheckWidget_CheckBox2");
    m_pCheckBox2->setCursor(QCursor(QPixmap(CURSOR_HAND)));
    m_pCheckBox2->setText("选项");
    // 分组框
    m_pGroupCheck = new QGroupBox;
    m_pGroupCheck->setFixedSize(STACK_WIDTH-160, 120);
    m_pGroupCheck->setTitle(tr("勾选框"));
    // 布局
    QHBoxLayout *pLayoutCheck = new QHBoxLayout(m_pGroupCheck);
    pLayoutCheck->addStretch();
    pLayoutCheck->addWidget(m_pCheckBox1);
    pLayoutCheck->addStretch();
    pLayoutCheck->addWidget(m_pCheckBox2);
    pLayoutCheck->addStretch();
    pLayoutCheck->setMargin(0);

    // 单选框
    m_pRadioBtn1 = new QRadioButton;
    m_pRadioBtn2 = new QRadioButton;
    m_pRadioBtn3 = new QRadioButton;
    m_pRadioBtn4 = new QRadioButton;
    m_pRadioBtn1->setCursor(QCursor(QPixmap(CURSOR_HAND)));
    m_pRadioBtn2->setCursor(QCursor(QPixmap(CURSOR_HAND)));
    m_pRadioBtn3->setCursor(QCursor(QPixmap(CURSOR_HAND)));
    m_pRadioBtn4->setCursor(QCursor(QPixmap(CURSOR_HAND)));
    m_pRadioBtn1->setChecked(true);
    // 设置样式表
    FlatUI::setRadioButtonQss(m_pRadioBtn1);
    FlatUI::setRadioButtonQss(m_pRadioBtn2, 8, "#D7DBDE", "#1ABC9C");
    FlatUI::setRadioButtonQss(m_pRadioBtn3, 8, "#D7DBDE", "#3498DB");
    FlatUI::setRadioButtonQss(m_pRadioBtn4, 8, "#D7DBDE", "#E74C3C");
    // 单选框分组框
    m_pGroupRadioBtn = new QGroupBox;
    m_pGroupRadioBtn->setFixedSize(STACK_WIDTH-160, 120);
    m_pGroupRadioBtn->setTitle(tr("单选框"));
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

    // 主布局
    QVBoxLayout *pLayoutMain = new QVBoxLayout(this);
    pLayoutMain->addStretch();
    pLayoutMain->addWidget(m_pGroupCheck, 0, Qt::AlignHCenter);
    pLayoutMain->addStretch();
    pLayoutMain->addWidget(m_pGroupRadioBtn, 0, Qt::AlignHCenter);
    pLayoutMain->addStretch();
//    pLayoutMain->addWidget(m_pGroupEye, 0, Qt::AlignHCenter);
//    pLayoutMain->addStretch();
    pLayoutMain->setSpacing(0);
    pLayoutMain->setMargin(0);
}
