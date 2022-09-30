#include "ColorSelWidget.h"

ColorSelWidget::ColorSelWidget(QWidget *parent) : QWidget(parent)
{
    // 初始化界面
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setFixedSize(730, 420);
    this->setFocusPolicy(Qt::ClickFocus);
    this->setObjectName("ColorSelWidget");
    this->setStyleSheet("QWidget#ColorSelWidget{background: rgb(23,25,29);}");

    // 标题栏窗口部件
    m_pLabTitle = new QLabel;
    m_pBtnClose = new QPushButton;
    m_pLabSplitLine = new QLabel;
    m_pLabTitle->setText("编辑颜色");
    m_pLabTitle->setObjectName("LabTitle");
    m_pBtnClose->setObjectName("m_pCloseBtn");
    m_pLabSplitLine->setObjectName("LabSplitLine");
    m_pBtnClose->setFixedSize(30, 30);
    m_pLabSplitLine->setFixedSize(width(), 2);

    // 初始化基本颜色界面
    m_pBasicColorArea = new BasicColorArea;
    // 自定义颜色区域
    m_pCustomColorArea = new CustomColorArea;

    // 初始化饱和度(S)与亮度(V)区域
    m_pSVColorArea = new SVColorArea;
    // 初始化色调区域
    m_pHColorArea = new HColorArea;

    // 初始化预览颜色界面
    m_pPreviewColorArea = new PreviewColorArea;
    m_pLabCurColor = new QLabel;
    m_pLabNewColor = new QLabel;
    m_pBtnOk = new QPushButton;
    m_pBtnCancle = new QPushButton;
    m_pLabCurColor->setText("当前\n颜色");
    m_pLabNewColor->setText("新的\n颜色");
    m_pBtnOk->setText("确定");
    m_pBtnCancle->setText("取消");
    m_pLabCurColor->setFixedSize(30, 40);
    m_pLabNewColor->setFixedSize(30, 40);
    m_pBtnOk->setFixedSize(62, 26);
    m_pBtnCancle->setFixedSize(62, 26);

    // 初始化GroupBox
    m_pGroupBoxBasic = new QGroupBox;
    m_pGroupBoxCustom = new QGroupBox;
    m_pGroupBoxBasic->setTitle("基本颜色");
    m_pGroupBoxCustom->setTitle("自定义颜色");

    // 色调、饱和度、亮度 - 标签、计数器控件
    m_pLabH = new QLabel;
    m_pSpinBoxH = new QSpinBox;
    m_pLabS = new QLabel;
    m_pSpinBoxS = new QSpinBox;
    m_pLabV = new QLabel;
    m_pSpinBoxV = new QSpinBox;
    m_pLabR = new QLabel;
    m_pSpinBoxR = new QSpinBox;
    m_pLabG = new QLabel;
    m_pSpinBoxG = new QSpinBox;
    m_pLabB = new QLabel;
    m_pSpinBoxB = new QSpinBox;
    m_pLabH->setText("色调(H):");
    m_pLabS->setText("饱和度(S):");
    m_pLabV->setText("亮度(V):");
    m_pLabR->setText("红(R):");
    m_pLabG->setText("绿(G):");
    m_pLabB->setText("蓝(B):");
    m_pLabH->setFixedSize(66, 26);
    m_pLabS->setFixedSize(66, 26);
    m_pLabV->setFixedSize(66, 26);
    m_pLabR->setFixedSize(50, 26);
    m_pLabG->setFixedSize(50, 26);
    m_pLabB->setFixedSize(50, 26);

    m_pLabColor = new QLabel; // 颜色文本标签
    m_pEditColor = new QLineEdit; // 颜色编辑框
    m_pBtnCustom = new QPushButton;
    m_pLabColor->setText("#");
    m_pEditColor->setText("000000");
    m_pBtnCustom->setText("添加到自定义颜色");
    m_pBtnCustom->setFixedSize(128, 26);
    m_pEditColor->setFixedSize(72, 26);

    // 正则表达式应用在颜色编辑栏
    QRegExp rx("(\\d?[a-f]?){0,6}");
    m_pEditColor->setValidator(new QRegExpValidator(rx, this));
    m_pEditColor->setText("000000");

    // 标题栏布局
    QHBoxLayout *pLayoutTitle = new QHBoxLayout;
    pLayoutTitle->addSpacing(6);
    pLayoutTitle->addWidget(m_pLabTitle);
    pLayoutTitle->addStretch();
    pLayoutTitle->addWidget(m_pBtnClose, 0, Qt::AlignTop);
    pLayoutTitle->addSpacing(4);
    pLayoutTitle->setMargin(0);

    // 基本颜色布局
    QVBoxLayout *pLayoutBasic = new QVBoxLayout(m_pGroupBoxBasic);
    pLayoutBasic->addWidget(m_pBasicColorArea);
    // 自定义颜色布局
    QVBoxLayout *pLayoutCustom = new QVBoxLayout(m_pGroupBoxCustom);
    pLayoutCustom->addWidget(m_pCustomColorArea);

    // 下方布局
    QHBoxLayout *pLayoutDown = new QHBoxLayout;
    pLayoutDown->addStretch();
    pLayoutDown->addWidget(m_pLabColor);
    pLayoutDown->addSpacing(2);
    pLayoutDown->addWidget(m_pEditColor);
    pLayoutDown->addStretch();
    pLayoutDown->addWidget(m_pBtnCustom);
    pLayoutDown->addSpacing(0);
    pLayoutDown->setSpacing(0);
    pLayoutDown->setMargin(0);

    // 左侧布局
    QVBoxLayout *pLayoutLeft = new QVBoxLayout;
    pLayoutLeft->addWidget(m_pGroupBoxBasic);
    pLayoutLeft->addSpacing(12);
    pLayoutLeft->addWidget(m_pGroupBoxCustom);
    pLayoutLeft->addSpacing(12);
    pLayoutLeft->addLayout(pLayoutDown);
    pLayoutLeft->setSpacing(0);
    pLayoutLeft->addStretch();
    pLayoutLeft->setMargin(0);

    // 网格布局
    QGridLayout *m_pGridLayout = new QGridLayout;
    m_pGridLayout->addWidget(m_pLabH, 0, 0, Qt::AlignRight);
    m_pGridLayout->addWidget(m_pSpinBoxH, 0, 1);
    m_pGridLayout->addWidget(m_pLabS, 1, 0, Qt::AlignRight);
    m_pGridLayout->addWidget(m_pSpinBoxS, 1, 1);
    m_pGridLayout->addWidget(m_pLabV, 2, 0, Qt::AlignRight);
    m_pGridLayout->addWidget(m_pSpinBoxV, 2, 1);
    m_pGridLayout->addWidget(m_pLabR, 3, 0, Qt::AlignRight);
    m_pGridLayout->addWidget(m_pSpinBoxR, 3, 1);
    m_pGridLayout->addWidget(m_pLabG, 4, 0, Qt::AlignRight);
    m_pGridLayout->addWidget(m_pSpinBoxG,4, 1);
    m_pGridLayout->addWidget(m_pLabB, 5, 0, Qt::AlignRight);
    m_pGridLayout->addWidget(m_pSpinBoxB, 5, 1);

    // 色调布局
    QHBoxLayout *pLayoutHue = new QHBoxLayout;
    pLayoutHue->addStretch();
    pLayoutHue->addWidget(m_pSVColorArea);
    pLayoutHue->addSpacing(10);
    pLayoutHue->addWidget(m_pHColorArea);
    pLayoutHue->addSpacing(10);
    pLayoutHue->addLayout(m_pGridLayout);
    pLayoutHue->addStretch();
    pLayoutHue->setSpacing(0);
    pLayoutHue->setMargin(0);

    // 颜色预览布局
    QHBoxLayout *pLayoutPreview = new QHBoxLayout;
    pLayoutPreview->addSpacing(12);
    pLayoutPreview->addWidget(m_pLabCurColor);
    pLayoutPreview->addSpacing(8);
    pLayoutPreview->addWidget(m_pPreviewColorArea);
    pLayoutPreview->addSpacing(8);
    pLayoutPreview->addWidget(m_pLabNewColor);
    pLayoutPreview->addStretch();
    pLayoutPreview->addWidget(m_pBtnOk);
    pLayoutPreview->addSpacing(10);
    pLayoutPreview->addWidget(m_pBtnCancle);
    pLayoutPreview->addSpacing(4);
    pLayoutPreview->setSpacing(0);
    pLayoutPreview->setMargin(0);

    // 中间布局
    QVBoxLayout *pLayoutCenter = new QVBoxLayout;
    pLayoutCenter->addStretch();
    pLayoutCenter->addLayout(pLayoutHue);
    pLayoutCenter->addLayout(pLayoutPreview);
    pLayoutCenter->addStretch();
    pLayoutCenter->setMargin(0);

    // 布局
    QHBoxLayout *pLayoutMainR = new QHBoxLayout;
    pLayoutMainR->addSpacing(0);
    pLayoutMainR->addLayout(pLayoutLeft);
    pLayoutMainR->addSpacing(12);
    pLayoutMainR->addLayout(pLayoutCenter);
    pLayoutMainR->addSpacing(0);
    pLayoutCenter->setSpacing(0);
    pLayoutMainR->setContentsMargins(12, 0, 12, 12);

    // 主布局
    QVBoxLayout *pLayoutMain = new QVBoxLayout(this);
    pLayoutMain->addSpacing(0);
    pLayoutMain->addLayout(pLayoutTitle);
    pLayoutMain->addWidget(m_pLabSplitLine);
    pLayoutMain->addLayout(pLayoutMainR);
    pLayoutMain->addStretch();
    pLayoutMain->setMargin(0);

    // 各个界面的信号槽连接
    connect(m_pBasicColorArea, &BasicColorArea::sigColorItemSel, this, &ColorSelWidget::slotColorItemSel);
    connect(m_pCustomColorArea, &CustomColorArea::sigColorItemSel, this, &ColorSelWidget::slotColorItemSel);
    connect(m_pSVColorArea, &SVColorArea::sigSvChanged, m_pPreviewColorArea, &PreviewColorArea::slotSvChanged);
    connect(m_pPreviewColorArea, &PreviewColorArea::sigSvChanged, this, &ColorSelWidget::slotUpdateEditData);
    connect(m_pHColorArea, &HColorArea::sigHueChanged, m_pSVColorArea, &SVColorArea::slotHueChanged);

    // 颜色编辑框改变
    connect(m_pEditColor, &QLineEdit::textEdited, this, &ColorSelWidget::slotEditChanged);
    connect(m_pEditColor, &QLineEdit::editingFinished, this, &ColorSelWidget::slotEditFinished);

    // 各按钮
    connect(m_pBtnCustom, &QPushButton::clicked, this, &ColorSelWidget::slotAddCustomColor);
    connect(m_pBtnOk, &QPushButton::clicked, this, &ColorSelWidget::slotOkBtnClicked);
    connect(m_pBtnCancle, &QPushButton::clicked, this, &ColorSelWidget::slotCancelBtnClicked);
    connect(m_pBtnClose, &QPushButton::clicked, this, &ColorSelWidget::slotCancelBtnClicked);

    // 计数器控件
    connect(m_pSpinBoxH, SIGNAL(valueChanged(int)), this, SLOT(slotValueChangedH(int)));
    connect(m_pSpinBoxS, SIGNAL(valueChanged(int)), this, SLOT(slotValueChangedS(int)));
    connect(m_pSpinBoxV, SIGNAL(valueChanged(int)), this, SLOT(slotValueChangedV(int)));
    connect(m_pSpinBoxR, SIGNAL(valueChanged(int)), this, SLOT(slotValueChangedR(int)));
    connect(m_pSpinBoxG, SIGNAL(valueChanged(int)), this, SLOT(slotValueChangedG(int)));
    connect(m_pSpinBoxB, SIGNAL(valueChanged(int)), this, SLOT(slotValueChangedB(int)));
}

