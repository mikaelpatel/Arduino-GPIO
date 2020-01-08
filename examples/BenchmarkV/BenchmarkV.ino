#include "GPIO.h"
#include "benchmark.h"

/* 
 *  NANO GPIO
16:06:16.704 -> 1.1 Arduino core digitalRead: 3.836
16:06:16.704 -> 1.2 Arduino core digitalWrite(HIGH): 4.216
16:06:16.704 -> 1.3 Arduino core digitalWrite(LOW): 4.088
16:06:16.739 -> 1.4 Arduino core toggle; digitalRead-digitalWrite: 8.236
16:06:16.739 -> 1.5 Arduino core toggle; digitalWrite: 8.304
16:06:16.774 -> 2.1 GPIO pin value operator: 0.064
16:06:16.774 -> 2.2 GPIO high member function: 0.128
16:06:16.774 -> 2.3 GPIO low member function: 0.132
16:06:16.774 -> 2.4 GPIO assignment HIGH: 0.132
16:06:16.774 -> 2.5 GPIO assignment LOW: 0.132
16:06:16.807 -> 2.6 GPIO toggle; value and assignment operator: 0.344
16:06:16.807 -> 2.7 GPIO toggle; high and low member functions: 0.248
16:06:16.807 -> 2.8 GPIO toggle; assignment operator, HIGH/LOW: 0.248
16:06:16.807 -> 2.9 GPIO toggle member function: 0.124
16:06:16.843 ->
  
  NANO VGPIO
16:10:40.288 -> 1.1 Arduino core digitalRead: 3.836
16:10:40.288 -> 1.2 Arduino core digitalWrite(HIGH): 4.216
16:10:40.321 -> 1.3 Arduino core digitalWrite(LOW): 4.084
16:10:40.321 -> 1.4 Arduino core toggle; digitalRead-digitalWrite: 8.236
16:10:40.321 -> 1.5 Arduino core toggle; digitalWrite: 8.304
16:10:40.356 -> 2.1 VGPIO pin value operator: 0.064
16:10:40.356 -> 2.2 VGPIO high member function: 0.756
16:10:40.356 -> 2.3 VGPIO low member function: 0.756
16:10:40.390 -> 2.4 VGPIO assignment HIGH: 0.132
16:10:40.390 -> 2.5 VGPIO assignment LOW: 0.132
16:10:40.390 -> 2.6 VGPIO toggle; value and assignment operator: 1.356
16:10:40.390 -> 2.7 VGPIO toggle; high and low member functions: 1.512
16:10:40.424 -> 2.8 VGPIO toggle; assignment operator, HIGH/LOW: 0.256
16:10:40.424 -> 2.9 VGPIO toggle member function: 0.756
16:10:40.424 -> 


 */
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
