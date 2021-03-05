//
// Created by Nikolay on 28.02.2021.
//

#ifndef OMI_REMOTE_UARTCOMMUNICATION_H
#define OMI_REMOTE_UARTCOMMUNICATION_H
#include "Arduino.h"

class UartCommunication
{
public:
    UartCommunication();

    void begin(int bitRate=9600);

    void sendPackege(uint8_t type, uint8_t val1, uint8_t val2, uint8_t val3);
    bool recivePackege();

    void loop();
    uint8_t read();
    void subscribe(uint8_t type, void (*subscriber)(uint8_t, uint8_t, uint8_t));
    void subConFail(void (*subscriber)());

    uint8_t recivedPackege[5];

private:
    int bitRate;
    uint8_t packege[5];

    uint8_t subId[10];
    void (*subs[10])(uint8_t,uint8_t,uint8_t);
    uint8_t nextId;


    void (*subFail[10])();
    uint8_t subNextId;

    uint8_t error;

    void send();
    void callback(uint8_t type, uint8_t val1, uint8_t val2, uint8_t val3);
    void callbackFail();

};


#endif //OMI_REMOTE_UARTCOMMUNICATION_H
