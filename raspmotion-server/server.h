#ifndef SERVER_H
#define SERVER_H

#include "Leap.h"
#include "commandserver.h"
#include <QBluetoothHostInfo>
#include <QBluetoothLocalDevice>

using namespace Leap;

class CommandServer;

class Server : public QObject
{
    Q_OBJECT

public:
    Server(QObject *parent = 0);
    ~Server();

private:
    // Bluetooth
    CommandServer *server;
    QList<QBluetoothHostInfo> localAdapters;
    QString localName;

    // Leap Motion
    Controller controller;
};

#endif // SERVER_H
