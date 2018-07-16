#ifndef AS5045_h
#define AS5045_h

#include "Arduino.h"
#ifdef __cplusplus
extern "C" {
class AS5045
{
  public:
    AS5045(uint16_t DataPin, uint16_t ClockPin, uint16_t ChipSelectPin);
    uint32_t encoder_degrees(uint16_t Number);
    uint32_t encoder_value(uint16_t Number);
    uint32_t encoder_error(uint16_t Number);
    struct err_struct{
  	bool DECn;
	bool INCn;
	bool OCF;
	bool COF;
	bool LIN; } err_value;
  public:
    uint32_t read_chip(uint16_t Number);
    const uint16_t _clock;        // clock pin: output from arduino to as5045
    const uint16_t _cs;           // chip select: output
    const uint16_t _data;         // data pin: input
    //nt32_t encode_number[6]={0,0,0,0,0,0};
};
#ifdef __cplusplus
}
#endif
#endif
#endif
