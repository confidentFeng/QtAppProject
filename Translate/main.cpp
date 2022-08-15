#include "Translate.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 国际化翻译
    QString language = "CH"; // 默认为中文，后期可以使用ini方式保存语言选项
    QTranslator translator;
    translator.load(QString(":/Translate_") + language);
    a.installTranslator(&translator);

    Translate w;
    w.setTranslator(&translator);
    w.show();

    return a.exec();
}
