#include "GPIO.h"
#include "Software/Serial.h"

Software::Serial<BOARD::D13> outs;

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
