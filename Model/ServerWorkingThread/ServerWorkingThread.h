#ifndef SERVERWORKINGTHREAD_H
#define SERVERWORKINGTHREAD_H

#include <Model/TcpServer/TcpServer.h>
#include <QObject>
#include <QThread>
#include <QtGlobal>

class ServerWorkingThread : public QThread
{
    Q_OBJECT

public:
    ServerWorkingThread(QObject *parent, TcpServer* tcpServer, int clientId);
private:
    TcpServer* tcpServer;
    int clientId;
    void run();

signals:
    void signalIncomingConnection(int clientId);
};

#endif // SERVERWORKINGTHREAD_H
