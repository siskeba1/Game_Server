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
protected:
    void incomingConnection(qintptr socketDescriptor) Q_DECL_OVERRIDE;
private:
    QTcpSocket *connection;
    QString msg;
signals:
    signalServerStarted();
    signalServerStopped();

    signalServerAlreadyRunning();
    signalServerNotEvenStarted();

private slots:
    void slotMessageRead();
public slots:
    bool startServer(QString ipAddress, int port);
    void shutDownServer();
};

#endif // TCPSERVER_H
