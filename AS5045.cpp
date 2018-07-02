#include "Arduino.h"
#include "AS5045.h"


AS5045::AS5045(uint16_t DataPin, uint16_t ClockPin, uint16_t ChipSelectPin)
           : _data(DataPin), _clock(ClockPin), _cs(ChipSelectPin)
{
    pinMode(_data, INPUT);
    pinMode(_clock, OUTPUT);
    pinMode(_cs, OUTPUT);
}


uint32_t AS5045::encoder_degrees(uint16_t Number)
{
  return (((read_chip(Number) >> 6)* 360)/4096);
}

uint32_t AS5045::encoder_value(uint16_t Number)
{
  return (read_chip(Number) >> 6);
}

uint32_t AS5045::encoder_error(uint16_t Number)
{
  uint16_t error_code;
  uint32_t raw_value;
  raw_value = read_chip(Number);
  error_code = raw_value & 0b000000000000111111;
  err_value.DECn = error_code & 2;
  err_value.INCn = error_code & 4;
  err_value.LIN = error_code & 8;
  err_value.COF = error_code & 16;
  err_value.OCF = error_code & 32;
  return error_code;
}

uint32_t AS5045::read_chip(uint16_t Number)
{
  uint32_t raw_value = 0;
  uint16_t inputstream = 0;
  uint16_t c,n;
  digitalWrite(_cs, HIGH);
  digitalWrite(_clock, HIGH);
  delayMicroseconds(10);
  digitalWrite(_cs, LOW);
  delayMicroseconds(5);
  digitalWrite(_clock, LOW);
  delayMicroseconds(5);
  for(n = 0; n < Number; n++)
  {
  	  raw_value = 0;
	  for (c = 0; c < 18; c++)
	  {
	    digitalWrite(_clock, HIGH);
	    delayMicroseconds(5);
	    inputstream = digitalRead(_data);
	    raw_value = ((raw_value << 1) + inputstream);
	    digitalWrite(_clock, LOW);
	    delayMicroseconds(5);
	  }
	   digitalWrite(_clock, HIGH);
	   delayMicroseconds(5);
	   digitalWrite(_clock, LOW);
	   delayMicroseconds(5);
  }
 return raw_value;
}


