/**
 * @file Board.h
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

#ifndef BOARD_H
#define BOARD_H

#if defined(ARDUINO_AVR_UNO)
/**
 * Arduino Uno board pins and definitions.
 *
 * @section Board
 * @code
 *                         Arduino Uno
 *                  -----              -------
 *                +-|(o)|--------------| USB |---+
 *                | |   |              |     |   |
 *                | -----              |     |   |
 *                |                    -------   |
 *                |                              |
 *                |                            []| SCL
 *                |                            []| SDA
 *                |                            []| AREF
 *                |                            []| GND
 *             NC |[]                          []| D13/SCK/LED
 *          IOREF |[]                          []| D12/MISO
 *          RESET |[]                          []| D11/MOSI/PWM5
 *            3V3 |[]                          []| D10/SS/PWM4
 *             5V |[]                          []| D9/PWM3
 *            GND |[]                          []| D8
 *            GND |[]                            |
 *            Vin |[]                          []| D7
 *                |                            []| D6/PWM2
 *         A0/D14 |[]                          []| D5/PWM1
 *         A1/D15 |[]                          []| D4
 *         A2/D16 |[]                          []| D3/EXT1/PWM0
 *         A3/D17 |[]                          []| D2/EXT0
 *     SDA/A4/D18 |[]           ICSP           []| D1/TX
 *     SCL/A5/D19 |[]           o-o-o*         []| D0/RX
 *                 \            o-o-o           /
 *                  +--------------------------+
 * @endcode
 */
namespace BOARD {
  /**
   * Board pin values are constructed from port control register
   * address (msb, bit 15..4) and pin bit position in control register
   * (lsb, bit 3..0). This allows the pin values to be written
   * directly in hexadecimal format.
   */
  enum pin_t {
    D0 = 0x290,
    D1 = 0x291,
    D2 = 0x292,
    D3 = 0x293,
    D4 = 0x294,
    D5 = 0x295,
    D6 = 0x296,
    D7 = 0x297,
    D8 = 0x230,
    D9 = 0x231,
    D10 = 0x232,
    D11 = 0x233,
    D12 = 0x234,
    D13 = 0x235,
    D14 = 0x260,
    D15 = 0x261,
    D16 = 0x262,
    D17 = 0x263,
    D18 = 0x264,
    D19 = 0x265,
    D20 = 0x266,
    D21 = 0x267
  };
};
#else
#error Board.h: unknown board
#endif
#endif
