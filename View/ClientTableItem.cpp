#include "View/ClientTableItem.h"

ClientTableItem::ClientTableItem(int id, int ping, QDateTime connectionDate, bool connectionStatus) : QObject()
{
    this->id = id;
    this->ping = ping;
    this->connectionDate = connectionDate;
    this->connectionStatus = connectionStatus;
}

bool ClientTableItem::getConnectionStatus() const
{
    return connectionStatus;
}

void ClientTableItem::setConnectionStatus(bool value)
{
    connectionStatus = value;
}

QDateTime ClientTableItem::getConnectionDate() const
{
    return connectionDate;
}

void ClientTableItem::setConnectionDate(const QDateTime &value)
{
    connectionDate = value;
}

int ClientTableItem::getPing() const
{
    return ping;
}

void ClientTableItem::setPing(int value)
{
    ping = value;
}

int ClientTableItem::getId() const
{
    return id;
}

void ClientTableItem::setId(int value)
{
    id = value;
}
