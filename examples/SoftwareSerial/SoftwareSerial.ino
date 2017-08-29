#include "GPIO.h"
#include "ASO.h"

ASO<BOARD::D13> outs;

void setup()
{
  // outs.begin(9600);
  // outs.begin(57600);
  // outs.begin(114200);
  // outs.begin(230400);
  outs.begin(250000);
}

void loop()
{
  outs.println(millis());
  delay(10);
}