ColorSelWidget::ButtonRole ColorSelWidget::showDialog()
{
    show();
    QEventLoop evtLoop;
    m_pEvtLoop = &evtLoop;
    evtLoop.exec();

    m_pEvtLoop = NULL;
    hide();
    return m_buttonRole;
}

// 实现可拖拽窗口
void ColorSelWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bPressed = true;
        m_point = event->pos();
    }
}
void ColorSelWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bPressed)
    {
        move(event->pos() - m_point + pos());
    }
}
void ColorSelWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    m_bPressed = false;
}

// 同步饱和度与亮度区域、色调区域的颜色值
void ColorSelWidget::slotColorItemSel(const QColor &c)
{
    m_bNotEdit = true;

    // 同步饱和度与亮度区域、色调区域的颜色值
    m_pHColorArea->setHue(c.hue());
    m_pSVColorArea->setColor(c);

    m_bNotEdit = false;
}

// 添加自定义颜色
void ColorSelWidget::slotAddCustomColor()
{
    QColor color;
    color.setHsv(m_iHue, m_iSaturation, m_iBrightness);
    m_pCustomColorArea->setGivenColor(color);
}

// 确定按钮按下
void ColorSelWidget::slotOkBtnClicked()
{
    QColor color;
    color.setHsv(m_iHue, m_iSaturation, m_iBrightness);
    m_pPreviewColorArea->setCurColor(color);

    m_buttonRole = Yes;
    if (m_pEvtLoop != NULL)
    {
        m_pEvtLoop->exit();
    }
}

