#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include "math.h"

#define SMALL_CIRCLE_RADIUS 30 //小圆半径 （小圆图片分辨率为60*60）
#define BIG_CIRCLE_RADIUS 90 //大圆半径 （大圆图片分辨率为180*180）

class Widget : public QDialog
{
    Q_OBJECT

public:
    Widget(QDialog *parent = nullptr);
    ~Widget();

private:
    QPoint BigCir_xy; //大圆圆心坐标
    QPoint SmallCir_xy; //小圆圆心坐标

    bool MousePressFlag; //鼠标按下的标志位

    QPoint MapRemov_Old;

    void Init();

    void paintEvent(QPaintEvent *event); //绘图事件：绘制地图、摇杆中的大圆和小圆
    void mouseMoveEvent(QMouseEvent *); //鼠标移动事件：实现摇杆功能
    void mousePressEvent(QMouseEvent *); //鼠标按下事件：获取摇杆所在的实时坐标
    void mouseReleaseEvent(QMouseEvent *); //鼠标释放事件：释放鼠标，则MousePressFlag复位，且小圆圆心设置为初始值，更新绘图事件后，重新绘图使小圆（摇杆）回到原处
};

#endif // WIDGET_H
