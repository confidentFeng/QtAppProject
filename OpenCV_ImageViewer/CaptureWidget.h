#ifndef CAPTUREWIDGET_H
#define CAPTUREWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QRect>

class CaptureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CaptureWidget(QWidget *parent = nullptr);

protected:
    void mouseMoveEvent(QMouseEvent *event); // 鼠标点击事件
    void mousePressEvent(QMouseEvent *event); // 鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *event); // 鼠标释放事件
    void paintEvent(QPaintEvent *event); // 绘图事件
    void showEvent(QShowEvent *event); // 显示事件

signals:
    void sigSendCaptureRect(QRect rect); // 发送截取区域矩形

private:
    bool isDragging;
    QPoint startPoint;
    QPoint endPoint;
    QPoint currentPoint;
    QRect selectionRect; // 最终的选择区域矩形，用于绘制和截取屏幕时使用。
};

#endif // CAPTUREWIDGET_H
