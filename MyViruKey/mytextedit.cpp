#include "mytextedit.h"


mytextEdit::mytextEdit(QWidget *parent) : QTextEdit(parent)
{

}

void mytextEdit::mousePressEvent(QMouseEvent *e)
{
    curTextSignal(this->toPlainText(), this->objectName());
    return QTextEdit::mousePressEvent(e);
}

void mytextEdit::setTextSlot(const QString &text, const QString &ObjName)
{
    if(this->objectName()==ObjName)
        this->setText(text);
}

