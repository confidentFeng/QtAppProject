#ifndef CUSTOMLABWIDGET_H
#define CUSTOMLABWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMovie>
#include "src/Util/def.h"
#include "src/Control/CustomLabScroll.h"
#include "src/Control/CustomLabLoad.h"
#include "src/Control/CustomLabTip.h"

class CustomLabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomLabWidget(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    // 图标标签
    QLabel *m_pLabIcon1;
    QLabel *m_pLabIcon2;
    QLabel *m_pLabIcon3;
    QLabel *m_pLabIcon4;
    QGroupBox *m_pGroupIcon;

    // gif标签
    QLabel *m_pLabGif;
    CustomLabLoad *m_pCustomLabLoad;
    QGroupBox *m_pGroupGif;

    // 自适应标签
    QLabel *m_pLabAdjust1;
    QGroupBox *m_pGroupAdjust;

    // 省略标签
    QLabel *m_pLabOmit1;
    QLabel *m_pLabOmit2;
    QLabel *m_pLabOmit3;
    CustomLabScroll *m_pCustomLabScroll;
    QGroupBox *m_pGroupOmit;

    // 富文本与超链接标签
    QLabel *m_pLabRich;
    QLabel *m_pLabUrl;
    QGroupBox *m_pGroupHtml;

    // 自定义定时隐藏提示标签
    CustomLabTip *m_pCustomLabTip;
};

#endif // CUSTOMLABWIDGET_H
