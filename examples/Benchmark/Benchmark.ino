#include "GPIO.h"

#if defined(ARDUINO_attiny)
GPIO<BOARD::D0> led;
GPIO<BOARD::D1> button;
GPIO<BOARD::D2> ss;
#define LED_PIN 0
#define BUTTON_PIN 1
#define SS_PIN 2
#else
GPIO<BOARD::D13> led;
GPIO<BOARD::D12> button;
GPIO<BOARD::D11> ss;
#define LED_PIN 13
#define BUTTON_PIN 12
#define SS_PIN 11
#endif

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  led.output();
  button.input().pullup();
  ss.output();
}

void loop()
{
  // Benchmark#1: Read-write digital pin
  // 1.1 Arduino core digitalRead-digitalWrite
  // 2.625 us, 5.313 us, 188 kHz (Due)
  // 8.312 us, 16.81 us, 59 kHz (Uno)
  // 13.56 us, 27.31 us, 37 kHz (Mega)
  ss.high();
  for (int i = 0; i < 8; i++) {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  }
  ss.low();
  delayMicroseconds(10);

  // 1.2 GPIO value and assignment operator
  // 0.25 us, 0.4375 us, 2.3 MHz (Due)
  // 0.4375 us, 0.9375 us, 1 MHz (Uno/Mega)
  ss.high();
  for (int i = 0; i < 8; i++) {
    led = !led;
    led = !led;
  }
  ss.low();
  delay(1);

  // Benchmark#2: Write digital pin
  // 2.1 Arduino core digitalWrite
  // 2.125 us, 4.375 us, 229 kHz (Due)
  // 4.312 us, 8.562 us, 117 kHz (Uno)
  // 6.938 us, 14 us, 71.4 kHz (Mega)
  ss.high();
  for (int i = 0; i < 8; i++) {
    digitalWrite(LED_PIN, 1);
    digitalWrite(LED_PIN, 0);
  }
  ss.low();
  delayMicroseconds(10);

  // 2.2 GPIO pin assignment operator
  // 0.0625 us, 0.1875 us, 5.33 MHz (Due)
  // 0.125 us, 0.5 us, 2 MHz (Uno/Mega)
  ss.high();
  for (int i = 0; i < 8; i++) {
    led = 1;
    led = 0;
  }
  ss.low();
  delayMicroseconds(10);


  // 2.3 GPIO high and low
  // 0.0625 us, 0.1875 us, 5.33 MHz (Due)
  // 0.125 us, 0.5 us, 2 MHz (Uno/Mega)
  ss.high();
  for (int i = 0; i < 8; i++) {
    led.high();
    led.low();
  }
  ss.low();
  delayMicroseconds(10);

  // 2.4 GPIO toggle (single)
  // 0.1875 us, 0.375 us, 2.66 MHz (Due)
  // 0.375 us, 0.75 us, 1.33 MHz (Uno/Mega)
  ss.high();
  for (int i = 0; i < 16; i++) {
    led.toggle();
  }
  ss.low();
  delayMicroseconds(10);

  // 2.5 GPIO toggle (double)
  // 0.125 us, 0.4375 us, 2.286 MHz (Due)
  // 0.125 us, 0.5 us, 2 MHz (Uno/Mega)
  ss.high();
  for (int i = 0; i < 8; i++) {
    led.toggle();
    led.toggle();
  }
  ss.low();
  delayMicroseconds(10);

  // 2.6 GPIO toggle (unrolled)
  // 0.1875 us, 0.3125 us, 3.2 MHz (Due)
  // 0.125 us, 0.25 us, 4 MHz (Uno/Mega)
  ss.high();
  led.toggle();
  led.toggle();
  led.toggle();
  led.toggle();
  led.toggle();
  led.toggle();
  led.toggle();
  led.toggle();
  led.toggle();
  led.toggle();
  led.toggle();
  led.toggle();
  led.toggle();
  led.toggle();
  led.toggle();
  led.toggle();
  ss.low();
  delay(1);

  // Benchmark#3: Read digital pin
  // 3.1 Arduino core digitalRead
  // 3.312 us, 5.5 us (Due)
  // 8.062 us, 12.37 us (Uno)
  // 13.31 us, 20.38 us (Mega)
  ss.high();
  for (int i = 0; i < 8; i++) {
    digitalWrite(LED_PIN, 1);
    uint8_t value = digitalRead(BUTTON_PIN);
    (void) value;
    digitalWrite(LED_PIN, 0);
  }
  ss.low();
  delayMicroseconds(10);

  // 3.2 GPIO pin value operator
  // 0.0625 us, 0.125 us (Due)
  // 0.1875 us, 0.5625 us (Uno/Mega)
  ss.high();
  for (int i = 0; i < 8; i++) {
    led = 1;
    uint8_t value = button;
    (void) value;
    led = 0;
  }
  ss.low();

#ifdef PORTH
  delay(1);

  // Benchmark#4: GPIO atomic access of io ports with higher address
  // These benchmarks are for Arduino Mega pins that use ports above
  // address 0x60 (PORTH, PORTJ, PINK and PINL). See Board.h.
  GPIO<BOARD::D6> data;
#define DATA_PIN 6

  // 0.625 us (Mega)
  ss.high();
  data.output();
  ss.low();

  // 0.625 us (Mega)
  ss.high();
  data.write(0);
  ss.low();

  // 4.1 Arduino core digitalRead-digitalWrite
  // 14 us, 28.25 us, 35 kHz (Mega)
  ss.high();
  for (int i = 0; i < 8; i++) {
    digitalWrite(DATA_PIN, !digitalRead(DATA_PIN));
    digitalWrite(DATA_PIN, !digitalRead(DATA_PIN));
  }
  ss.low();
  delayMicroseconds(10);

  // 4.2 GPIO value and assignment operator
  // 0.8125 us, 1.938 us, 516 kHz (Mega)
  ss.high();
  for (int i = 0; i < 8; i++) {
    data = !data;
    data = !data;
  }
  ss.low();
  delayMicroseconds(10);

  // 4.3 Arduino core digitalWrite
  // 7.3 us, 14.75 us, 68 kHz (Mega)
  ss.high();
  for (int i = 0; i < 8; i++) {
    digitalWrite(DATA_PIN, 1);
    digitalWrite(DATA_PIN, 0);
  }
  ss.low();
  delayMicroseconds(10);

  // 4.4 GPIO pin assignment operator
  // 0.5 us, 1.25, 800 kHz (Mega)
  ss.high();
  for (int i = 0; i < 8; i++) {
    data = 1;
    data = 0;
  }
  ss.low();
  delayMicroseconds(10);

  // 4.5 GPIO high and low
  // 0.5 us, 1.25, 800 kHz (Mega)
  ss.high();
  for (int i = 0; i < 8; i++) {
    data.high();
    data.low();
  }
  ss.low();
  delayMicroseconds(10);

  // 4.6 GPIO toggle (single)
  // 0.75 us, 1.5, 667 kHz (Mega)
  ss.high();
  for (int i = 0; i < 16; i++) {
    data.toggle();
  }
  ss.low();
  delayMicroseconds(10);

  // 4.7 GPIO toggle (double)
  // 0.5 us, 1.25, 800 kHz (Mega)
  ss.high();
  for (int i = 0; i < 8; i++) {
    data.toggle();
    data.toggle();
  }
  ss.low();
  delayMicroseconds(10);

  // 4.8 GPIO toggle (unrolled)
  // 0.5 us, 1.25, 1 MHz (Mega)
  ss.high();
  data.toggle();
  data.toggle();
  data.toggle();
  data.toggle();
  data.toggle();
  data.toggle();
  data.toggle();
  data.toggle();
  data.toggle();
  data.toggle();
  data.toggle();
  data.toggle();
  data.toggle();
  data.toggle();
  data.toggle();
  data.toggle();
  ss.low();
  delayMicroseconds(10);

  // 4.9 Arduino core digitalRead
  // 6.563 us, 6.938 us, 144 kHz (Mega)
  data.input();
  ss.high();
  for (int i = 0; i < 8; i++) {
    led = 1;
    uint8_t value = digitalRead(DATA_PIN);
    (void) value;
    led = 0;
  }
  ss.low();

  // 4.10 GPIO data value operator
  // 0.25 us, 0.625, 1.6 MHz (Mega)
  ss.high();
  for (int i = 0; i < 8; i++) {
    led = 1;
    uint8_t value = data;
    (void) value;
    led = 0;
  }
  ss.low();

#endif
  delay(10);
}
