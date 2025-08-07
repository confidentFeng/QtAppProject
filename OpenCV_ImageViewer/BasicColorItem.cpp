#include "BasicColorItem.h"

BasicColorItem::BasicColorItem(const QColor &c, QWidget *parent)
    : QLabel(parent)
    , m_bMouseIn(false)
{
    setFixedSize(ITEM_EDGE_LENGTH, ITEM_EDGE_LENGTH);
    m_color = c;
    this->update();
}

// 设置颜色
void BasicColorItem::setColor(const QColor &color)
{
    m_color = color;
    QImage itemImg = QImage(ITEM_EDGE_LENGTH, ITEM_EDGE_LENGTH, QImage::Format_RGB32);
    QPainter painter(&itemImg);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.drawImage(0, 0, itemImg);
    painter.setPen(Qt::NoPen);
    painter.setBrush(color);
    painter.drawRect(0, 0, width(), height());
    painter.end();
    this->setPixmap(QPixmap::fromImage(itemImg));
    update();
}

// 获取颜色
QColor BasicColorItem::getColor()
{
    return m_color;
}

void BasicColorItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    if (m_bMouseIn)
        painter.setPen(QPen(Qt::white, 3));
    else
        painter.setPen(QPen(m_color, 0));
    painter.setBrush(m_color);
    painter.drawRect(1, 1, ITEM_EDGE_LENGTH - 3, ITEM_EDGE_LENGTH - 3);
}

void BasicColorItem::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    emit sigItemClicked(m_color);
}

void BasicColorItem::enterEvent(QEvent *event)
{
    Q_UNUSED(event);

    m_bMouseIn = true;
    this->update();
}

void BasicColorItem::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);

    m_bMouseIn = false;
    this->update();
}
