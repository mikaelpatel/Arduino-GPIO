#include "GPIO.h"

#if defined(ARDUINO_attiny)
#include "Software/Serial.h"
GPIO<BOARD::D0> led;
GPIO<BOARD::D1> button;
GPIO<BOARD::D2> ss;
Software::Serial<BOARD::D3> Serial;
#define LED_PIN 0
#define BUTTON_PIN 1
#else
GPIO<BOARD::D13> led;
GPIO<BOARD::D12> button;
GPIO<BOARD::D11> ss;
#define LED_PIN 13
#define BUTTON_PIN 12
#endif

/** Benchmark timestamp variables. */
uint32_t start, baseline;

/**
 * Benchmark support macros. Use in the form:
 * @code
 *   BENCHMARK("description") statement
 * @endcode
 * Prints description message and time to execute the statement in
 * micro-seconds.
 * @param[in] descr description of the benchmark.
 */
#define BENCHMARK(descr)						\
  Serial.print(F(descr ": "));						\
  Serial.flush();							\
  start = micros();							\
  for (int _i = 1; _i; _i--, Serial.println(micros() - start - baseline))

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
  ss.output();

  // Calculate baseline
  Serial.flush();
  start = micros();
  for (int _i = 1; _i; _i--, baseline = micros() - start) {}
}

