#ifndef XMLHELPER_H
#define XMLHELPER_H

#include <QApplication>
#include <QFile>
#include <QtXml\QtXml>
#include <QtXml\QDomDocument>

class XmlHelper
{
public:
    XmlHelper();
    ~XmlHelper();
    static XmlHelper *Get()
    {
        static XmlHelper ct;
        return &ct;
    }
    void WriteXml(const QString& strWifiName, const QString& strWifiPasswd); // 写xml：WIFI的profile脚本文本
    void ReadXml(); // 读xml
};

#endif // XMLHELPER_H
