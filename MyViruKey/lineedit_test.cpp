#include "lineedit_test.h"
#include <QMouseEvent>

LineEdit_test::LineEdit_test(QWidget *parent) :
    QLineEdit(parent)
{

}


void LineEdit_test::mousePressEvent(QMouseEvent *e)
{
    curTextSignal(this->text(), this->objectName());
    return QLineEdit::mousePressEvent(e);
}

void LineEdit_test::setTextSlot(const QString &text, const QString &ObjName)
{
    if(ObjName==this->objectName())
        this->setText(text);
}

