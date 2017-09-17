#include "GPIO.h"
#include "SRPIO.h"

#if defined(ARDUINO_attiny)
SRPIO<LSBFIRST, BOARD::D0, BOARD::D1> srpio;
GPIO<BOARD::D2> ss;
#else
SRPIO<LSBFIRST, BOARD::D12, BOARD::D13> srpio;
GPIO<BOARD::D11> ss;
#endif

void setup()
{
  ss.output();
}

void loop()
{
  uint8_t value = 0;

  // 4.7 us, 0.5625 us, 1.8 MHz (Uno)
  ss.toggle();
  srpio >> value;
  ss.toggle();
  delayMicroseconds(100);

  // 8.125 us, 0.9275 us, 1 MHz (Uno)
  value = 0xa5;
  ss.toggle();
  srpio << value;
  ss.toggle();

  delay(1);
}
