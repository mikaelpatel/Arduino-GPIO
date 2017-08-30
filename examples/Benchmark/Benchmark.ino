#include "GPIO.h"

GPIO<BOARD::D13> led;
GPIO<BOARD::D12> pin;

void setup()
{
  led.output();
  pin.input_pullup();
}

void loop()
{
  // Benchmark#1: Write digital pin
  // 1.1 Arduino core digitalWrite
  // 4.25 us, 8.562 us, 117 kHz
  for (int i = 0; i < 8; i++) {
    digitalWrite(13, 1);
    digitalWrite(13, 0);
  }
  delayMicroseconds(10);

  // 1.2 GPIO pin assignment operator
  // 0.125 us, 0.5 us, 2 MHz
  for (int i = 0; i < 8; i++) {
    led = 1;
    led = 0;
  }
  delayMicroseconds(10);

  // 1.3 GPIO high and low
  // 0.125 us, 0.5 us, 2 MHz
  for (int i = 0; i < 8; i++) {
    led.high();
    led.low();
  }
  delayMicroseconds(10);

  // 1.4 GPIO toggle (double)
  // 0.125 us, 0.5 us, 2 MHz
  for (int i = 0; i < 8; i++) {
    led.toggle();
    led.toggle();
  }
  delayMicroseconds(10);

  // 1.5 GPIO toggle (single)
  // 0.375 us, 0.75 us, 1.33 MHz
  for (int i = 0; i < 16; i++) {
    led.toggle();
  }
  delayMicroseconds(10);

  // 1.6 GPIO toggle (unfold)
  // 0.125 us, 0.25 us, 4 MHz
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
  delay(10);

  // Benchmark#2: Read digital pin
  // 2.1 Arduino core digitalRead
  // 8.062 us, 3.812 us
  for (int i = 0; i < 8; i++) {
    digitalWrite(13, 1);
    uint8_t value = digitalRead(12);
    (void) value;
    digitalWrite(13, 0);
  }
  delayMicroseconds(10);

  // 2.2 GPIO pin value operator
  // 0.1875 us, 0.0625 us
  for (int i = 0; i < 8; i++) {
    led = 1;
    uint8_t value = pin;
    (void) value;
    led = 0;
  }
  delay(10);

  // Benchmark#3: Read-write digital pin
  // 3.1 Arduino core digitalRead-digitalWrite
  // 7.938 us, 16.08 us, 62 kHz
  for (int i = 0; i < 8; i++) {
    digitalWrite(13, !digitalRead(13));
    digitalWrite(13, !digitalRead(13));
  }
  delayMicroseconds(10);

  // 3.2 GPIO value and assignment operator
  // 0.4375 us, 0.9375 us, 1 MHz
  for (int i = 0; i < 8; i++) {
    led = !led;
    led = !led;
  }
  delay(100);
}
