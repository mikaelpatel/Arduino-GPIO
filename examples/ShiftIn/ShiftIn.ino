#include "GPIO.h"
#include "SRPI.h"

#if defined(ARDUINO_attiny)
SRPI<BOARD::D0, BOARD::D1, LSBFIRST> ins;
#else
SRPI<BOARD::D12, BOARD::D13, LSBFIRST> ins;
#endif

void setup()
{
  pinMode(12, INPUT);
  pinMode(13, OUTPUT);
}

void loop()
{
  uint8_t value;

  // 10.5 us per bit, 95 kHz
  value = shiftIn(12, 13, LSBFIRST);
  delayMicroseconds(100);

  // 0.5625 us per bit, 1.8 MHz
  ins >> value;
  delayMicroseconds(100);
}
