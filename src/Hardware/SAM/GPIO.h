/**
 * @file Hardware/SAM/GPIO.h
 * @version 1.0
 *
 * @section License
 * Copyright (C) 2017, Mikael Patel
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 */

#ifndef HARDWARE_SAM_GPIO_H
#define HARDWARE_SAM_GPIO_H

#include "Hardware/SAM/Board.h"

/**
 * General Purpose Digital I/O pin template class. Highly optimized
 * pin access. The PIN address is the port control register index and
 * pin bit position. See Hardware/SAM/Board.h for details.
 * @param[in] PIN board pin definition.
 */
template<BOARD::pin_t PIN>
class GPIO {
public:
  GPIO()
  {
    SFR()->PIO_PER = MASK;
  }

  /**
   * Set pin to input mode.
   */
  void input()
    __attribute__((always_inline))
  {
    SFR()->PIO_ODR = MASK;
    SFR()->PIO_PUDR = MASK;
  }

  /**
   * Set pin to input mode and activate internal pullup resistor.
   */
  void input_pullup()
    __attribute__((always_inline))
  {
    SFR()->PIO_ODR = MASK;
    SFR()->PIO_PUER = MASK;
  }

  /**
   * Set pin to output mode.
   */
  void output()
    __attribute__((always_inline))
  {
    SFR()->PIO_OER = MASK;
    SFR()->PIO_PUER = MASK;
  }

  /**
   * Return current pin state.
   * @return state.
   */
  bool read()
    __attribute__((always_inline))
  {
    if (SFR()->PIO_OSR & MASK)
      return ((SFR()->PIO_ODSR & MASK) != 0);
    return ((SFR()->PIO_PDSR & MASK) != 0);
  }

  /**
   * Return current pin state. Shorthand for read().
   * @return state.
   */
  operator bool()
    __attribute__((always_inline))
  {
    return (read());
  }

  /**
   * Set pin low(0). Shorthand for write(LOW).
   */
  void low()
    __attribute__((always_inline))
  {
    SFR()->PIO_CODR = MASK;
  }

  /**
   * Set pin high(1). Shorthand for write(HIGH).
   */
  void high()
    __attribute__((always_inline))
  {
    SFR()->PIO_SODR = MASK;
  }

  /**
   * Toggle pin state. Shorthand for write(!read()).
   */
  void toggle()
    __attribute__((always_inline))
  {
    if (SFR()->PIO_ODSR & MASK)
      SFR()->PIO_CODR = MASK;
    else
      SFR()->PIO_SODR = MASK;
  }

  /**
   * Set pin to given state. Non-zero value will set the pin HIGH(1),
   * and zero value will set the pin LOW(0).
   * @param[in] value to set pin.
   */
  void write(int value)
    __attribute__((always_inline))
  {
    if (value) high(); else low();
  }

  /**
   * Set pin to given state. Non-zero value will set the pin HIGH(1),
   * and zero value will set the pin LOW(0). Shorthand for write(value).
   * @param[in] value to set pin.
   */
  void operator=(int value)
    __attribute__((always_inline))
  {
    write(value);
  }

  /**
   * Generate pulse with given width in micro-seconds. Interrupts
   * are disabled while generating the pulse.
   * @param[in] width in micro-seconds.
   */
  void pulse(uint16_t width)
  {
    if (width == 0) return;
    toggle();
    delayMicroseconds(width);
    toggle();
  }

  /**
   * Detect pulse and return width in micro-seconds.
   * @return width in micro-seconds.
   */
  int pulse()
  {
    bool s0 = read();
    while (read() == s0);
    uint16_t t0 = micros();
    while (read() != s0);
    return (micros() - t0);
  }

protected:
  /** Pin bit position mask in control registers. */
  static const uint32_t MASK = GPIO_MASK(PIN);

  /**
   * Return pointer to control registers.
   * @return pointer.
   */
  Pio* SFR()
    __attribute__((always_inline))
  {
    switch (GPIO_REG(PIN)) {
    case 0: return (PIOA);
    case 1: return (PIOB);
    case 2: return (PIOC);
    default:
      return (PIOD);
    }
  }
};
#endif
