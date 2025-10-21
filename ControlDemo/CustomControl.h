#ifndef CUSTOMCONTROL_H
#define CUSTOMCONTROL_H

#include <QWidget>
#include <QListView>
#include <QStringListModel>
#include <QModelIndex>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "src/Widget/CustomBtnWidget.h"
#include "src/Widget/CustomLabWidget.h"
#include "src/Widget/CustomEidtWidget.h"
#include "src/Widget/CustomCheckWidget.h"
#include "src/Widget/CustomSliderWidget.h"

class CustomControl : public QWidget
{
    Q_OBJECT

public:
    CustomControl(QWidget *parent = nullptr);

    QListView *m_pListView;

    QStackedWidget *m_pStackedWidget;

    CustomLabWidget *m_pCustomLabWidget; // 自定义标签界面
    CustomBtnWidget *m_pCustomBtnWidget; // 自定义按钮界面
    CustomEidtWidget *m_pCustomEidtWidget; // 自定义编辑框界面
    CustomCheckWidget *m_pCustomCheckWidget; // 自定义勾选框界面
    CustomSliderWidget *m_pCustomSliderWidget; // 自定义滑动条界面
};
#endif // CUSTOMCONTROL_H
