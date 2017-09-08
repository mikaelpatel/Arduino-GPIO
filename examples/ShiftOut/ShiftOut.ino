#include "GPIO.h"
#include "SRPO.h"

#if defined(ARDUINO_attiny)
SRPO<LSBFIRST, BOARD::D0, BOARD::D1> outs;
#define DATA_PIN 0
#define CLOCK_PIN 1
#else
SRPO<LSBFIRST, BOARD::D12, BOARD::D13> outs;
#define DATA_PIN 12
#define CLOCK_PIN 13
#endif

void setup()
{
}

void loop()
{
  uint8_t value = 0xaa;

  // 12 us per bit, 81 kHz
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, value);
  delayMicroseconds(100);

  // 1 us per bit, 1 MHz
  outs << value;
  delayMicroseconds(100);
}
