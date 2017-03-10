#ifndef SERVERCONNECTOR_H
#define SERVERCONNECTOR_H

#include <tcpserver.h>
#include <servermainwindow.h>
#include <QObject>

class ServerConnector : public QObject
{
    Q_OBJECT
public:
    ServerConnector(QObject *parent = 0);
    ServerConnector(TcpServer* tcpServer, ServerMainWindow* serverMainWindow);
private:
    TcpServer* tcpServer;
    ServerMainWindow* serverMainWindow;
signals:

public slots:
};

#endif // SERVERCONNECTOR_H
