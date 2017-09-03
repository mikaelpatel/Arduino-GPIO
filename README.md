# Arduino-GPIO
The Arduino GPIO library has been developed to allow high performance
digital pin access. Most access functions are compiled to a single
instruction and execute in 1-2 clock cycles. The library functions are
more than 10 times faster than the Arduino digital pin functions. In
some cases as much as 60 times faster.

Additional support classes are available for Shift Register
Input/Output, and Software Serial. These also demonstrate how the GPIO
template class may be used to construct additional libraries.

## Classes

* [Configuration, Board](./src/Board.h)
* [General Purpose Input/Output, GPIO](./src/GPIO.h)
* [Shift Register Parallel Input, SRPI](./src/SRPI.h)
* [Shift Register Parallel Output, SRPO](./src/SRPO.h)
* [Software Serial, Software::Serial](./src/Software/Serial.h)

## Example Sketches

* [Benchmark](./examples/Benchmark)
* [Blink](./examples/Blink)
* [Pulse](./examples/Pulse)
* [ShiftIn](./examples/ShiftIn)
* [ShiftOut](./examples/ShiftOut)
* [SoftwareSerial](./examples/SoftwareSerial)
