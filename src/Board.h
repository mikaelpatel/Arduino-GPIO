/**
 * @file Board.h
 * @version 1.2
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

/**
 * Board pin values are constructed from port control register
 * address (msb, bit 15..4) and pin bit position in control register
 * (lsb, bit 3..0). This allows the pin values to be written
 * directly in hexadecimal format.
 */
#if defined(ARDUINO_AVR_UNO)						\
 || defined(ARDUINO_AVR_DUEMILANOVE)					\
 || defined(ARDUINO_AVR_NANO)						\
 || defined(ARDUINO_AVR_MINI)						\
 || defined(ARDUINO_AVR_ETHERNET)					\
 || defined(ARDUINO_AVR_FIO)						\
 || defined(ARDUINO_AVR_BT)						\
 || defined(ARDUINO_AVR_LILYPAD)					\
 || defined(ARDUINO_AVR_PRO)						\
 || defined(ARDUINO_AVR_UNO_WIFI_DEV_ED)
class BOARD {
public:
  enum pin_t {
    D0 = 0x290,			//!< PIND:0
    D1 = 0x291,			//!< PIND:1
    D2 = 0x292,			//!< PIND:2
    D3 = 0x293,			//!< PIND:3
    D4 = 0x294,			//!< PIND:4
    D5 = 0x295,			//!< PIND:5
    D6 = 0x296,			//!< PIND:6
    D7 = 0x297,			//!< PIND:7

    D8 = 0x230,			//!< PINB:0
    D9 = 0x231,			//!< PINB:1
    D10 = 0x232,		//!< PINB:2, SS
    D11 = 0x233,		//!< PINB:3, MOSI, ICSP.4
    D12 = 0x234,		//!< PINB:4, MISO, ICSP.1
    D13 = 0x235,		//!< PINB:5, SCK, ICSP.3

    D14 = 0x260,		//!< PINC:0, A0
    D15 = 0x261,		//!< PINC:1, A1
    D16 = 0x262,		//!< PINC:2, A2
    D17 = 0x263,		//!< PINC:3, A3
    D18 = 0x264,		//!< PINC:4, A4, SDA
    D19 = 0x265			//!< PINC:5, A5, SCL
  };
};

#elif defined(ARDUINO_AVR_YUN)						\
 ||   defined(ARDUINO_AVR_LEONARDO)					\
 ||   defined(ARDUINO_AVR_LEONARDO_ETH)					\
 ||   defined(ARDUINO_AVR_MICRO)					\
 ||   defined(ARDUINO_AVR_ESPLORA)					\
 ||   defined(ARDUINO_AVR_LILYPAD_USB)					\
 ||   defined(ARDUINO_AVR_ROBOT_CONTROL)				\
 ||   defined(ARDUINO_AVR_ROBOT_MOTOR)
class BOARD {
public:
  enum pin_t {
    D0 = 0x292,			//!< PIND:2
    D1 = 0x293,			//!< PIND:3
    D2 = 0x291,			//!< PIND:1, SDA
    D3 = 0x290,			//!< PIND:0, SCL
    D4 = 0x294,			//!< PIND:4
    D5 = 0x266,			//!< PINC:6
    D6 = 0x297,			//!< PIND:7
    D7 = 0x2c6,			//!< PINE:6

    D8 = 0x234,			//!< PINB:4
    D9 = 0x235,			//!< PINB:5
    D10 = 0x236,		//!< PINB:6
    D11 = 0x237,		//!< PINB:7
    D12 = 0x296,		//!< PIND:6
    D13 = 0x267,		//!< PINC:7

    D14 = 0x2f7,		//!< PINF:7, A0
    D15 = 0x2f6,		//!< PINF:6, A1
    D16 = 0x2f5,		//!< PINF:5, A2
    D17 = 0x2f4,		//!< PINF:4, A3
    D18 = 0x2f1,		//!< PINF:1, A4
    D19 = 0x2f0,		//!< PINF:0, A5

    D20 = 0x233,		//!< PINB:3, MISO, ICSP.1
    D21 = 0x231,		//!< PINB:1, SCK, ICSP.3
    D22 = 0x232,		//!< PINB:2, MOSI, ICSP.4
    D23 = 0x230			//!< PINB:0, SS, RXLED
  };
};

#elif defined(ARDUINO_attiny)
#if   defined(__AVR_ATtiny25__)						\
 ||   defined(__AVR_ATtiny45__)						\
 ||   defined(__AVR_ATtiny85__)
class BOARD {
public:
  enum pin_t {
    D0 = 0x360,			//!< PINB:0,
    D1 = 0x361,			//!< PINB:1,
    D2 = 0x362,			//!< PINB:2, A1
    D3 = 0x363,			//!< PINB:3, A3
    D4 = 0x364,			//!< PINB:4, A2
    D5 = 0x365			//!< PINB:5, A0
  };
};
#elif defined(__AVR_ATtiny24__)						\
 ||   defined(__AVR_ATtiny44__)						\
 ||   defined(__AVR_ATtiny84__)
class BOARD {
public:
  enum pin_t {
    D0 = 0x390,			//!< PINA:0, A0
    D1 = 0x391,			//!< PINA:1, A1
    D2 = 0x392,			//!< PINA:2, A2
    D3 = 0x393,			//!< PINA:3, A3
    D4 = 0x394,			//!< PINA:4, A4
    D5 = 0x395,			//!< PINA:5, A5
    D6 = 0x396,			//!< PINA:6, A6
    D7 = 0x397,			//!< PINA:7, A7
    D8 = 0x362,			//!< PINB:2
    D9 = 0x361,			//!< PINB:1
    D10 = 0x360			//!< PINB:0
  };
};
#else
#error Board.h: attiny variant not supported
#endif

#else
#error Board.h: arduino board not supported
#endif
#endif
