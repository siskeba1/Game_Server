#include "tcpserver.h"

#include <QDebug>
#include <QString>
#include <QDateTime>
#include <stringconstant.h>
#include <QDataStream>

TcpServer::TcpServer(QObject *parent) : QTcpServer(parent)
{
    startServer(QString("192.168.153.1"), 6000);
    qDebug() << "Hello";
}

bool TcpServer::startServer(QString ipAddress, int port)
{
    ///Parameter checking
    //Ipv4 format checking
//    if(!ipAddress.contains(QRegExp(Strings::REGEX_IPV4)))
//    {
//       qDebug () << Strings::ERROR_INVALID_INPUT_IP_ADDRESS;
//       return false;
//    }
//    //Port range checking.
//    if (port > PORT_RANGE)
//    {
//        qDebug() << Strings::ERROR_OUT_OF_RANGE_PORT;
//        return false;
//    }
    //Converting QString to QHostAddress.
    QHostAddress ip = QHostAddress(ipAddress);

    //Try to start the server using the given ip and port.
    if (!(this->listen(ip, port)))
    {
//        qDebug() << Strings::ERROR_UNABLE_TO_START_SERVER << ipAddress;
        qDebug() << this->errorString();
        this->close();
        return false;
    }
    else
    {
        //The server is running.
        printServerInfo();
        return true;
    }
}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
    ///Parameter checking
    if(socketDescriptor == NULL)
    {
        //TODO: Error logging - Server::incomingConnection - parameter error.
        return;
    }

    connection = new QTcpSocket(this);
    connection->setSocketDescriptor(socketDescriptor);
    if (connection)
    {
        QString signalMessage = "ip:" + connection->peerAddress().toString() + " port:" + QString::number(connection->peerPort()) + " client connected. [" + QDateTime::currentDateTime().date().toString(StringConstant::DATE_FORMAT) + " " + QDateTime::currentDateTime().time().toString(StringConstant::TIME_FORMAT) +"]";
        //emit signalClientsChanged(signalMessage);

        //connection->startWarningTimer();
        //clientConnections.append(connection);

        connect(connection, &QIODevice::readyRead, this, &TcpServer::slotMessageRead);
        //connect(connection, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
    }
}

void TcpServer::slotMessageRead()
{
    connection = qobject_cast<QTcpSocket*>(sender());
    connection->waitForReadyRead(10);
    do
    {
      QDataStream in;
      in.setDevice(connection);
      in.setVersion(QDataStream::Qt_5_7);
      in.startTransaction();
      in >> msg;
      in.commitTransaction();
      //Decryption.
      qDebug() << "Üzenet: " << msg;
    }
    while (connection->bytesAvailable() > 0);
}

void TcpServer::printServerInfo()
{
    qDebug().noquote() << "Server ip: " << this->serverAddress().toString() << "\nServer port: " << this->serverPort();
}
