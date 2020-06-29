#include "myVirtualKeyboard_qLb.h"
#include <QStyle>
MyVirtualKeyboard_qLb::MyVirtualKeyboard_qLb(QWidget *parent) : QLabel(parent)
{

}

void MyVirtualKeyboard_qLb::setText(const QString &text)
{
    QLabel::setText(text);

    this->style()->unpolish(this);
    this->style()->polish(this);
    this->update();
}

void MyVirtualKeyboard_qLb::clear()
{
    QLabel::setText("");
    this->style()->unpolish(this);
    this->style()->polish(this);
    this->update();
}
