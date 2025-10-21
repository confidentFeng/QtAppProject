#include "ControlWidget.h"

ControlWidget::ControlWidget(QWidget *parent) : QWidget(parent)
{
    /* 主界面-初始化 */
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_StyledBackground); // 不继承父窗口样式
    this->setFixedSize(STACK_WIDTH, STACK_HEIGHT);
    this->setObjectName("ControlWidget");

    // 标签
    m_pLabText = new QLabel;
    m_pLabText->setObjectName("ControlWidget_LabText");
    m_pLabText->setText("Hello World");
    m_pLabIcon = new QLabel;
    m_pLabIcon->setPixmap(QPixmap(":/Image/Widget/item_01.png"));
    m_pLabIcon->setFixedSize(39, 35);
    m_pLabIcon->setScaledContents(true);
    // 分组框
    m_pGroupLab = new QGroupBox;
    m_pGroupLab->setFixedHeight(120);
    // 布局
    QHBoxLayout *pLayoutLab = new QHBoxLayout(m_pGroupLab);
    pLayoutLab->addSpacing(32);
    pLayoutLab->addWidget(m_pLabText);
    pLayoutLab->addSpacing(64);
    pLayoutLab->addWidget(m_pLabIcon);
    pLayoutLab->addStretch();
    pLayoutLab->setSpacing(0);
    pLayoutLab->setMargin(0);

    // 图标按钮
    m_pBtnIcon = new MyIconBtn;
    m_pBtnIcon->setObjectName("ControlWidget_BtnIcon");
    m_pBtnIcon->setFixedSize(59, 30);
    m_pBtnIcon->m_iconNormal = ":/Image/HoverMenu/btn_bigScreen_hov.png";
    m_pBtnIcon->m_iconHover = ":/Image/HoverMenu/btn_bigScreen_nor.png";
    m_pBtnIcon->m_iconPressed = ":/Image/HoverMenu/btn_bigScreen_nor.png";
    // 普通按钮
    m_pBtnNormal = new MyIconBtn;
    m_pBtnNormal->setObjectName("Common_BtnBlue");
    m_pBtnNormal->setFixedSize(59, 30);
    // 开关按钮-内圆形
    pSwitchButton = new SwitchBtn;
    pSwitchButton->setFixedSize(50, 24);
    pSwitchButton->setButtonStyle(SwitchBtn::ButtonStyle_CircleIn);
    // 开关按钮-内圆形带文本
    pSwitchButtonText = new SwitchBtn;
    pSwitchButtonText->setFixedSize(56, 24);
    pSwitchButtonText->setButtonStyle(SwitchBtn::ButtonStyle_CircleIn);
    pSwitchButtonText->setText("OFF", "ON");
    // 开关按钮-外圆形
    pSwitchButtonOut = new SwitchBtn;
    pSwitchButtonOut->setFixedSize(50, 24);
    pSwitchButtonOut->setButtonStyle(SwitchBtn::ButtonStyle_CircleOut);
    pSwitchButtonOut->setRectRadius(10);
    // 边框按钮
    m_pCustomBtnBorder = new CustomBtnBorder;
    m_pCustomBtnBorder->setFixedSize(160, 48);
    m_pCustomBtnBorder->setIconPixmap(QPixmap(":/Image/Control/btn_browse Folder_unchecked.png")); // 平时的图标图像
    m_pCustomBtnBorder->setIconPixmapChecked(QPixmap(":/Image/Control/btn_browse Folder_checked.png")); // 选中时的图标图像
    m_pCustomBtnBorder->setIconPixmapDis(QPixmap(":/Image/Control/btn_browse Folder_dis.png")); // 禁用时的图标图像
    m_pCustomBtnBorder->setIconSize(QSize(32, 32));
    m_pCustomBtnBorder->setBtnText("搜索");
    m_pCustomBtnBorder->setChecked(true);
    // 下拉按钮
    m_pBtnShortCut = new MyComboxBtn;
    m_pBtnShortCut->setFixedSize(200, 32);
    m_pBtnShortCut->setLabIcon1(":/Image/Control/icon_shortCut.png");
    m_pBtnShortCut->m_isFold = true;      // 默认折叠
    m_pBtnShortCut->setLabIcon2(":/Image/Control/icon_arrowDown.png");
    // 开关按钮
    m_pBtnAudioMix = new MyComboxBtnWithSwitch;
    m_pBtnAudioMix->setFixedSize(200, 32);
    m_pBtnAudioMix->setLabIcon1(":/Image/Control/icon_audioMix.png");
    m_pBtnAudioMix->setTipShow(true);
    m_pBtnAudioMix->setSwitchState(true);
    // 分组框
    m_pGroupBtn = new QGroupBox;
    m_pGroupBtn->setFixedHeight(120);
    m_pGroupBtn->setTitle(tr("按钮"));
    // 按钮布局
    QGridLayout *pLayoutBtn = new QGridLayout(m_pGroupBtn);
    pLayoutBtn->addWidget(m_pBtnIcon, 0, 0);
    pLayoutBtn->addWidget(m_pBtnNormal, 1, 0);
    pLayoutBtn->addWidget(pSwitchButton, 0, 1);
    pLayoutBtn->addWidget(pSwitchButtonText, 1, 1);
    pLayoutBtn->addWidget(pSwitchButtonOut, 2, 1);
    pLayoutBtn->addWidget(m_pBtnShortCut, 0, 2);
    pLayoutBtn->addWidget(m_pBtnAudioMix, 1, 2);
    pLayoutBtn->addWidget(m_pCustomBtnBorder, 0, 3);

    // 账号编辑框
    m_pEditAccount = new MyLineEdit;
    m_pEditAccount->setObjectName("LoginWidget_EditAccount");
    m_pEditAccount->setFixedSize(300, 40);
    m_pEditAccount->setLeftIcon(QIcon(":/Image/Control/icon_user.png"));
    m_pEditAccount->setMaxLength(30);
    // 密码编辑框
    m_pEditPasswd = new MyLineEdit;
    m_pEditPasswd->setObjectName("LoginWidget_EditPasswd");
    m_pEditPasswd->setFixedSize(300, 40);
    m_pEditPasswd->setLeftIcon(QIcon(":/Image/Control/icon_password.png"));
    m_pEditPasswd->setMaxLength(30);
    m_pEditPasswd->setEchoMode(QLineEdit::Password);
    m_pEditPasswd->setClearButtonEnabled(true);
    // 分组框
    m_pGroupEdit = new QGroupBox;
    m_pGroupEdit->setFixedHeight(120);
    m_pGroupEdit->setTitle(tr("编辑框"));
    // 布局
    QGridLayout *pLayoutEdit = new QGridLayout(m_pGroupEdit);
    pLayoutEdit->addWidget(m_pEditAccount, 0, 0);
    pLayoutEdit->addWidget(m_pEditPasswd, 1, 0);
    pLayoutEdit->setSpacing(8);
    pLayoutEdit->setMargin(10);

    // 勾选框
    m_pCheckBox = new QCheckBox(this);
    // 分组框
    m_pGroupCheck = new QGroupBox;
    m_pGroupCheck->setFixedHeight(120);
    m_pGroupCheck->setTitle(tr("勾选框"));
    // 布局
    QGridLayout *pLayoutCheck = new QGridLayout(m_pGroupCheck);
    pLayoutCheck->addWidget(m_pCheckBox, 0, 0);
    pLayoutCheck->setSpacing(8);
    pLayoutCheck->setMargin(10);

    // 初始化滑动条
    m_pSlider = new QSlider;
    m_pSlider->setOrientation(Qt::Horizontal);  // 水平方向
    m_pSlider->setMinimum(0);  // 最小值
    m_pSlider->setMaximum(100);  // 最大值
    m_pSlider->setSingleStep(1);  // 步长
    m_pSlider->setFixedWidth(500); // 设置固定宽度，高度由样式表设置
    m_pSlider->setValue(50);
    // 初始化数字滑动条
    m_pCustomSliderNum = new CustomSliderNum;
    m_pCustomSliderNum->setOrientation(Qt::Horizontal);  // 水平方向
    m_pCustomSliderNum->setMinimum(0);  // 最小值
    m_pCustomSliderNum->setMaximum(100);  // 最大值
    m_pCustomSliderNum->setSingleStep(1);  // 步长
    m_pCustomSliderNum->setFixedSize(500, 70); // 设置固定宽高，高度设置大一些，让数字显示出来
    m_pCustomSliderNum->setValue(50);
    // 初始化进度条
    m_pProBar = new QProgressBar;
    m_pProBar->setRange(0, 100); // 设置进度条最小值和最大值(取值范围)
    m_pProBar->setValue(50);  // 设置当前的运行值
    m_pProBar->setOrientation(Qt::Horizontal);  // 水平方向
    m_pProBar->setTextVisible(false); // 隐藏进度条文本
    m_pProBar->setFixedSize(500, 16);   // 进度条固定大小
    m_pProBar->setInvertedAppearance(false); // true:反方向  false:正方向
    // 初始化加载进度条
    m_pProBarLoad = new QProgressBar;
    m_pProBarLoad->setOrientation(Qt::Horizontal);  // 水平方向
    m_pProBarLoad->setTextVisible(false); // 隐藏进度条文本
    m_pProBarLoad->setFixedSize(500, 16);   // 进度条固定大小
    m_pProBarLoad->setMinimum(0); // 将进度条控件的最大值、最小值都设置为0时，可以显示忙碌状态，从而替代百分比表示的进度
    m_pProBarLoad->setMaximum(0);
    // 分组框
    m_pGroupSlider = new QGroupBox;
    m_pGroupSlider->setFixedHeight(160);
    m_pGroupSlider->setTitle(tr("滑动条与进度条"));
    // 布局
    QVBoxLayout *pLayoutSlider = new QVBoxLayout(m_pGroupSlider);
    pLayoutSlider->addSpacing(12);
    pLayoutSlider->addWidget(m_pCustomSliderNum);
    pLayoutSlider->addSpacing(0);
    pLayoutSlider->addWidget(m_pSlider);
    pLayoutSlider->addSpacing(12);
    pLayoutSlider->addWidget(m_pProBar);
    pLayoutSlider->addSpacing(12);
    pLayoutSlider->addWidget(m_pProBarLoad);
    pLayoutSlider->addStretch();
    pLayoutSlider->setAlignment(Qt::AlignHCenter);
    pLayoutSlider->setSpacing(0);
    pLayoutSlider->setMargin(0);

    // 初始化滚动条
    m_pScrollBar = new QScrollBar;
    m_pScrollBar->setOrientation(Qt::Vertical);  // 垂直方向
    m_pScrollBar->setMinimum(0);  // 最小值
    m_pScrollBar->setMaximum(500);  // 最大值
    m_pScrollBar->setSingleStep(10);  // 步长
    m_pScrollBar->setFixedHeight(500); // 设置固定高度，宽度由样式表设置

    // 背景子界面
    m_pWidgetBack = new QWidget(); //子部件
    m_pWidgetBack->setFixedSize(width(), height()+300);
    m_pWidgetBack->setObjectName("ControlWidget_WidgetBack");

    // 背景子界面布局
    QVBoxLayout *pLayoutBack = new QVBoxLayout(m_pWidgetBack);
    pLayoutBack->addWidget(m_pGroupLab);
    pLayoutBack->addWidget(m_pGroupBtn);
    pLayoutBack->addWidget(m_pGroupEdit);
    pLayoutBack->addWidget(m_pGroupCheck);
    pLayoutBack->addWidget(m_pGroupSlider);
    pLayoutBack->addStretch();
    pLayoutBack->setSpacing(24);
    pLayoutBack->setMargin(25);

    // 主布局
    QVBoxLayout *pLayoutMain = new QVBoxLayout(this);
    // 滚动区域
    m_pScrollArea = new QScrollArea(this) ;
    m_pScrollArea->setObjectName("ControlWidget_ScrollArea");
    m_pScrollArea->setBackgroundRole(QPalette::Dark);
    m_pScrollArea->setFixedSize(width(), height());
    m_pScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_pScrollArea->setWidget(m_pWidgetBack); // 设置滚动部件
    pLayoutMain->addWidget(m_pScrollArea); // 添加QScrollArea布局
    pLayoutMain->setSpacing(0);
    pLayoutMain->setMargin(0);

    // 语言
    connect(m_pBtnShortCut, &QPushButton::clicked, [=]{
        if(m_pBtnShortCut->m_isFold) {
            m_pBtnShortCut->m_isFold = false;
            m_pBtnShortCut->setLabIcon2(":/Image/Control/icon_arrowUp.png");
            m_pBtnShortCut->setStyleSheet("background:rgba(0,102,204,0.5);border:none;");
        }
        else {
            m_pBtnShortCut->m_isFold = true;
            m_pBtnShortCut->setLabIcon2(":/Image/Control/icon_arrowDown.png");
            m_pBtnShortCut->setStyleSheet(STYLE_NORMAL);
        }
    });

    // 音频混合开关
    connect(m_pBtnAudioMix, &MyComboxBtnWithSwitch::switchStateChanged, [=](bool checked){
        qDebug() << "m_pBtnAudioMix" << checked;
    });

    // 滑动条信号槽
    connect(m_pCustomSliderNum, &QSlider::valueChanged, [=](int value) {
        m_pSlider->setValue(value);
        m_pProBar->setValue(value);
    });
    connect(m_pSlider, &QSlider::valueChanged, [=](int value) {
        m_pCustomSliderNum->setValue(value);
        m_pProBar->setValue(value);
    });
}

// 统一设置需要被翻译的文本
void ControlWidget::translateUI()
{
    m_pGroupLab->setTitle(tr("标签"));
    m_pBtnIcon->setText(tr("开启"));
    m_pBtnNormal->setText(tr("登录"));

    m_pBtnShortCut->setBtnText(tr("快捷键"));
    m_pBtnAudioMix->setBtnText(tr("音频混合"));
}
