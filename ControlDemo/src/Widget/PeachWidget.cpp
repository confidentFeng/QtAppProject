#include "PeachWidget.h"

PeachWidget::PeachWidget(QWidget *parent) : QWidget(parent)
{
    //初始化窗口边框
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_StyledBackground); // 禁止父窗口样式影响子控件样式
    this->setFixedSize(1030, 685);
    this->setObjectName("PeachWidget");
    this->setProperty("canMove", true);

    // 初始化背景界面
    m_pBackWidget = new QWidget;
    m_pBackWidget->setFixedSize(width()-18, height()-18);
    m_pBackWidget->setObjectName("PeachWidget_BackWidget");
    // 左侧子界面
    m_pWidgetLeft = new QWidget;
    m_pWidgetLeft->setFixedSize(252, 640);
    m_pWidgetLeft->setObjectName("PeachWidget_WidgetLeft");

    // logo图标等窗口部件
    m_pLabLogo = new QLabel;
    m_pLabLogo->setFixedSize(30, 30);
    m_pLabLogo->setObjectName("PeachWidget_LabLogo");
    m_pLabLogo->setPixmap(QPixmap(":/Image/Widget/logo.png"));
    m_pLabTitle = new QLabel;
    m_pLabTitle->setObjectName("PeachWidget_LabTitle");
    m_pBtnSet = new QPushButton;
    m_pBtnSet->setFixedSize(30, 30);
    m_pBtnSet->setObjectName("PeachWidget_BtnSet");
    m_pBtnSet->setIcon(QIcon(":/Image/Widget/setting.png"));
    m_pBtnHomePage = new QPushButton;
    m_pBtnHomePage->setFixedSize(30, 30);
    m_pBtnHomePage->setObjectName("PeachWidget_BtnHomePage");
    m_pBtnHomePage->setIcon(QIcon(":/Image/Widget/member.png"));

    // 服务相关按钮
    m_pLabService = new QLabel;
    m_pLabService->setObjectName("PeachWidget_LabService");
    m_pBtnSplitScr = new QToolButton;
    m_pBtnSplitScr->setFixedSize(70, 70);
    m_pBtnSplitScr->setObjectName("PeachWidget_Btn1");
    m_pBtnSplitScr->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_pBtnSplitScr->setIcon(QIcon(":/Image/Widget/modular.png"));
    m_pBtnLoad = new QToolButton;
    m_pBtnLoad->setFixedSize(70, 70);
    m_pBtnLoad->setObjectName("PeachWidget_Btn2");
    m_pBtnLoad->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_pBtnLoad->setIcon(QIcon(":/Image/Widget/umbrella.png"));
    m_pBtnMask = new QToolButton;
    m_pBtnMask->setFixedSize(70, 70);
    m_pBtnMask->setObjectName("PeachWidget_Btn3");
    m_pBtnMask->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_pBtnMask->setIcon(QIcon(":/Image/Widget/money.png"));
    m_pBtn4 = new QToolButton;
    m_pBtn4->setFixedSize(70, 70);
    m_pBtn4->setObjectName("PeachWidget_Btn4");
    m_pBtn4->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_pBtn4->setIcon(QIcon(":/Image/Widget/member.png"));
    m_pBtn5 = new QToolButton;
    m_pBtn5->setFixedSize(70, 70);
    m_pBtn5->setObjectName("PeachWidget_Btn5");
    m_pBtn5->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    m_pBtn5->setIcon(QIcon(":/Image/Widget/phone.png"));
    m_pBtn6 = new QToolButton;
    m_pBtn6->setFixedSize(70, 70);
    m_pBtn6->setObjectName("PeachWidget_Btn6");
    m_pBtn6->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    // 最小化按钮等界面
    m_pBtnLittleShow = new QPushButton;
    m_pBtnLittleShow->setFixedSize(35, 35);
    m_pBtnLittleShow->setObjectName("PeachWidget_BtnLittleShow");
    m_pBtnLittleShow->setIcon(QIcon(":/Image/Widget/mini.png"));
    m_pBtnHome = new QPushButton;
    m_pBtnHome->setFixedSize(35, 35);
    m_pBtnHome->setObjectName("PeachWidget_BtnHome");
    m_pBtnHome->setIcon(QIcon(":/Image/Widget/home.png"));
    m_pBtnLogout = new QPushButton;
    m_pBtnLogout->setFixedSize(35, 35);
    m_pBtnLogout->setObjectName("PeachWidget_BtnLogout");
    m_pBtnLogout->setIcon(QIcon(":/Image/Widget/logout.png"));

    // 各按钮
    m_pBtnStack1 = new QPushButton;
    m_pBtnStack1->setFixedSize(100, 30);
    m_pBtnStack1->setObjectName("PeachWidget_BtnStack1");
    m_pBtnStack2 = new QPushButton;
    m_pBtnStack2->setFixedSize(100, 30);
    m_pBtnStack2->setObjectName("PeachWidget_BtnStack2");
    m_pBtnStack3 = new QPushButton;
    m_pBtnStack3->setFixedSize(100, 30);
    m_pBtnStack3->setObjectName("PeachWidget_BtnStack3");
    m_pBtnStack4 = new QPushButton;
    m_pBtnStack4->setFixedSize(100, 30);
    m_pBtnStack4->setObjectName("PeachWidget_BtnStack4");


    // 右侧子界面
    m_pWidgetRight = new QWidget;
    m_pWidgetRight->setFixedSize(STACK_WIDTH, m_pWidgetLeft->height());
    m_pWidgetRight->setObjectName("PeachWidget_WidgetRight");

    // 堆栈窗口
    m_pStackedWidget = new QStackedWidget;
    m_pStackedWidget->setFixedSize(STACK_WIDTH, STACK_HEIGHT);
    m_pStackedWidget->setObjectName("PeachWidget_StackedWidget");
