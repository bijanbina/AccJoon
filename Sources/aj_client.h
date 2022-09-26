#ifndef AjClient_H
#define AjClient_H

#include <QTcpSocket>
#include <QString>
#include <QObject>
#include <QVector>
#include <stdio.h>
#include <stdlib.h>
#include <QTimer>

#define AJ_TIMEOUT    1000
#define AJ_WATCHDOG   1000  //Watchdog interval
#define AJ_Live       100   //Live send interval
#define AJ_CHECK_BTN  4     //Live send interval
#define AJ_CHECK_IN   4     //check input(native mode)
#define AJ_TAB_TIME   900   //Alt pressed time

#define AJ_PORT      7611
#define AJ_IP        "192.168.88.25"

class AjClient : public QObject
{
    Q_OBJECT

public:
    explicit AjClient(QString data, QObject *parent = 0);
    ~AjClient();

    void sendData(const char *data, int size);
    QString message;

signals:
    void errorConnection();

public slots:
    void connected();
    void start();
    void displayError(QAbstractSocket::SocketError socketError);
    void disconnected();

private:
    QTcpSocket tcpClient;
};

#endif // AjClient_H
