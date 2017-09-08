#include "GPIO.h"
#include "SRPO.h"

#if defined(ARDUINO_attiny)
SRPO<LSBFIRST, BOARD::D0, BOARD::D1> srpo;
GPIO<BOARD::D2> ss;
#define DATA_PIN 0
#define CLOCK_PIN 1
#else
SRPO<LSBFIRST, BOARD::D12, BOARD::D13> srpo;
GPIO<BOARD::D11> ss;
#define DATA_PIN 12
#define CLOCK_PIN 13
#endif

void setup()
{
  ss.output();
}

void loop()
{
  uint8_t value = 0xaa;

  // 103 us, 12 us per bit, 80 kHz
  ss.toggle();
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, value);
  ss.toggle();
  delayMicroseconds(100);

  // 8 us, 1 us per bit, 1 MHz
  ss.toggle();
  srpo << value;
  ss.toggle();
  delayMicroseconds(100);
}
