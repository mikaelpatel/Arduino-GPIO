#include "GPIO.h"
#include "SRPO.h"

#if defined(ARDUINO_attiny)
SRPO<BOARD::D0, BOARD::D1, LSBFIRST> outs;
#define DATA_PIN 0
#define CLOCK_PIN 1
#else
SRPO<BOARD::D12, BOARD::D13, LSBFIRST> outs;
#define DATA_PIN 12
#define CLOCK_PIN 13
#endif

void setup()
{
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
}

void loop()
{
  // 12 us per bit, 81 kHz
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, 0xaa);
  delayMicroseconds(100);

  // 1 us per bit, 1 MHz
  outs << 0xaa;
  delayMicroseconds(100);
}
