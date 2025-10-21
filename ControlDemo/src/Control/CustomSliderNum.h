#ifndef CUSTOMSLIDER_H
#define CUSTOMSLIDER_H

#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QMouseEvent>

class CustomSliderNum : public QSlider
{
    Q_OBJECT
public:
    explicit CustomSliderNum(QWidget *parent = nullptr);
    void updateCurrentSliderValueSite();

protected:
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;

signals:
    void sigCurrentValueChange(int value);

private:
    QLabel *m_pDisplayLabel;
};

#endif // CUSTOMSLIDER_H
