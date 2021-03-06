//
// Created by Nikolay on 27.02.2021.
//

#include "OmniBot.h"
#include "Arduino.h"
#include "Motor.h"


OmniBot::OmniBot(Motor leftFront, Motor leftRear,
                 Motor rightFront, Motor rightRear) :
                 leftFront(leftFront), leftRear(leftRear),
                 rightFront(rightFront), rightRear(rightRear)
{
    id = 0;
}

void OmniBot::drive(int leftFront, int leftRear, int rightFront, int rightRear)
{
    /*
     * speed sets between -100 and 100 for each motor
     * -1 to -100 - drive back
     * 1 to 100 - drive forward
     * 0 - stop
     * */
    if (leftFront >= 0)
        this->leftFront.rotate(true, leftFront);
    else
        this->leftFront.rotate(false, -leftFront);
    if (leftRear >= 0)
        this->leftRear.rotate(true, leftRear);
    else
        this->leftRear.rotate(false, -leftRear);
    if (rightFront >= 0)
        this->rightFront.rotate(true, rightFront);
    else
        this->rightFront.rotate(false, -rightFront);
    if (rightRear >= 0)
        this->rightRear.rotate(true, rightRear);
    else
        this->rightRear.rotate(false, -rightRear);



}

void OmniBot::move(double xSpeed, double ySpeed, double wSpeed)
{
    /*
     * speed sets between -100 and 100
     * -1 to -100 - drive back
     * 1 to 100 - drive forward
     * 0 - stop
     * */
    double s = abs(xSpeed) + abs(ySpeed) + abs(wSpeed);
    xSpeed /= s;
    ySpeed /= s;
    wSpeed /= s;
    if (s > 100)
        s = 100;
    if (s < -100)
        s = -100;
    xSpeed *= s;
    ySpeed *= s;
    wSpeed *= s;
    int w1 = int(-ySpeed + xSpeed + (wSpeed * 1));
    int w2 = int(ySpeed + xSpeed + (-wSpeed * 1));
    int w3 = int(ySpeed + xSpeed + (wSpeed * 1));
    int w4 = int(-ySpeed + xSpeed + (-wSpeed * 1));
    this->drive(w1,w3,w2,w4);
}

void OmniBot::stop()
{
    this->drive(0,0,0,0);

}

void OmniBot::addServo(uint8_t pin, uint8_t minPos=0, uint8_t maxPos=180)
{
    this->servo[id].attach(pin);
    this->servo[id].write(90);
    id++;

}

void OmniBot::writeServo(uint8_t id, uint8_t pos, uint8_t v)
{
    this->servo[id].write(pos);
}

void OmniBot::writeMotor(uint8_t vx, uint8_t vy, uint8_t w)
{
    this->move(vx - 128, vy - 128, w - 128);
}
