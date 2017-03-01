#include <QCoreApplication>
#include <QtBluetooth>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream out(stdout);

    QBluetoothLocalDevice localDevice;
    QString localDeviceName;

    Leap::Controller controller;

    // vérification de la disponibilité du Bluetooth
    if(localDevice.isValid())
    {
        out << "Bluetooth : OUI." << endl;

        localDevice.powerOn(); // activation du Bluetooth

        localDeviceName = localDevice.name();

        localDevice.setHostMode(QBluetoothLocalDevice::HostDiscoverable); // visibilité
    }
    else
    {
        out << "Bluetooth : NON." << endl;
    }

    return a.exec();
}
