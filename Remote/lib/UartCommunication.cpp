//
// Created by Nikolay on 28.02.2021.
//

#include "UartCommunication.h"
#include "Arduino.h"


UartCommunication::UartCommunication()
{
    this->nextId = 0;
    this->subNextId = 0;
}

void UartCommunication::begin(int bitRate)
{
    this->bitRate = bitRate;
    Serial.begin(bitRate);
    this->nextId = 0;
    this->subNextId = 0;

}

void UartCommunication::sendPackege(uint8_t type, uint8_t val1, uint8_t val2, uint8_t val3)
{
    this->packege[0] = type;
    this->packege[1] = val1;
    this->packege[2] = val2;
    this->packege[3] = val3;
    byte sum = type ^val1 ^val2 ^val3;
    this->packege[4] = sum;
    this->send();

}

bool UartCommunication::recivePackege()
{
    uint8_t first[2];
    while (Serial.available() >= 9)
    {
        Serial.readBytes(first, 2);
        //Serial.print(first[0]);
        //Serial.print(first[1]);
        //Serial.write(first, 2);
        //delay(30);
        if (Serial.available() < 7)
        {
            //delay(20);
        }
        if (first[0] == 0xFF && first[1] == 0xFF && Serial.available() >= 7)
        {
            Serial.readBytes(this->recivedPackege, 5);
            Serial.readBytes(first, 2);
            // Serial.write(this->recivedPackege, 5);
            return true;
        }
    }
    return false;
}

bool UartCommunication::loop()
{
    bool status = this->recivePackege();

    if (status)
    {
        this->callback(recivedPackege[0], recivedPackege[1], recivedPackege[2], recivedPackege[3]);
        //Serial.print(recivedPackege[0]);

        //delay(10);
        error = 0;
    } else
    {
        error += 1;
        delay(10);
    }
    if (error >= 100)
    {
        callbackFail();
        error = 0;

    }
    return false;
}

void UartCommunication::subscribe(uint8_t type, void (*subscriber)(uint8_t, uint8_t, uint8_t))
{
    this->subId[nextId] = type;
    this->subs[nextId] = subscriber;
    nextId++;
    //subscriber(12,33, 12);
}


void UartCommunication::send()
{
    if (Serial.availableForWrite())
    {
        Serial.write(0xFF);
        Serial.write(0xFF);
        for (unsigned char i : this->packege)
        {
            Serial.write(i);
        }
        Serial.write(0xEE);
        Serial.write(0xEE);
        Serial.flush();
        delay(50);
    }
}

uint8_t UartCommunication::read()
{
    return this->recivedPackege[0];
}

void UartCommunication::callback(uint8_t type, uint8_t val1, uint8_t val2, uint8_t val3)
{
    for (uint8_t i = 0; i < nextId; i++)
    {
        if (this->subId[i] == type)
        {
            this->subs[i](val1, val2, val3);
        }
    }

}

void UartCommunication::callbackFail()
{
    for (uint8_t i = 0; i < subNextId; i++)
    {
        this->subFail[i]();
    }
}

void UartCommunication::subConFail(void (*subscriber)())
{
    this->subFail[subNextId] = subscriber;
    subNextId++;
}
