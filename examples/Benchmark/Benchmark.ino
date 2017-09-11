#include "GPIO.h"

#if defined(ARDUINO_attiny)
GPIO<BOARD::D0> led;
GPIO<BOARD::D1> button;
#define LED_PIN 0
#define BUTTON_PIN 1
#else
GPIO<BOARD::D13> led;
GPIO<BOARD::D12> button;
#define LED_PIN 13
#define BUTTON_PIN 12
#endif

void setup()
{
  led.output();
  button.input_pullup();
}

void loop()
{
  // Benchmark#1: Read-write digital pin
  // 1.1 Arduino core digitalRead-digitalWrite
  // 8.312 us, 16.81 us, 59 kHz (Uno)
  // 13.56 us, 27.31 us, 37 kHz (Mega)
  for (int i = 0; i < 8; i++) {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  }
  delayMicroseconds(10);

  // 1.2 GPIO value and assignment operator
  // 0.4375 us, 0.9375 us, 1 MHz (Uno/Mega)
  for (int i = 0; i < 8; i++) {
    led = !led;
    led = !led;
  }
  delay(1);

  // Benchmark#2: Write digital pin
  // 2.1 Arduino core digitalWrite
  // 4.312 us, 8.562 us, 117 kHz (Uno)
  // 6.938 us, 14 us, 71.4 kHz (Mega)
  for (int i = 0; i < 8; i++) {
    digitalWrite(LED_PIN, 1);
    digitalWrite(LED_PIN, 0);
  }
  delayMicroseconds(10);

  // 2.2 GPIO pin assignment operator
  // 0.125 us, 0.5 us, 2 MHz (Uno/Mega)
  for (int i = 0; i < 8; i++) {
    led = 1;
    led = 0;
  }
  delayMicroseconds(10);

  // 2.3 GPIO high and low
  // 0.125 us, 0.5 us, 2 MHz (Uno/Mega)
  for (int i = 0; i < 8; i++) {
    led.high();
    led.low();
  }
  delayMicroseconds(10);

  // 2.4 GPIO toggle (single)
  // 0.375 us, 0.75 us, 1.33 MHz (Uno/Mega)
  for (int i = 0; i < 16; i++) {
    led.toggle();
  }
  delayMicroseconds(10);

  // 2.5 GPIO toggle (double)
  // 0.125 us, 0.5 us, 2 MHz (Uno/Mega)
  for (int i = 0; i < 8; i++) {
    led.toggle();
    led.toggle();
  }
  delayMicroseconds(10);

  // 2.6 GPIO toggle (unrolled)
  // 0.125 us, 0.25 us, 4 MHz (Uno/Mega)
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
  delay(1);

  // Benchmark#3: Read digital pin
  // 3.1 Arduino core digitalRead
  // 8.062 us, 12.37 us (Uno)
  // 13.31 us, 20.38 us (Mega)
  for (int i = 0; i < 8; i++) {
    digitalWrite(LED_PIN, 1);
    uint8_t value = digitalRead(BUTTON_PIN);
    (void) value;
    digitalWrite(LED_PIN, 0);
  }
  delayMicroseconds(10);

  // 3.2 GPIO pin value operator
  // 0.1875 us, 0.5625 us (Uno/Mega)
  for (int i = 0; i < 8; i++) {
    led = 1;
    uint8_t value = button;
    (void) value;
    led = 0;
  }
  delay(1);

#ifdef PORTH
  // Benchmark#4: GPIO atomic access of io ports with higher address
  // These benchmarks are for Arduino Mega pins that use ports above
  // address 0x60 (PORTH, PORTJ, PINK and PINL). See Board.h.
  GPIO<BOARD::D6> pin;

  // 0.625 us (Mega)
  led.toggle();
  pin.output();
  led.toggle();

  // 0.625 us (Mega)
  led.toggle();
  pin.write(0);
  led.toggle();

  // 4.1 GPIO value and assignment operator
  // 0.8125 us, 1.938 us, 516 kHz (Mega)
  for (int i = 0; i < 8; i++) {
    pin = !pin;
    pin = !pin;
  }
  delayMicroseconds(10);

  // 4.2 GPIO pin assignment operator
  // 0.5 us, 1.25, 800 kHz (Mega)
  for (int i = 0; i < 8; i++) {
    pin = 1;
    pin = 0;
  }
  delayMicroseconds(10);

  // 4.3 GPIO high and low
  // 0.5 us, 1.25, 800 kHz (Mega)
  for (int i = 0; i < 8; i++) {
    pin.high();
    pin.low();
  }
  delayMicroseconds(10);

  // 4.4 GPIO toggle (single)
  // 0.75 us, 1.5, 667 kHz (Mega)
  for (int i = 0; i < 16; i++) {
    pin.toggle();
  }
  delayMicroseconds(10);

  // 4.5 GPIO toggle (double)
  // 0.5 us, 1.25, 800 kHz (Mega)
  for (int i = 0; i < 8; i++) {
    pin.toggle();
    pin.toggle();
  }
  delayMicroseconds(10);

  // 4.6 GPIO toggle (unrolled)
  // 0.5 us, 1.25, 1 MHz (Mega)
  pin.toggle();
  pin.toggle();
  pin.toggle();
  pin.toggle();
  pin.toggle();
  pin.toggle();
  pin.toggle();
  pin.toggle();
  pin.toggle();
  pin.toggle();
  pin.toggle();
  pin.toggle();
  pin.toggle();
  pin.toggle();
  pin.toggle();
  pin.toggle();
  delayMicroseconds(10);

  // 4.7 GPIO pin value operator
  // 0.25 us, 0.625, 1.6 MHz (Mega)
  pin.input();
  for (int i = 0; i < 8; i++) {
    led = 1;
    uint8_t value = pin;
    (void) value;
    led = 0;
  }

#endif
  delay(10);
}