//    m_pStackedWidget->addWidget(m_pWidgetControl);
//    m_pStackedWidget->addWidget(m_pFlatUiWidget);
//    m_pStackedWidget->addWidget(m_pWifiListWidget);
//    m_pStackedWidget->addWidget(m_pCarouselWidget);

    // Logo图标布局
    QHBoxLayout *pLayoutLogo = new QHBoxLayout;
    pLayoutLogo->addSpacing(16);
    pLayoutLogo->addWidget(m_pLabLogo);
    pLayoutLogo->addWidget(m_pLabTitle);
    pLayoutLogo->addStretch();
    pLayoutLogo->addWidget(m_pBtnSet);
    pLayoutLogo->addWidget(m_pBtnHomePage);
    pLayoutLogo->addSpacing(12);
    pLayoutLogo->setMargin(0);
    pLayoutLogo->setSpacing(9);
    // 服务按钮布局
    QGridLayout *pLayoutGrid = new QGridLayout;
    pLayoutGrid->addWidget(m_pBtnSplitScr, 0, 0);
    pLayoutGrid->addWidget(m_pBtnLoad, 0, 1);
    pLayoutGrid->addWidget(m_pBtnMask, 0, 2);
    pLayoutGrid->addWidget(m_pBtn4, 1, 0);
    pLayoutGrid->addWidget(m_pBtn5, 1, 1);
    pLayoutGrid->addWidget(m_pBtn6, 1, 2);
    pLayoutGrid->setSpacing(3);
    // 最小化按钮等界面
    QHBoxLayout *pLayoutMin = new QHBoxLayout;
    pLayoutMin->addStretch(1);
    pLayoutMin->addWidget(m_pBtnLittleShow);
    pLayoutMin->addStretch(2);
    pLayoutMin->addWidget(m_pBtnHome);
    pLayoutMin->addStretch(2);
    pLayoutMin->addWidget(m_pBtnLogout);
    pLayoutMin->addStretch(1);
    pLayoutMin->setMargin(0);
    pLayoutMin->setSpacing(0);
    // 左侧布局
    QVBoxLayout *pLayoutLeft = new QVBoxLayout(m_pWidgetLeft);
    pLayoutLeft->addSpacing(3);
    pLayoutLeft->addLayout(pLayoutLogo);
    pLayoutLeft->addStretch();
    pLayoutLeft->addWidget(m_pLabService);
    pLayoutLeft->addSpacing(12);
    pLayoutLeft->addLayout(pLayoutGrid);
    pLayoutLeft->addStretch();
    pLayoutLeft->addLayout(pLayoutMin);
    pLayoutLeft->addSpacing(3);
    pLayoutLeft->setSpacing(0);
    pLayoutLeft->setMargin(0);

    // 按钮布局
    QHBoxLayout *pLayoutBtn = new QHBoxLayout;
    pLayoutBtn->addStretch();
    pLayoutBtn->addWidget(m_pBtnStack1);
    pLayoutBtn->addSpacing(40);
    pLayoutBtn->addWidget(m_pBtnStack2);
    pLayoutBtn->addSpacing(40);
    pLayoutBtn->addWidget(m_pBtnStack3);
    pLayoutBtn->addSpacing(40);
    pLayoutBtn->addWidget(m_pBtnStack4);
    pLayoutBtn->addStretch();
    pLayoutBtn->setMargin(0);
    pLayoutBtn->setSpacing(0);
    // 右侧布局
    QVBoxLayout *pLayoutRight = new QVBoxLayout(m_pWidgetRight);
    pLayoutRight->addStretch();
    pLayoutRight->addLayout(pLayoutBtn);
    pLayoutRight->addSpacing(16);
    pLayoutRight->addWidget(m_pStackedWidget);
    pLayoutRight->addSpacing(2);
    pLayoutRight->setSpacing(0);
    pLayoutRight->setMargin(0);

    // 背景界面布局
    QHBoxLayout *pLayoutBack = new QHBoxLayout(m_pBackWidget);
    pLayoutBack->addSpacing(3);
    pLayoutBack->addWidget(m_pWidgetLeft);
    pLayoutBack->addStretch();
    pLayoutBack->addWidget(m_pWidgetRight);
    pLayoutBack->addSpacing(3);
    pLayoutBack->setSpacing(0);
    pLayoutBack->setMargin(0);
    // 主布局
    QVBoxLayout *pLayoutMain = new QVBoxLayout(this);
    pLayoutMain->addWidget(m_pBackWidget);
    pLayoutMain->setSpacing(0);
    pLayoutMain->setContentsMargins(9, 9, 9, 9);

    // 界面边框添加阴影
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setColor(QColor("#444444"));
    shadow->setBlurRadius(16);
    m_pBackWidget->setGraphicsEffect(shadow);
    pLayoutBack->setMargin(12);

    // 分屏界面
    m_pSplitScreenWidget = new SplitScreenWidget(this);
    m_pSplitScreenWidget->move(50,50);
    m_pSplitScreenWidget->raise();
    m_pSplitScreenWidget->hide();

    // 分屏自定义界面
    m_pSplitScrCustomWidget = new SplitScrCustomWidget(this);
    m_pSplitScrCustomWidget->move(m_pSplitScreenWidget->x()+m_pSplitScreenWidget->width()+12, m_pSplitScreenWidget->y());
    m_pSplitScrCustomWidget->raise();
    m_pSplitScrCustomWidget->hide();

    // 冒泡提示框
    m_pBubbleTip = new BubbleTipsWidget(this);
    m_pBubbleTip->setBackColor(255,255,255);
    m_pBubbleTip->setContent(tr("确认删除此分隔模式？"), QColor(102,102,102));
    m_pBubbleTip->setFixedSize(200, 100);
    m_pBubbleTip->hide();



    // 弹出提示框
    m_pWidget = new Widget(this);
    m_pWidget->move((width()-m_pWidget->width())/2, (height()-m_pWidget->height())/2);
    m_pWidget->hide();

    // 显示冒泡提示框
    connect(m_pSplitScreenWidget, &SplitScreenWidget::sigBubbleShow, [=](const bool &isShow, const int &x, const int &y){
        if(isShow) {
            double size = 0.5;
            m_pBubbleTip->setDirect(DIRECT::DIRECT_BOTTOM, size);
            m_pBubbleTip->move(m_pSplitScreenWidget->x()+x-13, m_pSplitScreenWidget->y()+y-m_pBubbleTip->height() - 2);
            m_pBubbleTip->show();
        }
        else {
            m_pBubbleTip->hide();
        }
    });

    // 冒泡提示框-确定按钮
    connect(m_pBubbleTip, &BubbleTipsWidget::sigOk, [=]{
        m_pBubbleTip->hide();

        m_pSplitScreenWidget->delSplitBtn();
    });

    initTray();

    // 初始化信号槽连接
    initSigSlot();

    connect(m_pBtnStack1, &QPushButton::clicked, [=]{
        m_pStackedWidget->setCurrentIndex(0);
    });
    connect(m_pBtnStack2, &QPushButton::clicked, [=]{
        m_pStackedWidget->setCurrentIndex(1);
    });
    connect(m_pBtnStack3, &QPushButton::clicked, [=]{
        m_pStackedWidget->setCurrentIndex(2);
    });
    connect(m_pBtnStack4, &QPushButton::clicked, [=]{
        m_pStackedWidget->setCurrentIndex(3);
    });

    // 最小化按钮
    connect(m_pBtnLittleShow, &QPushButton::clicked, [=]{
        this->littleShow();
    });

    // 注销按钮
    connect(m_pBtnLogout, &QPushButton::clicked, [=]{
        this->close();
    });

    // 显示自定义分屏界面
    connect(&AppEvent::Get(), &AppEvent::sigShowCustomScr, [=]() {
        // 显示自定义分屏界面
        m_pSplitScrCustomWidget->show();
    });


    // 显示自定义分屏界面
    connect(&AppEvent::Get(), &AppEvent::sigAddSplitScrBtn, [=](QVector<StGrid> vecRectCell) {
        // 获取当前分屏模式
        //KVM_PRE_MODE_E splitMode;
        int mode = (int)KVM_PRE_MODE_CUSTOM0;
        static int index = 0;

        // 添加分屏按钮
        m_pSplitScreenWidget->addSplitScrBtn(vecRectCell, KVM_PRE_MODE_E(mode+index));

        index++;
    });

    // 分屏按钮
    connect(m_pBtnSplitScr, &QPushButton::clicked, [=]{
        m_pSplitScreenWidget->setVisible(!m_pSplitScreenWidget->isVisible());
    });


