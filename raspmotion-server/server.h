#ifndef SERVER_H
#define SERVER_H

#include "commandserver.h"
#include <QBluetoothHostInfo>
#include <QBluetoothLocalDevice>

QT_USE_NAMESPACE

class CommandServer;

class Server : public QObject
{
    Q_OBJECT

public:
    Server(QObject *parent = 0);
    ~Server();

private:
    CommandServer *server;
    QList<QBluetoothHostInfo> localAdapters;
    QString localName;
};

#endif // SERVER_H
