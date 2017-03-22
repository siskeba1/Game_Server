#ifndef SERVERMAINWINDOW_H
#define SERVERMAINWINDOW_H

#include <View/ClientTableItem.h>

#include <QMainWindow>
#include <QSplitter>
#include <QTableWidget>
#include <QStandardItemModel>
#include <QTcpSocket>
#include <QMap>

namespace Ui {
class ServerMainWindow;
}

class ServerMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerMainWindow(QWidget *parent = 0);
    ~ServerMainWindow();

public slots:
    void slotServerStarted(QString ipAddress, int port);
    void slotServerStopped(QString ipAddress, int port);

    void slotServerAlreadyRunning(QString ipAddress, int port);
    void slotServerNotEvenStarted(QString ipAddress, int port);

    void slotUpdateStatusBar(QString message);
    void slotNewClientConnected(QTcpSocket* client);
    void slotClientDisconnected(QTcpSocket *client);
private slots:
    void on_startButton_clicked();
    void on_shutDownButton_clicked();
private:
    Ui::ServerMainWindow* ui;
    bool checkIpFormat();
    void setupSplitterCollapsibility(QSplitter *splitter, bool collapseFlag);
    QString ServerAddress(QString ipAddress, int port);
    QStandardItemModel* tableModel;
    QStringList tableHeader;
    QMap<QTcpSocket *, ClientTableItem*> *clientItemList;
    void setupTableView();
    void updateClientTable();
    void clearTableView();
signals:
    void signalStartButton(QString ip, int port);
    void signalShutDownButton();
protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // SERVERMAINWINDOW_H
