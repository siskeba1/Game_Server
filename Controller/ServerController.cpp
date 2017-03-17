#include "Controller/ServerController.h"

ServerController::ServerController(QObject *parent) : QObject(parent)
{

}

ServerController::ServerController(TcpServer *tcpServer, ServerMainWindow *serverMainWindow)
{
    this->tcpServer = tcpServer;
    this->serverMainWindow = serverMainWindow;

    //Start listening at GUI button signal.
    connect(this->serverMainWindow, SIGNAL(signalStartButton(QString, int)), this->tcpServer, SLOT(startServer(QString, int)));

    //Stop listening at GUI button signal.
    connect(this->serverMainWindow, SIGNAL(signalShutDownButton()), this->tcpServer, SLOT(shutDownServer()));

    //GUI slot called at server start/stop signal.
    connect(this->tcpServer, SIGNAL(signalServerStarted(QString, int)), this->serverMainWindow, SLOT(slotServerStarted(QString, int)));
    connect(this->tcpServer, SIGNAL(signalServerStopped(QString, int)), this->serverMainWindow, SLOT(slotServerStopped(QString, int)));

    connect(this->tcpServer, SIGNAL(signalServerAlreadyRunning(QString, int)), this->serverMainWindow, SLOT(slotServerAlreadyRunning(QString, int)));
    connect(this->tcpServer, SIGNAL(signalServerNotEvenStarted(QString, int)), this->serverMainWindow, SLOT(slotServerNotEvenStarted(QString, int)));
    connect(this->tcpServer, SIGNAL(signalShowOnStatusBar(QString)), this->serverMainWindow, SLOT(slotUpdateStatusBar(QString)));
    connect(this->tcpServer, SIGNAL(signalRegisterClient(QTcpSocket*)), this->serverMainWindow, SLOT(slotNewClientConnected(QTcpSocket*)));

    //Show GUI - mainWindow
    this->serverMainWindow->show();
}
