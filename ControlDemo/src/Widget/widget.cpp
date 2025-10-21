#include "widget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // 设置当前界面的固定宽高为400x400
    this->setFixedSize(400, 400);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setObjectName("Widget");
    this->setStyleSheet("QWidget#Widget{background: rgba(51, 51, 51, 0.5)}");

    // 初始化消息框
    m_message = new QLabel(this);
    m_message->setAlignment(Qt::AlignCenter);
    m_message->setWordWrap(true);
    m_message->setFocusPolicy(Qt::NoFocus);
    m_message->setObjectName("message");
    m_message->setStyleSheet("QLabel#message{background-color:#30cc30;color:#ffffff;font-size:20px;font-style:'Microsoft YaHei';border:0px;}");

    // 初始化输入框
    m_msgEdit = new QLineEdit(this);

    // 初始化按钮
    m_successBtn = new QPushButton("🚀Alert Success", this);
    connect(m_successBtn, &QPushButton::clicked, [=](){
        if (m_msgEdit->text().isEmpty()) return;
        alertSuccess(m_msgEdit->text());
    });
    m_errorBtn = new QPushButton("👹Alert Error", this);
    connect(m_errorBtn, &QPushButton::clicked, [=](){
        if (m_msgEdit->text().isEmpty()) return;
        alertError(m_msgEdit->text());
    });
    // 将按钮放入水平布局中
    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnLayout->addWidget(m_successBtn);
    btnLayout->addStretch();
    btnLayout->addWidget(m_errorBtn);

    // 初始化正向动画
    m_messageAntF = new QPropertyAnimation(m_message, "geometry");
    m_messageAntF->setStartValue(QRect(0, 0, 400, 0));
    m_messageAntF->setEndValue(QRect(0, 0, 400, 40));
    m_messageAntF->setDuration(300);

    // 初始化反向动画
    m_messageAntB = new QPropertyAnimation(m_message, "geometry");
    m_messageAntB->setStartValue(QRect(0, 0, 400, 40));
    m_messageAntB->setEndValue(QRect(0, 0, 400, 0));
    m_messageAntB->setDuration(300);

    // 将上面两个动画组合成动画组
    m_messageAntG = new QSequentialAnimationGroup(this);
    m_messageAntG->addAnimation(m_messageAntF);
    m_messageAntG->addPause(2000);
    m_messageAntG->addAnimation(m_messageAntB);

    // 初始化布局
    QVBoxLayout *vLayout = new QVBoxLayout(this);
//    vLayout->addWidget(m_message);
    vLayout->addStretch();
    vLayout->addWidget(m_msgEdit);
    vLayout->addLayout(btnLayout);
    this->setLayout(vLayout);
}


void Widget::alertSuccess(const QString& text)
{
    m_message->raise();
    m_message->setStyleSheet("QLabel#message{background-color:#30cc30;color:#ffffff;font-size:20px;font-style:'Microsoft YaHei';border:0px;}");
    m_message->setText(text);
    m_messageAntG->start();
}

void Widget::alertError(const QString& text)
{
    m_message->raise();
    m_message->setStyleSheet("QLabel#message{background-color:#cc3030;color:#ffffff;font-size:20px;font-style:'Microsoft YaHei';border:0px;}");
    m_message->setText(text);
    m_messageAntG->start();
}

Widget::~Widget()
{
}

