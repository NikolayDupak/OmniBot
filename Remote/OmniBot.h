//
// Created by Nikolay on 27.02.2021.
//

#ifndef OMI_REMOTE_ROBOT_H
#define OMI_REMOTE_ROBOT_H
#include "Arduino.h"
#include "Motor.h"


class OmniBot
{
public:
    OmniBot(Motor leftFront, Motor leftRear,
            Motor rightFront, Motor rightRear);

    void move(double xSpeed, double ySpeed, double wSpeed);

    void drive(int leftFront, int leftRear,
               int rightFront, int rightRear);

    void stop();



private:
    Motor leftFront;
    Motor leftRear;
    Motor rightFront;
    Motor rightRear;




};


#endif //OMI_REMOTE_ROBOT_H
