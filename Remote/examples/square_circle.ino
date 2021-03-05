#include <Arduino.h>
#include "OmniBot.h"
#include "Motor.h"
#include <cmath>

#define PIN_MOT1 2
#define PIN_MOT1_PWM 3
#define PIN_MOT2 8
#define PIN_MOT2_PWM 9

#define PIN_MOT3 4
#define PIN_MOT3_PWM 5
#define PIN_MOT4 7
#define PIN_MOT4_PWM 6

void square();

void setup()
{

}
Motor m1(PIN_MOT3,PIN_MOT3_PWM, true); //left front
Motor m2(PIN_MOT4,PIN_MOT4_PWM); //right front

Motor m3(PIN_MOT1,PIN_MOT1_PWM); //left rear
Motor m4(PIN_MOT2,PIN_MOT2_PWM, true); //right rear

OmniBot robot(m1, m3, m2, m4);

void circle()
{
    double lapTime = 10;
    int n = 3;
    double r = 2.5;
    double vx, vy;
    int v0 = 0;
    //double w = 2*PI / lapTime;
    double w = 1 / r;

    unsigned long t0 = millis() / 1000;
    unsigned long t = 0;

    while (w * t < 2 * PI)
    {
        vx = w*r* sin(w*t);
        vy = w*r* cos(w*t);
        t =  millis() / 1000 - t0;
        int vx_robot = vx*100;
        int vy_robot = vy*100;
        //int vx_world = vx_robot*cos(w*t) - vy_robot*sin(w*t);
        //int vy_world = vx_robot*sin(w*t) + vy_robot*cos(w*t);
        robot.move(vx_robot, vy_robot, 0);
    }

}

void loop()
{
    //square();
    circle();
    
    robot.stop();
    delay(5000);


}

void square()
{

    robot.move(100, 0,0);
    delay(2000);
    robot.move(0, 100,0);
    delay(2000);
    robot.move(-100, 0,0);
    delay(2000);
    robot.move(0, -100,0);
    delay(2000);


}
