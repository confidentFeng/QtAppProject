#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QVector>
#include "ToolPage.h"

class ToolBox : public QWidget
{
    Q_OBJECT

public:
    explicit ToolBox(QWidget *parent = nullptr);
    void addWidget(const QString &title, QWidget *widget);

private:
    QVBoxLayout *m_pLayoutContent;

    QWidget *m_pWidgetBack; // 背景子界面
    QScrollArea *m_pScrollArea; // 滚动区域
};

#endif // TOOLBOX_H
