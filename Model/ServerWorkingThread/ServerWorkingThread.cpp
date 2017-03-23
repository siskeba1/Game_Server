#include "Model/ServerWorkingThread/ServerWorkingThread.h"
#include <QDebug>


ServerWorkingThread::ServerWorkingThread(QObject* parent, TcpServer *tcpServer, int clientId) : QThread(parent)
{
    this->tcpServer = tcpServer;
    this->clientId = clientId;
    connect(this, SIGNAL(signalIncomingConnection(int)), this->tcpServer, SLOT(slotIncomingConnection(int)));
}

void ServerWorkingThread::run()
{
    emit signalIncomingConnection(clientId);
}
