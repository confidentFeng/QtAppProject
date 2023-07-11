#include "AppInit.h"

// 使用私有静态成员变量
AppInit *AppInit::m_appInit = 0;
AppInit *AppInit::Instance()
{
    if (!m_appInit) {
        QMutex mutex;
        QMutexLocker locker(&mutex); // 加锁为了线程安全
        if (!m_appInit) {
            m_appInit = new AppInit;
        }
    }

    return m_appInit;
}

AppInit::AppInit(QObject *parent) : QObject(parent)
{

}

void AppInit::start()
{
    qApp->installEventFilter(this);


    // 应用全局加载样式表
    QFile qss(":/qss/style.qss");
    if (qss.open(QFile::ReadOnly))
    {
        qApp->setStyleSheet(qss.readAll());
        qss.close();
    }
    else{
        qDebug("Open qss failed");
    }

    // 初始化配置文件
    QFile userIniCfg(QString("./user.ini"));
    if ( !userIniCfg.exists() )
    {
        // 不存在则创建
        userIniCfg.open(QIODevice::ReadWrite);
        userIniCfg.close();

        AppConfig::Get().writeIni(QString("./user.ini"), QString("language"), QString("CH"));
        AppConfig::Get().writeIni(QString("./user.ini"), QString("isAutoLogin"), false);
        AppConfig::Get().writeIni(QString("./user.ini"), QString("isKeyBoard"), false);
    }
}

bool AppInit::eventFilter(QObject *obj, QEvent *evt)
{
    QWidget *w = (QWidget *)obj;
    if (!w->property("canMove").toBool()) {
        return QObject::eventFilter(obj, evt);
    }

    static QPoint mousePoint;
    static bool mousePressed = false;

    QMouseEvent *event = static_cast<QMouseEvent *>(evt);
    if (event->type() == QEvent::MouseButtonPress) {
        if (event->button() == Qt::LeftButton) {
            mousePressed = true;
            mousePoint = event->globalPos() - w->pos();
            return true;
        }
    } else if (event->type() == QEvent::MouseButtonRelease) {
        mousePressed = false;
        return true;
    } else if (event->type() == QEvent::MouseMove) {
        if (mousePressed && (event->buttons() & Qt::LeftButton)) {
            w->move(event->globalPos() - mousePoint);
            return true;
        }
    }

    return QObject::eventFilter(obj, evt);
}
