#include "myVirtualKeyboard_qBtn.h"
#include <QMouseEvent>
#include "myVirtualKeyboard_qProxystyle.h"
//#include <QDebug>
#include <QTimer>//控制连续点击按钮的效果


MyVirtualKeyBoard_qBtn::MyVirtualKeyBoard_qBtn(QWidget *parent) : QPushButton(parent)
{
    timer_ = new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(updatePressStatus()));

    is_press_on_timer_ = new QTimer(this);
    connect(is_press_on_timer_, SIGNAL(timeout()), this, SLOT(pressOnSlot()));

    this->setStyle(new MyVirtualKeyboard_qProxyStyle);
    this->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
}

void MyVirtualKeyBoard_qBtn::setText(const QString &text)
{
    QPushButton::setText(text);

    this->style()->unpolish(this);
    this->style()->polish(this);
    this->update();
}

void MyVirtualKeyBoard_qBtn::mousePressEvent(QMouseEvent *event)
{
    is_press_on_timer_->start(100);
    return QPushButton::mousePressEvent(event);
}


void MyVirtualKeyBoard_qBtn::mouseReleaseEvent(QMouseEvent *event)
{
    is_press_on_=false;
    if(is_press_on_timer_->isActive())
        is_press_on_timer_->stop();

    pos2_ = event->pos();
    if(this->rect().contains(pos2_))
    {
        if(is_ok_)
        {
            is_ok_ = false;
            timer_->start(100);//限制连续点击速度
            emit clicked(this->text());
        }
    }
QPushButton::mouseReleaseEvent(event);
}


void MyVirtualKeyBoard_qBtn::updatePressStatus()
{
    is_ok_ = true;
    timer_->stop();
}

void MyVirtualKeyBoard_qBtn::pressOnSlot()
{
    if(is_press_on_)emit clicked(this->text());//模拟连续点击
    is_press_on_=true;
}


