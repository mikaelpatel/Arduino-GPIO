/**
 * @file SRPO.h
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

#ifndef SRPO_H
#define SRPO_H

#include "GPIO.h"

/**
 * Shift Register Parallel Output (SRPO) template class using GPIO.
 * @param[in] DATA_PIN board pin for data output signal.
 * @param[in] CLOCK_PIN board pin for clock output signal.
 * @param[in] BIT_ORDER LSBFIRST or MSBFIRST.
 */
template<BOARD::pin_t DATA_PIN, BOARD::pin_t CLOCK_PIN, uint8_t BIT_ORDER>
class SRPO {
public:
  /**
   * Construct Shift Register Parallel Output (SRPO) instance with
   * given template parameters. Initiate GPIO pins for data and clock
   * to output mode.
   */
  SRPO()
  {
    m_data.output();
    m_clock.output();
  }

  /**
   * Serialize given value according to the template bit order
   * parameter. Generate a positive clock pulse for each bit transfer.
   * @param[in] value.
   */
  void operator<<(uint8_t value)
  {
    if (BIT_ORDER == LSBFIRST) {
      for (uint8_t mask = 1; mask; mask <<= 1) {
	m_data = value & mask;
	m_clock.toggle();
	m_clock.toggle();
      }
    }
    else {
      for (uint8_t mask = 0x80; mask; mask >>= 1) {
	m_data = value & mask;
	m_clock.toggle();
	m_clock.toggle();
      }
    }
  }

protected:
  GPIO<DATA_PIN> m_data;
  GPIO<CLOCK_PIN> m_clock;
};

#endif
