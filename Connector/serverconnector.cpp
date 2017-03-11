#include "Connector/serverconnector.h"

ServerConnector::ServerConnector(QObject *parent) : QObject(parent)
{

}

ServerConnector::ServerConnector(TcpServer *tcpServer, ServerMainWindow *serverMainWindow)
{
    this->tcpServer = tcpServer;
    this->serverMainWindow = serverMainWindow;

    //Start listening at GUI button signal.
    connect(this->serverMainWindow, SIGNAL(signalStartButton(QString,int)), this->tcpServer, SLOT(startServer(QString,int)));

    //Stop listening at GUI button signal.
    connect(this->serverMainWindow, SIGNAL(signalShutDownButton()), this->tcpServer, SLOT(shutDownServer()));

    //GUI slot called at server start signal.
    connect(this->tcpServer, SIGNAL(signalServerStarted()), this->serverMainWindow, SLOT(slotServerStarted()));

    //GUI slot called at server stop signal.
    connect(this->tcpServer, SIGNAL(signalServerStopped()), this->serverMainWindow, SLOT(slotServerStopped()));

    connect(this->tcpServer, SIGNAL(signalServerAlreadyRunning()), this->serverMainWindow, SLOT(slotServerAlreadyRunning()));
    connect(this->tcpServer, SIGNAL(signalServerNotEvenStarted()), this->serverMainWindow, SLOT(slotServerNotEvenStarted()));

    //Show GUI - mainWindow
    this->serverMainWindow->show();
}
