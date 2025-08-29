#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QMqttClient>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void readResponse();
private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QMqttClient *mqttClient;
    void sendCommand(const QString &cmd);
};
#endif // MAINWINDOW_H
