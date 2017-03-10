#include <qbluetoothserviceinfo.h>
#include <qbluetoothsocket.h>
#include <qbluetoothhostinfo.h>

#include <QDebug>

QT_USE_NAMESPACE

class ChatServer;

//! [declaration]
class Chat : public QObject
{
    Q_OBJECT

public:
    Chat(QObject *parent = 0);
    ~Chat();

private slots:

private:
    int currentAdapterIndex;

    ChatServer *server;
    QList<QBluetoothHostInfo> localAdapters;

    QString localName;
};
//! [declaration]
