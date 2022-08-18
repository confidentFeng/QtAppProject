#include "HColorArea.h"

HColorArea::HColorArea(QWidget *parent)
	: QWidget(parent)
	, m_hue(0.0)
	, m_iHue(0)
	, m_iColorHeight(256)
    , m_iColorWidth(25)
{
    this->setFixedSize(34, 270);

    // 创建色调pixmap
	createHuePixmap();
}

void HColorArea::setHue(int h)
{
	m_hue = (double)h / 360;
	m_iHue = h;
	update();
}

void HColorArea::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.drawPixmap(0, 0, m_huePixmap);

	int iHeight = m_iColorHeight - m_hue * m_iColorHeight;
	QPolygonF triangle;
	triangle.append(QPointF(m_iColorWidth, iHeight + topMargin));
	triangle.append(QPointF(width(), iHeight));
	triangle.append(QPointF(width(), iHeight + 2 * topMargin - 1));
	painter.setPen(Qt::NoPen);
	painter.setBrush(Qt::white);
	painter.drawPolygon(triangle);
}

void HColorArea::mousePressEvent(QMouseEvent *ev)
{
	double tempValue = 1 - (double)(ev->pos().y() - topMargin) / m_iColorHeight;
	m_hue = qBound(0.0, tempValue, 1.0);
	update();
	m_iHue = m_hue * 360;
    emit sigHueChanged(m_iHue);
}

void HColorArea::mouseMoveEvent(QMouseEvent *ev)
{
	double tempValue = 1 - (double)(ev->pos().y() - topMargin) / m_iColorHeight;
	m_hue = qBound(0.0, tempValue, 1.0);
	update();
	m_iHue = m_hue * 360;
    emit sigHueChanged(m_iHue);
}

// 创建色调pixmap
void HColorArea::createHuePixmap()
{
	m_huePixmap = QPixmap(34, 270);
	m_huePixmap.fill(Qt::transparent);
	QPainter painter(&m_huePixmap);
	painter.setRenderHint(QPainter::Antialiasing);
	QLinearGradient hueGradient(0, m_iColorHeight, 0, 0);
    for (double i = 0; i < 1.0; i += 1.0 / 16)
	{
		hueGradient.setColorAt(i, QColor::fromHsvF(i, 1, 1, 1));
	}
	hueGradient.setColorAt(1, QColor::fromHsvF(0, 1, 1, 1));
	painter.setPen(Qt::NoPen);
	painter.setBrush(QBrush(hueGradient));
	painter.drawRect(0, topMargin, m_iColorWidth, m_iColorHeight);
}
