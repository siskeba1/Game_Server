#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class TcpServer : public QTcpServer
{
    Q_OBJECT
    void printServerInfo();
public:
    TcpServer(QObject *parent = NULL);
    bool startServer(QString ipAddress, int port);
protected:
    void incomingConnection(qintptr socketDescriptor) Q_DECL_OVERRIDE;
private:
    QTcpSocket *connection;
    QString msg;
private slots:
    void slotMessageRead();
};

#endif // TCPSERVER_H
