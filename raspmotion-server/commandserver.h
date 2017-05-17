#ifndef COMMANDSERVER_H
#define COMMANDSERVER_H

#include <QUdpSocket>

QT_USE_NAMESPACE

class CommandServer : public QObject
{
    Q_OBJECT

public:
    explicit CommandServer(QObject *parent = 0);
    ~CommandServer();

public slots:
    void readPendingDatagrams();
    void write(char c);

private:
    qint16 port;

    QHostAddress hostTablet;
    qint16 portTablet;

    QUdpSocket *socket;
};

#endif // COMMANDSERVER_H
