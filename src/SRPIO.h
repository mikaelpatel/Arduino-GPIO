/**
 * @file SRPIO.h
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

#ifndef SRPIO_H
#define SRPIO_H

#include "GPIO.h"

/**
 * Shift Register Parallel Input Output (SRPIO) template class using GPIO.
 * @param[in] BITORDER LSBFIRST or MSBFIRST.
 * @param[in] DATA_PIN board pin for data input/output signal.
 * @param[in] CLOCK_PIN board pin for clock output signal.
 */
template<uint8_t BITORDER, BOARD::pin_t DATA_PIN, BOARD::pin_t CLOCK_PIN>
class SRPIO {
public:
  /**
   * Construct Shift Register Parallel Input Output (SRPIO) instance
   * with given template parameters. Initiate GPIO pins for data to
   * open drain mode (external pullup resistor) and clock to output
   * mode.
   */
  SRPIO()
  {
    m_data.open_drain();
    m_clock.output();
  }

  /**
   * Serialize given value according to the template bit order
   * parameter. Generate a positive clock pulse for each bit transfer.
   * @param[in] value to data output signal.
   */
  void write(uint8_t value)
  {
    if (BITORDER == LSBFIRST) {
      uint8_t mask = 1;
      do {
	if (value & mask) m_data.input(); else m_data.output();
	m_clock.toggle();
	mask <<= 1;
	m_clock.toggle();
      } while (mask);
    }
    else {
      uint8_t mask = 0x80;
      do {
	if (value & mask) m_data.input(); else m_data.output();
	m_clock.toggle();
	mask >>= 1;
	m_clock.toggle();
      } while (mask);
    }
    m_data.input();
  }

  /**
   * Serial output operator. Shorthand for write().
   * @param[in] value to data output signal.
   */
  void operator<<(uint8_t value)
  {
    write(value);
  }

  /**
   * Return deserialized value according to the template bit order
   * parameter. Generates a positive clock pulse for each bit
   * transfer.
   * @return byte read from data input signal.
   */
  uint8_t read()
  {
    if (BITORDER == LSBFIRST) {
      uint8_t mask = 1;
      do {
	m_clock.toggle();
	value |= (m_data ? mask : 0);
	m_clock.toggle();
	mask <<= 1;
      } while (mask);
    }
    else {
      uint8_t mask = 0x80;
      do {
	m_clock.toggle();
	value |= (m_data ? mask : 0);
	m_clock.toggle();
	mask >>= 1;
      } while (mask);
    }
  }

  /**
   * Serial input operator. Shorthand for read().
   * @param[out] value from data input signal.
   */
  void operator>>(uint8_t& value)
  {
    value = read();
  }

protected:
  GPIO<DATA_PIN> m_data;
  GPIO<CLOCK_PIN> m_clock;
};

#endif
