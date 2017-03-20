#ifndef CLIENT_H
#define CLIENT_H

#include <QBluetoothSocket>
#include <QBluetoothServiceDiscoveryAgent>

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = 0);
    void stop();

public slots:
    void start();
    void sendMessage(const QString &message);
    void discoverAndStart();
    void serviceDiscovered(const QBluetoothServiceInfo &service);
    void fini();

signals:
    void found();
    void messageReceived(const QString &sender, const QString &message);
    void connected(const QString &name);
    void disconnected();

private slots:
    void readSocket();
    void connected();

private:
    QBluetoothSocket *socket = NULL;
    QBluetoothServiceInfo *serviceInfo = NULL;
};

#endif // CLIENT_H
