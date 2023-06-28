#include "func.h"


//#include <QTextStream>
#include <QStringList>
#include <QTextCodec>
#include <QFont>
//字体相关
#include <QFontDatabase>

#ifdef QT5
#include <QCoreApplication>
#endif


#ifdef QT4
void setFontPath(const QString &font_path, QApplication &a)
{
    //解决qDebug中文乱码
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    int index = QFontDatabase::addApplicationFont(font_path);//添加字体文件(eg.  ":/font.ttf"  )
    if(index != -1) {
        QStringList fontList(QFontDatabase::applicationFontFamilies(index));
        // font -- LiHei Pro
        if(fontList.count() > 0) {
            QFont font_zh(fontList.at(0));
            font_zh.setBold(false);
            a.setFont(font_zh);
        }
    }
}
#endif



#ifdef QT5
void setFontPath(const QString &font_path)
{
  if(font_path.isEmpty())
    return;

    //添加字体库
    QString dir = QCoreApplication::applicationDirPath();
    QStringList m_fontList;
    m_fontList.clear();

    int fontId = QFontDatabase::addApplicationFont(font_path); //添加字体文件(eg.  ":/font.ttf"  )
    if (fontId != -1) // -1为加载失败
    {
        m_fontList << QFontDatabase::applicationFontFamilies(fontId);
    }

    if (!m_fontList.isEmpty())
    {
        QFont font;
        font.setFamily(m_fontList.at(0));
    }
    //解决qDebug中文乱码的问题
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));  //指定编码
}
#endif









