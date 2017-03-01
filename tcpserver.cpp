#include "tcpserver.h"

//#include <QDebug>
//#include <QString>

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
//    if (connection)
//    {
//        QString signalMessage = "ip:" + connection->peerAddress().toString() + " port:" + QString::number(connection->peerPort()) + " client connected. [" + QDateTime::currentDateTime().date().toString(Strings::DATE_FORMAT) + " " + QDateTime::currentDateTime().time().toString(Strings::TIME_FORMAT) +"]";
//        emit signalClientsChanged(signalMessage);

//        connection->startWarningTimer();
//        clientConnections.append(connection);

//        connect(connection, &QIODevice::readyRead, this, &Server::slotReadReady);
//        connect(connection, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
//    }
}

void TcpServer::printServerInfo()
{
    qDebug().noquote() << "Server ip: " << this->serverAddress().toString() << "\nServer port: " << this->serverPort();
}
