#include "CaptureWidget.h"

CaptureWidget::CaptureWidget(QWidget *parent) : QWidget(parent)
{

}

// 鼠标点击事件
void CaptureWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isDragging = true;
        startPoint = event->pos();
    }
}

// 鼠标移动事件
void CaptureWidget::mouseMoveEvent(QMouseEvent *event) {
    if (isDragging && (event->buttons() & Qt::LeftButton)) {
        currentPoint = event->pos();
        this->update(); // 触发重绘，显示选择区域
    }
}

// 鼠标释放事件
void CaptureWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && isDragging) {
        isDragging = false;
        endPoint = event->pos();
        this->update(); // 再次触发重绘，显示最终选择区域

        // 在这里可以添加代码来截取屏幕的这部分区域，例如使用QPixmap和QScreen类
        emit sigSendCaptureRect(QRect(startPoint, endPoint).normalized());
    }
}

// 绘图事件
void CaptureWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setPen(Qt::green); // 设置边框颜色为绿色
    if (isDragging) {
        painter.drawRect(QRect(startPoint, currentPoint)); // 绘制当前的选择区域预览
    }
    else {
        if (!selectionRect.isNull()) { // 如果已经释放鼠标，绘制最终的选择区域
            painter.drawRect(selectionRect); // 使用最终的选择区域坐标绘制矩形框
        }
        else {
            painter.drawRect(0, 0, this->width()-1, 360-1);
        }
    }
}

// 显示事件
void CaptureWidget::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);

    this->update(); // 触发重绘
}