// 取消按钮按下
void ColorSelWidget::slotCancelBtnClicked()
{
    m_buttonRole = No;
    if (m_pEvtLoop != NULL)
    {
        m_pEvtLoop->exit();
    }
}

// HSV/RGB值改变触发的槽函数
void ColorSelWidget::slotValueChangedH(int h)
{
    if (m_bNotEdit)
    {
        return;
    }
    m_bNotEdit = true;

    m_iHue = h;
    m_pHColorArea->setHue(h);
    QColor color;
    color.setHsv(h, m_iSaturation, m_iBrightness);
    m_pSVColorArea->setHue(h);
    updateRGBColor(color);

    m_bNotEdit = false;
}

void ColorSelWidget::slotValueChangedS(int s)
{
    if (m_bNotEdit)
    {
        return;
    }
    m_bNotEdit = true;

    m_iSaturation = s;
    QColor color;
    color.setHsv(m_iHue, s, m_iBrightness);
    m_pSVColorArea->setSaturation(s);
    updateRGBColor(color);

    m_bNotEdit = false;
}

void ColorSelWidget::slotValueChangedV(int v)
{
    if (m_bNotEdit)
    {
        return;
    }
    m_bNotEdit = true;

    m_iBrightness = v;
    QColor color;
    color.setHsv(m_iHue, m_iSaturation, v);
    m_pSVColorArea->setBrightness(v);
    updateRGBColor(color);

    m_bNotEdit = false;
}

