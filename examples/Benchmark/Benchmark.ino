#include "GPIO.h"

GPIO<BOARD::D13> led;
GPIO<BOARD::D12> pin;

void setup()
{
  led.output();
  pin.input(true);
}

void loop()
{
  // 4.25 us, 8.562 us, 117 kHz
  for (int i = 0; i < 8; i++) {
    digitalWrite(13, 1);
    digitalWrite(13, 0);
  }
  delayMicroseconds(10);

  // 0.125 us, 0.5 us, 2 MHz (X34)
  for (int i = 0; i < 8; i++) {
    led = 1;
    led = 0;
  }
  delay(10);

  // 8.062 us, 3.812 us
  for (int i = 0; i < 8; i++) {
    digitalWrite(13, 1);
    uint8_t value = digitalRead(12);
    (void) value;
    digitalWrite(13, 0);
  }
  delayMicroseconds(10);

  // 0.1875 us, 0.0625 us (X61)
  for (int i = 0; i < 8; i++) {
    led = 1;
    uint8_t value = pin;
    (void) value;
    led = 0;
  }
  delay(10);

  // 7.938 us, 16.08 us, 62 kHz
  for (int i = 0; i < 8; i++) {
    digitalWrite(13, !digitalRead(13));
    digitalWrite(13, !digitalRead(13));
  }
  delayMicroseconds(10);

  // 0.4375 us, 0.9375 us, 1 MHz (X18)
  for (int i = 0; i < 8; i++) {
    led = !led;
    led = !led;
  }
  delay(10);

  // 0.125 us, 0.5 us, 2 MHz
  for (int i = 0; i < 8; i++) {
    led.high();
    led.low();
  }
  delayMicroseconds(10);

  // 0.125 us, 0.5 us, 2 MHz
  for (int i = 0; i < 8; i++) {
    led.toggle();
    led.toggle();
  }
  delayMicroseconds(10);

  // 0.375 us, 0.75 us, 1.33 MHz
  for (int i = 0; i < 16; i++) {
    led.toggle();
  }
  delayMicroseconds(10);

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

  delay(100);
}