//    // 遮罩界面
//    connect(m_pBtnMask, &QPushButton::clicked, [=]{
//        // 设置遮罩的父窗口
//          MaskWidget *maskForm = new MaskWidget(this);
//          maskForm->setTopWidget(this);

//          // 构造显示窗口ToolTips
//          QDialog *toolTips = new QDialog();
//          // 注册显示窗口，进行事件拦截（显示窗口开关，遮罩也跟着开关）。
//          maskForm->installWidget(toolTips);
//          toolTips->exec();
//    });

    //
    connect(m_pBtn4, &QPushButton::clicked, [=]{
        m_pWidget->setVisible(!m_pWidget->isVisible());
    });
}

// 统一设置需要被翻译的文本
void PeachWidget::translateUI()
{
    m_pLabTitle->setText("fengMisaka");
    m_pLabService->setText(tr("服务"));

    m_pBtnSplitScr->setText(tr("分屏"));
    m_pBtnLoad->setText(tr("加载"));
    m_pBtnMask->setText(tr("遮罩"));
    m_pBtn4->setText(tr("待定"));
    m_pBtn5->setText(tr("待定"));
    m_pBtn6->setText(tr("待定"));

    m_pBtnStack1->setText(tr("控件"));
    m_pBtnStack2->setText(tr("Falt控件"));
    m_pBtnStack3->setText(tr("列表"));
    m_pBtnStack4->setText(tr("轮播图"));


}