void ColorSelWidget::slotValueChangedR(int r)
{
    if (m_bNotEdit)
    {
        return;
    }
    m_bNotEdit = true;

    int iGreen = m_pSpinBoxG->value();
    int iBlue = m_pSpinBoxB->value();
    QColor color;
    color.setRgb(r, iGreen, iBlue);
    int h = m_iHue = color.hue();
    int s = m_iSaturation = color.saturation();
    int v = m_iBrightness = color.value();

    m_pHColorArea->setHue(h);
    m_pSVColorArea->setHsv(h, s, v);
    m_pPreviewColorArea->setNewColor(color);

    m_pSpinBoxH->setValue(h);
    m_pSpinBoxS->setValue(s);
    m_pSpinBoxV->setValue(v);

    QString strR = QString::number(r, 16);
    QString strG = QString::number(iGreen, 16);
    QString strB = QString::number(iBlue, 16);
    QString strRgb = QString("%1%2%3").arg(QString("%1").arg(strR.size() == 1 ? strR.prepend("0") : strR),
        QString("%1").arg(strG.size() == 1 ? strG.prepend("0") : strG),
        QString("%1").arg(strB.size() == 1 ? strB.prepend("0") : strB));
    m_pEditColor->setText(strRgb);

    m_bNotEdit = false;
}

