#include "myqproxystyle.h"

#include <QProxyStyle>

void MyQProxyStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    if (PE_FrameFocusRect == element)//当焦点集中时的策略
    {
        //这里不做任何操作，Qt默认是绘制矩形虚线框,以及焦点时的content背景色
    }
    else
    {
        QProxyStyle::drawPrimitive(element, option,painter, widget);
    }
}

int MyQProxyStyle::pixelMetric(QStyle::PixelMetric metric, const QStyleOption *option, const QWidget *widget) const
{
        if (metric == QStyle::PM_TextCursorWidth)//lineEdit光标不绘制
            return 0;
        return QProxyStyle::pixelMetric(metric, option, widget);
}