// 初始化托盘
void PeachWidget::initTray()
{
    // 初始化消息框
    m_pMsgBox = new MyMessageBox();
    connect(m_pMsgBox,SIGNAL(btnchicked(int)),this,SLOT(changeMboxReturn(int)));

    // 最小化到托盘
    QIcon icon = QIcon(":/Image/Widget/logo.png");//设置最小图标
    m_pTrayIcon = new QSystemTrayIcon(this);
    m_pTrayIcon->setIcon(icon);
    m_pTrayIcon->setToolTip("Peach"); //提示文字
    // 添加托盘列表项动作(还原与退出)
    returnNormal = new QAction(" Show", this);
    returnNormal->setFont(QFont("Arial", 9));
    returnNormal->setObjectName("returnNormal");
    returnNormal->setIcon(QIcon(":/Image/Widget/show.png"));
    quitAction = new QAction(" Quit", this);
    quitAction->setFont(QFont("Arial", 9));
    quitAction->setObjectName("quitAction");
    quitAction->setIcon(QIcon(":/Image/Widget/out.png"));
    // 绑定槽函数退出
    connect(quitAction, &QAction::triggered, qApp, &QApplication::quit);
    // 绑定槽函数还原界面
    connect(returnNormal, &QAction::triggered, this, &PeachWidget::showNormal);

    // 创建托盘菜单(必须先创建动作，后添加菜单项，还可以加入菜单项图标美化)
    m_pTrayIconMenu = new QMenu(this);
    m_pTrayIconMenu->addAction(returnNormal);
    m_pTrayIconMenu->addAction(quitAction);
    m_pTrayIcon->setContextMenu(m_pTrayIconMenu);
}

// 最小化显示函数
void PeachWidget::littleShow()
{
    this->hide(); // 隐藏主窗口
    m_pTrayIcon->show(); // 显示托盘

    // 显示到系统提示框的信息
    QString title="Peach";
    QString text="正自动在后台运行";
    m_pTrayIcon->showMessage(title,text,QSystemTrayIcon::Information,3000); // 此参数为提示时长
}

void PeachWidget::changeMboxReturn(int num)
{
    this->mbox_return = num;
}

// 初始化信号槽连接
void PeachWidget::initSigSlot()
{
    // 登录按钮
    connect(m_pBtnHomePage, &QPushButton::clicked, [=]{
        emit sigShowLogin();
    });
}

void PeachWidget::closeEvent(QCloseEvent *event)
{
    m_pMsgBox->setIcon("question");
    m_pMsgBox->setBodyText("How to leave?");
    m_pMsgBox->setButtonText("Little","Logout");
    m_pMsgBox->exec();
    if(mbox_return == 0) {
        event->ignore();
    }else if(mbox_return == 1){
        event->ignore();
        littleShow();
    }
}
