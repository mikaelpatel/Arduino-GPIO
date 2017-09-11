/**
 * @file GPIO.h
 * @version 1.3
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

#ifndef GPIO_H
#define GPIO_H

#include "Board.h"

/**
 * Forces given expression to be atomic. Higher port addresses
 * cannot be accessed with a single instruction and require
 * disabling of interrupts to become atomic.
 * @param[in] expr expression to be atomic.
 */
#define GPIO_ATOMIC(expr)					\
  do {								\
    if (PIN < 0x600) {						\
      expr;							\
    }								\
    else {							\
      uint8_t sreg = SREG;					\
      __asm__ __volatile__("cli" ::: "memory");			\
      expr;							\
      SREG = sreg;						\
      __asm__ __volatile__("" ::: "memory");			\
    }								\
  } while (0)

/**
 * General Purpose Digital I/O pin template class. Highly optimized
 * pin access. The PIN address is 12-bit control register address
 * (msb) and 4-bit bit number (lsb). See Board.h for definitions.
 * @param[in] PIN board pin definition.
 */
template<BOARD::pin_t PIN>
class GPIO {
public:
  /**
   * Set pin to input mode.
   */
  void input()
    __attribute__((always_inline))
  {
    GPIO_ATOMIC(SFR()->ddr &= ~MASK);
  }

  /**
   * Set pin to input mode and activate internal pullup resistor.
   */
  void input_pullup()
    __attribute__((always_inline))
  {
    input();
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
   * Toggle pin state.
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
   * and zero value will set the pin LOW(0). Sorthand for write(value).
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
    __attribute__((always_inline))
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

protected:
  /** General Purpose Digital I/O Control Registers. */
  struct gpio_reg_t {
    volatile uint8_t pin;	//!< Port Input Pins.
    volatile uint8_t ddr;	//!< Data Direction Register.
    volatile uint8_t port;	//!< Data Register.
  };

  /**
   * Return pointer to pin control registers.
   * @return pointer.
   */
  gpio_reg_t* SFR()
    __attribute__((always_inline))
  {
    return ((gpio_reg_t*) (PIN >> 4));
  }

  /** Pin bit position mask for control registers. */
  static const uint8_t MASK = _BV(PIN & 0xf);
};
#endif