void loop()
{
  BENCHMARK("1.1 Arduino core digitalRead-digitalWrite") {
    // Measurements from Logic Analyzer: ss pin is used
    // to mark the start and stop of the benchmark
    // 42.42 us, 2.625 us, 5.313 us, 188 kHz (Due)
    // 135 us, 8.312 us, 16.81 us, 59 kHz (Uno)
    // 221 us, 13.75 us, 27.69 us, 36 kHz (Mega)
    ss.high();
    for (int i = 0; i < 8; i++) {
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    }
    ss.low();
  }

  BENCHMARK("1.2 GPIO value and assignment operator") {
    // 3.33 us, 0.25 us, 0.4375 us, 2.3 MHz (Due)
    // 7.75 us, 0.5 us, 0.9375 us, 1 MHz (Uno/Mega)
    ss.high();
    for (int i = 0; i < 8; i++) {
      led = !led;
      led = !led;
    }
    ss.low();
  }

  BENCHMARK("2.1 Arduino core digitalWrite") {
    // 35 us, 2.125 us, 4.375 us, 229 kHz (Due)
    // 68.7 us, 4.25 us, 8.562 us, 117 kHz (Uno)
    // 116 us, 7.2 us, 14 us, 70 kHz (Mega)
    ss.high();
    for (int i = 0; i < 8; i++) {
      digitalWrite(LED_PIN, 1);
      digitalWrite(LED_PIN, 0);
    }
    ss.low();
  }

  BENCHMARK("2.2 GPIO pin assignment operator") {
    // 1.25 us, 0.0625 us, 0.1875 us, 5.33 MHz (Due)
    // 4.188 us, 0.125 us, 0.5 us, 2 MHz (Uno/Mega)
    ss.high();
    for (int i = 0; i < 8; i++) {
      led = 1;
      led = 0;
    }
    ss.low();
  }

  BENCHMARK("2.3 GPIO high and low") {
    // 1.25 us, 0.0625 us, 0.1875 us, 5.33 MHz (Due)
    // 4.188 us, 0.125 us, 0.5 us, 2 MHz (Uno/Mega)
    ss.high();
    for (int i = 0; i < 8; i++) {
      led.high();
      led.low();
    }
    ss.low();
  }

  BENCHMARK("2.4 GPIO toggle (single)") {
    // 3 us, 0.1875 us, 0.375 us, 2.66 MHz (Due)
    // 6.188 us, 0.375 us, 0.75 us, 1.33 MHz (Uno/Mega)
    ss.high();
    for (int i = 0; i < 16; i++) {
      led.toggle();
    }
    ss.low();
  }

  BENCHMARK("2.5 GPIO toggle (double)") {
    // 3.5 us, 0.125 us, 0.4375 us, 2.286 MHz (Due)
    // 4.188 us, 0.125 us, 0.5 us, 2 MHz (Uno/Mega)
    ss.high();
    for (int i = 0; i < 8; i++) {
      led.toggle();
      led.toggle();
    }
    ss.low();
  }

  BENCHMARK("2.6 GPIO toggle (unrolled)") {
    // 2.8 us, 0.1875 us, 0.3125 us, 3.2 MHz (Due)
    // 2.125 us, 0.125 us, 0.25 us, 4 MHz (Uno/Mega)
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
  }

  BENCHMARK("3.1 Arduino core digitalRead") {
    // 44.17 us, 3.312 us, 5.5 us (Due)
    // 99.19 us, 8.062 us, 12.37 us (Uno)
    // 166 us, 13.56 us, 20.8 us (Mega)
    ss.high();
    for (int i = 0; i < 8; i++) {
      // digitalWrite(LED_PIN, 1);
      uint8_t value = digitalRead(BUTTON_PIN);
      (void) value;
      // digitalWrite(LED_PIN, 0);
    }
    ss.low();
  }

  BENCHMARK("3.2 GPIO pin value operator") {
    // 1.292 us, 0.0625 us, 0.125 us (Due)
    // 4.688 us, 0.1875 us, 0.5625 us (Uno/Mega)
    ss.high();
    for (int i = 0; i < 8; i++) {
      // led = 1;
      uint8_t value = button;
      (void) value;
      // led = 0;
    }
    ss.low();
  }

#ifdef PORTH

  // Benchmark#4: GPIO atomic access of io ports with higher address
  // These benchmarks are for Arduino Mega pins that use ports above
  // address 0x40 (PORTH, PORTJ, PINK and PINL). See Board.h.
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

  BENCHMARK("4.1 Arduino core digitalRead-digitalWrite") {
    // 225 us, 14 us, 28.25 us, 35 kHz (Mega)
    ss.high();
    for (int i = 0; i < 8; i++) {
      digitalWrite(DATA_PIN, !digitalRead(DATA_PIN));
      digitalWrite(DATA_PIN, !digitalRead(DATA_PIN));
    }
    ss.low();
  }

  BENCHMARK("4.2 GPIO value and assignment operator") {
    // 15.8 us, 0.8125 us, 1.938 us, 516 kHz (Mega)
    ss.high();
    for (int i = 0; i < 8; i++) {
      data = !data;
      data = !data;
    }
    ss.low();
  }

  BENCHMARK("4.3 Arduino core digitalWrite") {
    // 118 us, 7.3 us, 14.75 us, 68 kHz (Mega)
    ss.high();
    for (int i = 0; i < 8; i++) {
      digitalWrite(DATA_PIN, 1);
      digitalWrite(DATA_PIN, 0);
    }
    ss.low();
  }

  BENCHMARK("4.4 GPIO pin assignment operator") {
    // 10.25 us, 0.5 us, 1.25, 800 kHz (Mega)
    ss.high();
    for (int i = 0; i < 8; i++) {
      data = 1;
      data = 0;
    }
    ss.low();
  }

  BENCHMARK("4.5 GPIO high and low") {
    // 10.25 us, 0.5 us, 1.25, 800 kHz (Mega)
    ss.high();
    for (int i = 0; i < 8; i++) {
      data.high();
      data.low();
    }
    ss.low();
  }

  BENCHMARK("4.6 GPIO toggle (single)") {
    // 12.31 us, 0.75 us, 1.5, 667 kHz (Mega)
    ss.high();
    for (int i = 0; i < 16; i++) {
      data.toggle();
    }
    ss.low();
  }

  BENCHMARK("4.7 GPIO toggle (double)") {
    // 10.25 us, 0.5 us, 1.25, 800 kHz (Mega)
    ss.high();
    for (int i = 0; i < 8; i++) {
      data.toggle();
      data.toggle();
    }
    ss.low();
  }

  BENCHMARK("4.8 GPIO toggle (unrolled)") {
    // 8.2 us, 0.5 us, 1.25, 1 MHz (Mega)
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
  }

  BENCHMARK("4.9 Arduino core digitalRead") {
    // 56 us, 6.625 us, 7 us, 143 kHz (Mega)
    data.input();
    ss.high();
    for (int i = 0; i < 8; i++) {
      // digitalWrite(LED_PIN, 1);
      uint8_t value = digitalRead(DATA_PIN);
      (void) value;
      // digitalWrite(LED_PIN, 0);
    }
    ss.low();
  }

  BENCHMARK("4.10 GPIO data value operator") {
    // 5.25 us, 0.25 us, 0.625, 1.6 MHz (Mega)
    ss.high();
    for (int i = 0; i < 8; i++) {
      // led = 1;
      uint8_t value = data;
      (void) value;
      // led = 0;
    }
    ss.low();
  }
#endif

  Serial.println();
  delay(2000);
}
