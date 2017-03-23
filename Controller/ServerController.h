#ifndef SERVERCONNECTOR_H
#define SERVERCONNECTOR_H

#include <Model/TcpServer/TcpServer.h>
#include <View/ServerMainWindow.h>
#include <QObject>

class ServerController : public QObject
{
    Q_OBJECT
public:
    ServerController(QObject *parent = 0);
    ServerController(TcpServer* tcpServer, ServerMainWindow* serverMainWindow);
private:
    TcpServer* tcpServer;
    ServerMainWindow* serverMainWindow;
signals:

public slots:
};

#endif // SERVERCONNECTOR_H
