#include "GPIO.h"
#include "SRPI.h"

#if defined(ARDUINO_attiny)
SRPI<BOARD::D0, BOARD::D1, LSBFIRST> ins;
#define DATA_PIN 0
#define CLOCK_PIN 1
#else
SRPI<BOARD::D12, BOARD::D13, LSBFIRST> ins;
#define DATA_PIN 12
#define CLOCK_PIN 13
#endif

void setup()
{
  pinMode(DATA_PIN, INPUT);
  pinMode(CLOCK_PIN, OUTPUT);
}

void loop()
{
  uint8_t value;

  // 10.5 us per bit, 95 kHz
  value = shiftIn(DATA_PIN, CLOCK_PIN, LSBFIRST);
  delayMicroseconds(100);

  // 0.5625 us per bit, 1.8 MHz
  ins >> value;
  delayMicroseconds(100);
}
