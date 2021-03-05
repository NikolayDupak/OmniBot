//
// Created by Nikolay on 27.02.2021.
//

#ifndef OMI_REMOTE_MOTOR_H
#define OMI_REMOTE_MOTOR_H


class Motor
{
public:
    Motor(int dir_pin, int pwm_pin, bool reverse= false);

    void rotate(bool direction, int speed);
    void stop();
private:
    int direction_pin;
    int pwm_pin;
    int reverse;
};


#endif //OMI_REMOTE_MOTOR_H
