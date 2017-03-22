#ifndef CLIENTTABLEITEM_H
#define CLIENTTABLEITEM_H

#include <QObject>
#include <QStandardItem>
#include <QDateTime>

class ClientTableItem : public QObject
{
    Q_OBJECT
public:
    ClientTableItem(int id, int ping, QDateTime connectionDate, bool connectionStatus);
    bool getConnectionStatus() const;
    void setConnectionStatus(bool value);

    QDateTime getConnectionDate() const;
    void setConnectionDate(const QDateTime &value);

    int getPing() const;
    void setPing(int value);

    int getId() const;
    void setId(int value);
private:
    int id;
    int ping;
    QDateTime connectionDate;
    bool connectionStatus;
};

#endif // CLIENTTABLEITEM_H
