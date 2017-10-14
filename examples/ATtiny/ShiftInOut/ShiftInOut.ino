#include "GPIO.h"
#include "SRPIO.h"
#include "benchmark.h"

#include "Software/Serial.h"
Software::Serial<BOARD::D0> Serial;
SRPIO<LSBFIRST, BOARD::D1, BOARD::D2> srpio;

void setup()
{
  Serial.begin(57600);
  while (!Serial);
  BENCHMARK_BASELINE(1000);
}

void loop()
{
  uint8_t value = 0;

  BENCHMARK("1. SRPIO input operator", 1000) {
    srpio >> value;
  }

  value = 0xa5;
  BENCHMARK("2. SRPIO output operator", 1000) {
    srpio << value;
  }

  Serial.println();
  delay(2000);
}