void ColorSelWidget::slotValueChangedG(int g)
{
    if (m_bNotEdit)
    {
        return;
    }
    m_bNotEdit = true;

    int iRed = m_pSpinBoxR->value();
    int iBlue = m_pSpinBoxB->value();
    QColor color;
    color.setRgb(iRed, g, iBlue);
    int h = m_iHue = color.hue();
    int s = m_iSaturation = color.saturation();
    int v = m_iBrightness = color.value();

    m_pHColorArea->setHue(h);
    m_pSVColorArea->setHsv(h, s, v);
    m_pPreviewColorArea->setNewColor(color);

    m_pSpinBoxH->setValue(h);
    m_pSpinBoxS->setValue(s);
    m_pSpinBoxV->setValue(v);

    QString strR = QString::number(iRed, 16);
    QString strG = QString::number(g, 16);
    QString strB = QString::number(iBlue, 16);
    QString strRgb = QString("%1%2%3").arg(QString("%1").arg(strR.size() == 1 ? strR.prepend("0") : strR),
        QString("%1").arg(strG.size() == 1 ? strG.prepend("0") : strG),
        QString("%1").arg(strB.size() == 1 ? strB.prepend("0") : strB));
    m_pEditColor->setText(strRgb);

    m_bNotEdit = false;
}

void ColorSelWidget::slotValueChangedB(int b)
{
    if (m_bNotEdit)
    {
        return;
    }
    m_bNotEdit = true;

    int iRed = m_pSpinBoxR->value();
    int iGreen = m_pSpinBoxG->value();
    QColor color;
    color.setRgb(iRed, iGreen, b);
    int h = m_iHue = color.hue();
    int s = m_iSaturation = color.saturation();
    int v = m_iBrightness = color.value();

    m_pHColorArea->setHue(h);
    m_pSVColorArea->setHsv(h, s, v);
    m_pPreviewColorArea->setNewColor(color);

    m_pSpinBoxH->setValue(h);
    m_pSpinBoxS->setValue(s);
    m_pSpinBoxV->setValue(v);

    QString strR = QString::number(iRed, 16);
    QString strG = QString::number(iGreen, 16);
    QString strB = QString::number(b, 16);
    QString strRgb = QString("%1%2%3").arg(QString("%1").arg(strR.size() == 1 ? strR.prepend("0") : strR),
        QString("%1").arg(strG.size() == 1 ? strG.prepend("0") : strG),
        QString("%1").arg(strB.size() == 1 ? strB.prepend("0") : strB));
    m_pEditColor->setText(strRgb);

    m_bNotEdit = false;
}

void ColorSelWidget::updateRGBColor(const QColor &color)
{
    m_pPreviewColorArea->setNewColor(color);

    m_pSpinBoxR->setValue(color.red());
    m_pSpinBoxG->setValue(color.green());
    m_pSpinBoxB->setValue(color.blue());

    QString strR = QString::number(color.red(), 16);
    QString strG = QString::number(color.green(), 16);
    QString strB = QString::number(color.blue(), 16);
    QString strRgb = QString("%1%2%3").arg(QString("%1").arg(strR.size() == 1 ? strR.prepend("0") : strR),
        QString("%1").arg(strG.size() == 1 ? strG.prepend("0") : strG),
        QString("%1").arg(strB.size() == 1 ? strB.prepend("0") : strB));
    m_pEditColor->setText(strRgb);
}

// 更新颜色编辑框的值
void ColorSelWidget::slotUpdateEditData(int h, int s, int v)
{
    m_bNotEdit = true;

    m_iHue = h;
    m_iSaturation = s;
    m_iBrightness = v;
    QColor color;
    color.setHsv(h, s, v);
    m_pSpinBoxH->setValue(h);
    m_pSpinBoxS->setValue(s);
    m_pSpinBoxV->setValue(v);
    m_pSpinBoxR->setValue(color.red());
    m_pSpinBoxG->setValue(color.green());
    m_pSpinBoxB->setValue(color.blue());

    QString strR = QString::number(color.red(), 16);
    QString strG = QString::number(color.green(), 16);
    QString strB = QString::number(color.blue(), 16);
    QString strRgb = QString("%1%2%3").arg(QString("%1").arg(strR.size() == 1 ? strR.prepend("0") : strR),
        QString("%1").arg(strG.size() == 1 ? strG.prepend("0") : strG),
        QString("%1").arg(strB.size() == 1 ? strB.prepend("0") : strB));
    m_pEditColor->setText(strRgb);

    m_bNotEdit = false;
}

