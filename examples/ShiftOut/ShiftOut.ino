#include "GPIO.h"
#include "SRPO.h"

SRPO<BOARD::D12, BOARD::D13, LSBFIRST> outs;

void setup()
{
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop()
{
  // 12 us per bit, 81 kHz
  shiftOut(12, 13, LSBFIRST, 0xaa);
  delayMicroseconds(100);

  // 1 us per bit, 1 MHz
  outs << 0xaa;
  delayMicroseconds(100);
}
