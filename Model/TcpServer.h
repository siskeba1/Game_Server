#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    TcpServer(QObject *parent = NULL);    
protected:
    void incomingConnection(qintptr clientId) Q_DECL_OVERRIDE;
private:
    QTcpSocket *connection;
    QString msg;
    void printServerInfo();
signals:
    signalServerStarted(QString ip, int port);
    signalServerStopped(QString ip, int port);

    signalServerAlreadyRunning(QString ip, int port);
    signalServerNotEvenStarted(QString ip, int port);

    signalShowOnStatusBar(QString message);
    signalRegisterClient(QTcpSocket*);
    signalDeleteClient(QTcpSocket*);

private slots:
    void slotIncomingConnection(int clientId);
    void slotMessageRead();
    void slotDisconnected();
public slots:
    bool startServer(QString ipAddress, int port);
    void shutDownServer();
};

#endif // TCPSERVER_H
