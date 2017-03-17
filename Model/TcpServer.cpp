#include "Model/TcpServer.h"
#include <Const/StringConstant.h>
#include <ServerWorkingThread/ServerWorkingThread.h>

#include <QDebug>
#include <QString>
#include <QDateTime>
#include <QDataStream>


#define PORT_RANGE 65535

TcpServer::TcpServer(QObject *parent) : QTcpServer(parent)
{
    qDebug() << "Tcp server constructor.";
}

bool TcpServer::startServer(QString ipAddress, int port)
{
    //If the server is already running and listening on ip/port.
    if (isListening())
    {
        qDebug() << StringConstant::ERROR_SERVER_IS_ALREADY_RUNNING;
        emit signalServerAlreadyRunning(ipAddress, port);
        return false;
    }
    ///Parameter checking
    //Ipv4 format checking
    if(!ipAddress.contains(QRegExp(StringConstant::REGEX_IPV4)))
    {
       qDebug () << StringConstant::ERROR_FORMAT_NOT_IPV4;
       emit signalShowOnStatusBar(StringConstant::ERROR_FORMAT_NOT_IPV4);
       return false;
    }
    //Port range checking.
    if (port > PORT_RANGE)
    {
        qDebug() << StringConstant::ERROR_OUT_OF_RANGE_PORT;
        emit signalShowOnStatusBar(StringConstant::ERROR_OUT_OF_RANGE_PORT);
        return false;
    }
    //Converting QString to QHostAddress.
    QHostAddress ip = QHostAddress(ipAddress);

    //Try to start the server using the given ip and port.
    if (!(this->listen(ip, port)))
    {
        qDebug() << StringConstant::ERROR_SERVER_UNABLE_TO_START << " Ip: " << ipAddress;
        emit signalShowOnStatusBar(StringConstant::ERROR_SERVER_UNABLE_TO_START);
        qDebug() << this->errorString();
        this->close();
        return false;
    }
    else
    {
        //The server is running.
        emit signalServerStarted(ipAddress, this->serverPort());
        printServerInfo();
        return true;
    }
}

void TcpServer::shutDownServer()
{
    if(isListening())
    {
        emit signalServerStopped(this->serverAddress().toString(), this->serverPort());
        this->close();
    }
    else
    {
        emit signalServerNotEvenStarted(this->serverAddress().toString(), this->serverPort());
    }
}

void TcpServer::incomingConnection(qintptr clientId)
{
    ///Parameter checking
    if(clientId == NULL)
    {
        //TODO: Error logging - Server::incomingConnection - parameter error.
        return;
    }

    //Start new thread for the new connection.
    ServerWorkingThread* serverWorkingThread = new ServerWorkingThread(this->parent(), this, clientId);
    serverWorkingThread->start();
}

void TcpServer::slotIncomingConnection(int clientId)
{
    qDebug() << StringConstant::CLIENT_CONNECTED << clientId;

    connection = new QTcpSocket(this);
    connection->setSocketDescriptor(clientId);

    emit signalRegisterClient(connection);

    if (connection)
    {
        //QString signalMessage = "ip:" + connection->peerAddress().toString() + " port:" + QString::number(connection->peerPort()) + " client connected. [" + QDateTime::currentDateTime().date().toString(StringConstant::DATE_FORMAT) + " " + QDateTime::currentDateTime().time().toString(StringConstant::TIME_FORMAT) +"]";
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
      qDebug() << "Üzenet[" << connection->socketDescriptor() <<"]: " << msg;
    }
    while (connection->bytesAvailable() > 0);
}

void TcpServer::printServerInfo()
{
    qDebug().noquote() << "Server ip: " << this->serverAddress().toString() << "\nServer port: " << this->serverPort();
}
