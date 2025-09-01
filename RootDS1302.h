
#ifndef RootDS1302_h
#define RootDS1302_h

#include <Arduino.h>

struct RootDS1302Struct {
    uint8_t Sec;
    uint8_t Min;
    uint8_t Hour;
    uint8_t Day;
    uint8_t Month;
    uint8_t Year;
};


class RootDS1302 {
	
public:
    RootDS1302(uint8_t InPinCLK, uint8_t InPinDAT, uint8_t InPinRST);

	void Setup();

    void SetTime(const RootDS1302Struct& Time);
    RootDS1302Struct GetTime();
	
private:
    uint8_t PinCLK, PinDIO, PinRST;
	
	void WriteByte(uint8_t Value);
    uint8_t ReadByte();
	
    void WriteRegister(uint8_t Reg, uint8_t Value);
    uint8_t ReadRegister(uint8_t Reg);

    uint8_t DecToBcd(uint8_t Val);
    uint8_t BcdToDec(uint8_t Val);
};

#endif
