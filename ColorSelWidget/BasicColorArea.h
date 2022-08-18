#ifndef BASICCOLORAREA_H
#define BASICCOLORAREA_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include "BasicColorItem.h"

// 基本颜色区域
class BasicColorArea : public QWidget
{
	Q_OBJECT

public:
    BasicColorArea(QWidget *parent = nullptr);

signals:
    void sigColorItemSel(const QColor &); // 颜色item选中的信号

private:
    QGridLayout *m_pLayoutGrid; // 网格布局
};

#endif // BASICCOLORAREA_H
