#include "CustomColorArea.h"

CustomColorArea::CustomColorArea(QWidget *parent)
	: QWidget(parent)
	, m_iCurIndex(0)
{
    // 初始化网格布局
    m_pLayoutGrid = new QGridLayout(this);
    m_pLayoutGrid->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    m_pLayoutGrid->setSpacing(2);
    m_pLayoutGrid->setMargin(2);
    m_pLayoutGrid->setGeometry(QRect(0,0,width(),height()));

    // 调色板子界面布局
    QString color;
    QStringList strList;
    for(int i=0; i<16; i++) {
        BasicColorItem *pItem11 = new BasicColorItem(Qt::white);
        connect(pItem11, SIGNAL(sigItemClicked(const QColor &)), this, SIGNAL(sigColorItemSel(const QColor &)));

        m_pLayoutGrid->addWidget(pItem11, m_pLayoutGrid->count()/8, m_pLayoutGrid->count()%8);

        m_mapIndexToItem.insert(i, pItem11);
    }
}

// 设置自定义颜色
void CustomColorArea::setGivenColor(const QColor &c)
{
	int iIndex = m_iCurIndex % 16;
    BasicColorItem *pCurItem = m_mapIndexToItem[iIndex];
	pCurItem->setColor(c);
	m_iCurIndex++;
}

// 设置自定义项颜色
void CustomColorArea::setGivenItemColor(int iIndex, const QColor &c)
{
	BasicColorItem *pCurItem = m_mapIndexToItem[iIndex];
	pCurItem->setColor(c);
}
