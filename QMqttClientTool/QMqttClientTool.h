#ifndef QMQTTCLIENTTOOL_H
#define QMQTTCLIENTTOOL_H

#include <QWidget>
#include "QtMqtt/qmqttclient.h"
#include "QPushButton"
#include "QLineEdit"
#include "QLabel"

class QMqttClientTool : public QWidget
{
    Q_OBJECT

public:
    QMqttClientTool(QWidget *parent = 0);
    ~QMqttClientTool();

    QPushButton * btnConnect; // 连接MQTT服务器
    QPushButton * btnPublish; // 发布消息
    QLabel * qlbHostNameTag;
    QLabel * qlbHostPortTag;
    QLabel * qlbPubLishTopicTag;
    QLabel * qlbPublishMessageTag;
    QLineEdit * qleHostName;
    QLineEdit * qleHostPort;
    QLineEdit * qlePublishTopic;
    QLineEdit * qlePublishMessage;

private:
    QMqttClient * m_client;//mqtt client指针

private slots:
    void on_btnConnect_clicked(void);//连接MQTT服务器槽函数
    void on_btnPublish_clicked(void);//发布消息槽函数
};

#endif // QMQTTCLIENTTOOL_H
