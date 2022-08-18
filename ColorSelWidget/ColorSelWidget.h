#ifndef COLORSELWIDGET_H
#define COLORSELWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMouseEvent>
#include <QEventLoop>
#include "BasicColorArea.h"
#include "CustomColorArea.h"
#include "SVColorArea.h"
#include "HColorArea.h"
#include "PreviewColorArea.h"

class ColorSelWidget : public QWidget
{
    Q_OBJECT
public:
    enum ButtonRole{Yes, No};

    explicit ColorSelWidget(QWidget *parent = nullptr);
    ButtonRole showDialog();

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

public slots:
    void slotColorItemSel(const QColor &); // 同步饱和度与亮度区域、色调区域的颜色值
    void slotAddCustomColor(); // 添加自定义颜色
    void slotOkBtnClicked(); // 确定按钮按下
    void slotCancelBtnClicked(); // 取消按钮按下

    void slotUpdateEditData(int, int, int); // 更新颜色编辑框的值
    void slotEditChanged(const QString &); // 编辑框文本改变
    void slotEditFinished(); // 编辑框编辑完成

    // HSV/RGB值改变触发的槽函数
    void slotValueChangedH(int);
    void slotValueChangedS(int);
    void slotValueChangedV(int);
    void slotValueChangedR(int);
    void slotValueChangedG(int);
    void slotValueChangedB(int);

private:
    void updateRGBColor(const QColor &);

    // 标题栏窗口部件
    QLabel *m_pLabTitle;
    QPushButton *m_pBtnClose;
    QLabel *m_pLabSplitLine; // 分割线

    BasicColorArea *m_pBasicColorArea; // 基本颜色区域
    CustomColorArea *m_pCustomColorArea; // 自定义颜色区域
    SVColorArea *m_pSVColorArea; // 饱和度(S)与亮度(V)区域
    HColorArea *m_pHColorArea; // 色调区域
    PreviewColorArea *m_pPreviewColorArea; // 颜色预览区域

    QGroupBox *m_pGroupBoxBasic;
    QGroupBox *m_pGroupBoxCustom;

    // 色调、饱和度、亮度、红、绿、蓝 - 标签、计数器控件
    QLabel *m_pLabH;
    QSpinBox *m_pSpinBoxH;
    QLabel *m_pLabS;
    QSpinBox *m_pSpinBoxS;
    QLabel *m_pLabV;
    QSpinBox *m_pSpinBoxV;
    QLabel *m_pLabR;
    QSpinBox *m_pSpinBoxR;
    QLabel *m_pLabG;
    QSpinBox *m_pSpinBoxG;
    QLabel *m_pLabB;
    QSpinBox *m_pSpinBoxB;

    QLabel *m_pLabColor; // 颜色文本标签
    QLineEdit *m_pEditColor; // 颜色编辑框
    QPushButton *m_pBtnCustom; // 自定义颜色按钮
    QLabel *m_pLabCurColor; // 当前颜色标签
    QLabel *m_pLabNewColor; // 新的颜色标签
    QPushButton *m_pBtnOk; // 确定按钮
    QPushButton *m_pBtnCancle; // 确定按钮

    int m_iHue; // 色调
    int m_iSaturation; // 饱和度
    int m_iBrightness; //亮度

    bool m_bNotEdit;
    ButtonRole m_buttonRole;
    QEventLoop *m_pEvtLoop;

    // 实现可拖拽窗口
    bool m_bPressed = false;
    QPoint m_point;
};

#endif // COLORSELWIDGET_H
