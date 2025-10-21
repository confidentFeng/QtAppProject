#ifndef CUSTOMLABSCROLL_H
#define CUSTOMLABSCROLL_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QTimer>
#include <QFontMetrics>
#include <QTimerEvent>

class CustomLabScroll : public QLabel
{
    Q_OBJECT
public:
    explicit CustomLabScroll(QWidget *parent = nullptr);
    void setText (const QString & txt);

protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *e);
    void resizeEvent (QResizeEvent *e);

private:
    void upateLabelRollingState();

    int timerId;
    int fontSize = 28;
    int left = 0;
};

#endif // CUSTOMLABSCROLL_H
