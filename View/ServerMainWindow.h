#ifndef SERVERMAINWINDOW_H
#define SERVERMAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>

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

private slots:
    void on_startButton_clicked();
    void on_shutDownButton_clicked();
private:
    Ui::ServerMainWindow *ui;
    bool checkIpFormat();
    void setupSplitterCollapsibility(QSplitter *splitter, bool collapseFlag);
    QString ServerAddress(QString ipAddress, int port);
signals:
    void signalStartButton(QString ip, int port);
    void signalShutDownButton();
protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // SERVERMAINWINDOW_H
