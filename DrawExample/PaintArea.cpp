#include "PaintArea.h"

PaintArea::PaintArea(QWidget *parent) :
    QWidget(parent)
{
    // 设置尺寸
    this->setMinimumSize(600, 300);

    // 用调色板设置背景色
    this->setPalette(QPalette(Qt::white));
    this->setAutoFillBackground(true);

    // 初始化画布
    m_pix = new QPixmap(size()); // 此QPixmap对象用来准备随时接收绘制的内容
    m_pix->fill(Qt::white); // 填充背景色为白色
}

// 鼠标点击事件
void PaintArea::mousePressEvent(QMouseEvent *event)
{
    m_posStart = event->pos();
}

// 鼠标移动事件
void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
    QPainter *painter = new QPainter;

    // 鼠标移动绘图在画布pix上
    painter->begin(m_pix);
    painter->setPen(m_pen);

    if(m_shape == Dot)
        painter->drawLine(m_posStart, event->pos());
    else if(m_shape == Line)
        painter->drawLine(m_posStart, event->pos());

    painter->end();

    // 形状为Dot时，也就是自由绘图模式时，才时刻更新开始点击坐标
    if(m_shape == Dot)
        m_posStart = event->pos();

    this->update();
}

// 绘图事件
void PaintArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(QPoint(0,0), *m_pix);
}

// 设置形状
void PaintArea::setShape(Shape shape)
{
    m_shape = shape;
}

// 设置画笔
void PaintArea::setPen(QPen pen)
{
    m_pen = pen;
}

// 设置画刷
void PaintArea::setBrush(QBrush brush)
{
    m_brush = brush;
}

// 清除绘图区域
void PaintArea::clear()
{
    QPixmap *clearPix  =new QPixmap(size());
    clearPix->fill(Qt::white);
    m_pix = clearPix;
    this->update();
}
