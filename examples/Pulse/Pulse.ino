#include "GPIO.h"

GPIO<BOARD::D13> led;

void setup()
{
  led.output();
}

void loop()
{
  for (int width = 0; width < 8; width++)
    led.pulse(width);
  delayMicroseconds(10);
}
