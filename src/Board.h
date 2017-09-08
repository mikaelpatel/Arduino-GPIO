/**
 * @file Board.h
 * @version 1.3
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
 * (lsb, bit 3..0). This allows the pin values to be written directly
 * in hexadecimal format and allows compile-time optimisation in GPIO
 * template class.
 */
#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__)
/**
 * GPIO digital pin symbols for ATmega168/ATmega328P based boards.
 * @section Board
 * @code
 *                     Arduino Uno
 *              -----              -------
 *            +-|(o)|--------------| USB |---+
 *            | |   |              |     |   |
 *            | -----              |     |   |
 *            |                    -------   |
 *            |                              |
 *            |                            []| SCL
 *            |                            []| SDA
 *            |                            []| AREF
 *            |                            []| GND
 *         NC |[]                          []| D13/SCK/LED
 *      IOREF |[]                          []| D12/MISO
 *      RESET |[]                          []| D11/MOSI/PWM5
 *        3V3 |[]                          []| D10/SS/PWM4
 *         5V |[]                          []| D9/PWM3
 *        GND |[]                          []| D8
 *        GND |[]                            |
 *        Vin |[]                          []| D7
 *            |                            []| D6/PWM2
 *     A0/D14 |[]                          []| D5/PWM1
 *     A1/D15 |[]                          []| D4
 *     A2/D16 |[]                          []| D3/EXT1/PWM0
 *     A3/D17 |[]                          []| D2/EXT0
 * SDA/A4/D18 |[]           ICSP           []| D1/TX
 * SCL/A5/D19 |[]          [o-o-*]         []| D0/RX
 *             \           [o-o-o]          /
 *              +--------------------------+
 * @endcode
 */
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
    D19 = 0x265,		//!< PINC:5, A5, SCL

    SS = D10,			//!< Slave Select
    MOSI = D11,			//!< Master Output Slave Input
    MISO = D12,			//!< Master Input Slave Output
    SCK = D13			//!< Clock
  };
};
#elif defined(__AVR_ATmega32U4__)
/**
 * GPIO digital pin symbols for ATmega32U4 based boards.
 * @section Board
 * @code
 *                   Arduino Leonardo
 *              -----               -----
 *            +-|(o)|---------------|USB|----+
 *            | |   |               |   |    |
 *            | -----               ----|    |
 *            |                              |
 *            |                              |
 *            |                            []| SCL
 *            |                            []| SDA
 *            |                            []| AREF
 *            |                            []| GND
 *         NC |[]                          []| D13/PWM5/LED
 *      IOREF |[]                          []| D12/A7
 *      RESET |[]                          []| D11/PWM0
 *        3V3 |[]                          []| D10/PWM3/A11
 *         5V |[]                          []| D9/PWM2/A10
 *        GND |[]                          []| D8/A9
 *        GND |[]                            |
 *        Vin |[]                          []| D7
 *            |                            []| D6/PWM6/A8
 *     A0/D14 |[]                          []| D5/PWM4
 *     A1/D15 |[]                          []| D4/A6
 *     A2/D16 |[]                          []| D3/SCL/EXT0/PWM1
 *     A3/D17 |[]                          []| D2/SDA/EXT1
 *     A4/D18 |[]           ICSP           []| D1/TX1/EXT3
 *     A5/D19 |[]          [o-o-*]         []| D0/RX1/EXT2
 *             \           [o-o-o]          /
 *              +--------------------------+
 * @endcode
 * @section ICSP
 * The SPI pins (on ICSP) are also numbered as digital pins. SPI SS
 * is used for the RX LED.
 * @code
 *                          ICSP
 *                         +----+
 *                MISO/D20 |*  o| VCC
 *                 SCK/D21 |o  o| D22/MOSI
 *                 RESET   |o  o| GND
 *                         +----+
 * @endcode
 */
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
    D23 = 0x230,		//!< PINB:0, SS, RXLED

    SS = D23,			//!< Slave Select
    MOSI = D22,			//!< Master Output Slave Input
    MISO = D20,			//!< Master Input Slave Output
    SCK = D21			//!< Clock
  };
};
#elif defined(ARDUINO_attiny)
#if   defined(__AVR_ATtiny24__)						\
 ||   defined(__AVR_ATtiny44__)						\
 ||   defined(__AVR_ATtiny84__)
/**
 * GPIO digital pin symbols for ATtinyX4 based boards.
 * @section Circuit
 * @code
 *                       ATinyX4
 *                     +----U----+
 * (VCC)-------------1-|VCC   GND|-14------------(GND)
 * (D8)--------------2-|PB0   PA0|-13----------(D0/A0)
 * (D9)--------------3-|PB1   PA1|-12----------(D1/A1)
 * (/RESET)----------4-|PB3   PA2|-11----------(D2/A2)
 * (EXT0/D10)--------5-|PB2   PA3|-10-------(D3/A3/SS)
 * (LED/D7/A7)-------6-|PA7   PA4|-9---(D4/A4/SCL/SCK)
 * (MISO/SDA/D6/A6)--7-|PA6   PA5|-8------(D5/A5/MOSI)
 *                     +---------+
 * @endcode
 */
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
#elif defined(__AVR_ATtiny25__)						\
 ||   defined(__AVR_ATtiny45__)						\
 ||   defined(__AVR_ATtiny85__)
/**
 * GPIO digital pin symbols for ATtinyX5 based boards.
 * @section Circuit
 * @code
 *                       ATinyX5
 *                     +----U----+
 * (/RESET)----------1-|PB5   VCC|-8-----------------(VCC)
 * (D3/A3)-----------2-|PB3   PB2|-7--(D2/A1/EXT0/SCL/SCK)
 * (LED/D4/A2)-------3-|PB4   PB1|-6-------------(D1/MOSI)
 * (GND)-------------4-|GND   PB0|-5---------(D0/SDA/MISO)
 *                     +---------+
 * @endcode
 */
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
#else
#error Board.h: attiny variant not supported
#endif

#else
#error Board.h: avr mcu not supported
#endif
#endif
