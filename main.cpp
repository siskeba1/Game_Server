#include "servermainwindow.h"
#include "Connector/serverconnector.h"
#include <tcpserver.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Model
    TcpServer *tcpServer = new TcpServer(new QObject);

    //View
    ServerMainWindow* serverMainWindow = new ServerMainWindow();

    //Connecctor
    ServerConnector* serverConnector = new ServerConnector(tcpServer, serverMainWindow);

    return a.exec();
}
