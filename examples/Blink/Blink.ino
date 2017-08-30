#include "GPIO.h"

GPIO<BOARD::D13> led;

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
