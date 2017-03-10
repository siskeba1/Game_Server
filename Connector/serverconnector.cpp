#include "Connector/serverconnector.h"

ServerConnector::ServerConnector(QObject *parent) : QObject(parent)
{

}

ServerConnector::ServerConnector(TcpServer *tcpServer, ServerMainWindow *serverMainWindow)
{
    this->tcpServer = tcpServer;
    this->serverMainWindow = serverMainWindow;

    connect(this->serverMainWindow, SIGNAL(signalStartButton(QString,int)), this->tcpServer, SLOT(startServer(QString,int)));
    connect(this->serverMainWindow, SIGNAL(signalShutDownButton()), this->tcpServer, SLOT(shutDownServer()));

    this->serverMainWindow->show();
}
