#include "IGPIO.h"
#include "benchmark.h"

/* 
 *  UNO GPIO baseline
07:13:50.128 -> 1.1 Arduino core digitalRead: 3.836
07:13:50.128 -> 1.2 Arduino core digitalWrite(HIGH): 4.216
07:13:50.128 -> 1.3 Arduino core digitalWrite(LOW): 4.088
07:13:50.162 -> 1.4 Arduino core toggle; digitalRead-digitalWrite: 8.236
07:13:50.162 -> 1.5 Arduino core toggle; digitalWrite: 8.304

07:13:50.197 -> 2.1 GPIO pin value operator: 0.064
07:13:50.197 -> 2.2 GPIO high member function: 0.128
07:13:50.197 -> 2.3 GPIO low member function: 0.132
07:13:50.197 -> 2.4 GPIO assignment HIGH: 0.132
07:13:50.197 -> 2.5 GPIO assignment LOW: 0.132
07:13:50.234 -> 2.6 GPIO toggle; value and assignment operator: 0.344
07:13:50.234 -> 2.7 GPIO toggle; high and low member functions: 0.248
07:13:50.234 -> 2.8 GPIO toggle; assignment operator, HIGH/LOW: 0.248
07:13:50.234 -> 2.9 GPIO toggle member function: 0.124

 *  UNO VGPIO
07:12:45.468 -> 2.1 VGPIO pin value operator: 0.064
07:12:45.468 -> 2.2 VGPIO high member function: 0.756
07:12:45.468 -> 2.3 VGPIO low member function: 0.756
07:12:45.503 -> 2.4 VGPIO assignment HIGH: 0.132
07:12:45.503 -> 2.5 VGPIO assignment LOW: 0.132
07:12:45.503 -> 2.6 VGPIO toggle; value and assignment operator: 1.356
07:12:45.503 -> 2.7 VGPIO toggle; high and low member functions: 1.512
07:12:45.538 -> 2.8 VGPIO toggle; assignment operator, HIGH/LOW: 0.256
07:12:45.538 -> 2.9 VGPIO toggle member function: 0.756

 *  UNO IGPIO
1.1 Arduino core digitalRead: 3.840
07:10:08.171 -> 2.1 IGPIO pin value operator: 1.512
07:10:08.171 -> 2.2 IGPIO high member function: 1.448
07:10:08.171 -> 2.3 IGPIO low member function: 1.452
07:10:08.206 -> 2.4 IGPIO assignment HIGH: 1.700
07:10:08.206 -> 2.5 IGPIO assignment LOW: 1.764
07:10:08.206 -> 2.6 IGPIO toggle; value and assignment operator: 2.924
07:10:08.206 -> 2.7 IGPIO toggle; high and low member functions: 2.892
07:10:08.240 -> 2.8 IGPIO toggle; assignment operator, HIGH/LOW: 3.456
07:10:08.240 -> 2.9 IGPIO toggle member function: 1.452
07:10:08.275 -> 

 */
const IGPIO& button = VGPIO<BOARD::D12>();
const IGPIO& led = VGPIO<BOARD::D13>();
#define BUTTON_PIN 12
#define LED_PIN 13

void setup()
{
  Serial.begin(57600);
  while (!Serial);
  delay(1000);
  
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

  BENCHMARK("2.1 IGPIO pin value operator", 1000) {
    bool state = button;
    (void) state;
  }

  BENCHMARK("2.2 IGPIO high member function", 1000) {
    led.high();
  }

  BENCHMARK("2.3 IGPIO low member function", 1000) {
    led.low();
  }

  BENCHMARK("2.4 IGPIO assignment HIGH", 1000) {
    led = HIGH;
  }

  BENCHMARK("2.5 IGPIO assignment LOW", 1000) {
    led = LOW;
  }

  BENCHMARK("2.6 IGPIO toggle; value and assignment operator", 1000) {
    led.write( !led.read() );
  }

  BENCHMARK("2.7 IGPIO toggle; high and low member functions", 1000) {
    led.high();
    led.low();
  }

  BENCHMARK("2.8 IGPIO toggle; assignment operator, HIGH/LOW", 1000) {
    led = HIGH;
    led = LOW;
  }

  BENCHMARK("2.9 IGPIO toggle member function", 1000) {
    led.toggle();
  }

#ifdef PORTH

  // IGPIO atomic access of io ports with higher address. These
  // benchmarks are for Arduino Mega pins that use ports above address
  // 0x40 (PORTH, PORTJ, PINK and PINL). See Hardware/AVR/Board.h.

#define DIN_PIN 6
#define DOUT_PIN 7
  const IGPIO& din = VGPIO<BOARD::D6>();
  const IGPIO& dout = VGPIO<BOARD::D7>();
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

  BENCHMARK("4.1 IGPIO pin value operator", 1000) {
    bool state = din;
    (void) state;
  }

  BENCHMARK("4.2 IGPIO high member function", 1000) {
    dout.high();
  }

  BENCHMARK("4.3 IGPIO low member function", 1000) {
    dout.low();
  }

  BENCHMARK("4.4 IGPIO assignment HIGH", 1000) {
    dout = HIGH;
  }

  BENCHMARK("4.5 IGPIO assignment LOW", 1000) {
    dout = LOW;
  }

  BENCHMARK("4.6 IGPIO toggle; value and assignment operator", 1000) {
    dout.write( !dout.read() );
  }

  BENCHMARK("4.7 IGPIO toggle; high and low member functions", 1000) {
    dout.high();
    dout.low();
  }

  BENCHMARK("4.8 IGPIO toggle; assignment operator", 1000) {
    dout = HIGH;
    dout = LOW;
  }

  BENCHMARK("4.9 IGPIO toggle member function", 1000) {
    dout.toggle();
  }
#endif

  Serial.println();
  delay(2000);
  while(true) ;
}
