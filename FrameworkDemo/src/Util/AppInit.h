#ifndef APPINIT_H
#define APPINIT_H

#include <QObject>
#include <QApplication>
#include <QFile>
#include "src/Util/LogHandler.h"
#include "src/Util/AppConfig.h"

// 全局程序初始化类 AppInit 用来做一些程序启动后的初始化处理
class AppInit : public QObject
{
    Q_OBJECT
public:
    static AppInit& Get() {
        static AppInit m_appInit;
        return m_appInit;
    }

    static void init() {
        // 1、日志：安装消息处理函数（为降低性能消耗，暂时屏蔽）
        LogHandler::Get().installMessageHandler();

        // 2、应用全局加载样式表
        QFile qss(":/qss/style.qss");
        if (qss.open(QFile::ReadOnly))
        {
            qApp->setStyleSheet(qss.readAll());
            qss.close();
        }
        else{
            qDebug("Open qss failed");
        }

        // 3、初始化配置文件
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

//        // 是否显示虚拟键盘
//        QString isKeyBoard = "false";
//        CommonHelper::Get().readIni(QString("./user.ini"), QString("isKeyBoard"), isKeyBoard);
//        qDebug() << "isKeyBoard: " << isKeyBoard;
//        AppEvent::Get().m_isKeyBoard = isKeyBoard == "true" ? true : false;
    }

private:
    explicit AppInit(QObject *parent = nullptr);
};

#endif // APPINIT_H
