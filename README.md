# Arduino-GPIO
The Arduino GPIO library has been developed to allow high performance
digital pin access. Most access functions are compiled to a single
instruction and execute in 1-2 clock cycles. The library functions are
more than 10 times faster than the Arduino digital pin functions. In
some cases as much as 60 times faster. Additional support classes are
available for Shift Register Input/Output, and Asychronous Serial
Output. These also demonstrate how the GPIO template class may be used
to construct additional libraries.

```
GPIO<BOARD:D4> pin;  // Construct pin instance.

pin.input();         // Set pin to input mode.
pin.input_pullup();  // Set pin to input mode with internal pullup resistor.
pin.output();        // Set pin to output mode.

bool state = pin;    // Read current pin state.
if (pin) ...         // Use pin as boolean value in conditional expression.

pin = state;         // Write new pin state.
pin.low();           // Set pin low(0).
pin.high();          // Set pin high(1).
pin.toggle();        // Toggle pin state.
pin.pulse(width);    // Generate pulse with given width in micro-seconds.

```

## Classes

* [Boards](./src/Board.h)
* [General Purpose Input/Output, GPIO](./src/GPIO.h)
* [Asynchronous Serial Output, ASO](./src/ASO.h)
* [Shift Register Parallel Input, SRPI](./src/SRPI.h)
* [Shift Register Parallel Output, SRPO](./src/SRPO.h)

## Example Sketches

* [Benchmark](./examples/Benchmark)
* [Blink](./examples/Blink)
* [Pulse](./examples/Pulse)
* [ShiftIn](./examples/ShiftIn)
* [ShiftOut](./examples/ShiftOut)
* [SoftwareSerial](./examples/SoftwareSerial)
