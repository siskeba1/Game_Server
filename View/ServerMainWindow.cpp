#include "View/ServerMainWindow.h"
#include "ui_servermainwindow.h"
#include "Const/StringConstant.h"
#include <QTableWidget>
#include "QKeyEvent"
#include <QDebug>

ServerMainWindow::ServerMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerMainWindow)
{
    ui->setupUi(this);

    setupSplitterCollapsibility(ui->splitter, false);
    setupSplitterCollapsibility(ui->splitter_2, false);

    setupTableView();
}

ServerMainWindow::~ServerMainWindow()
{
    delete ui;
}

void ServerMainWindow::setupTableView()
{
    tableModel = new QStandardItemModel(0, 4);
    tableHeader.append(QString("Client number"));
    tableHeader.append(QString("Client port"));
    tableHeader.append(QString("Connect date"));
    tableHeader.append(QString("Ping"));
    tableModel->setHorizontalHeaderLabels(tableHeader);
    ui->tableView->setModel(tableModel);
    ui->tableView->setVisible(true);
}

QString ServerMainWindow::ServerAddress(QString ipAddress, int port)
{
    if(ipAddress.isNull())
    {
       return QString();
    }
    else
    {
        return " " + ipAddress + ":" + QString::number(port);
    }
}

void ServerMainWindow::setupSplitterCollapsibility(QSplitter *splitter, bool collapseFlag)
{
    //Set all splitter element to non-collapsible.
    QList<QFrame *> childrenOfSplitter = splitter->findChildren<QFrame *>(QRegExp(".*"), Qt::FindDirectChildrenOnly);
    for(int i = 0; i < childrenOfSplitter.size(); i++)
    {
        splitter->setCollapsible(i, collapseFlag);
    }
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

void ServerMainWindow::slotServerStarted(QString ipAddress, int port)
{
    ui->serverStatusValue->setText(StringConstant::SERVER_RUNNING);
    ui->serverStatusSign->setStyleSheet("QLabel { background-color : green; }");
    ui->statusBar->showMessage(StringConstant::SERVER_RUNNING + ServerAddress(ipAddress, port));
    ui->portLineEdit->setText(QString::number(port));

    //Disable line edits
    ui->ipLineEdit->setEnabled(false);
    ui->portLineEdit->setEnabled(false);
}

void ServerMainWindow::slotServerStopped(QString ipAddress, int port)
{
    ui->serverStatusValue->setText(StringConstant::SERVER_NOT_RUNNING);
    ui->serverStatusSign->setStyleSheet("QLabel { background-color : red; }");
    ui->statusBar->showMessage(StringConstant::SERVER_NOT_RUNNING + ServerAddress(ipAddress, port));

    //Enable line edits
    ui->ipLineEdit->setEnabled(true);
    ui->portLineEdit->setEnabled(true);
}

void ServerMainWindow::slotServerAlreadyRunning(QString ipAddress, int port)
{
    ui->statusBar->showMessage(StringConstant::ERROR_SERVER_IS_ALREADY_RUNNING + ServerAddress(ipAddress, port));
}

void ServerMainWindow::slotServerNotEvenStarted(QString ipAddress, int port)
{
    ui->statusBar->showMessage(StringConstant::ERROR_SERVER_NOT_EVEN_STARTED + ServerAddress(ipAddress, port));
}

void ServerMainWindow::keyPressEvent(QKeyEvent *event)
{

    switch(event->key())
    {
    //When ENTER key is pressed behaves, like start button was pressed.
    case Qt::Key_Return:
    {
        on_startButton_clicked();
    }
        break;
    }
}

void ServerMainWindow::slotUpdateStatusBar(QString message)
{
    ui->statusBar->showMessage(message);
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
