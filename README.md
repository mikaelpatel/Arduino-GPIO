# Arduino-GPIO
The Arduino GPIO library has been developed to allow high performance
digital pin access. Most access functions are compiled to a single
instruction and execute in 1-2 clock cycles. The library functions are
more than 10 times faster than the Arduino digital pin functions. In
some cases as much as 100 times faster.

Additional support classes are available for Debounced Digital and
Analog Pin, Shift Register Input/Output, and Software Serial. These
also demonstrate how the GPIO template class may be used to construct
additional libraries.

This library supports boards based on ATtinyX4, ATtinyX5, ATmega168,
ATmega328P, ATmega32U4, ATmega1280, ATmega2560 and SAM3X8E.

Version: 1.11

## Classes

* [AVR Board Configuration, BOARD](./src/Hardware/AVR/Board.h)
* [AVR General Purpose Input/Output, GPIO](./src/Hardware/AVR/GPIO.h)
* [SAM Board Configuration, BOARD](./src/Hardware/SAM/Board.h)
* [SAM General Purpose Input/Output, GPIO](./src/Hardware/SAM/GPIO.h)
* [Debounced Digital Pin, Button](./src/Button.h)
* [Debounced Analog Pin, Keypad](./src/Keypad.h)
* [Shift Register Parallel Input, SRPI](./src/SRPI.h)
* [Shift Register Parallel Input/Output, SRPIO](./src/SRPIO.h)
* [Shift Register Parallel Output, SRPO](./src/SRPO.h)
* [Software Serial, Software::Serial](./src/Software/Serial.h)

## Example Sketches

* [Benchmark](./examples/Benchmark)
* [Blink](./examples/Blink)
* [Button](./examples/Button)
* [Pulse](./examples/Pulse)
* [ShiftIn](./examples/ShiftIn)
* [ShiftInOut](./examples/ShiftInOut)
* [ShiftOut](./examples/ShiftOut)
* [SoftwareSerial](./examples/SoftwareSerial)

Benchmarks for [ATtiny](./examples/ATtiny).

## Benchmarks

Wiring | us | GPIO | us | Xn (Due/Uno/Mega)
------ |---------------|------|----|--------------
digitalRead | 1.23/3.75/6.4 | var = pin | 0.0625/0.071 | 17/60/99
digitalWrite | 2.30/4.25/7.2 | pin = val | 0.125/0.048 | 48/34/56
shiftIn | 46/87/151 | srpi >> var | 4.8/4.6/4.6 | 9.6/19/32
shiftOut | 53/104/161 | srpo << val | 5.7/7.9/7.9 | 9.3/13/20

## Usage

* [Arduino-DHT](https://github.com/mikaelpatel/Arduino-DHT)
* [Arduino-LCD](https://github.com/mikaelpatel/Arduino-LCD)
* [Arduino-OWI](https://github.com/mikaelpatel/Arduino-OWI)
* [Arduino-RTC](https://github.com/mikaelpatel/Arduino-RTC)
* [Arduino-SPI](https://github.com/mikaelpatel/Arduino-SPI)
* [Arduino-TWI](https://github.com/mikaelpatel/Arduino-TWI)
* [Arduino-Storage](https://github.com/mikaelpatel/Arduino-Storage)
