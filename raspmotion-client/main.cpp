#include <QCoreApplication>
#include <QDebug>
#include <client.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Client client;

    client.discoverAndStart();

    return a.exec();
}
