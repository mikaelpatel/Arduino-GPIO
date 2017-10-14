#include "GPIO.h"
#include "SRPO.h"
#include "benchmark.h"

#include "Software/Serial.h"
Software::Serial<BOARD::D0> Serial;
SRPO<LSBFIRST, BOARD::D1, BOARD::D2> srpo;
#define DATA_PIN 0
#define CLOCK_PIN 1

void setup()
{
  Serial.begin(57600);
  while (!Serial);
  BENCHMARK_BASELINE(1000);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
}

void loop()
{
  uint8_t value = 0xa5;

  BENCHMARK("1. Arduino core shiftOut", 1000) {
    shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, value);
  }

  BENCHMARK("2. SRPO output operator", 1000) {
    srpo << value;
  }

  Serial.println();
  delay(2000);
}
