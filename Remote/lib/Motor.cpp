//
// Created by Nikolay on 27.02.2021.
//

#include "Motor.h"
#include "Arduino.h"

Motor::Motor(int dir_pin, int pwm_pin, bool reverse)
{
    /*
     * reverse
     * */
    this->direction_pin = dir_pin;
    this->pwm_pin = pwm_pin;
    this->reverse = reverse;
    pinMode(dir_pin, OUTPUT);
    pinMode(pwm_pin, OUTPUT);
}

void Motor::rotate(bool direction, int speed)
{
    if (speed > 100)
        speed = 100;
    if (speed < 0)
        speed = 0;

    if (direction != this->reverse)
    {
        direction = false;

    } else
    {
        direction = true;
        speed = 100 - speed;
    }


    digitalWrite(this->direction_pin, uint8_t(direction));

    analogWrite(this->pwm_pin, int(speed * 2.55));
}

void Motor::stop()
{
    this->rotate(true, 0);
}
