#include "aj_client.h"
#include <string.h>
#include <QHostAddress>
#include "QThread"

AjClient::AjClient(QString data, QObject *parent) : QObject(parent)
{
    message = data;

    connect(&tcpClient, SIGNAL(connected()), this, SLOT(connected()));
    connect(&tcpClient, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(&tcpClient, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
}

AjClient::~AjClient()
{
    tcpClient.close();
}

void AjClient::displayError(QAbstractSocket::SocketError socketError)
{
    if (socketError == QTcpSocket::RemoteHostClosedError)
        return;

    qDebug() << tr("Network error") << tr("The following error occurred: %1.").arg(tcpClient.errorString());
    tcpClient.close();
    emit errorConnection();

}

void AjClient::connected()
{
    qDebug() << "Client: Connected";
    tcpClient.setSocketOption(QAbstractSocket::LowDelayOption, 1);
    sendData(message.toStdString().c_str(), message.length());
}

void AjClient::disconnected()
{
    tcpClient.close();
    qDebug() << "Client: Disconnected";
}

//TimerTick
void AjClient::start()
{
    if(!tcpClient.isOpen())
    {
        qDebug() << "TimerTick, connecting to: " << AJ_IP << AJ_PORT;
        tcpClient.connectToHost(QHostAddress(AJ_IP), AJ_PORT );
    }
}

void AjClient::sendData(const char *data, int size)
{
    if ( tcpClient.isOpen() )
    {
        tcpClient.write(data,size);
        tcpClient.waitForBytesWritten(50);

        qDebug() << "finisihed sending";
        exit(0);
    }
    else
    {
        qDebug() << "send data" << data << " failed";
    }
}
