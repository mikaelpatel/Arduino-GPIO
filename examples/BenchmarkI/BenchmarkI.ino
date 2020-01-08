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

   NANO IGPIO
16:20:32.106 -> 1.1 Arduino core digitalRead: 3.840
16:20:32.106 -> 1.2 Arduino core digitalWrite(HIGH): 4.216
16:20:32.140 -> 1.3 Arduino core digitalWrite(LOW): 4.084
16:20:32.140 -> 1.4 Arduino core toggle; digitalRead-digitalWrite: 8.236
16:20:32.175 -> 1.5 Arduino core toggle; digitalWrite: 8.304
16:20:32.175 -> 2.1 IGPIO pin value operator: 1.512
16:20:32.175 -> 2.2 IGPIO high member function: 1.448
16:20:32.212 -> 2.3 IGPIO low member function: 1.452
16:20:32.212 -> 2.4 IGPIO assignment HIGH: 1.700
16:20:32.212 -> 2.5 IGPIO assignment LOW: 1.764
16:20:32.212 -> 2.6 IGPIO toggle; value and assignment operator: 2.924
16:20:32.246 -> 2.7 IGPIO toggle; high and low member functions: 2.896
16:20:32.246 -> 2.8 IGPIO toggle; assignment operator, HIGH/LOW: 3.460
16:20:32.246 -> 2.9 IGPIO toggle member function: 1.444
16:20:32.281 -> 

  MEGA GPIO
16:26:50.265 -> 1.1 Arduino core digitalRead: 6.412
16:26:50.299 -> 1.2 Arduino core digitalWrite(HIGH): 6.916
16:26:50.299 -> 1.3 Arduino core digitalWrite(LOW): 6.792
16:26:50.332 -> 1.4 Arduino core toggle; digitalRead-digitalWrite: 13.204
16:26:50.366 -> 1.5 Arduino core toggle; digitalWrite: 13.712
16:26:50.366 -> 2.1 GPIO pin value operator: 0.064
16:26:50.366 -> 2.2 GPIO high member function: 0.124
16:26:50.366 -> 2.3 GPIO low member function: 0.124
16:26:50.401 -> 2.4 GPIO assignment HIGH: 0.124
16:26:50.401 -> 2.5 GPIO assignment LOW: 0.128
16:26:50.401 -> 2.6 GPIO toggle; value and assignment operator: 0.352
16:26:50.401 -> 2.7 GPIO toggle; high and low member functions: 0.256
16:26:50.434 -> 2.8 GPIO toggle; assignment operator, HIGH/LOW: 0.248
16:26:50.434 -> 2.9 GPIO toggle member function: 0.132
16:26:50.434 -> 3.1 Arduino core digitalRead: 6.284
16:26:50.468 -> 3.2 Arduino core digitalWrite(HIGH): 7.168
16:26:50.468 -> 3.3 Arduino core digitalWrite(LOW): 7.048
16:26:50.468 -> 3.4 Arduino core toggle; digitalRead-digitalWrite: 13.652
16:26:50.502 -> 3.5 Arduino core toggle; digitalWrite: 14.208
16:26:50.536 -> 4.1 GPIO pin value operator: 0.128
16:26:50.536 -> 4.2 GPIO high member function: 0.504
16:26:50.536 -> 4.3 GPIO low member function: 0.504
16:26:50.536 -> 4.4 GPIO assignment HIGH: 0.508
16:26:50.571 -> 4.5 GPIO assignment LOW: 0.504
16:26:50.571 -> 4.6 GPIO toggle; value and assignment operator: 0.944
16:26:50.571 -> 4.7 GPIO toggle; high and low member functions: 1.008
16:26:50.571 -> 4.8 GPIO toggle; assignment operator: 1.012
16:26:50.606 -> 4.9 GPIO toggle member function: 0.500
16:26:50.606 -> 
  
  MEGA VGPIO
