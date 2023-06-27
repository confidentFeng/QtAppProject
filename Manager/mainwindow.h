#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QMessageBox>
#include "database_xml.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // "品牌车管理"-点击槽函数
    void on_manageAction_triggered();
    // "销售统计"菜单动作-触发槽函数
    void on_chartAction_triggered();
    // "退出"菜单动作-触发槽函数
    void on_quitAction_triggered();
    // "厂家"下拉列表-条目改变槽函数
    void on_sellFactoryComboBox_currentIndexChanged(const QString &arg1);
    // "取消"按钮-点击槽函数
    void on_sellCancelBtn_clicked();
    // "品牌"下拉列表-条目改变槽函数
    void on_sellBrandComboBox_currentIndexChanged(const QString &arg1);
    // "购买数目"微调框-值改变槽函数
    void on_sellNumSpinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
