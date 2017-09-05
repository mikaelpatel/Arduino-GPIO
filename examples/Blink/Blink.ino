#include "GPIO.h"

#if defined(ARDUINO_attiny)
GPIO<BOARD::D0> led;
#else
GPIO<BOARD::D13> led;
#endif

void setup()
{
  led.output();
}

void loop()
{
  led = HIGH;
  delay(1000);
  led = LOW;
  delay(1000);
}
