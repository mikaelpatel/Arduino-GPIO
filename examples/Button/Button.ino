#include "GPIO.h"
#include "Button.h"

#if defined(ARDUINO_attiny)
Button<BOARD::D0> button;
#else
Button<BOARD::D7> button;
#endif

void setup()
{
  Serial.begin(57600);
  while (!Serial);
}

void loop()
{
  if (button.ischanged()) {
    Serial.print(button.timestamp());
    Serial.print(':');
    Serial.println(button ? F("released") : F("pushed"));
  }
}
