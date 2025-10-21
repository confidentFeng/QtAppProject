#ifndef CUSTOMCHECKWIDGET_H
#define CUSTOMCHECKWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QRadioButton>
#include <QGroupBox>
#include <QHBoxLayout>
#include "src/Control/FlatUI.h"
#include "src/Util/def.h"

class CustomCheckWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomCheckWidget(QWidget *parent = nullptr);

private:
    // 勾选框
    QCheckBox *m_pCheckBox1;
    QCheckBox *m_pCheckBox2;
    QGroupBox *m_pGroupCheck;

    // 单选框
    QRadioButton *m_pRadioBtn1;
    QRadioButton *m_pRadioBtn2;
    QRadioButton *m_pRadioBtn3;
    QRadioButton *m_pRadioBtn4;
    QGroupBox *m_pGroupRadioBtn;
};

#endif // CUSTOMCHECKWIDGET_H
