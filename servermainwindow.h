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

private slots:
    void on_startButton_clicked();
    void on_shutDownButton_clicked();
private:
    Ui::ServerMainWindow *ui;
    bool checkIpFormat();
signals:
    void signalStartButton(QString ip, int port);
    void signalShutDownButton();
};

#endif // SERVERMAINWINDOW_H
