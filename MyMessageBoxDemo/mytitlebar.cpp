#include "mytitlebar.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QFile>
#include <QMouseEvent>

MyTitleBar::MyTitleBar(QWidget *parent) : QWidget(parent)
{
    // 初始化标题栏背景色
    m_colorR = 153;
    m_colorG = 153;
    m_colorB = 153;
    // 初始化移动窗口的变量
    m_isPressed = false;
    // 初始化按钮类型
    m_buttonType = MIN_MAX_BUTTON;
    // 窗口边框宽度
    m_windowBorderWidth = 0;

    // 设置标题栏高度
    this->setFixedHeight(TITLE_HEIGHT);
    // 设置默认标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint);

    // 初始化控件
    initControl();

    // 信号槽的绑定（最小化、最大化、还原、关闭按钮）
    connect(m_pButtonMin, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pButtonMax, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pButtonRestore, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pButtonClose, SIGNAL(clicked(bool)), this, SLOT(onClicked()));

    // 加载本地样式文件：可以将样式直接写在文件中，程序运行时直接加载进来
    loadStyleSheet("MyTitle");
}

MyTitleBar::~MyTitleBar()
{

}

// 初始化控件
void MyTitleBar::initControl()
{
    // 标题栏图标
    m_pIcon = new QLabel;
    // 标题栏内容
    m_pTitleLabel = new QLabel;

    // 初始化按钮（最小化、最大化\还原、关闭按钮）
    m_pButtonMin = new QPushButton;
    m_pButtonRestore = new QPushButton;
    m_pButtonMax = new QPushButton;
    m_pButtonClose = new QPushButton;
    // 设置按钮的固定大小
    m_pButtonMin->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    m_pButtonRestore->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    m_pButtonMax->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    m_pButtonClose->setFixedSize(QSize(BUTTON_WIDTH, BUTTON_HEIGHT));
    // 设置按钮的名称
    m_pTitleLabel->setObjectName("TitleContent");
    m_pButtonMin->setObjectName("ButtonMin");
    m_pButtonRestore->setObjectName("ButtonRestore");
    m_pButtonMax->setObjectName("ButtonMax");
    m_pButtonClose->setObjectName("ButtonClose");
    // 设置按钮的提示信息
    m_pButtonMin->setToolTip("最小化");
    m_pButtonRestore->setToolTip("还原");
    m_pButtonMax->setToolTip("最大化");
    m_pButtonClose->setToolTip("关闭");

    // 将控件添加到水平布局中
    QHBoxLayout* mylayout = new QHBoxLayout(this);
    mylayout->addWidget(m_pIcon);
    mylayout->addWidget(m_pTitleLabel);
    mylayout->addWidget(m_pButtonMin);
    mylayout->addWidget(m_pButtonRestore);
    mylayout->addWidget(m_pButtonMax);
    mylayout->addWidget(m_pButtonClose);
    // 设置4个方向的外边距
    mylayout->setContentsMargins(5, 0, 0, 0);
    mylayout->setSpacing(0);
    // 设置控件在布局（layout）里面的大小变化的属性
    m_pTitleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

// 设置标题栏背景色,在paintEvent事件中进行绘制标题栏背景色
void MyTitleBar::setBackgroundColor(int colorR, int colorG, int colorB)
{
    // 在构造函数中给了默认值，可以外部设置颜色值改变标题栏背景色
    m_colorR = colorR;
    m_colorG = colorG;
    m_colorB = colorB;
    // 重新绘制（调用paintEvent事件）
    this->update();
}

// 设置标题栏图标
void MyTitleBar::setTitleIcon(QString filePath, QSize IconSize)
{
    QPixmap titleIcon(filePath);
    m_pIcon->setPixmap(titleIcon.scaled(IconSize));
}

// 设置标题内容
void MyTitleBar::setTitleContent(QString titleContent, int titleFontSize)
{
    // 设置标题字体大小
    QFont font = m_pTitleLabel->font();
    font.setPointSize(titleFontSize);
    m_pTitleLabel->setFont(font);
    // 设置标题标签内容
    m_pTitleLabel->setText(titleContent);
    // 设置标题栏内容
    m_titleContent = titleContent;
}

// 设置标题栏长度
void MyTitleBar::setTitleWidth(int width)
{
    this->setFixedWidth(width);
}

// 设置标题颜色
void MyTitleBar::setTitleColor(int colorR, int colorG, int colorB)
{
    m_pTitleLabel->setStyleSheet(QString("color: rgb(%1, %2, %3);").arg(colorR).arg(colorG).arg(colorB));
}

// 设置标题栏上按钮类型
void MyTitleBar::setButtonType(ButtonType buttonType)
{
    // 由于不同窗口标题栏上的按钮都不一样，所以可以自定义标题栏中的按钮
    // 这里提供了四个按钮，分别为最小化、还原、最大化、关闭按钮，如果需要其他按钮可自行添加设置
    m_buttonType = buttonType;
    switch (buttonType)
    {
        case MIN_BUTTON:
        {
            m_pButtonRestore->setVisible(false);
            m_pButtonMax->setVisible(false);
        }
        break;
        case MIN_MAX_BUTTON:
        {
            m_pButtonRestore->setVisible(false);
        }
        break;
        case ONLY_CLOSE_BUTTON:
        {
            m_pButtonMin->setVisible(false);
            m_pButtonRestore->setVisible(false);
            m_pButtonMax->setVisible(false);
        }
        break;
    }
}

// 设置标题栏中的标题是否会自动滚动，跑马灯的效果
void MyTitleBar::setTitleRoll()
{
    // 一般情况下标题栏中的标题内容是不滚动的，但是既然自定义就看自己需要嘛，想怎么设计就怎么搞O(∩_∩)O！
    connect(&m_titleRollTimer, SIGNAL(timeout()), this, SLOT(onRollTitle()));
    m_titleRollTimer.start(200);
}

// 设置窗口边框宽度
void MyTitleBar::setWindowBorderWidth(int borderWidth)
{
    m_windowBorderWidth = borderWidth;
}

// 绘图事件：绘制标题栏背景色
void MyTitleBar::paintEvent(QPaintEvent *event)
{
    // 设置标题栏背景色
    QPainter painter(this);
    QPainterPath pathBack;
    pathBack.setFillRule(Qt::WindingFill);
    pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()), 3, 3);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.fillPath(pathBack, QBrush(QColor(m_colorR, m_colorG, m_colorB)));

    // 当窗口最大化或者还原后，窗口长度变了，标题栏的长度应当一起改变
    // 这里减去m_windowBorderWidth，是因为窗口可能设置了不同宽度的边框
    // 如果窗口有边框则需要设置m_windowBorderWidth的值，否则m_windowBorderWidth默认为0
    if (this->width() != (this->parentWidget()->width() - m_windowBorderWidth))
    {
        this->setFixedWidth(this->parentWidget()->width() - m_windowBorderWidth);
    }
    QWidget::paintEvent(event);
}

