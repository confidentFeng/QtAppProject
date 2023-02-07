#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "src/HoverMenu/HoverMenu.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    void setTranslator(QTranslator* translator); // 设置翻译对象

protected:
    void changeEvent(QEvent *event); // 改变事件

private:
    void translateUI(); // 统一设置需要被翻译的文本

    HoverMenu *m_pHoverMenu; // 悬浮菜单界面
    QWidget *m_pWidget1;
    QWidget *m_pWidget2;

    QTranslator *m_translator; // 国际化翻译对象
};
#endif // MAINWIDGET_H
