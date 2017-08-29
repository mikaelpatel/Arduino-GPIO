#include "GPIO.h"

GPIO<BOARD::D13> led;

void setup()
{
  led.output();
}

void loop()
{
  led.toggle();
  delay(500);
}
