#include "CustomLabScroll.h"

const QString strSpace("   ");

CustomLabScroll::CustomLabScroll(QWidget *parent) : QLabel(parent)
{
    //setStyleSheet(QString ("color: red;"));

    timerId = -1;
    fontSize = 16;
}

void CustomLabScroll::setText(const QString & txt)
{
    QLabel::setText(txt) ;

    upateLabelRollingState();
}

void CustomLabScroll::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event);

    QPainter p (this) ;
    // 获取文本框的大小
    QRect rc = rect() ;
    rc.setHeight(rc.height()-2);
    rc.setWidth(rc.width()-2);

    // 设置即将绘制文字的字体
    QFont ft = font() ;
    ft.setPointSize(fontSize) ;
    p.setFont(ft) ;
    p.setPen(QPen(Qt::red)) ;

    // 设置绘制文字的开始位置，也就是将文字往左移动多少
    rc.setLeft(rc.left()-left) ;

    // 如果文字已经显示到末尾，则再添加一遍文字，做出循环滚动的效果
    QString strText = text() ;
    if(timerId >= 0)
        strText += strSpace + text () ;

    // 绘制文字
    p.drawText(rc, Qt::AlignVCenter, strText);
}

void CustomLabScroll::timerEvent (QTimerEvent *e)
{
    if(e->timerId() == timerId && isVisible())
    {
        // 每次左移1个像素
        left += 1;

        // 判断是否已经完成一遍循环，完成则恢复起始位置，重新开始循环
        QFont ft = font();
        ft.setPointSize(fontSize);
        QFontMetrics fm(ft);
        int txtWidth = fm.width(text()) ;
        int spaceWidth = fm.width(strSpace) ;

        if((txtWidth + spaceWidth) < left)
            left = 0;

        repaint();
    }

    QLabel::timerEvent(e);
}

void CustomLabScroll::resizeEvent(QResizeEvent *e)
{
    QLabel::resizeEvent(e);

    upateLabelRollingState();
}

void CustomLabScroll::upateLabelRollingState()
{
    // 获取文本大小，小于文本框长度，则无需滚动
    QFont ft = font();
    ft.setPointSize(fontSize) ;
    QFontMetrics fm(ft) ;
    int nW = fm.width (text ()) ;
    left = 0;

    // 开启文本框滚动
    if(nW > width ())
    {
        timerId = startTimer (100) ;
    }
    // 关闭文本框滚动
    else
    {
        if(timerId >= 0)
        {
            killTimer(timerId) ;
            timerId = -1;
        }
    }
}