16:26:20.659 -> 1.1 Arduino core digitalRead: 6.412
16:26:20.659 -> 1.2 Arduino core digitalWrite(HIGH): 6.920
16:26:20.693 -> 1.3 Arduino core digitalWrite(LOW): 6.796
16:26:20.693 -> 1.4 Arduino core toggle; digitalRead-digitalWrite: 13.204
16:26:20.728 -> 1.5 Arduino core toggle; digitalWrite: 13.712
16:26:20.761 -> 2.1 VGPIO pin value operator: 0.068
16:26:20.761 -> 2.2 VGPIO high member function: 0.820
16:26:20.761 -> 2.3 VGPIO low member function: 0.820
16:26:20.761 -> 2.4 VGPIO assignment HIGH: 0.124
16:26:20.761 -> 2.5 VGPIO assignment LOW: 0.124
16:26:20.795 -> 2.6 VGPIO toggle; value and assignment operator: 1.660
16:26:20.795 -> 2.7 VGPIO toggle; high and low member functions: 1.636
16:26:20.795 -> 2.8 VGPIO toggle; assignment operator, HIGH/LOW: 0.256
16:26:20.829 -> 2.9 VGPIO toggle member function: 0.820
16:26:20.829 -> 3.1 Arduino core digitalRead: 6.356
16:26:20.829 -> 3.2 Arduino core digitalWrite(HIGH): 7.232
16:26:20.864 -> 3.3 Arduino core digitalWrite(LOW): 7.104
16:26:20.864 -> 3.4 Arduino core toggle; digitalRead-digitalWrite: 13.768
16:26:20.899 -> 3.5 Arduino core toggle; digitalWrite: 14.344
16:26:20.899 -> 4.1 VGPIO pin value operator: 0.132
16:26:20.932 -> 4.2 VGPIO high member function: 1.448
16:26:20.932 -> 4.3 VGPIO low member function: 1.448
16:26:20.932 -> 4.4 VGPIO assignment HIGH: 1.576
16:26:20.932 -> 4.5 VGPIO assignment LOW: 1.764
16:26:20.966 -> 4.6 VGPIO toggle; value and assignment operator: 2.072
16:26:20.966 -> 4.7 VGPIO toggle; high and low member functions: 2.892
16:26:20.966 -> 4.8 VGPIO toggle; assignment operator: 3.332
16:26:21.000 -> 4.9 VGPIO toggle member function: 1.452
16:26:21.000 -> 
  

  MEGA IGPIO
16:24:12.181 -> 1.1 Arduino core digitalRead: 6.420
16:24:12.181 -> 1.2 Arduino core digitalWrite(HIGH): 6.920
16:24:12.181 -> 1.3 Arduino core digitalWrite(LOW): 6.792
16:24:12.216 -> 1.4 Arduino core toggle; digitalRead-digitalWrite: 13.212
16:24:12.251 -> 1.5 Arduino core toggle; digitalWrite: 13.704
16:24:12.251 -> 2.1 IGPIO pin value operator: 1.700
16:24:12.251 -> 2.2 IGPIO high member function: 1.572
16:24:12.286 -> 2.3 IGPIO low member function: 1.572
16:24:12.286 -> 2.4 IGPIO assignment HIGH: 1.828
16:24:12.286 -> 2.5 IGPIO assignment LOW: 1.884
16:24:12.286 -> 2.6 IGPIO toggle; value and assignment operator: 3.176
16:24:12.319 -> 2.7 IGPIO toggle; high and low member functions: 3.152
16:24:12.319 -> 2.8 IGPIO toggle; assignment operator, HIGH/LOW: 3.712
16:24:12.352 -> 2.9 IGPIO toggle member function: 1.572
16:24:12.352 -> 3.1 Arduino core digitalRead: 6.356
16:24:12.352 -> 3.2 Arduino core digitalWrite(HIGH): 7.236
16:24:12.386 -> 3.3 Arduino core digitalWrite(LOW): 7.108
16:24:12.386 -> 3.4 Arduino core toggle; digitalRead-digitalWrite: 13.776
16:24:12.421 -> 3.5 Arduino core toggle; digitalWrite: 14.336
16:24:12.421 -> 4.1 IGPIO pin value operator: 1.140
16:24:12.455 -> 4.2 IGPIO high member function: 1.452
16:24:12.455 -> 4.3 IGPIO low member function: 1.444
16:24:12.455 -> 4.4 IGPIO assignment HIGH: 1.576
16:24:12.455 -> 4.5 IGPIO assignment LOW: 1.760
16:24:12.488 -> 4.6 IGPIO toggle; value and assignment operator: 2.076
16:24:12.488 -> 4.7 IGPIO toggle; high and low member functions: 2.896
16:24:12.488 -> 4.8 IGPIO toggle; assignment operator: 3.328
16:24:12.523 -> 4.9 IGPIO toggle member function: 1.452
16:24:12.523 -> 
  
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
