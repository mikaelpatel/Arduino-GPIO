/**
 * @file SRPI.h
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

#ifndef SRPI_H
#define SRPI_H

#include "GPIO.h"

/**
 * Shift Register Parallel Input (SRPI) template class using GPIO.
 * @param[in] BITORDER LSBFIRST or MSBFIRST.
 * @param[in] DATA_PIN board pin for data input signal.
 * @param[in] CLOCK_PIN board pin for clock output signal.
 */
template<uint8_t BITORDER, BOARD::pin_t DATA_PIN, BOARD::pin_t CLOCK_PIN>
class SRPI {
public:
  /**
   * Construct Shift Register Parallel Input (SRPI) instance with given
   * template parameters. Initiate GPIO pins for data to input mode
   * and clock to output mode.
   */
  SRPI()
  {
    m_data.input();
    m_clock.output();
  }

  /**
   * Return deserialized value according to the template bit order
   * parameter. Generates a positive clock pulse for each bit
   * transfer.
   * @return read byte.
   */
  uint8_t read()
  {
    uint8_t res = 0;
    if (BITORDER == LSBFIRST) {
      uint8_t mask = 1;
      do {
	m_clock.toggle();
	res |= (m_data ? mask : 0);
	m_clock.toggle();
	mask <<= 1;
      } while (mask);
    }
    else {
      uint8_t mask = 0x80;
      do {
	m_clock.toggle();
	res |= (m_data ? mask : 0);
	m_clock.toggle();
	mask >>= 1;
      } while (mask);
    }
    return (res);
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
