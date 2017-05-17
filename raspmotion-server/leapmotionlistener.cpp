#include "leapmotionlistener.h"

#include "message.h"

LeapMotionListener::LeapMotionListener()
{
    server = new CommandServer();

    qDebug() << "LeapMotionListener created";
}


void LeapMotionListener::onConnect(const Controller& controller){
    qDebug() << "LeapMotion connected";
}

void LeapMotionListener::onFrame(const Controller &controller){

    Frame frame = controller.frame();
    HandList hands = frame.hands();

    //init hand right/left
    if(!hands.isEmpty()) {
        if((frame.hands()[0]).isRight())
        {
            handRight = frame.hands()[0];
            handLeft = frame.hands()[1];
        }
        else
        {
            handRight = frame.hands()[1];
            handLeft = frame.hands()[0];
        }
    }

    //init
    double percent;

    float leftPitch = handLeft.direction().pitch();
    float rightPitch = handRight.direction().pitch();

    float leftRoll = handLeft.palmNormal().roll();
    float rightRoll = handRight.palmNormal().roll();

    float leftPalm = handLeft.palmPosition().z;
    float rightPalm = handRight.palmPosition().z;

    float rightFist = handRight.pinchStrength(); // grabAngle


    //change weapon
    if(rightRoll < - 1.5 && rightRoll > -2.)
    {
        cptFrame++;

        if(!initHandPosition)
        {
            initHandPosition = true;
            handPosition = handRight.palmPosition().x;
            //System.out.println("initHandPosition : " + handPosition);
        }

        if(cptFrame >= 150)
        {
            //System.out.println("Temps écoulé");
            initHandPosition = false;
            cptFrame = 0;
        }

        if(initHandPosition && handRight.palmPosition().x >= handPosition + 50.)
        {
            qDebug() << "Changement d'arme"; //REMPLACEMENT TIRE MISSIBLE
            initHandPosition = false;
            cptFrame = 0;
        }
    }
    else
    {
        initHandPosition = false;
        cptFrame = 0;
    }


    //  Up - Down
        if(leftPitch > -0.6 && leftPitch < -0.2)
        { //down
                leftPitch += 0.2;
                percent = floor((leftPitch * 100) / -0.4);
                tmpPitch = (int)percent/10;
        }
        else if(leftPitch > 0.2 && leftPitch < 0.6)
        { //up
            if (rightPitch > 0.2 && rightPitch < 0.6 )
            {
                tmpIsLoopingUp = true;
            }
            else
            {
                tmpIsLoopingUp = false;
                isLoopingUp = false;
                leftPitch -= 0.2;
                percent = floor((leftPitch * 100) / 0.4);
                tmpPitch = -(int)percent/10;
            }
        }
        else
        {
            tmpIsLoopingUp = false;
            isLoopingUp = false;
            //tout droit
        }


        // Left - right
        if (leftRoll > -0.6 && leftRoll < -0.2)
        { //right
            tmpIsLoopingLeft = false;
            isLoopingLeft = false;
            if (rightRoll > -0.6 && rightRoll < -0.2)
            {
                tmpIsLoopingRight = true;
            }
            else
            {
                tmpIsLoopingRight = false;
                isLoopingRight = false;
                leftRoll += 0.2;
                percent = floor((leftRoll * 100) / -0.4);
                tmpRoll = (int)percent/10;
            }
        }
        else if (leftRoll > 0.2 && leftRoll < 0.6)
        { //left
            tmpIsLoopingRight = false;
            isLoopingRight = false;
            if (rightRoll > 0.2 && rightRoll < 0.6)
            {
                tmpIsLoopingLeft = true;
            }
            else
            {
                tmpIsLoopingLeft = false;
                isLoopingLeft = false;
                leftRoll -= 0.2;
                percent = floor((leftRoll * 100) / 0.4);
                tmpRoll = -(int)percent/10;
            }

        }
        else
        {
            tmpIsLoopingLeft = false;
            isLoopingLeft = false;
            tmpIsLoopingRight = false;
            isLoopingRight = false;
            //tout droit
        }


        // Speed up - Speed down
       if(leftPalm > 20. && leftPalm < 65.)
       {  //speed down
           leftPalm -= 20.;
           percent = floor((leftPalm * 100) / 45.);
           tmpSpeed = -(int)percent/10;
       }
       else if(leftPalm > -65. && leftPalm < -20.)
       { //speed up
           leftPalm += 20.;
           percent = floor((leftPalm * 100) / -45.);
           tmpSpeed = (int)percent/10;
       }

       update();

       //Tirer
        if (rightFist > 0.8)
        {
            if (cptFrame%50 == 0)
            {
                qDebug() << frame.id() << " : Tirer";
                tmpPitch = pitch;
                tmpSpeed = speed;
                tmpRoll = roll;
            }
        }
}

void LeapMotionListener::update()
{
    std::stringstream str;

    if(tmpIsLoopingRight && !isLoopingRight)
    {
        isLoopingRight = tmpIsLoopingRight;
        qDebug() << " : looping right";
        return;
    }

    if(tmpIsLoopingUp && !isLoopingUp)
    {
        isLoopingUp = tmpIsLoopingUp;
        qDebug() << " : looping up";
        return;
    }

    if(tmpIsLoopingLeft && !isLoopingLeft)
    {
        isLoopingLeft = tmpIsLoopingLeft;
        qDebug() << " : looping left";
        return;
    }

    if(tmpPitch != pitch)
    {
        pitch = tmpPitch;
        str << "up/down (" << pitch << ") ";
    }

    if(tmpRoll != roll)
    {
        roll = tmpRoll;
        str << "left/right (" << roll << ") ";
    }

    if(tmpSpeed != speed)
    {
        speed = tmpSpeed;
        str << "speed (" << speed << ") ";
    }

    std::string s = str.str();

    if(s.compare("") != 0)
    {
        std::string strFrame = "Frame ";
        qDebug() << QString::fromStdString(strFrame) << " : " << QString::fromStdString(s);
    }
}
