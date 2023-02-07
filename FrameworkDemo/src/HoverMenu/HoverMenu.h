#ifndef RIGHTWIDGET_H
#define RIGHTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QButtonGroup>
#include <QComboBox>
#include <QTranslator>
#include <QDebug>
#include "src/Control/MyTitleBar.h"
#include "src/Control/MyIconBtn.h"
#include "src/Util/AppData.h"
#include "src/Util/AppConfig.h"
#include "src/Util/AppEvent.h"

// 悬浮菜单界面
class HoverMenu : public QWidget
{
    Q_OBJECT
public:
    explicit HoverMenu(QWidget *parent = nullptr);
    void translateUI(); // 统一设置需要被翻译的文本

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);        

private:
    MyTitleBar *m_pMyTitleBar; // 标题栏
    MyIconBtn *m_pBtnOpt1; // 接管按钮
    MyIconBtn *m_pBtnOpt2; // 接管推送按钮
    MyIconBtn *m_pBtnOpt3; // 推送按钮
    MyIconBtn *m_pBtnOpt4; // 大屏按钮
    MyIconBtn *m_pBtnOther; // m_pBtnOther按钮
    QComboBox *m_pComboBox;

    bool m_bPressed  = false;
    QPoint m_point;
};


#endif // RIGHTWIDGET_H
