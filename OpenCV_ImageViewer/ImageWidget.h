#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPainter>
#include <QVBoxLayout>
#include <QDebug>
#include "./CaptureWidget.h"

class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    ImageWidget(QWidget *parent = nullptr);
    void setPixmap(QPixmap pixamp); // 设置图片
    void clear(); // 清空初始化
    void startMatting(); // 开始抠图
    void endMatting(); // 结束抠图

protected:
    void paintEvent(QPaintEvent *event) override; // 重写paintEvent，用于绘制图片
    void mousePressEvent(QMouseEvent *event) override; // 鼠标按下事件
    void mouseMoveEvent(QMouseEvent *event) override; // 鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *event) override; // 鼠标释放事件
    void wheelEvent(QWheelEvent *event) override; // 滚轮事件，用于缩放图片

signals:
    void sigSendWheelVal(const double &val); // 发送滚轮值给父窗口缩放图片的信号
    void sigSendCaptureRect(QRect rect); // 发送截取区域矩形

private:
    QPixmap m_pixmap;           // 图片
    double m_scaleValue = 1.0;  // 图片缩放倍数
    QPointF m_drawPoint;      // 绘图起点
    QPointF m_mousePoint;     // 鼠标当前位置点
    QRect m_rectPixmap;       // 被绘图片的矩形范围
    bool m_isMousePress;      // 鼠标是否按下

    const double SCALE_MAX_VALUE = 10.0; // 最大放大到原来的10倍
    const double SCALE_MIN_VALUE = 0.1; // 最小缩小到原来的0.1倍

    CaptureWidget *m_pCaptureWidget;
};

#endif // IMAGEWIDGET_H
