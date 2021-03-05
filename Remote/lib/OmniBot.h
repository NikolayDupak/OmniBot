//
// Created by Nikolay on 27.02.2021.
//

#ifndef OMI_REMOTE_ROBOT_H
#define OMI_REMOTE_ROBOT_H
#include "Arduino.h"
#include "Motor.h"
#include "Servo/src/Servo.h"

class OmniBot
{
public:
    OmniBot(Motor leftFront, Motor leftRear,
            Motor rightFront, Motor rightRear);

    void move(double xSpeed, double ySpeed, double wSpeed);

    void drive(int leftFront, int leftRear,
               int rightFront, int rightRear);

    void stop();

    void addServo(uint8_t pin, uint8_t minPos, uint8_t maxPos);

    void writeServo(uint8_t id, uint8_t pos, uint8_t v);

    void writeMotor(uint8_t vx, uint8_t vy, uint8_t w);

    Servo servo[5];

private:
    Motor leftFront;
    Motor leftRear;
    Motor rightFront;
    Motor rightRear;
    uint8_t id;







};


#endif //OMI_REMOTE_ROBOT_H
