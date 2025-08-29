#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTcpSocket>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // --- TCP Socket ---
    socket = new QTcpSocket(this);
    socket->connectToHost("192.168.30.65", 8080); // IP của ESP8266
    if (!socket->waitForConnected(3000)) {
        ui->statusbar->showMessage("Không kết nối được ESP");
    } else {
        ui->statusbar->showMessage("Đã kết nối ESP");
        connect(socket, &QTcpSocket::readyRead, this, &MainWindow::readResponse);  // THÊM DÒNG NÀY
    }
    // --- MQTT ---
    // Connect form ec2 ubuntu server: mosquitto_sub -h 34.239.131.243 -t device/led/status
    mqttClient = new QMqttClient(this);
    mqttClient->setHostname("3.81.129.74"); // IP của MQTT broker (Ubuntu hoặc RPi)
    mqttClient->setPort(1883);
    mqttClient->setClientId("QtClient");

    connect(mqttClient, &QMqttClient::stateChanged, this, [=](QMqttClient::ClientState state){
        if (state == QMqttClient::Connected)
            ui->statusbar->showMessage("MQTT Connected");
        else
            ui->statusbar->showMessage("MQTT Disconnected");
    });

    mqttClient->connectToHost();

}

MainWindow::~MainWindow()
{
    socket->disconnectFromHost();
    delete ui;
}
void MainWindow::readResponse()
{
    QByteArray data = socket->readAll();
    QString response = QString::fromUtf8(data).trimmed();

    qDebug() << "Received chunk:" << response;
    if (!response.isEmpty()) {      // Chỉ update khi không rỗng
        ui->status->setText("ESP: " + response);
    }
}

void MainWindow::sendCommand(const QString &cmd) {
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(cmd.toUtf8() + "\r\n");
        socket->flush();
    }
}

void MainWindow::on_pushButton_clicked()
{
    sendCommand("LED_ON");
    if (mqttClient->state() == QMqttClient::Connected) {
        mqttClient->publish(QMqttTopicName("device/led/status"), QByteArray("ON"));
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    sendCommand("LED_OFF");
    if (mqttClient->state() == QMqttClient::Connected) {
        mqttClient->publish(QMqttTopicName("device/led/status"), QByteArray("OFF"));
    }
}
