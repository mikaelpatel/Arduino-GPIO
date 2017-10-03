/**
 * @file Keypad.h
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

#ifndef KEYPAD_H
#define KEYPAD_H

/**
 * Resistor ladder keypad read and debounce template class.
 * @param[in] PIN analog pin.
 * @param[in] DEBOUNCE time limit (default 50 ms).
 */
template<int PIN, uint16_t DEBOUNCE = 50>
class Keypad {
public:
  /**
   * Construct keypad with given template parameters.
   */
  Keypad(const uint16_t* map = NULL) :
    m_timestamp(0),
    m_key(0),
    m_map(map)
  {
  }

  /**
   * Check if it is time to sample the keypad and check for
   * key pressed/release.
   * @return true(1) if a change was detected, otherwise false(0).
   */
  bool ischanged()
  {
    // Check if debounce time limit has elapsed
    if (millis() - m_timestamp < DEBOUNCE) return (false);
    m_timestamp = millis();

    // Read the analog pin and map
    uint16_t value = analogRead(PIN);
    uint8_t key = 0;
    if (m_map == NULL) return (false);
    while (value < (uint16_t) pgm_read_word(&m_map[key])) key++;
    if (key == m_key) return (false);
    m_key = key;
    return (true);
  }

  /**
   * Return latest key.
   * @return key number.
   */
  uint8_t key()
    __attribute__((always_inline))
  {
    return (m_key);
  }

  /**
   * Return debounce timestamp.
   * @return timestamp.
   */
  uint16_t timestamp()
    __attribute__((always_inline))
  {
    return (m_timestamp);
  }

protected:
  /** Timestamp for latest pin read. */
  uint16_t m_timestamp;

  /** Latest debounced key. */
  uint8_t m_key;

  /** Key map; program memory with values in descent order. */
  const uint16_t* m_map;
};

#endif
