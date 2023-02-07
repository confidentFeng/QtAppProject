#include <QApplication>
#include <QFile>
#include "MainWidget.h"
#include "src/Util/LogHandler.h"
#include "src/Util/AppInit.h"
#include "src/Util/SingleApplication.h"

int main(int argc, char *argv[])
{
    SingleApplication a(argc, argv);
    if(!a.isRunning()) {
        MainWidget w;

        // 全局程序初始化类 AppInit 用来做一些程序启动后的初始化处理
        AppInit::Get().init();

        // 国际化翻译（尝试过放在AppInit内，不行）
        QString language = "CH"; // 默认为中文，后期可以使用ini方式保存语言选项
        AppConfig::Get().readIni(QString("./user.ini"), QString("language"), language);
        qDebug() << "curLanguage:" << language;
        QTranslator translator;
        translator.load(QString(":/Translate/Translate_") + language);
        a.installTranslator(&translator);
        w.setTranslator(&translator);

        w.show();
        return a.exec();
    }

    return 0;
}
