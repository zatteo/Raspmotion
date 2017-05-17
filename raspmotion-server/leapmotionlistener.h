#ifndef LEAPMOTIONLISTENER_H
#define LEAPMOTIONLISTENER_H

#include "Leap.h"
#include "message.h"
#include "commandserver.h"
#include "leapmotionlistener.h"
#include <QDebug>

using namespace Leap;

class LeapMotionListener : public Listener
{
public:
    LeapMotionListener();
    void onConnect(const Controller &controller);
    void onFrame(const Controller& controller);
    void update();

private:
    CommandServer *server;

    // LeapMotion
    Hand handLeft;
    Hand handRight;

    int pitch = 0;
    int roll = 0;
    int speed = 0;
    int tmpPitch= 0;
    int tmpRoll = 0;
    int tmpSpeed = 0;

    bool isLoopingUp = false;
    bool isLoopingRight = false;
    bool isLoopingLeft = false;
    bool tmpIsLoopingUp = false;
    bool tmpIsLoopingRight = false;
    bool tmpIsLoopingLeft = false;

    bool initHandPosition = false;
    float handPosition;

    int cptFrame = 0;
};

#endif // LEAPMOTIONLISTENER_H
