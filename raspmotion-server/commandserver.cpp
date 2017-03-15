#include "commandserver.h"

#include <qbluetoothserver.h>
#include <qbluetoothsocket.h>
#include <qbluetoothlocaldevice.h>

static const QLatin1String serviceUuid("e8e10f95-1a70-4b27-9ccf-02010264e9c9");

CommandServer::CommandServer(QObject *parent): QObject(parent), rfcommServer(0){}

CommandServer::~CommandServer()
{
    stopServer();
}

void CommandServer::startServer(const QBluetoothAddress& localAdapter)
{
    if (rfcommServer)
        return;

    rfcommServer = new QBluetoothServer(QBluetoothServiceInfo::RfcommProtocol, this);
    connect(rfcommServer, SIGNAL(newConnection()), this, SLOT(clientConnected()));

    bool result = rfcommServer->listen(localAdapter);
    if (!result) {
        qWarning() << "ERR : Cannot bind chat server to" << localAdapter.toString();
        return;
    }

    QBluetoothServiceInfo::Sequence classId;

    classId << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::SerialPort));
    serviceInfo.setAttribute(QBluetoothServiceInfo::BluetoothProfileDescriptorList, classId);

    classId.prepend(QVariant::fromValue(QBluetoothUuid(serviceUuid)));

    serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceClassIds, classId);
    serviceInfo.setAttribute(QBluetoothServiceInfo::BluetoothProfileDescriptorList, classId);

    // service name, description, provider and UUID
    serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceName, tr("CommandServer"));
    serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceDescription, tr("CommandServer 0.1"));
    serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceProvider, tr("ProjetIntegrateur2017"));
    serviceInfo.setServiceUuid(QBluetoothUuid(serviceUuid));

    QBluetoothServiceInfo::Sequence publicBrowse;
    publicBrowse << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::PublicBrowseGroup));
    serviceInfo.setAttribute(QBluetoothServiceInfo::BrowseGroupList, publicBrowse);

    QBluetoothServiceInfo::Sequence protocolDescriptorList;
    QBluetoothServiceInfo::Sequence protocol;
    protocol << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::L2cap));
    protocolDescriptorList.append(QVariant::fromValue(protocol));
    protocol.clear();
    protocol << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::Rfcomm)) << QVariant::fromValue(quint8(rfcommServer->serverPort()));
    protocolDescriptorList.append(QVariant::fromValue(protocol));
    serviceInfo.setAttribute(QBluetoothServiceInfo::ProtocolDescriptorList,
                             protocolDescriptorList);

    serviceInfo.registerService(localAdapter);

    qDebug() << "CommandServer started";
}

void CommandServer::stopServer()
{
    serviceInfo.unregisterService();

    delete client;

    delete rfcommServer;
    rfcommServer = 0;
}

void CommandServer::sendMessage(const QString &message)
{
    QByteArray text = message.toUtf8() + '\n';

    client->write(text);
}

void CommandServer::clientConnected()
{
    qDebug() << "Client connected";
    QBluetoothSocket *socket = rfcommServer->nextPendingConnection();
    if (!socket)
        return;

    connect(socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
    client = socket;
    emit clientConnected(socket->peerName());

    sendMessage("bonjour à toi aussi");
    sendMessage("ça va ?");
}

void CommandServer::clientDisconnected()
{
    QBluetoothSocket *socket = qobject_cast<QBluetoothSocket *>(sender());
    if (!socket)
        return;

    emit clientDisconnected(socket->peerName());

    client->deleteLater();
    socket->deleteLater();
}

void CommandServer::readSocket()
{
    QBluetoothSocket *socket = qobject_cast<QBluetoothSocket *>(sender());
    if (!socket)
        return;

    while (socket->canReadLine()) {
        QByteArray line = socket->readLine().trimmed();
        emit messageReceived(socket->peerName(),
                             QString::fromUtf8(line.constData(), line.length()));
        qDebug() << QString::fromUtf8(line.constData(), line.length());
    }
}
