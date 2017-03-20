#include "client.h"

static const QLatin1String serviceUuid("e8e10f95-1a70-4b27-9ccf-02010264e9c9");

Client::Client(QObject *parent): QObject(parent)
{
    qDebug() << "CommandController 0.1\n";
}

void Client::discoverAndStart()
{
    qDebug() << "Searching a CommandServer...";

    QBluetoothServiceDiscoveryAgent *discoveryAgent = new QBluetoothServiceDiscoveryAgent(this);

    connect(discoveryAgent, SIGNAL(serviceDiscovered(QBluetoothServiceInfo)), this, SLOT(serviceDiscovered(QBluetoothServiceInfo)));
    connect(discoveryAgent, SIGNAL(finished()), this, SLOT(fini()));

    discoveryAgent->start();
}

void Client::serviceDiscovered(const QBluetoothServiceInfo &service)
{

    qDebug() << "Device :" << service.device().address().toString();

    if(service.serviceUuid() == QBluetoothUuid(serviceUuid))
    {

       qDebug() << "CommandServer found" << "at" << service.device().address().toString();
       serviceInfo = new QBluetoothServiceInfo(service);

       connect(this, SIGNAL(found()), this, SLOT(start()));
       emit found();
   }
}

void Client::fini()
{
    qDebug() << "Search done.";
}

void Client::start()
{
    if(!serviceInfo)
        return;

    qDebug() << "Waiting for connection with the CommandServer...";
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    qDebug() << "Création du socket";
    socket->connectToService(*serviceInfo);
    qDebug() << "ConnectToService done";

    qDebug() << serviceInfo;

    connect(socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
}

void Client::stop()
{
    delete socket;
    socket = 0;
}

void Client::connected()
{
    qDebug() << "Connected";
    emit connected(socket->peerName());
    bonjour();
}

void Client::bonjour()
{
    sendMessage("bonjour");
}

void Client::sendMessage(const QString &message)
{
    qDebug() << "envoi du message" << message;
    QByteArray text = message.toUtf8() + '\n';
    socket->write(text);
}

void Client::readSocket()
{
    if (!socket)
        return;

    while (socket->canReadLine()) {
        QByteArray line = socket->readLine();
        emit messageReceived(socket->peerName(), QString::fromUtf8(line.constData(), line.length()));
        qDebug() << QString::fromUtf8(line.constData(), line.length());
    }
}
