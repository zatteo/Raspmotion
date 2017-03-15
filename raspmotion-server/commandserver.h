#ifndef COMMANDSERVER_H
#define COMMANDSERVER_H

#include <qbluetoothserviceinfo.h>
#include <qbluetoothaddress.h>

#include <QtCore/QObject>
#include <QtCore/QList>

QT_FORWARD_DECLARE_CLASS(QBluetoothServer)
QT_FORWARD_DECLARE_CLASS(QBluetoothSocket)

QT_USE_NAMESPACE

class CommandServer : public QObject
{
    Q_OBJECT

public:
    explicit CommandServer(QObject *parent = 0);
    ~CommandServer();

    void startServer(const QBluetoothAddress &localAdapter = QBluetoothAddress());
    void stopServer();

public slots:
    void sendMessage(const QString &message);

signals:
    void messageReceived(const QString &sender, const QString &message);
    void clientConnected(const QString &name);
    void clientDisconnected(const QString &name);

private slots:
    void clientConnected();
    void clientDisconnected();
    void readSocket();

private:
    QBluetoothServer *rfcommServer;
    QBluetoothServiceInfo serviceInfo;
    QBluetoothSocket *client;
};

#endif // COMMANDSERVER_H
