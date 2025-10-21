#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QProgressBar>
#include <QSlider>
#include <QScrollBar>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QScrollArea>
#include "src/Control/MyIconBtn.h"
#include "src/Control/MyLineEdit.h"
#include "src/Util/AppData.h"
#include "src/Control/MyComboxBtn.h"
#include "src/Control/CustomTooltip.h"
#include "src/Control/SwitchBtn.h"
#include "src/Control/CustomSliderNum.h"
#include "src/Control/CustomBtnBorder.h"

class ControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlWidget(QWidget *parent = nullptr);
    void translateUI(); // 统一设置需要被翻译的文本

private:
    // 标签
    QLabel *m_pLabText;
    QLabel *m_pLabIcon;
    QGroupBox *m_pGroupLab;

    // 按钮
    MyIconBtn *m_pBtnIcon;
    QPushButton *m_pBtnNormal;
    SwitchBtn *pSwitchButton;
    SwitchBtn *pSwitchButtonText;
    SwitchBtn *pSwitchButtonOut;
    CustomBtnBorder *m_pCustomBtnBorder;
    MyComboxBtn *m_pBtnShortCut;
    MyComboxBtnWithSwitch *m_pBtnAudioMix;
    QGroupBox *m_pGroupBtn;

    // 编辑框
    MyLineEdit *m_pEditAccount;
    MyLineEdit *m_pEditPasswd;
    QGroupBox *m_pGroupEdit;

    // 勾选框
    QCheckBox *m_pCheckBox;
    QGroupBox *m_pGroupCheck;

    // 滑动条与进度条
    QSlider *m_pSlider;
    CustomSliderNum *m_pCustomSliderNum;
    QProgressBar *m_pProBar;
    QProgressBar *m_pProBarLoad;
    QGroupBox *m_pGroupSlider;

    // 滚动条
    QScrollBar *m_pScrollBar;

    QWidget *m_pWidgetBack; // 背景子界面
    QScrollArea *m_pScrollArea; // 滚动区域
};

#endif // CONTROLWIDGET_H
