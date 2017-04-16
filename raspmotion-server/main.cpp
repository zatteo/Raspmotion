#include "leapmotionlistener.h"

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    LeapMotionListener leapmotion;
    Controller controller;
    controller.addListener(leapmotion);

    return app.exec();
}

