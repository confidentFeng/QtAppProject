#ifndef CUSTOMEDITPASSWD_H
#define CUSTOMEDITPASSWD_H

#include <QWidget>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QValidator>
#include <QRegExp>
#include <QHBoxLayout>
#include <QEvent>
#include "src/Util/def.h"

class CustomEditPasswd : public QLineEdit
{
    Q_OBJECT
public:
    explicit CustomEditPasswd(QWidget *parent = 0);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override; // 事件过滤器

protected:
    void resizeEvent(QResizeEvent *event) override; // 尺寸大小变化事件

private:
    QPushButton *m_pBtnEye; // eye按钮

    int m_nClearBtnOffset = 8; // 偏移值：数越大文本越往前偏移，太大会遮挡清除按钮，适当调整
};


#endif // CUSTOMEDITPASSWD_H
