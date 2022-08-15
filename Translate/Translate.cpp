#include "Translate.h"

Translate::Translate(QWidget *parent)
    : QWidget(parent)
{
    // 初始化界面
    this->setFixedSize(400, 200);

    // 初始化控件
    m_pLabText = new QLabel;
    m_pComboBox = new QComboBox;
    m_pComboBox->addItem("Chinese");
    m_pComboBox->addItem("English");

    // 主布局
    QVBoxLayout *m_pLayoutMain = new QVBoxLayout(this);
    m_pLayoutMain->addStretch();
    m_pLayoutMain->addWidget(m_pLabText, 0, Qt::AlignCenter);
    m_pLayoutMain->addSpacing(20);
    m_pLayoutMain->addWidget(m_pComboBox, 0, Qt::AlignCenter);
    m_pLayoutMain->addStretch();
    m_pLayoutMain->setMargin(0);

    // 连接信号槽
    connect(m_pComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [=](int index) {
        QString language_qm;
        if(index == 0)
            language_qm = QString(":/Translate_CH.qm");
        else
            language_qm = QString(":/Translate_EN.qm");

        m_translator->load(language_qm);
        qApp->installTranslator(m_translator); // 安装翻译器
    });

    // 统一设置需要被翻译的文本
    translateUI();
}

// 设置翻译对象
void Translate::setTranslator(QTranslator* translator)
{
    m_translator = translator;
}

// 改变事件：调用installTranslator后，系统会给窗体发送信号触发changeEvent事件
void Translate::changeEvent(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::LanguageChange:
        translateUI();
        break;
    default:
        QWidget::changeEvent(event);
    }
}

// 统一设置需要被翻译的文本
void Translate::translateUI()
{
    m_pLabText->setText(tr("这是需要测试的文本"));
}
