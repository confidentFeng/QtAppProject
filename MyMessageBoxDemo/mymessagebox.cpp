#include "mymessagebox.h"
#include "ui_mymessagebox.h"

MyMessageBox::MyMessageBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyMessageBox)
{
    ui->setupUi(this);

    // 让窗口居中显示 | 隐藏标题栏
    this->setWindowFlags(Qt::Window |Qt::FramelessWindowHint);

    // 初始化成员变量
    m_isModalFlag = false;

    // 初始化标题栏
    initTitleBar();

    //使用调色板设置窗口的背景色
    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(255, 255, 255));
    setAutoFillBackground(true);
    setPalette(pal);
}

MyMessageBox::~MyMessageBox()
{
    delete ui;
}

// 初始化标题栏
void MyMessageBox::initTitleBar()
{
    m_titleBar = new MyTitleBar(this);

    // 设置窗口边框宽度
    m_titleBar->setWindowBorderWidth(0);
    // 设置标题栏颜色
    m_titleBar->setBackgroundColor(185, 92, 125);
    // 设置标题栏上按钮类型
    m_titleBar->setButtonType(ONLY_CLOSE_BUTTON);
    // 设置标题栏长度
    m_titleBar->setTitleWidth(this->width());
    // 设置标题颜色
    m_titleBar->setTitleColor(255, 255, 255);
    // 设置标题栏图标
    m_titleBar->setTitleIcon("://image/MyMessageBox/WindowIcon.png", QSize(16, 16));

    // 默认隐藏输入栏
    ui->inputContent->setVisible(false);
}

// 设置标题内容
void MyMessageBox::setWindowTitle(QString title , int titleFontSize)
{
    m_titleBar->setTitleContent(title, titleFontSize);
}

// 设置提示内容
void MyMessageBox::setContentText(QString contentText)
{
    ui->MessageContent->setText(contentText);
}

// 设置对话框类型
void MyMessageBox::setMessageType(MessageType messageType)
{
    switch (messageType)
    {
        case MESSAGE_INFORMATION:
            ui->MessageIcon->setPixmap(QPixmap("://image/MyMessageBox/information.png"));
        break;
        case MESSAGE_WARNNING:
            ui->MessageIcon->setPixmap(QPixmap("://image/MyMessageBox/warnning.png"));
        break;
        case MESSAGE_QUESTION:
            ui->MessageIcon->setPixmap(QPixmap("://image/MyMessageBox/question.png"));
        break;
        case MESSAGE_INPUT:
            ui->MessageIcon->setVisible(false);
            ui->inputContent->setVisible(true);
        break;
    }
}

// 设置按钮类型
void MyMessageBox::setButtonType(MessageButtonType buttonType)
{
    switch (buttonType)
    {
        case BUTTON_OK:
        {
            ui->okButton->setText("确定");
            ui->cancelButton->setVisible(false);
        }
        break;
        case BUTTON_OK_AND_CANCEL:
        {
            ui->okButton->setText("确定");
            ui->cancelButton->setText("取消");
        }
        break;
        default:
        break;
    }
}

// 加载本地样式文件：可以将样式直接写在文件中，程序运行时直接加载进来
void MyMessageBox::loadStyleSheet(const QString &sheetName)
{
    QFile file("://image/MyMessageBox/" + sheetName + ".css");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet = this->styleSheet();
        styleSheet += QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);
    }
}

// 自定义显示函数
int MyMessageBox::showMyMessageBox(QWidget* parent, const QString &title, const QString &contentText,\
                                   MessageType messageType, MessageButtonType messageButtonType, bool isModelWindow)
{
    MyMessageBox * myMessage = new MyMessageBox(parent);
    // 设置标题内容
    myMessage->setWindowTitle(title, 10);
    // 设置提示内容
    myMessage->setContentText(contentText);
    // 设置对话框类型
    myMessage->setMessageType(messageType);
    // 设置按钮类型
    myMessage->setButtonType(messageButtonType);
    // 加载样式表
    myMessage->loadStyleSheet("MyMessageBox");
    // 设置是否为模态窗口
    m_isModalFlag = isModelWindow;
    if (m_isModalFlag)
    {
        // 设置为模态窗口时，参数parent必须设置父窗口指针，否则模态设置无效
        // 因为 Qt::WindowModal 参数只对父窗口有效，如果想要模态对全局窗口都有效可以设置 Qt::ApplicationModal
        return myMessage->exec();
    }
    else
    {
        myMessage->show();
    }

    return -1;
}

// 关闭事件：在exec()方法中返回选择结果
void MyMessageBox::closeEvent(QCloseEvent *event)
{
    // 关闭窗口时结束事件循环，在exec()方法中返回选择结果，且非模态窗口，使用exit()方法会出异常
    if (!m_isModalFlag && m_eventLoop != nullptr)
    {
        m_eventLoop->exit();
    }
    event->accept();
}

// 因为QWidget没有exec()方法，所以需要自己定义来完成exec()方法
int MyMessageBox::exec()
{
    // exec()方法就是直接设置窗口显示为模态，并且窗口关闭结束后返回用户选择结果(按了确定还是取消按钮)
    // 这里也可以继承QDialog类，QDialog有自己的exec()方法，根据返回 Accepted, Rejected 来决定是否按了确定按钮
    this->setWindowModality(Qt::WindowModal);
    this->show();
    // 使用事件循环QEventLoop ,不让exec()方法结束，在用户选择确定或者取消后，关闭窗口结束事件循环，并返回最后用户选择的结果
    // 根据返回结果得到用户按下了确定还是取消，采取相应的操作。从而模拟出QDialog类的exec()方法
    m_eventLoop = new QEventLoop(this);
    m_eventLoop->exec();

    return m_chooseResult;
}

// 确定按钮-点击信号槽
void MyMessageBox::on_okButton_clicked()
{
    m_chooseResult = ID_OK;
    this->close();
}

// 取消按钮-点击槽函数
void MyMessageBox::on_cancelButton_clicked()
{
    m_chooseResult = ID_CANCEL;
    this->close();
}
