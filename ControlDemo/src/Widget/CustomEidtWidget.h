#ifndef CUSTOMEIDTWIDGET_H
#define CUSTOMEIDTWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include "src/Control/CustomEditIcon.h"
#include "src/Control/CustomEditPasswd.h"
#include "src/Control/FlatUI.h"

class CustomEidtWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomEidtWidget(QWidget *parent = nullptr);

private:
    // 普通编辑框
    QLineEdit *m_pEditNormal1;
    QLineEdit *m_pEditNormal2;
    QGroupBox *m_pGroupNormal;

    // 登录编辑框
    CustomEditIcon *m_pEditAccount;
    CustomEditIcon *m_pEditPasswd;
    QGroupBox *m_pGroupLogin;

    // 自定义密码编辑框
    CustomEditPasswd *m_pEditPasswdEye;
    QGroupBox *m_pGroupEye;
};

#endif // CUSTOMEIDTWIDGET_H
