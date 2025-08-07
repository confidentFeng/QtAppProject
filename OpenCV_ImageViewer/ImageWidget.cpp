#include "ImageWidget.h"

ImageWidget::ImageWidget(QWidget *parent) : QWidget(parent)
{
    m_pCaptureWidget = new CaptureWidget(this);
    m_pCaptureWidget->setFixedSize(width(), height());
    m_pCaptureWidget->hide();

    // 发送截取区域矩形
    connect(m_pCaptureWidget, &CaptureWidget::sigSendCaptureRect, [=](QRect rect) {
        QRect imageRect = QRect(m_drawPoint.x(), m_drawPoint.y(), width()-m_drawPoint.x(),
                                height()-m_drawPoint.y()); // 获取图像绘图区域矩形
        QRect interRect = QRect(); // 相交矩形
        QRect sendRect = QRect(); // 最终发送的矩形
        qDebug() << "imageRect:" << imageRect;

        // 获取最终发送的矩形
        if (rect.intersects(imageRect)) { // 矩形相交
            if(rect.bottomRight().x() < imageRect.bottomRight().x()) {
                // 获取相交矩形
                interRect = rect.intersected(imageRect);
                qDebug() << "------------" << rect << imageRect << interRect;

                sendRect = interRect;
                int w = interRect.width();
                int h = interRect.height();

                if(rect.x() < imageRect.x())
                    sendRect = QRect(0, interRect.y(), w, h);
                else
                    sendRect = QRect(sendRect.x()-imageRect.x(), interRect.y(), w, h);
                if(rect.y() < imageRect.y())
                    sendRect = QRect(sendRect.x(), 0, w, h);
                else
                    sendRect = QRect(sendRect.x(), sendRect.y()-imageRect.y(), w, h);
            }
            if(imageRect.x() < 0 && imageRect.y() < 0)  {
                imageRect = QRect(0, 0, imageRect.width()+imageRect.x()*2, imageRect.height()+imageRect.y()*2);

                // 获取相交矩形
                interRect = rect.intersected(imageRect);
                qDebug() << "------------" << rect << imageRect << interRect;

                sendRect = interRect;
                int w = interRect.width();
                int h = interRect.height();

                if(rect.bottomRight().x() > imageRect.width())
                    sendRect = QRect(width()-interRect.width(), height()-(imageRect.height()-interRect.y()), w, h);
                else
                    sendRect = QRect(width()-(imageRect.width()-interRect.x()), height()-(imageRect.height()-interRect.y()), w, h);
            }
            // 还有两种情况暂不适配（只有 imageRect.x()<0 或者 imageRect.y()<0）

            qDebug() << "-----------" << imageRect << interRect << sendRect;
            emit sigSendCaptureRect(sendRect); // 发送截取区域矩形
        }
        else { // 矩形不相交
            qDebug() << "抠图区域无效，返回!!!";
        }
    });
}

// 设置图片
void ImageWidget::setPixmap(QPixmap pixamp)
{
    m_pixmap = pixamp;

    // 触发重新绘制
    this->update();
}

// 清空初始化
void ImageWidget::clear()
{
    m_scaleValue = 1.0;
    m_drawPoint = QPointF();
}

// 开始抠图
void ImageWidget::startMatting()
{
    m_pCaptureWidget->raise();
    m_pCaptureWidget->show();
}

// 结束抠图
void ImageWidget::endMatting()
{
    m_pCaptureWidget->hide();
}

// 重写paintEvent，用于绘制图片
void ImageWidget::paintEvent(QPaintEvent *)
{
    // 创建一个QPainter，用于绘制图片
    QPainter painter(this);
//    // 计算缩放后的图片尺寸（Qt缩放）
//    double width = this->width() * m_scaleValue;
//    double height = this->height() * m_scaleValue;
    // 计算缩放后的图片尺寸（OpenCV缩放）
    double width = m_pixmap.size().width();
    double height = m_pixmap.size().height();
    QPixmap scalePixmap = m_pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation); // 饱满缩放
    // 获取偏移后的绘图图片区域
    m_rectPixmap = QRect(m_drawPoint.x(), m_drawPoint.y(), width, height);  // 图片区域
    // 绘制图片
    painter.drawPixmap(m_rectPixmap, scalePixmap);

    // 绘制边框
    QPen pen; //画笔
    pen.setColor(QColor(0, 0, 0));
    painter.setPen(pen); //添加画笔
    painter.drawRect(0, 0, this->width()-1, this->height()-1); //绘制矩形
}

// 鼠标按下事件
void ImageWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_isMousePress = true; // 鼠标是否按下的标志位
        m_mousePoint = event->pos(); // 记录鼠标点击位置
    }
}

// 鼠标移动事件
void ImageWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(m_isMousePress)
    {
        // 分别计算鼠标的x和y方向的移动距离
        int x = event->pos().x() - m_mousePoint.x();
        int y = event->pos().y() - m_mousePoint.y();
        // 获取鼠标当前位置点
        m_mousePoint = event->pos();
        // 在绘图起点加上移动距离，得到新的绘图起点
        m_drawPoint = QPointF(m_drawPoint.x()+x, m_drawPoint.y()+y);

        // 触发重新绘制
        this->update();
    }
}

// 鼠标释放事件
void ImageWidget::mouseReleaseEvent(QMouseEvent *event)
{
    // 右键释放
    if(event->button() == Qt::RightButton)
    {
        // 清空变量
        m_drawPoint = QPointF(0,0);
        m_scaleValue = 1.0;

        // 触发重新绘制
        this->update();
    }

    // 左键释放，则清空鼠标是否按下的标志位
    if(event->button() == Qt::LeftButton)
        m_isMousePress = false;
}

// 滚轮事件，用于缩放图片
void ImageWidget::wheelEvent(QWheelEvent *event)
{
    // 滚轮缩放
    double oldScale = m_scaleValue;
    if(event->delta() > 0)
    {
        m_scaleValue *= 1.1; // 放大
    }
    else
    {
        m_scaleValue *= 0.9; // 缩小
    }

    // 限制缩放范围
    if(m_scaleValue > SCALE_MAX_VALUE)
        m_scaleValue = SCALE_MAX_VALUE;
    if(m_scaleValue < SCALE_MIN_VALUE)
        m_scaleValue = SCALE_MIN_VALUE;

    // 发送滚轮值给父窗口缩放图片
    emit sigSendWheelVal(m_scaleValue);

    // 计算新的绘图起点
    if(m_rectPixmap.contains(event->pos()))
    {
        double x = m_drawPoint.x() - (event->pos().x()-m_drawPoint.x())/m_rectPixmap.width()*(this->width()*(m_scaleValue-oldScale));
        double y = m_drawPoint.y() - (event->pos().y()-m_drawPoint.y())/m_rectPixmap.height()*(this->height()*(m_scaleValue-oldScale));
        m_drawPoint = QPointF(x, y);
    }
    else
    {
        double x = m_drawPoint.x() - (this->width()*(m_scaleValue-oldScale))/2;
        double y = m_drawPoint.y() - (this->height()*(m_scaleValue-oldScale))/2;
        m_drawPoint = QPointF(x, y);
    }

    // 触发重新绘制
    this->update();

    event->accept();
}
