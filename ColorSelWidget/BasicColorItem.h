#ifndef BASICCOLORITEM_H
#define BASICCOLORITEM_H

#include <QLabel>
#include <QPainter>
#include <QDebug>

#define ITEM_EDGE_LENGTH 25

// 基本颜色项
class BasicColorItem : public QLabel
{
	Q_OBJECT

public:
    BasicColorItem(const QColor &, QWidget *parent = nullptr);
    void setColor(const QColor &); // 设置颜色
    QColor getColor(); // 获取颜色

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

signals:
    void sigItemClicked(const QColor &); // item点击的信号

private:
	bool m_bMouseIn;
	QColor m_color;
};

#endif // BASICCOLORITEM_H
