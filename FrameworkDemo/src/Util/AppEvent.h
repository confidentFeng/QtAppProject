#ifndef APPEVENT_H
#define APPEVENT_H

#include <QObject>
#include "src/Util/AppData.h"

// 全局事件中转处理类 AppEvent 用来中转系统中各种跨多个 UI 以及多个类的事件。此类必须是全局单例类，便于全局统一使用
class AppEvent : public QObject
{
    Q_OBJECT
public:
    static AppEvent& Get() {
        static AppEvent m_sigForward;
        return m_sigForward;
    }

signals:
    void sigSwLanguage(LANGUAGE curLanguage); // 切换语言
    void sigShowHoverMenu(); // 显示悬浮菜单界面
    void sigShowWidget1(); // 显示界面1
    void sigShowWidget2(); // 显示界面2

private:
    explicit AppEvent(QObject *parent = nullptr);
};

#endif // APPEVENT_H
