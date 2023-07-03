#include "Form.h"

Form::Form(QWidget *parent, QStringList btnNameList) :
    QWidget(parent)
{
    // 初始化界面
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setFixedWidth(362);
    this->setObjectName("Form");
    this->setStyleSheet("QWidget#Form{background:transparent;}");

    // 按钮组
    m_pGroupBox = new QButtonGroup;
    m_pGroupBox->setExclusive(true); // 启用互斥

    // 主布局
    m_pLayoutMain = new QVBoxLayout(this);
    m_pLayoutMain->setSpacing(0);
    m_pLayoutMain->setMargin(0);

    // 设置按钮列表
    for (auto item : btnNameList) {
        QPushButton *pBtn = new QPushButton;
        pBtn->setObjectName("Common_BtnBlue");
        pBtn->setFixedSize(width(), 30);
        pBtn->setText(item);
        pBtn->setCheckable(true);
        m_pGroupBox->addButton(pBtn);
        m_pLayoutMain->addWidget(pBtn);

        // 方便取消选中其他界面的按钮
        connect(pBtn, &QPushButton::clicked, [=] {
            emit sigChecked();
        });
    }

    // 其他按钮：方便取消选中显示按钮
    m_pBtnOther = new QPushButton;
    m_pBtnOther->setCheckable(true);
    m_pGroupBox->addButton(m_pBtnOther);

    // 自适应高度
    this->setFixedHeight(30*btnNameList.count());
}

// 取消所有按钮的选中状态
void Form::setUncheckAll()
{
    m_pBtnOther->setChecked(true);
}
