#ifndef CUSTOMBTNWIDGET_H
#define CUSTOMBTNWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QProgressBar>
#include <QSlider>
#include <QScrollBar>
#include <QButtonGroup>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QScrollArea>
#include "src/Control/CustomBtnIcon.h"
#include "src/Control/CustomEditIcon.h"
#include "src/Control/CustomBtnCombox.h"
#include "src/Control/CustomTooltip.h"
#include "src/Control/CustomBtnSw.h"
#include "src/Control/CustomSliderNum.h"
#include "src/Control/CustomBtnBorder.h"
#include "src/Control/CustomBtnSplit.h"
#include "src/Control/FlatUI.h"

class CustomBtnWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomBtnWidget(QWidget *parent = nullptr);
    void translateUI(); // 统一设置需要被翻译的文本

private:
    void initDefaultBnt(); // 初始化分屏按钮

    // Falt按钮
    QPushButton *m_pBtnFalt1;
    QPushButton *m_pBtnFalt2;
    QPushButton *m_pBtnFalt3;
    QPushButton *m_pBtnFalt4;
    QGroupBox *m_pGroupFalt;

    // 开关按钮
    CustomBtnSw *pSwitchButton;
    CustomBtnSw *pSwitchButtonText;
    CustomBtnSw *pSwitchButtonText2;
    CustomBtnSw *pSwitchButtonOut;
    QGroupBox *m_pGroupSwitch;

    // 图标按钮
    CustomBtnIcon *m_pBtnIcon1;
    CustomBtnIcon *m_pBtnIcon2;
    CustomBtnIcon *m_pBtnIcon3;
    CustomBtnIcon *m_pBtnIcon4;
    CustomBtnIcon *m_pBtnOther;
    QGroupBox *m_pGroupIcon;

    // 图标在上方的按钮
    QPushButton *m_pBtnMember; // 成员按钮
    QPushButton *m_pBtnChat; // 聊天按钮
    QPushButton *m_pBtnMike; // 麦克风按钮
    QPushButton *m_pBtnCamera; // 摄像头按钮
    QGroupBox *m_pGroupIconUp;
    QWidget *m_pWidgetBtn; // 按钮widget

    // 分屏按钮
    CustomBtnSplit *m_pBtnSingle; // 单一画面(Single picture)
    CustomBtnSplit *m_pBtnFour; // 四等分(Four bisection)
    CustomBtnSplit *m_pBtnFive; // 一大五小(One big five small)
    CustomBtnSplit *m_pBtnNineGrid; // 九宫格(Jiugong grid)
    QGroupBox *m_pGroupSplit;
    QWidget *m_pWidgetSplit; // 分屏按钮widget
    QVector<CustomBtnSplit *> m_vecSplitBtn; // 存放分屏按钮的容器

    // 下拉开关按钮
    CustomBtnCombox *pBtnLanguage; // 语言
    CustomBtnCombox *m_pBtnShortCut; // 快捷键
    CustomBtnComboxSw *m_pKeyBoard; // 虚拟键盘
    CustomBtnComboxSw *m_pBtnMic; // 麦克风
    QGroupBox *m_pGroupCombox;

    // 特殊按钮
    CustomBtnBorder *m_pCustomBtnBorder; // 边框按钮
    QGroupBox *m_pGroupSpecial;

    QWidget *m_pWidgetScroll; // 滚动显示区域幕布
    QScrollArea *m_pScrollArea; // 滚动区域
};

#endif // CUSTOMBTNWIDGET_H
