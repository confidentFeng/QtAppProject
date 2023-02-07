#include "MainWidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    // 主界面初始化
    this->setFixedSize(800, 600);
    this->setStyleSheet("QWidget#MainWidget{background:transparent;}");

    // 初始化悬浮菜单界面
    m_pHoverMenu = new HoverMenu(this);
    m_pHoverMenu->move(width()-m_pHoverMenu->width()-20, 32);
    m_pHoverMenu->show();

    // 初始化子界面
    m_pWidget1 = new QWidget(this);
    m_pWidget2 = new QWidget(this);
    m_pWidget1->setAttribute(Qt::WA_StyledBackground);
    m_pWidget2->setAttribute(Qt::WA_StyledBackground);
    m_pWidget1->setObjectName("Widget1");
    m_pWidget2->setObjectName("Widget2");
    m_pWidget1->setWindowTitle("Im Widget1");
    m_pWidget2->setWindowTitle("Im Widget2");
    m_pWidget1->setFixedSize(400, 400);
    m_pWidget2->setFixedSize(400, 400);
    m_pWidget1->move(50, 50);
    m_pWidget2->move(50, 50);
    m_pWidget1->hide();
    m_pWidget2->hide();

    // 切换语言
    connect(&AppEvent::Get(), &AppEvent::sigSwLanguage, [=](LANGUAGE curLanguage) {
        qDebug() << "curLanguage_main:" << curLanguage;

        QString language_qm;
        if(curLanguage == UI_CH)
            language_qm = QString(":/Translate/Translate_CH.qm");
        else
            language_qm = QString(":/Translate/Translate_EN.qm");

        m_translator->load(language_qm);
        qApp->installTranslator(m_translator); // 安装翻译器
    });

    // 显示悬浮菜单界面
    connect(&AppEvent::Get(), &AppEvent::sigShowHoverMenu, [=]() {
        m_pHoverMenu->show();
    });

    // 显示界面1
    connect(&AppEvent::Get(), &AppEvent::sigShowWidget1, [=]() {
        m_pWidget1->show();
        m_pWidget2->hide();
    });

    // 显示界面2
    connect(&AppEvent::Get(), &AppEvent::sigShowWidget2, [=]() {
        m_pWidget1->hide();
        m_pWidget2->show();
    });
}

// 设置翻译对象
void MainWidget::setTranslator(QTranslator* translator)
{
    m_translator = translator;
}

// 改变事件：调用installTranslator后，系统会给窗体发送信号触发changeEvent事件
void MainWidget::changeEvent(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::LanguageChange:
        this->translateUI();
    break;
    default:
        QWidget::changeEvent(event);
    }
}

void MainWidget::translateUI()
{
    m_pHoverMenu->translateUI();
}
