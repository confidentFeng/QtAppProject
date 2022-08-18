#include "PreviewColorArea.h"

PreviewColorArea::PreviewColorArea(QWidget *parent)
	: QWidget(parent)
	, m_curColor(Qt::black)
	, m_newColor(Qt::black)
{
    // 初始化界面
    this->setFixedSize(166, 88);
}

// 设置当前颜色
void PreviewColorArea::setCurColor(const QColor &c)
{
	m_curColor = c;
	repaint();
}

// 设置新的颜色
void PreviewColorArea::setNewColor(const QColor &c)
{
	m_newColor = c;
	update();
}

void PreviewColorArea::paintEvent(QPaintEvent *)
{
	QStylePainter painter(this);
	paint(painter, geometry());
}

void PreviewColorArea::resizeEvent(QResizeEvent *)
{
	update();
}

void PreviewColorArea::paint(QPainter &painter, QRect rect) const
{
	int iMiddleWidth = rect.width() / 2;
	int iHeight = rect.height();
	painter.fillRect(0, 0, iMiddleWidth, iHeight, m_curColor);
	painter.fillRect(iMiddleWidth, 0, iMiddleWidth, iHeight, m_newColor);
	painter.setPen(QPen(Qt::black, 1));
	painter.drawRect(0, 0, width() - 1, height() - 1);
}

void PreviewColorArea::slotSvChanged(int h, int s, int v)
{
	m_newColor.setHsv(h, s, v);
	update();
    emit sigSvChanged(h, s, v);
}
