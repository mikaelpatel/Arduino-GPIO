/**
 * @file GPIO.h
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

#ifndef GPIO_H
#define GPIO_H

#include "Board.h"

/**
 * General Purpose Digital I/O pin template class. Highly opimized
 * pin access. PIN address is 12-bit control register address (msb)
 * and 4-bit bit number (lsb). See Board.h for definitions.
 * @param[in] PIN board pin definition.
 */
template<BOARD::pin_t PIN>
class GPIO {
public:
  /**
   * Set pin to input mode. Pullup resistor may be activated with
   * given flag parameter. Deactivated by default.
   * @param[in] pullup resistor flag (default false).
   */
  void input(bool pullup = false)
    __attribute__((always_inline))
  {
    SFR()->ddr &= ~MASK;
    if (pullup) SFR()->port |= MASK;
  }

  /**
   * Set pin to output mode.
   */
  void output()
    __attribute__((always_inline))
  {
    SFR()->ddr |= MASK;
  }

  /**
   * Return current pin state.
   * @return state.
   */
  operator bool()
    __attribute__((always_inline))
  {
    return ((SFR()->pin & MASK) != 0);
  }

  /**
   * Set pin low(0).
   */
  void low()
    __attribute__((always_inline))
  {
    SFR()->port &= ~MASK;
  }

  /**
   * Set pin high(1).
   */
  void high()
    __attribute__((always_inline))
  {
    SFR()->port |= MASK;
  }

  /**
   * Toggle pin state.
   */
  void toggle()
    __attribute__((always_inline))
  {
    SFR()->pin |= MASK;
  }

  /**
   * Set pin to low(0) if the given value is zero otherwise high(1).
   * @param[in] value.
   */
  void operator=(int value)
    __attribute__((always_inline))
  {
    if (value) high(); else low();
  }

protected:
  /** General Purpose Digital I/O control registers. */
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
    return (gpio_reg_t*) (PIN >> 4);
  }

  /** Bit position mask for control registers. */
  static const uint8_t MASK = _BV(PIN & 0xf);
};
#endif
