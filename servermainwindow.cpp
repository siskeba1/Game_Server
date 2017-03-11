#include "servermainwindow.h"
#include "ui_servermainwindow.h"
#include "stringconstant.h"

ServerMainWindow::ServerMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerMainWindow)
{
    ui->setupUi(this);
}

ServerMainWindow::~ServerMainWindow()
{
    delete ui;
}

/**
 * @brief ServerMainWindow::on_startButton_clicked
 * Called when start button clicked. Emits the start signal.
 */
void ServerMainWindow::on_startButton_clicked()
{
    emit signalStartButton(ui->ipLineEdit->text(), ui->portLineEdit->text().toInt());
}

/**
 * @brief ServerMainWindow::on_shutDownButton_clicked
 * Called when shutdown button clicked. Emits the shutdown signal.
 */
void ServerMainWindow::on_shutDownButton_clicked()
{
    emit signalShutDownButton();
}

void ServerMainWindow::slotServerStarted()
{
    ui->serverStatusValue->setText(StringConstant::SERVER_RUNNING);
    ui->statusBar->showMessage(StringConstant::SERVER_RUNNING);
}

void ServerMainWindow::slotServerStopped()
{
    ui->serverStatusValue->setText(StringConstant::SERVER_NOT_RUNNING);
    ui->statusBar->showMessage(StringConstant::SERVER_NOT_RUNNING);
}

void ServerMainWindow::slotServerAlreadyRunning()
{
    ui->statusBar->showMessage(StringConstant::ERROR_SERVER_IS_ALREADY_RUNNING);
}

void ServerMainWindow::slotServerNotEvenStarted()
{
    ui->statusBar->showMessage(StringConstant::ERROR_SERVER_NOT_EVEN_STARTED);
}

//bool ServerMainWindow::checkIpFormat()
//{
//    //Checks Ipv4 format match.
//    if(ui->ipLineEdit->text().contains(QRegExp(StringConstant::REGEX_IPV4)))
//    {
//        emit signalValidIp();
//        return true;
//    }
//    else
//    {
//        emit signalErrorMessage(StringConstant::ERROR_FORMAT_NOT_IPV4);
//        return false;
//    }
//}
