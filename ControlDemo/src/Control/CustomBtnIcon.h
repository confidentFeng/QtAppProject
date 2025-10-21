#ifndef MYICONBTN_H
#define MYICONBTN_H

#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QApplication>
#include "src/Util/def.h"

// 自定义图标按钮
class CustomBtnIcon : public QPushButton
{
    Q_OBJECT
public:
    CustomBtnIcon(QWidget *parent = nullptr);

    QString m_iconNormal;
    QString m_iconHover;
    QString m_iconPressed;
    QString m_iconDisable;
    bool m_isBaseBtn = false;

protected:
    void showEvent(QShowEvent *e) override; // 显示事件
    void enterEvent(QEvent *e) override; // 鼠标移入事件
    void leaveEvent(QEvent *e) override; // 鼠标移出事件
    void keyPressEvent(QKeyEvent *e) override; // 键盘事件
};

#endif // MYICONBTN_H
