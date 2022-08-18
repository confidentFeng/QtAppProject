#ifndef CUSTOMCOLORAREA_H
#define CUSTOMCOLORAREA_H

#include <QWidget>
#include <QMap>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include "BasicColorItem.h"

// 自定义颜色区域
class CustomColorArea : public QWidget
{
	Q_OBJECT

public:
    CustomColorArea(QWidget *parent = nullptr);
    void setGivenColor(const QColor &); // 设置自定义颜色

private:
    void setGivenItemColor(int iIndex, const QColor &); // 设置自定义项颜色

signals:
    void sigColorItemSel(const QColor &); // 颜色item选中的信号

private:
private:
    QGridLayout *m_pLayoutGrid; // 网格布局

	QMap<int, BasicColorItem *> m_mapIndexToItem;
	int m_iCurIndex;
};

#endif // CUSTOMCOLORAREA_H
