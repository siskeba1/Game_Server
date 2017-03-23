#include "View/ServerMainWindow.h"
#include "Controller//ServerController.h"
#include <Model/TcpServer/TcpServer.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    //Model
    TcpServer *tcpServer = new TcpServer(new QObject);

    //View
    ServerMainWindow* serverMainWindow = new ServerMainWindow();

    //Connecctor
    ServerController* serverController = new ServerController(tcpServer, serverMainWindow);

    return application.exec();
}
