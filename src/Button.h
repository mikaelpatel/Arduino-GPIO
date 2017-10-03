/**
 * @file Button.h
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

#ifndef BUTTON_H
#define BUTTON_H

#include "GPIO.h"

/**
 * Debounced Input Pin template class using GPIO. The internal pullup
 * resistor is used. The button/switch should be connected to ground.
 * @param[in] PIN board pin for input signal.
 * @param[in] DEBOUNCE time limit (Default 50 ms).
 */
template<BOARD::pin_t PIN, uint16_t DEBOUNCE = 50>
class Button {
public:
  /**
   * Construct debounced input pin instance with given template
   * parameters. Initiate GPIO pins input mode with pullup resistor.
   */
  Button() :
    m_timestamp(0),
    m_state(true)
  {
    m_pin.input().pullup();
  }

  /**
   * Return true(1) if a button state change was detected, otherwise
   * false(0). Rising or falling edge is determined by reading the
   * debounced pin state.
   * @return bool.
   */
  bool ischanged()
  {
    // Check if debounce time limit has elapsed
    if (millis() - m_timestamp < DEBOUNCE) return (false);
    m_timestamp = millis();

    // Check for the pin state has changed
    bool state = m_pin;
    if (state == m_state) return (false);
    m_state = state;
    return (true);
  }

  /**
   * Return debounced pin state.
   * @return state.
   */
  bool read()
  {
    return (m_state);
  }

  /**
   * Return debounced pin state. Shorthand for read().
   * @return bool.
   */
  operator bool()
    __attribute__((always_inline))
  {
    return (read());
  }

  /**
   * Return debounce timestamp.
   * @return timestamp.
   */
  uint16_t timestamp()
  {
    return (m_timestamp);
  }

protected:
  /** Button pin. */
  GPIO<PIN> m_pin;

  /** Timestamp for latest pin read. */
  uint16_t m_timestamp;

  /** Latest pin read; debounced pin state. */
  bool m_state;
};

#endif
