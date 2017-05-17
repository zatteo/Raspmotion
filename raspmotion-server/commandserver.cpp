#include "commandserver.h"
#include <QNetworkDatagram>

#include "message.h"

CommandServer::CommandServer(QObject *parent): QObject(parent)
{
//    port = 1234;

//    hostTablet = QHostAddress("192.168.43.13");

//    portTablet = 26000;

//    socket = new QUdpSocket(this);
//    socket->bind(QHostAddress::Any, port);

//    connect(socket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));

//    write('c');

        QTextStream s(stdin);
        qDebug() << "Port d'écoute :";
        port = s.readLine().toShort();

        qDebug() << "IP de la tablette :";
        hostTablet = QHostAddress(s.readLine());

        qDebug() << "Port de la tablette:";
        portTablet = s.readLine().toShort();

        socket = new QUdpSocket(this);
        socket->bind(QHostAddress::Any, port);

        connect(socket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));

        write('c');
}

CommandServer::~CommandServer()
{

}

/* prend en paramètre 2 entiers sur 16 bits
 * cmd : le numéro de la commande
 * arg : l'argument éventuel de la commande
 */
void CommandServer::write(char c)
{
    qDebug() << "a";
    socket->writeDatagram("aaaa", 4, hostTablet, portTablet);
}

void CommandServer::readPendingDatagrams()
{
    qDebug() << "yolo";

    while (socket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = socket->receiveDatagram();
        qDebug() << QString::fromStdString(datagram.data().toStdString());
    }
}
