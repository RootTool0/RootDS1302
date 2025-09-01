#include "RootDS1302.h"

RootDS1302::RootDS1302(uint8_t InPinCLK, uint8_t InPinDIO, uint8_t InPinRST)
    : PinCLK(InPinCLK), PinDIO(InPinDIO), PinRST(InPinRST) {}

void RootDS1302::Setup() 
{
    pinMode(PinCLK, OUTPUT);
    pinMode(PinRST, OUTPUT);
    pinMode(PinDIO, OUTPUT);

    digitalWrite(PinCLK, LOW);
    digitalWrite(PinRST, LOW);
}

void RootDS1302::SetTime(const RootDS1302Struct& Time) 
{
    WriteRegister(0x80, DecToBcd(Time.Sec));   // Секунды
    WriteRegister(0x82, DecToBcd(Time.Min));   // Минуты
    WriteRegister(0x84, DecToBcd(Time.Hour));  // Часы
    WriteRegister(0x86, DecToBcd(Time.Day));   // День
    WriteRegister(0x88, DecToBcd(Time.Month)); // Месяц
    WriteRegister(0x8C, DecToBcd(Time.Year));  // Год
}

RootDS1302Struct RootDS1302::GetTime() 
{
    RootDS1302Struct Time;
    Time.Sec   = BcdToDec(ReadRegister(0x81));
    Time.Min   = BcdToDec(ReadRegister(0x83));
    Time.Hour  = BcdToDec(ReadRegister(0x85));
    Time.Day   = BcdToDec(ReadRegister(0x87));
    Time.Month = BcdToDec(ReadRegister(0x89));
    Time.Year  = BcdToDec(ReadRegister(0x8D));
    return Time;
}

void RootDS1302::WriteByte(uint8_t Value) 
{
    pinMode(PinDIO, OUTPUT);
    for (uint8_t i = 0; i < 8; i++) 
    {
        digitalWrite(PinDIO, Value & 0x01);
        digitalWrite(PinCLK, HIGH);
        delayMicroseconds(1);
        digitalWrite(PinCLK, LOW);
        Value >>= 1;
    }
}

uint8_t RootDS1302::ReadByte() 
{
    uint8_t Value = 0;
    pinMode(PinDIO, INPUT);
    for (uint8_t i = 0; i < 8; i++) 
    {
        Value >>= 1;
        if (digitalRead(PinDIO)) Value |= 0x80;
        digitalWrite(PinCLK, HIGH);
        delayMicroseconds(1);
        digitalWrite(PinCLK, LOW);
    }
    return Value;
}

void RootDS1302::WriteRegister(uint8_t Reg, uint8_t Value) 
{
    digitalWrite(PinRST, HIGH);
    WriteByte(Reg & 0xFE); // RW=0
    WriteByte(Value);
    digitalWrite(PinRST, LOW);
}

uint8_t RootDS1302::ReadRegister(uint8_t Reg) 
{
    digitalWrite(PinRST, HIGH);
    WriteByte(Reg | 0x01); // RW=1
    uint8_t Value = ReadByte();
    digitalWrite(PinRST, LOW);
    return Value;
}

uint8_t RootDS1302::BcdToDec(uint8_t Val) 
{
    return ((Val >> 4) * 10) + (Val & 0x0F);
}

uint8_t RootDS1302::DecToBcd(uint8_t Val) 
{
    return ((Val / 10) << 4) | (Val % 10);
}
