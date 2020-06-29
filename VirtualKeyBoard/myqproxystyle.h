#ifndef MYQPROXYSTYLE_H
#define MYQPROXYSTYLE_H

#include <QWidget>
#include <QProxyStyle>
class PrimitiveElement;
class QStyleOption;

//用于解决各种样式问题

class MyQProxyStyle : public QProxyStyle
{
    Q_OBJECT
public:

    virtual void drawPrimitive(PrimitiveElement element, const QStyleOption * option,
        QPainter * painter, const QWidget * widget = nullptr) const;
    virtual int pixelMetric(PixelMetric metric, const QStyleOption* option = nullptr, const QWidget* widget = nullptr) const;


signals:

public slots:
};

#endif // MYQPROXYSTYLE_H
