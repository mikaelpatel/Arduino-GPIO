#include "IGPIO.h"
#include "benchmark.h"

VGPIO<BOARD::D12> button;
VGPIO<BOARD::D13> led;
#define BUTTON_PIN 12
#define LED_PIN 13

void setup()
{
  Serial.begin(57600);
  while (!Serial);

  // Set pin mode; Arduino style
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Set pin mode; GPIO style
  led.output();
  button.input();
  button.pullup();

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

  BENCHMARK("2.1 VGPIO pin value operator", 1000) {
    bool state = button;
    (void) state;
  }

  BENCHMARK("2.2 VGPIO high member function", 1000) {
    led.high();
  }

  BENCHMARK("2.3 VGPIO low member function", 1000) {
    led.low();
  }

  BENCHMARK("2.4 VGPIO assignment HIGH", 1000) {
    led = HIGH;
  }

  BENCHMARK("2.5 VGPIO assignment LOW", 1000) {
    led = LOW;
  }

  BENCHMARK("2.6 VGPIO toggle; value and assignment operator", 1000) {
    led = !led;
  }

  BENCHMARK("2.7 VGPIO toggle; high and low member functions", 1000) {
    led.high();
    led.low();
  }

  BENCHMARK("2.8 VGPIO toggle; assignment operator, HIGH/LOW", 1000) {
    led = HIGH;
    led = LOW;
  }

  BENCHMARK("2.9 VGPIO toggle member function", 1000) {
    led.toggle();
  }

#ifdef PORTH

  // VGPIO atomic access of io ports with higher address. These
  // benchmarks are for Arduino Mega pins that use ports above address
  // 0x40 (PORTH, PORTJ, PINK and PINL). See Hardware/AVR/Board.h.

#define DIN_PIN 6
#define DOUT_PIN 7
  VGPIO<BOARD::D6> din;
  VGPIO<BOARD::D7> dout;
  din.input();
  dout.input();

  BENCHMARK("3.1 Arduino core digitalRead", 1000) {
    bool state = digitalRead(DIN_PIN);
    (void) state;
  }

  BENCHMARK("3.2 Arduino core digitalWrite(HIGH)", 1000) {
    digitalWrite(DOUT_PIN, HIGH);
  }

  BENCHMARK("3.3 Arduino core digitalWrite(LOW)", 1000) {
    digitalWrite(DOUT_PIN, LOW);
  }

  BENCHMARK("3.4 Arduino core toggle; digitalRead-digitalWrite", 1000) {
    digitalWrite(DOUT_PIN, !digitalRead(DOUT_PIN));
  }

  BENCHMARK("3.5 Arduino core toggle; digitalWrite", 1000) {
    digitalWrite(DOUT_PIN, HIGH);
    digitalWrite(DOUT_PIN, LOW);
  }

  BENCHMARK("4.1 VGPIO pin value operator", 1000) {
    bool state = din;
    (void) state;
  }

  BENCHMARK("4.2 VGPIO high member function", 1000) {
    dout.high();
  }

  BENCHMARK("4.3 VGPIO low member function", 1000) {
    dout.low();
  }

  BENCHMARK("4.4 VGPIO assignment HIGH", 1000) {
    dout = HIGH;
  }

  BENCHMARK("4.5 VGPIO assignment LOW", 1000) {
    dout = LOW;
  }

  BENCHMARK("4.6 VGPIO toggle; value and assignment operator", 1000) {
    dout = !dout;
  }

  BENCHMARK("4.7 VGPIO toggle; high and low member functions", 1000) {
    dout.high();
    dout.low();
  }

  BENCHMARK("4.8 VGPIO toggle; assignment operator", 1000) {
    dout = HIGH;
    dout = LOW;
  }

  BENCHMARK("4.9 VGPIO toggle member function", 1000) {
    dout.toggle();
  }
#endif

  Serial.println();
  delay(2000);
  while(true) ;
}
