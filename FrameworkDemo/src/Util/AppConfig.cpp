#include "AppConfig.h"

AppConfig::AppConfig(QObject *parent) : QObject(parent)
{

}

bool AppConfig::writeIni(const QString &path, const QString &key, const QString &value)
{
    if(path.isEmpty() || key.isEmpty())
    {
        qDebug()<<"path is null...";
        return false;
    }

    // 创建配置文件操作对象
    QSettings *config = new QSettings(path, QSettings::IniFormat);
    // 将信息写入配置文件
    config->beginGroup("config");
    config->setValue(key, value);
    config->endGroup();
    delete config;

    return true;
}

bool AppConfig::readIni(const QString &path, const QString &key, QString &value)
{
    value = QString("");
    if(path.isEmpty() || key.isEmpty())
        return false;

    // 创建配置文件操作对象
    QSettings *config = new QSettings(path, QSettings::IniFormat);
    // 读取用户配置信息
    value = config->value(QString("config/") + key).toString();
    delete config;

    return true;
}

bool AppConfig::writeIni(const QString &path, const QString &key, const QVariant &value)
{
    if ( path.isEmpty() || key.isEmpty() )
        return false;

    QSettings configure(path, QSettings::IniFormat);
    // 将信息写入配置文件
    configure.beginGroup("config");
    configure.setValue(key, value);
    configure.endGroup();
    return true;
}

bool AppConfig::readIni(const QString &path, const QString &key, QVariant &value)
{
    if ( path.isEmpty() )
        return false;

    QSettings configure(path, QSettings::IniFormat);
    value = configure.value(QString("config/") + key);
    return true;
}
