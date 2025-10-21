#include "CustomSliderNum.h"

CustomSliderNum::CustomSliderNum(QWidget *parent) : QSlider(parent)
{
    //这里创建一个QLabel对象，并对其进行相关样式设置；样式可以根据具体需求进行具体的设置
    m_pDisplayLabel = new QLabel(this);
    m_pDisplayLabel->setFixedSize(QSize(40, 20));
    m_pDisplayLabel->setAlignment(Qt::AlignCenter);
    m_pDisplayLabel->setObjectName("displayLabel");
    m_pDisplayLabel->setStyleSheet("QLabel#displayLabel{color:#347df7;font-size:24px;}"
                                   "QLabel#displayLabel:disabled{color:#282A32;}");

#ifdef Q_OS_WIN
    this->setCursor(QCursor(Qt::PointingHandCursor));
#else
    this->setCursor(QCursor(QPixmap(":/Image/Util/icon_cursorHand.png")));
#endif
}

void CustomSliderNum::mousePressEvent(QMouseEvent *event)
{
    //这里先调用父类的鼠标点击处理事件，这样就不会出现点击时点击到中间值滑块在最大值和最小值来回跳转了
    //如果不需要响应拖动可以直接去掉
    QSlider::mousePressEvent(event);
    //这里获取当前鼠标点击位置并且设置当前滑块到鼠标点击位置；实现鼠标点击，滑块跳到对应点击位置上处理
    int dur = this->maximum() - this->minimum();
    int pos = qRound(this->minimum() + (dur * ((double)event->x() / this->width())));
    if(pos != this->sliderPosition())
    {
        setValue(pos);
    }

    updateCurrentSliderValueSite();
}
void CustomSliderNum::mouseReleaseEvent(QMouseEvent *event)
{
    updateCurrentSliderValueSite();
    QSlider::mouseReleaseEvent(event);
    //自定义信号，主要是为了避免点击到中间位置时产生两个值对后续其他逻辑产生影响
    emit sigCurrentValueChange(this->value());
}

void CustomSliderNum::mouseMoveEvent(QMouseEvent *event)
{
    updateCurrentSliderValueSite();
    QSlider::mouseMoveEvent(event);
}

void CustomSliderNum::updateCurrentSliderValueSite()
{
    //更新当前滑块上方数值显示位置
    m_pDisplayLabel->setText(QString::number(this->value()));
    //this->value() - 1 这里是由于Slider是从0开始，我这里设置区间是从1开始，故而移动位置会多出当前滑块位置
    m_pDisplayLabel->move((this->width() - m_pDisplayLabel->width()) * (this->value() - 1) / (this->maximum()-this->minimum()), 0);
}
