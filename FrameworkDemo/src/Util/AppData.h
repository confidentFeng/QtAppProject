#ifndef APPDATA_H
#define APPDATA_H

#include <QObject>

#define MENU_WIDTH 240
#define MENU_HEIGHT 100

// 鼠标光标图标
#define CURSOR_ICON ":/Image/Util/icon_cursorHand.png"
#define CURSOR_NORMAL ":/Image/Util/icon_mouse.png"
#define CURSOR_FORBID ":/Image/Util/icon_forbidden.png"

// 语言
typedef enum{
    UI_CH,
    UI_EN
}LANGUAGE;

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