// 编辑框文本改变
void ColorSelWidget::slotEditChanged(const QString &strColor)
{
    m_bNotEdit = true;

    int r = 0, g = 0, b = 0;
    switch (strColor.length())
    {
    case 0:
    {
        r = g = b = 0;
    }
        break;
    case 1:
    case 2:
    {
        r = g = 0;
        bool ok;
        b = strColor.toInt(&ok, 16);
    }
        break;
    case 3:
    {
        QString strR = QString("%1%2").arg(strColor.left(1), strColor.left(1));
        QString strG = QString("%1%2").arg(strColor.mid(1, 1), strColor.mid(1, 1));
        QString strB = QString("%1%2").arg(strColor.right(1), strColor.right(1));
        bool ok;
        r = strR.toInt(&ok, 16);
        g = strG.toInt(&ok, 16);
        b = strB.toInt(&ok, 16);
    }
        break;
    case 4:
    {
        r = 0;
        QString strG = QString("%1").arg(strColor.left(2));
        QString strB = QString("%1").arg(strColor.right(2));
        bool ok;
        g = strG.toInt(&ok, 16);
        b = strB.toInt(&ok, 16);
    }
        break;
    case 5:
    {
        QString strR = QString("%1").arg(strColor.left(1));
        QString strG = QString("%1").arg(strColor.mid(1, 2));
        QString strB = QString("%1").arg(strColor.right(2));
        bool ok;
        r = strR.toInt(&ok, 16);
        g = strG.toInt(&ok, 16);
        b = strB.toInt(&ok, 16);
    }
        break;
    case 6:
    {
        QString strR = QString("%1").arg(strColor.left(2));
        QString strG = QString("%1").arg(strColor.mid(2, 2));
        QString strB = QString("%1").arg(strColor.right(2));
        bool ok;
        r = strR.toInt(&ok, 16);
        g = strG.toInt(&ok, 16);
        b = strB.toInt(&ok, 16);
    }
        break;
    default:
        break;
    }

    QColor color;
    color.setRgb(r, g, b);
    int h, s, v;
    h = m_iHue = color.hue();
    s = m_iSaturation = color.saturation();
    v = m_iBrightness = color.value();
    m_pHColorArea->setHue(h);
    m_pSVColorArea->setHsv(h, s, v);
    m_pPreviewColorArea->setNewColor(color);

    m_pSpinBoxH->setValue(h);
    m_pSpinBoxS->setValue(s);
    m_pSpinBoxV->setValue(v);
    m_pSpinBoxR->setValue(r);
    m_pSpinBoxG->setValue(g);
    m_pSpinBoxB->setValue(b);

    m_bNotEdit = false;
}

// 编辑框编辑完成
void ColorSelWidget::slotEditFinished()
{
    QString strColor = m_pEditColor->text();
    switch (strColor.length())
    {
    case 0:
    {
        m_pEditColor->setText("000000");
    }
        break;
    case 1:
    {
        m_pEditColor->setText(strColor.prepend("00000"));
    }
        break;
    case 2:
    {
        m_pEditColor->setText(strColor.prepend("0000"));
    }
        break;
    case 3:
    {
        QString strR = QString("%1%2").arg(strColor.left(1), strColor.left(1));
        QString strG = QString("%1%2").arg(strColor.mid(1, 1), strColor.mid(1, 1));
        QString strB = QString("%1%2").arg(strColor.right(1), strColor.right(1));
        m_pEditColor->setText(strR.append(strG).append(strB));
    }
        break;
    case 4:
    {
        QString strG = QString("%1").arg(strColor.left(2));
        QString strB = QString("%1").arg(strColor.right(2));
        m_pEditColor->setText(strG.append(strB).prepend("00"));
    }
        break;
    case 5:
    {
        QString strR = QString("%1").arg(strColor.left(1));
        QString strG = QString("%1").arg(strColor.mid(1, 2));
        QString strB = QString("%1").arg(strColor.right(2));
        m_pEditColor->setText(strR.append(strG).append(strB).prepend("0"));
    }
        break;
    case 6:
    {
        return;
    }
        break;
    default:
        break;
    }
}
