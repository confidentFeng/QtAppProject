#ifndef FLATUIWIDGET_H
#define FLATUIWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include "src/Control/FlatUI.h"
#include "src/Util/def.h"

class FlatUiWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FlatUiWidget(QWidget *parent = nullptr);
    void translateUI(); // 统一设置需要被翻译的文本

private:
    // 按钮
    QPushButton *m_pBtn1;
    QPushButton *m_pBtn2;
    QPushButton *m_pBtn3;
    QPushButton *m_pBtn4;
    QGroupBox *m_pGroupBtn;

    // 编辑框
    QLineEdit *m_pEdit1;
    QLineEdit *m_pEdit2;
    QLineEdit *m_pEdit3;
    QLineEdit *m_pEdit4;
    QGroupBox *m_pGroupEdit;

    // 勾选框
    QCheckBox *m_pCheckBox1;
    QCheckBox *m_pCheckBox2;
    QCheckBox *m_pCheckBox3;
    QCheckBox *m_pCheckBox4;
    QGroupBox *m_pGroupCheck;

    // 单选框
    QRadioButton *m_pRadioBtn1;
    QRadioButton *m_pRadioBtn2;
    QRadioButton *m_pRadioBtn3;
    QRadioButton *m_pRadioBtn4;
    QGroupBox *m_pGroupRadioBtn;

    // 滑动条与进度条
    QSlider *m_pSlider1;
    QSlider *m_pSlider2;
    QProgressBar *m_pProBar1;
    QProgressBar *m_pProBar2;
    QGroupBox *m_pGroupSlider;

    // 滚动条
    QScrollBar *m_pScrollBar;
    QGroupBox *m_pGroupScrollBar;
};

#endif // FLATUIWIDGET_H
