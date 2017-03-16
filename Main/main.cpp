#include "View/ServerMainWindow.h"
#include "Controller//ServerController.h"
#include <Model/TcpServer.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Model
    TcpServer *tcpServer = new TcpServer(new QObject);

    //View
    ServerMainWindow* serverMainWindow = new ServerMainWindow();

    //Connecctor
    ServerController* serverController= new ServerController(tcpServer, serverMainWindow);

    return a.exec();
}
