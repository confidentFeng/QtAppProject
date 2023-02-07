#include "MyIconBtn.h"

MyIconBtn::MyIconBtn(QWidget *parent) : QPushButton(parent)
{

}

// 显示事件
void MyIconBtn::showEvent(QShowEvent *e)
{
    Q_UNUSED(e);

    if(!this->isEnabled()) {
        this->setIcon(QIcon(m_iconDisable));
        return;
    }

    if(!m_isBaseBtn)
        this->setIcon(QIcon(m_iconNormal));
}

// 鼠标移入事件
void MyIconBtn::enterEvent(QEvent *e)
{
    Q_UNUSED(e);

    if(!this->isEnabled()) {
        this->setIcon(QIcon(m_iconDisable));
        return;
    }

    if(!m_isBaseBtn) {
        if(!this->isChecked()) // 未选中了，才有悬浮效果
            this->setIcon(QIcon(m_iconHover));
    }

    this->setCursor(QCursor(QPixmap(":/Image/Util/icon_cursorHand.png")));
}
// 鼠标移出事件
void MyIconBtn::leaveEvent(QEvent *e)
{
    Q_UNUSED(e);

    if(!this->isEnabled()) {
        this->setIcon(QIcon(m_iconDisable));
        return;
    }

    if(!m_isBaseBtn)
        this->setIcon(QIcon(m_iconNormal));
}

// 键盘事件
void MyIconBtn::keyPressEvent(QKeyEvent *e)
{
    // 屏蔽空格键，避免其会异常触发按钮的点击槽函数
    if(e->key() == Qt::Key_Space)
        return;
    else
        e->ignore();
}
