#include "server.h"
#include "commandserver.h"

#include <qbluetoothuuid.h>
#include <qbluetoothserver.h>
#include <qbluetoothservicediscoveryagent.h>
#include <qbluetoothdeviceinfo.h>
#include <qbluetoothlocaldevice.h>

#include <QTimer>

#include <QDebug>

static const QLatin1String serviceUuid("e8e10f95-1a70-4b27-9ccf-02010264e9c9");

Server::Server(QObject *parent): currentAdapterIndex(0)
{
    localAdapters = QBluetoothLocalDevice::allDevices();

    server = new CommandServer(this);
    connect(server, SIGNAL(clientConnected(QString)), this, SLOT(clientConnected(QString)));
    connect(server, SIGNAL(clientDisconnected(QString)), this, SLOT(clientDisconnected(QString)));
    connect(server, SIGNAL(messageReceived(QString,QString)),
            this, SLOT(showMessage(QString,QString)));
    connect(this, SIGNAL(sendMessage(QString)), server, SLOT(sendMessage(QString)));
    server->startServer();

    localName = QBluetoothLocalDevice().name();
}

Server::~Server()
{
    delete server;
}
