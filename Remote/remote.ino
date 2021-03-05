#include <Arduino.h>
#include "lib/OmniBot.h"
#include "lib/Motor.h"
// #include "math.h"
#include "lib/UartCommunication.h"

#define PIN_MOT1 2
#define PIN_MOT1_PWM 3
#define PIN_MOT2 8
#define PIN_MOT2_PWM 9

#define PIN_MOT3 4
#define PIN_MOT3_PWM 5
#define PIN_MOT4 7
#define PIN_MOT4_PWM 6
UartCommunication comm;

void setup()
{
    //Serial.begin(9600);
    comm.begin(9600);
    pinMode(13, OUTPUT);
}


Motor m1(PIN_MOT3, PIN_MOT3_PWM, true); //left front
Motor m2(PIN_MOT4, PIN_MOT4_PWM); //right front

Motor m3(PIN_MOT1, PIN_MOT1_PWM); //left rear
Motor m4(PIN_MOT2, PIN_MOT2_PWM, true); //right rear

OmniBot robot(m1, m3, m2, m4);

void servo(uint8_t v1, uint8_t v2, uint8_t v3);

/**
 * add servo type = 20, pin, min, max
 * remote servo type = 22, id, pos, v(not use)
 * remote motor type = 55, vx, vy, w
 */

void r_stop()
{
    robot.stop();
}

void addServo(uint8_t pin, uint8_t minPos, uint8_t maxPos)
{
    robot.addServo(pin, minPos, maxPos);
}

void writeServo(uint8_t id, uint8_t pos, uint8_t v)
{
    robot.writeServo(id, pos, v);
}

void writeMotor(uint8_t vx, uint8_t vy, uint8_t w)
{
    robot.writeMotor(vx, vy, w);
}

void loop()
{

    comm.subscribe(20, addServo);
    comm.subscribe(22, writeServo);
    comm.subscribe(55, writeMotor);
    comm.subConFail(r_stop);

    while (true)
    {
        comm.loop();
    }


}

