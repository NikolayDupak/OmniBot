//
// Created by Nikolay on 28.02.2021.
//

#include "UartCommunication.h"
#include "Arduino.h"

UartCommunication::UartCommunication()
{

}

void UartCommunication::begin(int bitRate)
{
    this->bitRate = bitRate;
    Serial.begin(bitRate);

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
    while (Serial.available() >= 2)
    {
        Serial.readBytes(first, 2);
        //Serial.print(first[0]);
        //Serial.print(first[1]);
        //Serial.write(first, 2);
        delay(10);
        if (first[0] == 0xFF && first[1] == 0xFF && Serial.available() < 7)
        {
            delay(50);
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

void UartCommunication::loop()
{
    return;
}

void UartCommunication::subscribe(uint8_t type, void (*comparisonFcn)(uint8_t, uint8_t, uint8_t))
{
    //comparisonFcn(12,33, 12);
    return;
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
