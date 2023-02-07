#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QObject>
#include <QString>
#include <QSettings>
#include <QDebug>

// 全局配置文件管理类 AppConfig 用来读写对应项目的配置文件
class AppConfig : public QObject
{
    Q_OBJECT
public:
    static AppConfig& Get() {
        static AppConfig m_appConfig;
        return m_appConfig;
    }

    bool writeIni(const QString &path, const QString &key, const QString &value);
    bool readIni(const QString &path, const QString &key, QString &value);
    bool writeIni(const QString &path, const QString &key, const QVariant &value);
    bool readIni(const QString &path, const QString &key, QVariant &value);

private:
    explicit AppConfig(QObject *parent = nullptr);
};

#endif // APPCONFIG_H
