#include "GPIO.h"
#include "Software/Serial.h"

#if defined(ARDUINO_attiny)
Software::Serial<BOARD::D0> outs;
#else
Software::Serial<BOARD::D13> outs;
#endif

void setup()
{
  // outs.begin(9600);
  outs.begin(57600);
  // outs.begin(114200);
  // outs.begin(230400);
  // outs.begin(250000);
}

void loop()
{
  outs.println(millis());
  delay(10);
}
