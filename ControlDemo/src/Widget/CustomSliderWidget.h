#ifndef CUSTOMSLIDERWIDGET_H
#define CUSTOMSLIDERWIDGET_H

#include <QWidget>
#include <QSlider>
#include <QProgressBar>
#include <QHBoxLayout>
#include <QGroupBox>
#include "src/Control/CustomSliderNum.h"
#include "src/Util/def.h"

class CustomSliderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomSliderWidget(QWidget *parent = nullptr);

private:
    // 滑动条与进度条
    QSlider *m_pSlider;
    CustomSliderNum *m_pCustomSliderNum;
    QGroupBox *m_pGroupSlider;

    QProgressBar *m_pProg;
    QProgressBar *m_pProgLoad;
    QGroupBox *m_pGroupProg;
};

#endif // CUSTOMSLIDERWIDGET_H
