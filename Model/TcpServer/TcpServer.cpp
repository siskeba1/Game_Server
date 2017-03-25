#include "Model/TcpServer/TcpServer.h"
#include <Const/StringConstant.h>
#include <Model/ServerWorkingThread/ServerWorkingThread.h>
#include <Model/MessageProcessor/MessageProcessor.h>

#include <QDebug>
#include <QString>
#include <QDateTime>
#include <QDataStream>


#define PORT_RANGE 65535

TcpServer::TcpServer(QObject *parent) : QTcpServer(parent)
{
    qDebug() << "Tcp server constructor.";
    messageProcessor_ = new MessageProcessor(this);

    connect(messageProcessor_, SIGNAL(signalAnswerPing()), this, SLOT(slotTestAnswer()));
    connect(this, SIGNAL(signalRegisterClient(QTcpSocket*)), this, SLOT(slotRegisterClient(QTcpSocket*)));
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
    connection_ = qobject_cast<QTcpSocket*>(sender());
    int clientId = connection_->socketDescriptor();

    //Signal to the Main Window's table view slot.
    emit signalDeleteClient(connection_);

    //Removing from list.
    if(!clientList_.contains(clientId))
    {
        qDebug() << "[Warning] The client wasn't in the client list, delete from list failed.";
    }
    else
    {
        clientList_.remove(clientId);
        qDebug() << "Client removed from the list. ID: " << clientId;
    }
}

void TcpServer::slotRegisterClient(QTcpSocket *newClient)
{
    int clientId = newClient->socketDescriptor();
    if(clientList_.contains(clientId))
    {
        //Client is already registered.
        qDebug() << "[Warning] The client is already in the list.";
        return;
    }

    clientList_.insert(clientId, newClient);
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
        messageProcessor_->process(incomingMessage_);
        qDebug() << "Üzenet[" << connection_->socketDescriptor() <<"]: " << incomingMessage_;
    }
    while (connection_->bytesAvailable() > 0);
}

void TcpServer::sendMessage(QString msg)
{
    //FIXME : cast TCP socket connection_ from the clientlist, id given in this method's parameter.
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

///SLOTS

void TcpServer::slotTestAnswer()
{
    sendMessage(QString("Answer message from server."));
}
