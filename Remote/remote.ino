#include <Arduino.h>
#include "OmniBot.h"
#include "Motor.h"
// #include "math.h"
#include "UartCommunication.h"

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



Motor m1(PIN_MOT3,PIN_MOT3_PWM, true); //left front
Motor m2(PIN_MOT4,PIN_MOT4_PWM); //right front

Motor m3(PIN_MOT1,PIN_MOT1_PWM); //left rear
Motor m4(PIN_MOT2,PIN_MOT2_PWM, true); //right rear

OmniBot robot(m1, m3, m2, m4);



//
int error = 0;
void loop()
{
    //comm.sendPackege(10, 100, 100, 100);
    //robot.stop();
    //delay(500);

    bool status = comm.recivePackege();

    if (status)
    {

        uint8_t type = comm.recivedPackege[0];
        uint8_t vx = comm.recivedPackege[1];
        uint8_t vy = comm.recivedPackege[2];
        uint8_t vw = comm.recivedPackege[3];
        if (type == 55)
            robot.move(vx - 128,vy - 128,vw - 128);
        if (type == 56)
            digitalWrite(13, vx);
        // uint8_t val4 = comm.recivedPackege[1];
        //comm.sendPackege(type, val1, val2, val3);
        //comm.sendPackege(10, 10, 10, 10);
        //Serial.println(type);
        //Serial.println(val1);
        //Serial.println(val2);
        //Serial.println(val3);

        delay(10);
        error = 0;
    } else
    {
        error += 1;
        delay(50);
    }
    if (error >= 20)
        robot.stop();

    //delay(300);


}

