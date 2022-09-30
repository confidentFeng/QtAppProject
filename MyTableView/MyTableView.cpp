#include "MyTableView.h"
#include <QHeaderView>
#include "HoverDelegate.h"

MyTableView::MyTableView(QWidget *parent) : QTableView(parent)
{
    // 界面初始化
    this->setWindowFlags(Qt::FramelessWindowHint);

    // 设置Hover悬浮变色
    this->setItemDelegate(new HoverDelegate(this));
    this->setMouseTracking(true);
    this->setEnabled(true);

    // 初始化标准项模型、过滤代理模型
    m_pStandModel = new QStandardItemModel;
    m_pFilterModel = new QSortFilterProxyModel(this);
    m_pFilterModel->setSourceModel(m_pStandModel); // 将数据模型与QTableView绑定
    // QTableView初始化
    this->setModel(m_pFilterModel);
    this->setShowGrid(false); // 设置网格线不可见
    this->setWordWrap(false); // 文本过长不换行
    this->setEditTriggers(QAbstractItemView::NoEditTriggers); // 设置不可编辑
    this->setSelectionBehavior(QAbstractItemView::SelectRows); // 设置选中一整行
    this->setSelectionMode (QAbstractItemView::SingleSelection); // 只允许选中单行
    this->setFocusPolicy(Qt::NoFocus); // 取消Item选中后的虚线边框
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); // 显示垂直滑动条
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 隐藏水平滑动条
    this->setVerticalScrollMode(QTableView::ScrollPerPixel); // 垂直滚动条设置为像素滚动
    this->verticalScrollBar()->setSingleStep(ITEM_HEIGHT_MATRIX/3); // 设置滚动条步长（要先设置为像素滚动，才能生效）
    this->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter); // 设置表头为左对齐
    this->verticalHeader()->setMinimumSectionSize(ITEM_HEIGHT_MATRIX); // linux下默认最小高度为40，所以这里要修改下
    this->verticalHeader()->setDefaultSectionSize(ITEM_HEIGHT_MATRIX);
    this->horizontalHeader()->setMinimumSectionSize(ITEM_HEIGHT_MATRIX + 6); // linux下默认最小高度为40，所以这里要修改下
    this->horizontalHeader()->setDefaultSectionSize(ITEM_HEIGHT_MATRIX + 6);
    this->verticalScrollBar()->setContextMenuPolicy(Qt::NoContextMenu);
}

// 本地搜索并过滤
void MyTableView::searchAndFilter(const QString &sKeyword)
{
    // 设置根据表的哪一列进行过滤，默认值为0，如果设置成-1，则会根据所有列进行搜索
    m_pFilterModel->setFilterKeyColumn(-1);
    // 根据固定的字符串进行过滤
    m_pFilterModel->setFilterFixedString(sKeyword);
}

// 本地搜索并选择
void MyTableView::searchAndSel(const QString &sKeyword)
{
    QItemSelection selection;
    int iFirstSelcRow = -1;
    for (int i = 0; i < m_pFilterModel->rowCount(); ++i)
    {
        for(int j=0; j<m_pFilterModel->columnCount(); j++) {

            QString sTemp = m_pFilterModel->data(m_pFilterModel->index(i, j)).toString();
            // 判断是否符合条件
            if (sTemp.contains(sKeyword))
            {
                if (iFirstSelcRow == -1)
                {
                    iFirstSelcRow = i;
                }
                // 增加选中项
                QItemSelection rowSelc(m_pFilterModel->index(i, 0), m_pFilterModel->index(i, 0));
                selection.merge(rowSelc, QItemSelectionModel::Select);
            }
        }
    }
    // 清除之前所有选中项，并选中现在的所有匹配项
    QItemSelectionModel *pSelcModel = this->selectionModel();
    pSelcModel->clearSelection();
    pSelcModel->select(selection, QItemSelectionModel::Rows | QItemSelectionModel::Select);
    // 视图滚动到第一个选中项的位置
    if (iFirstSelcRow != -1)
    {
        this->scrollTo(m_pFilterModel->index(iFirstSelcRow, 0));
    }
}

// 设置悬浮颜色
void MyTableView::setHoverColor(const QBrush &brush)
{
    if(HoverDelegate* delegate = qobject_cast<HoverDelegate*>(itemDelegate())){
        delegate->setHoverColor(brush);
    }
}

// 设置使能
void MyTableView::setEnabled(bool enabled)
{
    if(HoverDelegate* delegate = qobject_cast<HoverDelegate*>(itemDelegate()))
        delegate->setEnabled(enabled);
}

// 获取model
QStandardItemModel *MyTableView::getModel()
{
    return  m_pStandModel;
}

// 获取FilterModel
QSortFilterProxyModel *MyTableView::getFilterModel()
{
    return m_pFilterModel;
}

// 鼠标点击事件
void MyTableView::mousePressEvent( QMouseEvent *event )
{
    if (event->button() == Qt::LeftButton)
    {
        m_startPos = event->pos();
    }
    QTableView::mousePressEvent(event);
}

// 鼠标移动事件
void MyTableView::mouseMoveEvent( QMouseEvent *event )
{
    if (event->buttons() & Qt::LeftButton) {
        int distance = (event->pos() - m_startPos).manhattanLength();
        // 列表中有选中内容才允许拖拽
        if (distance >= QApplication::startDragDistance() && this->selectionModel()->hasSelection()) {
            if(this->objectName() == "MatrixCfgList_tableView") { // 避免不用拖拽的tableview也进入
                // 如果此时Delegate生效，拖拽时HoverDelegate的绘图事件会绘制残影，所以拖拽时，要禁用
                this->setEnabled(false);

                QMimeData *mimeData = new QMimeData;
                mimeData->setProperty("type", this->selectionModel()->selectedRows(0).at(0).data().toString());
                mimeData->setProperty("id", this->selectionModel()->selectedRows(1).at(0).data().toString());
                mimeData->setProperty("ip", this->selectionModel()->selectedRows(2).at(0).data().toString());
                mimeData->setProperty("count", this->selectionModel()->selectedRows().count());

                // 创建拖拽对象
                QDrag* drag = new QDrag(this);
                drag->setMimeData(mimeData);
                drag->exec();

                // 拖拽结束后恢复
                this->setEnabled(true);
                // 拖拽结束清除选中
                this->clearSelection();
            }
            else if(this->objectName() == "MeetUserList_myTableView") {
                QMimeData *mimeData = new QMimeData;
                mimeData->setProperty("id", this->selectionModel()->selectedRows(0).at(0).data().toString());
                mimeData->setProperty("row", this->selectionModel()->selectedRows(0).at(0).row());
                mimeData->setProperty("count", this->selectionModel()->selectedRows().count());

                // 如果此时是"成员管理界面"，禁止拖拽
                if(this->getModel()->item(currentIndex().row(), 0)->statusTip() == "checked")
                    return;

                // 如果此时Delegate生效，拖拽时HoverDelegate的绘图事件会绘制残影，所以拖拽时，要禁用
                this->setEnabled(false);

                // 创建拖拽对象
                QDrag* drag = new QDrag(this);
                drag->setMimeData(mimeData);
                drag->exec();

                // 拖拽结束后恢复
                this->setEnabled(true);
                // 拖拽结束清除选中
                this->clearSelection(); //失效了，研究下，必须一开始没有选中，多行拖拽才正常
            }
        }
    }

    QTableView::mouseMoveEvent(event);
}

void MyTableView::mouseReleaseEvent(QMouseEvent *event)
{
    QTableView::mouseReleaseEvent(event);
}
