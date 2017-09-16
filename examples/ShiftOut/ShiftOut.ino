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
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  ss.output();
}

void loop()
{
  uint8_t value = 0xaa;

  // 52 us, 2.08 us, 6.375 us, 160 kHz (Due)
  // 103 us, 12 us, 80 kHz (Uno)
  // 160 us, 19.75 us, 50 kHz (Mega)
  ss.toggle();
  shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, value);
  ss.toggle();
  delayMicroseconds(100);

  // 4.79 us, 0.58 us, 1.7 MHz (Due)
  // 8 us, 1 us, 1 MHz (Uno/Mega)
  ss.toggle();
  srpo << value;
  ss.toggle();
  delayMicroseconds(100);
}
