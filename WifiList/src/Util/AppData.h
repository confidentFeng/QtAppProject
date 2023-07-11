#ifndef APPDATA_H
#define APPDATA_H

#include <QObject>
#include <QRect>
#include "def.h"

// 全局变量管理类 AppData 用来设置项目中用到的所有全局变量
class AppData : public QObject
{
    Q_OBJECT
public:
    static AppData& Get() {
        static AppData m_appData;
        return m_appData;
    }

    LANGUAGE m_curLanguage; // 当前语言

private:
    explicit AppData(QObject *parent = nullptr);
};

#endif // APPDATA_H
