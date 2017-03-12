#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>

class TcpServer : public QTcpServer
{
    Q_OBJECT
    void printServerInfo();
public:
    TcpServer(QObject *parent = NULL);    
protected:
    void incomingConnection(qintptr socketDescriptor) Q_DECL_OVERRIDE;
private:
    QTcpSocket *connection;
    QString msg;
signals:
    signalServerStarted(QString ip, int port);
    signalServerStopped(QString ip, int port);

    signalServerAlreadyRunning(QString ip, int port);
    signalServerNotEvenStarted(QString ip, int port);

private slots:
    void slotMessageRead();
public slots:
    bool startServer(QString ipAddress, int port);
    void shutDownServer();
};

#endif // TCPSERVER_H
