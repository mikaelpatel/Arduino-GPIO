/**
 * @file bcd.h
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

#ifndef BCD_H
#define BCD_H

/**
 * Binary-Coded Decimal (BCD) to integer conversion handling.
 */
struct bcd_t {
  /**
   * Default constructor.
   */
  bcd_t() : m_value(0) {}

  /**
   * Construct bcd value from given value; 0..99 to 0x00..0x99.
   * @param[in] value as integer.
   */
  bcd_t(uint8_t value)
  {
    uint8_t high = 0;
    uint8_t low = value;
    while (low > 9) {
      high += 0x10;
      low -= 10;
    }
    m_value = high + low;
  }

  /**
   * Convert bcd value to integer; 0x00..0x99 to 0..99.
   * @return integer.
   */
  operator uint8_t()
  {
    uint8_t high = (m_value & 0xf0);
    uint8_t low = (m_value & 0x0f);
    return ((high >> 1) + (high >> 3) + low);
  }

private:
  uint8_t m_value;
} __attribute__((packed));


#endif
