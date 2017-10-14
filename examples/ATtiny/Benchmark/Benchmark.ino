#include "GPIO.h"
#include "benchmark.h"

#include "Software/Serial.h"
Software::Serial<BOARD::D0> Serial;
GPIO<BOARD::D1> led;
GPIO<BOARD::D2> button;
#define LED_PIN 1
#define BUTTON_PIN 2

void setup()
{
  Serial.begin(57600);
  while (!Serial);

  // Set pin mode; Arduino style
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Set pin mode; GPIO style
  led.output();
  button.input().pullup();

  // Calculate baseline
  BENCHMARK_BASELINE(1000);
}

void loop()
{
  BENCHMARK("1.1 Arduino core digitalRead", 1000) {
    bool state = digitalRead(BUTTON_PIN);
    (void) state;
  }

  BENCHMARK("1.2 Arduino core digitalWrite(HIGH)", 1000) {
    digitalWrite(LED_PIN, HIGH);
  }

  BENCHMARK("1.3 Arduino core digitalWrite(LOW)", 1000) {
    digitalWrite(LED_PIN, LOW);
  }

  BENCHMARK("1.4 Arduino core toggle; digitalRead-digitalWrite", 1000) {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  }

  BENCHMARK("1.5 Arduino core toggle; digitalWrite", 1000) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(LED_PIN, LOW);
  }

  BENCHMARK("2.1 GPIO pin value operator", 1000) {
    bool state = button;
    (void) state;
  }

  BENCHMARK("2.2 GPIO high member function", 1000) {
    led.high();
  }

  BENCHMARK("2.3 GPIO low member function", 1000) {
    led.low();
  }

  BENCHMARK("2.4 GPIO assignment HIGH", 1000) {
    led = HIGH;
  }

  BENCHMARK("2.5 GPIO assignment LOW", 1000) {
    led = LOW;
  }

  BENCHMARK("2.6 GPIO toggle; value and assignment operator", 1000) {
    led = !led;
  }

  BENCHMARK("2.7 GPIO toggle; high and low member functions", 1000) {
    led.high();
    led.low();
  }

  BENCHMARK("2.8 GPIO toggle; assignment operator, HIGH/LOW", 1000) {
    led = HIGH;
    led = LOW;
  }

  BENCHMARK("2.9 GPIO toggle member function", 1000) {
    led.toggle();
  }

  Serial.println();
  delay(2000);
}
