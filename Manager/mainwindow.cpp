#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 使用 factory 表的 name 字段为"厂家"下拉列表提供条目
    QSqlQueryModel *factoryModel = new QSqlQueryModel(this);
    factoryModel->setQuery("SELECT name FROM factory");
    ui->sellFactoryComboBox->setModel(factoryModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// "品牌车管理"菜单动作-触发槽函数
void MainWindow::on_manageAction_triggered()
{
    // 选择 stackedWidget 的页面0
    ui->stackedWidget->setCurrentIndex(0);
}

// "销售统计"菜单动作-触发槽函数
void MainWindow::on_chartAction_triggered()
{
    // 选择 stackedWidget 的页面1
    ui->stackedWidget->setCurrentIndex(1);
}

// "退出"菜单动作-触发槽函数
void MainWindow::on_quitAction_triggered()
{
    this->close();
}

// "厂家"下拉列表-条目改变槽函数
void MainWindow::on_sellFactoryComboBox_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "请选择厂家")
    {
        // 进行其他部件的状态设置
        on_sellCancelBtn_clicked();
    }
    else
    {
        // 若在"厂家"下拉列表中选择任意一家，则在下面的"品牌"下拉列表中显示相应品牌汽车
        ui->sellBrandComboBox->setEnabled(true);
        QSqlQueryModel *model = new QSqlQueryModel(this);
        model->setQuery(QString("SELECT name FROM brand WHERE factory='%1'").arg(arg1));
        ui->sellBrandComboBox->setModel(model);
        ui->sellCancelBtn->setEnabled(true);
    }
}

// "取消"按钮-点击槽函数
void MainWindow::on_sellCancelBtn_clicked()
{
    qDebug() << "aaa";
    ui->sellFactoryComboBox->setCurrentIndex(0);
    ui->sellBrandComboBox->setCurrentIndex(5);
    ui->sellPriceLineEdit->setText(" ");
    ui->sellNumSpinBox->setValue(0);
    ui->sellLastNumLabel->setText("剩余数量：0");
    ui->sellSumLineEdit->clear();
}

// "品牌"下拉列表-条目改变槽函数
void MainWindow::on_sellBrandComboBox_currentIndexChanged(const QString &arg1)
{
    ui->sellNumSpinBox->setValue(0);
    ui->sellNumSpinBox->setEnabled(false);
    ui->sellSumLineEdit->clear();
    ui->sellSumLineEdit->setEnabled(false);
    ui->sellOkBtn->setEnabled(false);

    // 从"品牌"表中，根据"厂家"和"名称"检索出"单价"，并显示在QLineEdit上
    QSqlQuery query;
    query.exec(QString("SELECT price FROM brand WHERE name='%1' AND factory='%2'")\
               .arg(arg1).arg(ui->sellFactoryComboBox->currentText()));
    query.next();
    ui->sellPriceLineEdit->setEnabled(true); // 使能"单价label"
    ui->sellPriceLineEdit->setReadOnly(true); //设置"单价label"为只读
    ui->sellPriceLineEdit->setText(query.value(0).toString());

    // 从"品牌"表中，根据"厂家"和"名称"检索出"剩余数量"，并显示在QLabel上
    query.exec(QString("SELECT last FROM brand WHERE name='%1' AND factory='%2'")\
               .arg(arg1).arg(ui->sellFactoryComboBox->currentText()));
    query.next();
    int num = query.value(0).toInt();
    if(num == 0)
    {
        QMessageBox::information(this,tr("提示"),tr("该品牌汽车已经售完！"),QMessageBox::Ok);
    }
    else{
        ui->sellNumSpinBox->setEnabled(true);
        ui->sellNumSpinBox->setMaximum(num);
        ui->sellLastNumLabel->setText(tr("剩余数量：%1").arg(num));
        ui->sellLastNumLabel->setVisible(true);
    }
}

// "购买数目"微调框-值改变槽函数
void MainWindow::on_sellNumSpinBox_valueChanged(int arg1)
{
    // 更改购买数量后，自动显示总金额
    if(arg1 == 0)
    {
        ui->sellSumLineEdit->clear();
        ui->sellSumLineEdit->setEnabled(false);
        ui->sellOkBtn->setEnabled(false);
    }
    else
    {
        ui->sellSumLineEdit->setEnabled(true);
        ui->sellSumLineEdit->setReadOnly(true);
        // 计算总金额，并显示在"金额lienEdit"
        qreal sum = arg1*ui->sellPriceLineEdit->text().toInt();
        ui->sellSumLineEdit->setText(QString::number(sum));
        ui->sellOkBtn->setEnabled(true);
    }
}
