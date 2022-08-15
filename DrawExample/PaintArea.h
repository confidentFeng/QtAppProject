#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>
#include <QPainter>

// 绘图区域
class PaintArea : public QWidget
{
    Q_OBJECT
public:
    enum Shape{Dot, Line, Rectangle, RoundRect, Ellipse, Polygon, Polyline, Points, Arc, Path, Text, Pixmap};
    explicit PaintArea(QWidget *parent = nullptr);
    void setShape(Shape shape); // 设置形状
    void setPen(QPen pen); // 设置画笔
    void setBrush(QBrush brush); // 设置画刷
    void clear(); // 清除绘图区域

protected:
    void mousePressEvent(QMouseEvent *event); // 鼠标点击事件
    void mouseMoveEvent(QMouseEvent *event); // 鼠标移动事件
    void paintEvent(QPaintEvent *event); // 绘图事件

private:
    Shape m_shape; // 形状
    QPen m_pen; // 画笔
    QBrush m_brush; // 画刷

    QPixmap *m_pix; // 画布
    QPoint m_posStart; // 鼠标移动绘图的开始坐标
    QPoint m_posEnd; // 鼠标移动绘图的结束坐标
};

#endif // PAINTAREA_H
