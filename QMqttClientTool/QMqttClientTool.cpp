#include "QMqttClientTool.h"
#include "QDebug"
#include <QtWidgets/QMessageBox>
QMqttClientTool::QMqttClientTool(QWidget *parent)
    : QWidget(parent)
{

    this->setMaximumSize(600,200);
    this->setMinimumSize(600,200);

    m_client             =  new QMqttClient(this);
    btnConnect           =  new QPushButton(this);
    btnPublish           =  new QPushButton(this);
    qlbHostNameTag       =  new QLabel(this);
    qlbHostPortTag       =  new QLabel(this);
    qlbPubLishTopicTag   =  new QLabel(this);
    qlbPublishMessageTag =  new QLabel(this);
    qleHostName          =  new QLineEdit(this);
    qleHostPort          =  new QLineEdit(this);
    qlePublishTopic      =  new QLineEdit(this);
    qlePublishMessage    =  new QLineEdit(this);
    QFont ft;
    ft.setPointSize(15);
    ft.setBold(1);

    qlbHostNameTag->move(6,6);
    qlbHostNameTag->setText("Host");
    qlbHostNameTag->setFont(ft);
    qlbHostNameTag->setMaximumSize(65,35);
    qlbHostNameTag->setMinimumSize(65,35);

    qleHostName->move(60,6);
    qleHostName->setFont(ft);
    qleHostName->setMaximumSize(200,35);
    qleHostName->setMinimumSize(200,35);

    qlbHostPortTag->move(270,6);
    qlbHostPortTag->setText("Port");
    qlbHostPortTag->setFont(ft);
    qlbHostPortTag->setMaximumSize(65,35);
    qlbHostPortTag->setMinimumSize(65,35);

    qleHostPort->move(324,6);
    qleHostPort->setFont(ft);
    qleHostPort->setMaximumSize(60,35);
    qleHostPort->setMinimumSize(60,35);

    btnConnect->move(390,6);
    btnConnect->setText("Connect");
    btnConnect->setFont(ft);
    btnConnect->setMaximumSize(120,35);
    btnConnect->setMinimumSize(120,35);

    qlbPubLishTopicTag->move(6,50);
    qlbPubLishTopicTag->setText("PublishTopic");
    qlbPubLishTopicTag->setFont(ft);
    qlbPubLishTopicTag->setMaximumSize(130,35);
    qlbPubLishTopicTag->setMinimumSize(130,35);

    qlePublishTopic->move(145,50);
    qlePublishTopic->setFont(ft);
    qlePublishTopic->setMaximumSize(240,35);
    qlePublishTopic->setMinimumSize(240,35);

    btnPublish->move(390,50);
    btnPublish->setText("Publish");
    btnPublish->setFont(ft);
    btnPublish->setMaximumSize(120,35);
    btnPublish->setMinimumSize(120,35);

    qlbPublishMessageTag->move(6,94);
    qlbPublishMessageTag->setText("PublishMessage");
    qlbPublishMessageTag->setFont(ft);
    qlbPublishMessageTag->setMaximumSize(160,35);
    qlbPublishMessageTag->setMinimumSize(160,35);

    qlePublishMessage->move(170,94);
    qlePublishMessage->setFont(ft);
    qlePublishMessage->setMaximumSize(400,35);
    qlePublishMessage->setMinimumSize(400,35);

    connect(btnConnect,SIGNAL(clicked()),this,SLOT(on_btnConnect_clicked()));
    connect(btnPublish,SIGNAL(clicked()),this,SLOT(on_btnPublish_clicked()));
}

QMqttClientTool::~QMqttClientTool()
{

}

void QMqttClientTool::on_btnConnect_clicked()
{
    //未连接服务器则连接
    if (m_client->state() == QMqttClient::Disconnected) {
        btnConnect->setText(tr("Disconnect"));
        m_client->setHostname(qleHostName->text());
        m_client->setPort(qleHostPort->text().toInt());
        qleHostName->setEnabled(false);
        qleHostPort->setEnabled(false);
        m_client->connectToHost();
    } else {//断开连接
        btnConnect->setText(tr("Connect"));
        qleHostName->setEnabled(true);
        qleHostPort->setEnabled(true);
        m_client->disconnectFromHost();
    }
}

void QMqttClientTool::on_btnPublish_clicked()
{

    if (m_client->publish(qlePublishTopic->text(),qlePublishMessage->text().toUtf8()) == -1)
         QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not publish message"));
}
