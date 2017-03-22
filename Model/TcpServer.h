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
    QString getMsg() const;
    void setMsg(const QString &value);
    void sendMessage(QString msg);
protected:
    void incomingConnection(qintptr clientId) Q_DECL_OVERRIDE;
private:
    QTcpSocket *connection_;
    QString incomingMessage_;
    QMap<int, QTcpSocket*> clientList;
    void printServerInfo();
signals:
    signalServerStarted(QString ip, int port);
    signalServerStopped(QString ip, int port);

    signalServerAlreadyRunning(QString ip, int port);
    signalServerNotEvenStarted(QString ip, int port);

    signalShowOnStatusBar(QString statusMessage);
    signalRegisterClient(QTcpSocket*);
    signalDeleteClient(QTcpSocket*);

private slots:
    void slotIncomingConnection(int clientId);
    void slotMessageRead();
    void slotDisconnected();
    void slotRegisterClient(QTcpSocket* newClient);
public slots:
    bool startServer(QString ipAddress, int port);
    void shutDownServer();
};

#endif // TCPSERVER_H
