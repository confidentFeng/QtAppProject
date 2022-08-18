#include "SVColorArea.h"

SVColorArea::SVColorArea(QWidget *parent)
	: QWidget(parent)
	, m_iHue(0)
	, m_iSaturation(0)
	, m_iBrightness(0)
	, m_iAreaWidth(256)
{
    // 初始化界面
    this->setFixedSize(256, 256);

    // 创建正方形区域的pixmap
	createSVPixmap();
    // 创建亮度渐变的pixmap
	createVPixmap();
    // 更新正方形区域的pixmap
    updateSVPixmap();
}

void SVColorArea::setHue(int h)
{
	m_iHue = h;
	updateSVPixmap();
	update();
}

void SVColorArea::setSaturation(int s)
{
	m_iSaturation = s;
	update();
}

void SVColorArea::setBrightness(int v)
{
	m_iBrightness = v;
	update();
}

void SVColorArea::setHsv(int h, int s, int v)
{
	m_iHue = h;
	m_iSaturation = s;
	m_iBrightness = v;
	updateSVPixmap();
	update();
}

void SVColorArea::setColor(const QColor &c)
{
	m_iHue = c.hue();
	m_iSaturation = c.saturation();
	m_iBrightness = c.value();
	updateSVPixmap();
    emit sigSvChanged(m_iHue, m_iSaturation, m_iBrightness);
	update();
}

void SVColorArea::paintEvent(QPaintEvent *)
{
    // 画正方形的颜色区域
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.drawPixmap(0, 0, m_svPixmap);
	painter.drawPixmap(0, 0, m_vPixmap);

    // 画颜色选取点的圆圈（亮度>128为黑色；<128为白色；避免黑色圆圈可能在黑色背景下显示不清晰的问题）
	painter.setPen(QPen(m_iBrightness > 128 ? Qt::black : Qt::white, 2));
	QPointF selecPos = QPointF(m_iSaturation, 255 - m_iBrightness);
	painter.drawEllipse(selecPos, 6, 6);
}

void SVColorArea::mousePressEvent(QMouseEvent *ev)
{
	m_iSaturation = qBound(0, ev->x(), 255);
	m_iBrightness = qBound(0, 255 - ev->y(), 255);
    emit sigSvChanged(m_iHue, m_iSaturation, m_iBrightness);
	update();
}

void SVColorArea::mouseMoveEvent(QMouseEvent *ev)
{
	m_iSaturation = qBound(0, ev->x(), 255);
	m_iBrightness = qBound(0, 255 - ev->y(), 255);
    emit sigSvChanged(m_iHue, m_iSaturation, m_iBrightness);
	update();
}

// 创建亮度渐变的pixmap
void SVColorArea::createVPixmap()
{
	m_vPixmap = QPixmap(m_iAreaWidth, m_iAreaWidth);
	m_vPixmap.fill(Qt::transparent);
	QPainter painter(&m_vPixmap);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setCompositionMode(QPainter::CompositionMode_Source);
	QLinearGradient vGradient(0, 0, 0, m_iAreaWidth);
	vGradient.setColorAt(0, QColor(0, 0, 0, 0));
	vGradient.setColorAt(1, QColor(0, 0, 0, 255));
	painter.setPen(Qt::NoPen);
	painter.setBrush(QBrush(vGradient));
	painter.drawRect(0, 0, m_iAreaWidth, m_iAreaWidth);
}

// 创建正方形区域的pixmap
void SVColorArea::createSVPixmap()
{
	m_svPixmap = QPixmap(m_iAreaWidth, m_iAreaWidth);
	m_svPixmap.fill(Qt::transparent);
}

// 更新正方形区域的pixmap
void SVColorArea::updateSVPixmap()
{
	QColor newColor;
	newColor.setHsv(m_iHue, 255, 255);
	QPainter painter(&m_svPixmap);
	painter.setRenderHint(QPainter::Antialiasing);
	QLinearGradient svGradient(0, 0, m_iAreaWidth, 0);
	svGradient.setColorAt(1, newColor);
	svGradient.setColorAt(0, QColor("#ffffff"));
	painter.setPen(Qt::NoPen);
	painter.setBrush(QBrush(svGradient));
	painter.drawRect(0, 0, m_iAreaWidth, m_iAreaWidth);
}

// 色调改变的槽函数
void SVColorArea::slotHueChanged(int h)
{
	m_iHue = h;
	updateSVPixmap();
    emit sigSvChanged(m_iHue, m_iSaturation, m_iBrightness);
	update();
}
