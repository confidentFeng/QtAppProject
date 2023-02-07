#include "HoverMenu.h"

HoverMenu::HoverMenu(QWidget *parent) : QWidget(parent)
{
    /* 主界面-初始化 */
    this->setFixedSize(MENU_WIDTH, MENU_HEIGHT);
    this->setObjectName("HoverMenu");
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_StyledBackground); // 不继承父窗口样式

    // 标题栏-窗口部件初始化
    m_pMyTitleBar = new MyTitleBar;
    m_pMyTitleBar->setFixedSize(width(), 32);

    // 窗口部件初始化
    m_pBtnOpt1 = new MyIconBtn;
    m_pBtnOpt2 = new MyIconBtn;
    m_pBtnOpt3 = new MyIconBtn;
    m_pBtnOpt4 = new MyIconBtn;
    m_pBtnOther = new MyIconBtn;
    m_pBtnOpt1->setObjectName("HoverMenu_BtnOpt1");
    m_pBtnOpt2->setObjectName("HoverMenu_BtnOpt2");
    m_pBtnOpt3->setObjectName("HoverMenu_BtnOpt3");
    m_pBtnOpt4->setObjectName("HoverMenu_BtnOpt4");
    m_pBtnOpt1->setFixedSize(59, 30); // 要减2给圆角
    m_pBtnOpt2->setFixedSize(60, 30);
    m_pBtnOpt3->setFixedSize(60, 30);
    m_pBtnOpt4->setFixedSize(59, 30);
    m_pBtnOpt1->m_iconNormal = ":/Image/HoverMenu/btn_bigScreen_nor.png";
    m_pBtnOpt1->m_iconHover = ":/Image/HoverMenu/btn_bigScreen_hov.png";
    m_pBtnOpt1->m_iconPressed = ":/Image/HoverMenu/btn_bigScreen_pre.png";
    m_pBtnOpt2->m_iconNormal = ":/Image/HoverMenu/btn_bigScreen_nor.png";
    m_pBtnOpt2->m_iconHover = ":/Image/HoverMenu/btn_bigScreen_hov.png";
    m_pBtnOpt2->m_iconPressed = ":/Image/HoverMenu/btn_bigScreen_pre.png";
    m_pBtnOpt3->m_iconNormal = ":/Image/HoverMenu/btn_bigScreen_nor.png";
    m_pBtnOpt3->m_iconHover = ":/Image/HoverMenu/btn_bigScreen_hov.png";
    m_pBtnOpt3->m_iconPressed = ":/Image/HoverMenu/btn_bigScreen_pre.png";
    m_pBtnOpt4->m_iconNormal = ":/Image/HoverMenu/btn_bigScreen_nor.png";
    m_pBtnOpt4->m_iconHover = ":/Image/HoverMenu/btn_bigScreen_hov.png";
    m_pBtnOpt4->m_iconPressed = ":/Image/HoverMenu/btn_bigScreen_pre.png";

    m_pComboBox = new QComboBox;
    m_pComboBox->addItem("Chinese");
    m_pComboBox->addItem("English");

    // 布局
    QHBoxLayout *pHLayout = new QHBoxLayout;
    pHLayout->addWidget(m_pBtnOpt1);
    pHLayout->addWidget(m_pBtnOpt2);
    pHLayout->addWidget(m_pBtnOpt3);
    pHLayout->addWidget(m_pBtnOpt4);
    pHLayout->setSpacing(0);
    pHLayout->setMargin(0);

    // 主布局
    QVBoxLayout *pVLayoutMain = new QVBoxLayout(this);
    pVLayoutMain->addWidget(m_pMyTitleBar);
    pVLayoutMain->addLayout(pHLayout);
    pVLayoutMain->addWidget(m_pComboBox);
    pVLayoutMain->addStretch();
    pVLayoutMain->setMargin(0);

    // 设置互斥
    m_pBtnOpt1->setCheckable(true);
    m_pBtnOpt2->setCheckable(true);
    m_pBtnOpt3->setCheckable(true);
    m_pBtnOpt4->setCheckable(true);
    m_pBtnOther->setCheckable(true);
    // 将需要互斥的按钮全部添加到QButtonGroup中
    QButtonGroup *btnGroup = new QButtonGroup;
    btnGroup->setExclusive(true); // 设置是否互斥
    btnGroup->addButton(m_pBtnOpt1);
    btnGroup->addButton(m_pBtnOpt2);
    btnGroup->addButton(m_pBtnOpt3);
    btnGroup->addButton(m_pBtnOpt4);
    btnGroup->addButton(m_pBtnOther);
    m_pBtnOpt1->setChecked(false); // 默认先选中一个按钮

    // 文本读取语言选项
    QString language = "CH";
    AppConfig::Get().readIni(QString("./user.ini"), QString("language"), language);
    if(language == "CH")
        m_pComboBox->setCurrentIndex(0);
    else
        m_pComboBox->setCurrentIndex(1);

    // 统一设置需要被翻译的文本
    translateUI();

    // 选项1按钮
    connect(m_pBtnOpt1, &QPushButton::clicked, [=]{
        emit AppEvent::Get().sigShowWidget1(); // 显示界面1
    });
    // 选项2按钮
    connect(m_pBtnOpt2, &QPushButton::clicked, [=]{
        emit AppEvent::Get().sigShowWidget2(); // 显示界面1
    });
    // 选项3按钮
    connect(m_pBtnOpt3, &QPushButton::clicked, [=]{

    });
    // 选项4按钮
    connect(m_pBtnOpt4, &QPushButton::clicked, [=]{

    });
    // 标题栏的关闭按钮
    connect(m_pMyTitleBar, &MyTitleBar::sigClose, [=]{
        this->hide();
    });

    // 下拉框
    connect(m_pComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [=](int index) {
        if(index == 0) {
            AppConfig::Get().writeIni(QString("./user.ini"), QString("language"), QString("CH"));
            emit AppEvent::Get().sigSwLanguage(UI_CH);
        }
        else {
            AppConfig::Get().writeIni(QString("./user.ini"), QString("language"), QString("EN"));
            emit AppEvent::Get().sigSwLanguage(UI_EN);
        }
    });
}

// 统一设置需要被翻译的文本
void HoverMenu::translateUI()
{
    m_pMyTitleBar->setTitleName(tr("悬浮菜单"));
    m_pBtnOpt1->setText(tr("选项1"));
    m_pBtnOpt2->setText(tr("选项2"));
    m_pBtnOpt3->setText(tr("中文"));
    m_pBtnOpt4->setText(tr("英文"));
}

// 实现可拖拽窗口
void HoverMenu::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // 当透明窗口显示时，禁止拖拽窗口
        m_bPressed = true;
        m_point = event->pos();
    }
}
void HoverMenu::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bPressed)
        move(event->pos() - m_point + pos());
}
void HoverMenu::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_bPressed = false;
}
