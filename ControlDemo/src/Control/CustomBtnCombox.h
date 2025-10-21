#ifndef MYCOMBOXBTN_H
#define MYCOMBOXBTN_H

#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QApplication>
#include "CustomBtnSw.h"
#include "CustomTooltip.h"

#define STYLE_NORMAL "QPushButton{background:rgba(20,45,86,0.5);border:none;}"
#define STYLE_HOVER "QPushButton:hover{background:rgba(5,70,108,0.5);border:none;}"
#define STYLE_PRESS "QPushButton:pressed{background:rgba(0,102,204,0.5);border:none;}"

// 自定义下拉菜单按钮
class CustomBtnCombox : public QPushButton
{
public:
    CustomBtnCombox(QString color = "rgba(20,45,86,0.5)", QWidget *parent = nullptr);
    void setBtnText(const QString &sText);
    void setLabIcon1(const QString &sImgPath);
    void setLabIcon2(const QString &sImgPath);
    void setBtnTextColor(const QString &sColor);
    void setLableHide(bool isHide);

    bool m_isFold = false; // 是否折叠
    bool m_isTrueEnter = false;

protected:
    void enterEvent(QEvent *e) override; // 鼠标移入事件
    void leaveEvent(QEvent *e) override; // 鼠标移出事件

private:
    QLabel *pLabIcon1;
    QLabel *pLabText;
    QLabel *pLabIcon2;
    QLabel *m_pLabSpace;
    QHBoxLayout *pLayoutMain;
};

class CustomBtnComboxSw : public QPushButton
{
    Q_OBJECT
public:
    explicit CustomBtnComboxSw(QWidget *parent = nullptr);
    void setBtnText(const QString &sText);
    void setLabIcon1(const QString &sImgPath);
    void setBtnTextColor(const QString &sColor);
    void setSwitchState(bool state);
    bool switchState();
    void setTipShow(bool isShow = false);
    bool m_isFold = false; // 是否折叠
    bool m_isTrueEnter = false;


signals:
    void switchStateChanged(bool checked);

protected:
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    bool eventFilter(QObject *obj, QEvent *event); // 事件过滤器

private:
    QLabel *pLabIcon1;
    QLabel *pLabText;
    QLabel *pLabTip;
    CustomBtnSw *m_pSwitchBtn;
};

#endif // MYCOMBOXBTN_H
