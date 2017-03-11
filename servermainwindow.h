#ifndef SERVERMAINWINDOW_H
#define SERVERMAINWINDOW_H

#include <QMainWindow>

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
private slots:
    void on_startButton_clicked();
    void on_shutDownButton_clicked();
private:
    Ui::ServerMainWindow *ui;
    bool checkIpFormat();
signals:
    void signalStartButton(QString ip, int port);
    void signalShutDownButton();
protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // SERVERMAINWINDOW_H
