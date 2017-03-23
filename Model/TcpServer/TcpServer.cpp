#include "Model/TcpServer/TcpServer.h"
#include <Const/StringConstant.h>
#include <Model/ServerWorkingThread/ServerWorkingThread.h>

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

QString TcpServer::getMsg() const
{
    return incomingMessage_;
}

void TcpServer::setMsg(const QString &value)
{
    incomingMessage_ = value;
}

void TcpServer::slotIncomingConnection(int clientId)
{
    qDebug() << StringConstant::CLIENT_CONNECTED << clientId;
    connection_ = new QTcpSocket(this);
    connection_->setSocketDescriptor(clientId);
    emit signalRegisterClient(connection_);

    if (connection_)
    {
        connect(connection_, &QIODevice::readyRead, this, &TcpServer::slotMessageRead);
        connect(connection_, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
    }
}

void TcpServer::slotDisconnected()
{
    emit signalDeleteClient(connection_);
}

void TcpServer::slotRegisterClient(QTcpSocket *newClient)
{
    int clientId = newClient->socketDescriptor();
    if(clientList.contains(clientId))
    {
        //Client is already registered.
        qDebug() << "[Warning] The client is already in the list.";
        return;
    }

    clientList.insert(clientId, newClient);
}

void TcpServer::slotMessageRead()
{
    connection_ = qobject_cast<QTcpSocket*>(sender());
    connection_->waitForReadyRead(10);
    do
    {
        QDataStream in;
        in.setDevice(connection_);
        in.setVersion(QDataStream::Qt_5_7);
        in.startTransaction();
        in >> incomingMessage_;
        in.commitTransaction();
        //Decryption.
        //TODO: Message processing.
        qDebug() << "Üzenet[" << connection_->socketDescriptor() <<"]: " << incomingMessage_;
    }
    while (connection_->bytesAvailable() > 0);
}

void TcpServer::sendMessage(QString msg)
{
    connection_ = qobject_cast<QTcpSocket*>(sender());
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);

    //Encryption and message sending.
    out << msg; //QString::fromStdString(AESCrypterCommunication->encryption(msg.toStdString().c_str()).toStdString());
    connection_->write(block);
    connection_->waitForBytesWritten();
}

void TcpServer::printServerInfo()
{
    qDebug().noquote() << "Server ip: " << this->serverAddress().toString() << "\nServer port: " << this->serverPort();
}
