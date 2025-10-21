#ifndef STANDARDTITLEBAR_H
#define STANDARDTITLEBAR_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QPoint>
#include <QPixmap>
#include <QString>
#include "src/Util/def.h"

class StandardTitleBar : public QWidget
{
public:
    explicit StandardTitleBar(QWidget *parent = nullptr);
    void setWindowTitle(const QString& title); // 设置标题栏标题
    void SetTitleBarIcon(const QString& iconPath); // 设置标题栏的图标

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event); // 鼠标双击事件处理函数
    virtual void mousePressEvent(QMouseEvent *event); // 鼠标按下事件处理函数
    virtual void mouseMoveEvent(QMouseEvent *event); // 鼠标移动事件处理函数
    virtual void mouseReleaseEvent(QMouseEvent *event); // 鼠标释放事件处理函数
    virtual bool eventFilter(QObject *obj, QEvent *event); // 事件过滤处理器
    void updateMaximize(); // 最大化/还原

protected slots:
    void onClicked(); // 最小化、最大化/还原、关闭按钮点击时响应的槽函数

private:
    QLabel* m_pLabIcon; // 图标标签
    QLabel* m_pLabTitle; // 标题标签
    QPushButton* m_pBtnMin; // 最小化按钮
    QPushButton* m_pBtnMax; // 最大化按钮
    QPushButton* m_pBtnClose; // 关闭按钮

    QPoint m_pointStart; // 起始点
    QPoint m_pointEnd; // 结束点
    bool m_leftButtonPressed; // 鼠标左键按下标记
};

#endif // STANDARDTITLEBAR_H
