#ifndef SPLITSCRBTN_H
#define SPLITSCRBTN_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPainter>
#include <QDebug>
#include <QtMath>
#include "src/Util/def.h"

#define IS_DEBUG 1

// 要求网格按钮的尺寸，长宽为4:3
#define SPLIT_WIDTH 480
#define SPLIT_HEIGHT 360

// 自定义分屏按钮：通过绘图实现
class CustomBtnSplit : public QWidget
{
    Q_OBJECT
public:
    explicit CustomBtnSplit(QWidget *parent = nullptr);
    void isDefaultBtn(bool isFixed); // 是否为默认分屏按钮
    void setGridVector(QVector<StGrid> vecRectCell); // 设置网格容器
    QVector<QRect> getVector();
    void setDelBtnVisible(bool isVisible); // 设置删除按钮是否可见
    void setChecked(bool isChecked); // 设置选中状态
    bool isChecked(); // 获取选中状态
    void setEnabled(bool isEnabled); // 设置启用状态
    bool isEnabled(); // 获取启用状态
    void setSplitMode(EnumSplitMode splitMode); // 设置分屏模式
    EnumSplitMode getSplitMode(); // 获取分屏模式

protected:
    void paintEvent(QPaintEvent *event); // 绘图事件
    void enterEvent(QEvent *event); // 鼠标移入事件
    void leaveEvent(QEvent *event); // 鼠标移出事件
    void mousePressEvent(QMouseEvent *event); // 鼠标点击事件

signals:
    void sigDelBtn(); // 删除信号
    void sigChecked(EnumSplitMode splitMode); // 选中信号
    void clicked(); // 点击信号

private:
    QPushButton *m_pBtnDel; // 删除按钮

    bool m_isDefaultBtn = false; // 是否为默认分屏按钮
    bool m_isChecked = false; // 选中状态
    bool m_isEnabled = true; // 是否启用
    QColor m_colorPaintBoard; // 绘制边框颜色
    QColor m_colorBlue; // 蓝色边框颜色
    QVector<StGrid> m_vecRectCell; // 存放格子rect的容器
    EnumSplitMode m_splitMode = SplitNull;
};

#endif // SPLITSCRBTN_H
