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
 * @param[in] DATA_PIN board pin for data input signal.
 * @param[in] CLOCK_PIN board pin for clock output signal.
 * @param[in] BIT_ORDER LSBFIRST or MSBFIRST.
 */
template<BOARD::pin_t DATA_PIN, BOARD::pin_t CLOCK_PIN, uint8_t BIT_ORDER>
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
   * @param[out] value.
   */
  void operator>>(uint8_t& value)
  {
    if (BIT_ORDER == LSBFIRST) {
      for (uint8_t mask = 1; mask; mask <<= 1) {
	m_clock.toggle();
	value |= (m_data ? mask : 0);
	m_clock.toggle();
      }
    }
    else {
      for (uint8_t mask = 0x80; mask; mask >>= 1) {
	m_clock.toggle();
	value |= (m_data ? mask : 0);
	m_clock.toggle();
      }
    }
  }

protected:
  GPIO<DATA_PIN> m_data;
  GPIO<CLOCK_PIN> m_clock;
};

#endif
