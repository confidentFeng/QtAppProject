#include "CustomEidtWidget.h"

CustomEidtWidget::CustomEidtWidget(QWidget *parent) : QWidget(parent)
{
    // 初始化界面
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setFixedSize(STACK_WIDTH, STACK_HEIGHT);
    this->setObjectName("CustomBtnWidget");

    // 普通编辑框
    m_pEditNormal1 = new QLineEdit;
    m_pEditNormal1->setObjectName("CustomEidtWidget_Edit");
    m_pEditNormal1->setFixedSize(300, 40);
    m_pEditNormal1->setMaxLength(30);
    // 密码编辑框
    m_pEditNormal2 = new QLineEdit;
    m_pEditNormal2->setObjectName("CustomEidtWidget_Edit");
    m_pEditNormal2->setFixedSize(300, 40);
    m_pEditNormal2->setMaxLength(30);
    // 分组框
    m_pGroupNormal = new QGroupBox;
    m_pGroupNormal->setFixedSize(STACK_WIDTH-160, 140);
    m_pGroupNormal->setTitle(tr("普通编辑框"));
    // 布局
    QGridLayout *pLayoutNormal = new QGridLayout(m_pGroupNormal);
    pLayoutNormal->addWidget(m_pEditNormal1, 0, 0);
    pLayoutNormal->addWidget(m_pEditNormal2, 1, 0);
    pLayoutNormal->setSpacing(8);
    pLayoutNormal->setMargin(10);

    // 账号编辑框
    m_pEditAccount = new CustomEditIcon;
    m_pEditAccount->setObjectName("CustomEidtWidget_Edit");
    m_pEditAccount->setFixedSize(300, 40);
    m_pEditAccount->setLeftIcon(QIcon(":/Image/Control/icon_user.png"));
    m_pEditAccount->setMaxLength(30);
    m_pEditAccount->setPlaceholderText("请输入账号");
    // 密码编辑框
    m_pEditPasswd = new CustomEditIcon;
    m_pEditPasswd->setObjectName("CustomEidtWidget_Edit");
    m_pEditPasswd->setFixedSize(300, 40);
    m_pEditPasswd->setLeftIcon(QIcon(":/Image/Control/icon_password.png"));
    m_pEditPasswd->setMaxLength(30);
    m_pEditPasswd->setEchoMode(QLineEdit::Password);
    m_pEditPasswd->setPlaceholderText("请输入账号");
    // 分组框
    m_pGroupLogin = new QGroupBox;
    m_pGroupLogin->setFixedSize(STACK_WIDTH-160, 140);
    m_pGroupLogin->setTitle(tr("登录编辑框"));
    // 布局
    QGridLayout *pLayoutLogin = new QGridLayout(m_pGroupLogin);
    pLayoutLogin->addWidget(m_pEditAccount, 0, 0);
    pLayoutLogin->addWidget(m_pEditPasswd, 1, 0);
    pLayoutLogin->setSpacing(8);
    pLayoutLogin->setMargin(10);

    // 自定义密码编辑框
    m_pEditPasswdEye = new CustomEditPasswd;
    m_pEditPasswdEye->setFixedSize(300, 32);
    FlatUI::setLineEditQss(m_pEditPasswdEye, 0, 14, "#000000", 2, "#cfae80", "#cc8729");
    // 分组框
    m_pGroupEye = new QGroupBox;
    m_pGroupEye->setFixedSize(STACK_WIDTH-160, 80);
    m_pGroupEye->setTitle(tr("自定义密码编辑框"));
    // 布局
    QGridLayout *pLayoutEye = new QGridLayout(m_pGroupEye);
    pLayoutEye->addWidget(m_pEditPasswdEye);
    pLayoutEye->setSpacing(8);
    pLayoutEye->setMargin(10);

    // 主布局
    QVBoxLayout *pLayoutMain = new QVBoxLayout(this);
    pLayoutMain->addStretch();
    pLayoutMain->addWidget(m_pGroupNormal, 0, Qt::AlignHCenter);
    pLayoutMain->addStretch();
    pLayoutMain->addWidget(m_pGroupLogin, 0, Qt::AlignHCenter);
    pLayoutMain->addStretch();
    pLayoutMain->addWidget(m_pGroupEye, 0, Qt::AlignHCenter);
    pLayoutMain->addStretch();
    pLayoutMain->setSpacing(0);
    pLayoutMain->setMargin(0);
}