// 鼠标双击事件：主要是实现双击标题栏进行最大化和最小化操作
void MyTitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    // 只有存在最大化、还原按钮时双击才有效;
    if (m_buttonType == MIN_MAX_BUTTON)
    {
        // 通过最大化按钮的状态判断当前窗口是处于最大化还是原始大小状态
        // 或者通过单独设置变量来表示当前窗口状态
        if (m_pButtonMax->isVisible())
        {
            m_pButtonRestore->setVisible(true);
            m_pButtonMax->setVisible(false);
            QWidget *pWindow = this->window(); //获得标题栏所在的窗口
            pWindow->showMaximized();
        }
        else
        {
            m_pButtonRestore->setVisible(false);
            m_pButtonMax->setVisible(true);
            QWidget *pWindow = this->window(); //获得标题栏所在的窗口
            pWindow->showNormal();
        }
    }

    return QWidget::mouseDoubleClickEvent(event);
}

// 以下通过mousePressEvent、mouseMoveEvent、mouseReleaseEvent三个事件实现了鼠标拖动标题栏移动窗口的效果
void MyTitleBar::mousePressEvent(QMouseEvent *event)
{
    if (m_buttonType == MIN_MAX_BUTTON)
    {
        // 在窗口最大化时禁止拖动窗口
        if (m_pButtonMax->isVisible())
        {
            m_isPressed = true;
            m_startMovePos = event->globalPos();
        }
    }
    else
    {
        m_isPressed = true;
        m_startMovePos = event->globalPos();
    }

    return QWidget::mousePressEvent(event);
}

void MyTitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isPressed)
    {
        QPoint movePoint = event->globalPos() - m_startMovePos;
        QPoint widgetPos = this->parentWidget()->pos();
        m_startMovePos = event->globalPos();
        this->parentWidget()->move(widgetPos.x() + movePoint.x(), widgetPos.y() + movePoint.y());
    }
    return QWidget::mouseMoveEvent(event);
}

void MyTitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    m_isPressed = false;
    return QWidget::mouseReleaseEvent(event);
}

// 加载本地样式文件：可以将样式直接写在文件中，程序运行时直接加载进来
void MyTitleBar::loadStyleSheet(const QString &sheetName)
{
    // ://image/MyTitle/MyTitle.css
    QFile file("://image/MyTitle/" + sheetName + ".css");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet = this->styleSheet();
        styleSheet += QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
    }
}

// 该方法主要是让标题栏中的标题显示为滚动的效果
void MyTitleBar::onRollTitle()
{
    static int nPos = 0;
    QString titleContent = m_titleContent;
    // 当截取的位置比字符串长时，从头开始
    if (nPos > titleContent.length())
        nPos = 0;

    m_pTitleLabel->setText(titleContent.mid(nPos));
    nPos++;
}

// 进行最小化、最大化/还原、关闭操作
void MyTitleBar::onClicked()
{
    //QObject::Sender()返回发送信号的对象的指针，返回类型为QObject *
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());

    QWidget *pWindow = this->window(); // 获得标题栏所在的窗口

    if (pWindow->isTopLevel())
    {
        //判断发送信号的对象是哪个按钮
        if (pButton == m_pButtonMin) // 窗口最小化显示
        {
            pWindow->showMinimized();
        }
        else if (pButton == m_pButtonMax) // 窗口最大化
        {
            m_pButtonRestore->setVisible(true);
            m_pButtonMax->setVisible(false);
            pWindow->showMaximized();
        }
        else if (pButton == m_pButtonRestore) // 窗口还原
        {
            m_pButtonRestore->setVisible(false);
            m_pButtonMax->setVisible(true);
            pWindow->showNormal();
        }
        else if (pButton == m_pButtonClose) //窗口关闭
        {
            pWindow->close();
        }
    }
}
