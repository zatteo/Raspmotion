#include <qbluetoothserviceinfo.h>
#include <qbluetoothsocket.h>
#include <qbluetoothhostinfo.h>

#include <QDebug>

QT_USE_NAMESPACE

class CommandServer;

class Server : public QObject
{
    Q_OBJECT

public:
    Server(QObject *parent = 0);
    ~Server();

private slots:

private:
    int currentAdapterIndex;

    CommandServer *server;
    QList<QBluetoothHostInfo> localAdapters;

    QString localName;
};
