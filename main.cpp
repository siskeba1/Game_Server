#include "servermainwindow.h"
#include <QApplication>
#include <tcpserver.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TcpServer *tcpServer = new TcpServer(new QObject);

    ServerMainWindow w;
    w.show();

    return a.exec();
}
