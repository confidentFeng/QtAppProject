#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // 初始化绘图区域类对象
    m_paintArea = new PaintArea;

    // 画笔颜色选择控件
    penColorLabel =new QLabel(tr("画笔颜色："));
    penColorFrame =new QFrame;
    penColorFrame->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    penColorFrame->setAutoFillBackground(true);
    penColorFrame->setPalette(QPalette(Qt::black));
    penColorBtn =new QPushButton(tr("更改"));
    connect(penColorBtn,SIGNAL(clicked()),this,SLOT(slotPenColor()));

    // 画笔线宽选择控件
    penWidthLabel =new QLabel(tr("画笔线宽："));
    penWidthSpinBox =new QSpinBox;
    penWidthSpinBox->setRange(1,20);
    connect(penWidthSpinBox,SIGNAL(valueChanged(int)),this,SLOT (slotPenWidth(int)));

    // 画笔风格选择下拉列表框
    penStyleLabel =new QLabel(tr("画笔风格："));
    penStyleComboBox =new QComboBox;
    penStyleComboBox->addItem(tr("SolidLine"),static_cast<int>(Qt::SolidLine));
    penStyleComboBox->addItem(tr("DashLine"),static_cast<int>(Qt::DashLine));
    penStyleComboBox->addItem(tr("DotLine"),static_cast<int>(Qt::DotLine));
    penStyleComboBox->addItem(tr("DashDotLine"),static_cast<int>(Qt::DashDotLine));
    penStyleComboBox->addItem(tr("DashDotDotLine"),static_cast<int>(Qt::DashDotDotLine));
    penStyleComboBox->addItem(tr("CustomDashLine"),static_cast<int>(Qt::CustomDashLine));
    connect(penStyleComboBox,SIGNAL(activated(int)),this,SLOT (slotPenStyle(int)));

    // 清除按钮
    m_pBtnClear = new QPushButton;
    m_pBtnClear->setText("清除");
    connect(m_pBtnClear,SIGNAL(clicked()),this,SLOT (slotClear()));

    // 控制面板的布局
    rightLayout =new QGridLayout;
    rightLayout->addWidget(penColorLabel,1,0);
    rightLayout->addWidget(penColorFrame,1,1);
    rightLayout->addWidget(penColorBtn,1,2);
    rightLayout->addWidget(penWidthLabel,2,0);
    rightLayout->addWidget(penWidthSpinBox,2,1);
    rightLayout->addWidget(penStyleLabel,3,0);
    rightLayout->addWidget(penStyleComboBox,3,1);
    rightLayout->addWidget(m_pBtnClear,10,0);
    // 主布局
    QVBoxLayout *mainLayout =new QVBoxLayout(this);
    mainLayout->addLayout(rightLayout);
    mainLayout->addWidget(m_paintArea);
    mainLayout->setStretchFactor(m_paintArea,1);
    mainLayout->setStretchFactor(rightLayout,0);
}

// 形状
void MainWindow::slotShape(int value)
{
    PaintArea::Shape shape = PaintArea::Shape(penStyleComboBox->itemData(value, Qt::UserRole).toInt());

    m_paintArea->setShape(shape);
}

// 画笔颜色
void MainWindow::slotPenColor()
{
    QColor color = QColorDialog::getColor(static_cast<int>(Qt::black));
    penColorFrame->setPalette(QPalette(color));
    int value = penWidthSpinBox->value();
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(penStyleComboBox->currentIndex(),Qt::UserRole).toInt());

    m_paintArea->setPen(QPen(color,value,style));
}

// 画笔宽度
void MainWindow::slotPenWidth(int value)
{
    QColor color = penColorFrame->palette().color(QPalette::Window);
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(penStyleComboBox->currentIndex(),Qt::UserRole).toInt());

    m_paintArea->setPen(QPen(color,value,style));
}

// 画笔风格
void MainWindow::slotPenStyle(int styleValue)
{
    QColor color = penColorFrame->palette().color(QPalette::Window);
    int value = penWidthSpinBox->value();
    Qt::PenStyle style = Qt::PenStyle(penStyleComboBox->itemData(styleValue,Qt::UserRole).toInt());

    m_paintArea->setPen(QPen(color,value,style));
}

 // 清空绘图区域
void MainWindow::slotClear()
{
    m_paintArea->clear();
}
