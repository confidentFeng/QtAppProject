#include "BasicColorArea.h"

BasicColorArea::BasicColorArea(QWidget *parent)
	: QWidget(parent)
{
    // 初始化网格布局
    m_pLayoutGrid = new QGridLayout(this);
    m_pLayoutGrid->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    m_pLayoutGrid->setSpacing(2);
    m_pLayoutGrid->setMargin(2);
    m_pLayoutGrid->setGeometry(QRect(0,0,width(),height()));

    // 颜色列表
    QStringList colorList = {"0, 0, 0", "51, 51, 51", "102, 102, 102", "153, 153, 153", "204, 204, 204", "221, 221, 221", "238, 238, 238", "255, 255, 255",
                             "207, 42, 39", "255, 153, 0", "255, 255, 0", "0, 158, 15", "0, 255, 255", "43, 120, 228", "153, 0, 255", "255, 0, 255",
                             "234, 153, 153", "249, 203, 156", "255, 229, 153", "182, 215, 168", "162, 196, 201", "159, 197, 248", "180, 167, 214", "213, 166, 189",
                             "224, 102, 102", "246, 178, 107", "255, 217, 102", "147, 196, 125", "118, 165, 175", "111, 168, 220", "142, 124, 195", "194, 123, 160",
                             "204, 0, 0", "230, 145, 56", "241, 194, 50", "106, 168, 79", "69, 129, 142", "89, 126, 170", "103, 78, 167", "166, 77, 121",
                             "153, 0, 0", "180, 95, 6", "119, 144, 0", "56, 118, 29", "19, 79, 92", "8, 83, 148", "52, 28, 117", "116, 27, 71",
                             "102, 0, 0", "120, 63, 4", "127, 96, 0", "39, 78, 19", "12, 52, 61", "7, 55, 99", "32, 18, 77", "71, 17, 48"};
    // 对颜色名列表进行遍历
    QString color;
    QStringList strList;
    foreach(color,colorList) {
        strList = color.split(",");
        BasicColorItem *pItem11 = new BasicColorItem(QColor(strList.at(0).toInt(), strList.at(1).toInt(), strList.at(2).toInt()));
        connect(pItem11, SIGNAL(sigItemClicked(const QColor &)), this, SIGNAL(sigColorItemSel(const QColor &)));

        m_pLayoutGrid->addWidget(pItem11, m_pLayoutGrid->count()/8, m_pLayoutGrid->count()%8);
    }
}
