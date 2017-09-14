#include "GPIO.h"
#include "SRPI.h"

#if defined(ARDUINO_attiny)
SRPI<LSBFIRST, BOARD::D0, BOARD::D1> srpi;
GPIO<BOARD::D2> ss;
#define DATA_PIN 0
#define CLOCK_PIN 1
#else
SRPI<LSBFIRST, BOARD::D12, BOARD::D13> srpi;
GPIO<BOARD::D11> ss;
#define DATA_PIN 12
#define CLOCK_PIN 13
#endif

void setup()
{
  pinMode(DATA_PIN, INPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  ss.output();
}

void loop()
{
  uint8_t value;

  // 85 us, 10.5 us per bit, 95 kHz
  ss.toggle();
  value = shiftIn(DATA_PIN, CLOCK_PIN, LSBFIRST);
  ss.toggle();
  delayMicroseconds(100);

  // 5 us, 0.5625 us per bit, 1.8 MHz
  ss.toggle();
  srpi >> value;
  ss.toggle();
  delayMicroseconds(100);
}
