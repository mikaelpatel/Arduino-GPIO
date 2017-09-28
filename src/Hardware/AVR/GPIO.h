/**
 * @file Hardware/AVR/GPIO.h
 * @version 1.6
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

#ifndef HARDWARE_AVR_GPIO_H
#define HARDWARE_AVR_GPIO_H

#include "Hardware/AVR/Board.h"

/**
 * General Purpose Digital I/O pin template class. Highly optimized
 * pin access. The PIN address is a bit pointer to the port control
 * register. See Hardware/AVR/Board.h for details.
 * @param[in] PIN board pin definition.
 */
template<BOARD::pin_t PIN>
class GPIO {
public:
  /**
   * Set pin to input mode.
   */
  GPIO<PIN>& input()
    __attribute__((always_inline))
  {
    GPIO_ATOMIC(SFR()->ddr &= ~MASK);
    return (*this);
  }

  /**
   * Used with input() to activate internal pullup resistor on
   * input pin.
   */
  void pullup()
    __attribute__((always_inline))
  {
    high();
  }

  /**
   * Set pin to output mode.
   */
  void output()
    __attribute__((always_inline))
  {
    GPIO_ATOMIC(SFR()->ddr |= MASK);
  }

  /**
   * Open-drain pin. Use input() for high and output() for low.
   */
  void open_drain()
    __attribute__((always_inline))
  {
    input();
    low();
  }

  /**
   * Return current pin state.
   * @return state.
   */
  bool read()
    __attribute__((always_inline))
  {
    return ((SFR()->pin & MASK) != 0);
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
    GPIO_ATOMIC(SFR()->port &= ~MASK);
  }

  /**
   * Set pin high(1). Shorthand for write(HIGH).
   */
  void high()
    __attribute__((always_inline))
  {
    GPIO_ATOMIC(SFR()->port |= MASK);
  }

  /**
   * Toggle pin state. Shorthand for write(!read()).
   */
  void toggle()
    __attribute__((always_inline))
  {
    GPIO_ATOMIC(SFR()->pin |= MASK);
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
    uint16_t count = ((width * (F_CPU / 1000000L)) / 4);
    uint8_t sreg = SREG;
    __asm__ __volatile__("cli" ::: "memory");
    SFR()->pin |= MASK;
    _delay_loop_2(count);
    SFR()->pin |= MASK;
    SREG = sreg;
    __asm__ __volatile__("" ::: "memory");
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
  /** General Purpose Digital I/O Control Registers. */
  struct gpio_reg_t {
    volatile uint8_t pin;	//!< Port Input Pins.
    volatile uint8_t ddr;	//!< Data Direction Register.
    volatile uint8_t port;	//!< Data Register.
  };

  /**
   * Return pointer to control registers.
   * @return pointer.
   */
  gpio_reg_t* SFR()
    __attribute__((always_inline))
  {
    return ((gpio_reg_t*) GPIO_REG(PIN));
  }

  /** Pin bit position mask in control registers. */
  static const uint8_t MASK = GPIO_MASK(PIN);
};
#endif
