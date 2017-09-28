/**
 * @file Board.h
 * @version 1.6
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

#ifndef HARDWARE_AVR_BOARD_H
#define HARDWARE_AVR_BOARD_H

/**
 * Board pin values are bit-pointers and constructed from port control
 * register address and pin bit position.
 * @param[in] port control register address.
 * @param[in] pin pin bit position in control register.
 */
#define GPIO_PIN(port,pin) (((port) << 4) | (pin))

/**
 * Return port control register address from board pin value.
 * @return io port address
 */
#define GPIO_REG(pin) ((pin) >> 4)

/**
 * Return pin mask from board pin value.
 * @return pin mask
 */
#define GPIO_MASK(pin) _BV((pin) & 0xf)

/** Maximum port control register address for atomic bit instructions. */
#define GPIO_ATOMIC_MAX GPIO_PIN(0x40,0)

/**
 * Forces given expression to be atomic. Higher port addresses
 * cannot be accessed with a single instruction and require
 * disabling of interrupts to become atomic.
 * @param[in] expr expression to be atomic.
 */
#define GPIO_ATOMIC(expr)					\
  do {								\
    if (PIN < GPIO_ATOMIC_MAX) {				\
      expr;							\
    }								\
    else {							\
      uint8_t sreg = SREG;					\
      __asm__ __volatile__("cli" ::: "memory");			\
      expr;							\
      SREG = sreg;						\
      __asm__ __volatile__("" ::: "memory");			\
    }								\
  } while (0)

#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__)
/**
 * GPIO digital pin symbols for ATmega168/ATmega328P based boards.
 * @section Board
 * @code
 *                       Arduino Uno
 *              -----                    -------
 *            +-|(o)|--------------------| USB |---+
 *            | |   |                    |     |   |
 *            | -----                    |     |   |
 *            |                          -------   |
 *            |                                    |
 *            |                                  []| SCL
 *            |                                  []| SDA
 *            |                                  []| AREF
 *            |                                  []| GND
 *         NC |[]                                []| D13/SCK
 *      IOREF |[]                                []| D12/MISO
 *      RESET |[]                                []| D11/MOSI
 *        3V3 |[]                                []| D10/SS
 *         5V |[]                                []| D9
 *        GND |[]                                []| D8
 *        GND |[]                                  |
 *        Vin |[]                                []| D7
 *            |                                  []| D6
 *     A0/D14 |[]                                []| D5
 *     A1/D15 |[]                                []| D4
 *     A2/D16 |[]                                []| D3
 *     A3/D17 |[]                                []| D2
 * SDA/A4/D18 |[]                                []| D1
 * SCL/A5/D19 |[]              ICSP              []| D0
 *            |               [o-o-*]      +-------+
 *             \              [o-o-o]     /
 *              +------------------------+
 * @endcode
 */
class BOARD {
public:
  enum pin_t {
    D0 = GPIO_PIN(0x29,0),	//!< PIND:0
    D1 = GPIO_PIN(0x29,1),	//!< PIND:1
    D2 = GPIO_PIN(0x29,2),	//!< PIND:2
    D3 = GPIO_PIN(0x29,3),	//!< PIND:3
    D4 = GPIO_PIN(0x29,4),	//!< PIND:4
    D5 = GPIO_PIN(0x29,5),	//!< PIND:5
    D6 = GPIO_PIN(0x29,6),	//!< PIND:6
    D7 = GPIO_PIN(0x29,7),	//!< PIND:7

    D8 = GPIO_PIN(0x23,0),	//!< PINB:0
    D9 = GPIO_PIN(0x23,1),	//!< PINB:1
    D10 = GPIO_PIN(0x23,2),	//!< PINB:2/SS
    D11 = GPIO_PIN(0x23,3),	//!< PINB:3/MOSI/ICSP.4
    D12 = GPIO_PIN(0x23,4),	//!< PINB:4/MISO/ICSP.1
    D13 = GPIO_PIN(0x23,5),	//!< PINB:5/SCK/ICSP.3

    D14 = GPIO_PIN(0x26,0),	//!< PINC:0/A0
    D15 = GPIO_PIN(0x26,1),	//!< PINC:1/A1
    D16 = GPIO_PIN(0x26,2),	//!< PINC:2/A2
    D17 = GPIO_PIN(0x26,3),	//!< PINC:3/A3
    D18 = GPIO_PIN(0x26,4),	//!< PINC:4/A4/SDA
    D19 = GPIO_PIN(0x26,5),	//!< PINC:5/A5/SCL

    SS = D10,			//!< SPI Slave Select
    MOSI = D11,			//!< SPI Master Output Slave Input
    MISO = D12,			//!< SPI Master Input Slave Output
    SCK = D13,			//!< SPI Clock

    SDA = D18,			//!< TWI Data
    SCL = D19			//!< TWI Clock
  };
};
#elif defined(__AVR_ATmega32U4__)
/**
 * GPIO digital pin symbols for ATmega32U4 based boards.
 * @section Board
 * @code
 *                     Arduino Leonardo
 *              -----                     -----
 *            +-|(o)|---------------------|USB|----+
 *            | |   |                     |   |    |
 *            | -----                     -----    |
 *            |                                    |
 *            |                                    |
 *            |                                  []| SCL
 *            |                                  []| SDA
 *            |                                  []| AREF
 *            |                                  []| GND
 *         NC |[]                                []| D13/
 *      IOREF |[]                                []| D12/A7
 *      RESET |[]                                []| D11
 *        3V3 |[]                                []| D10
 *         5V |[]                                []| D9
 *        GND |[]                                []| D8
 *        GND |[]                                  |
 *        Vin |[]                                []| D7
 *            |                                  []| D6
 *     A0/D14 |[]                                []| D5
 *     A1/D15 |[]                                []| D4
 *     A2/D16 |[]                                []| D3/SCL
 *     A3/D17 |[]                                []| D2/SDA
 *     A4/D18 |[]                                []| D1
 *     A5/D19 |[]              ICSP              []| D0
              |               [o-o-*]      +-------+
 *             \              [o-o-o]     /
 *              +------------------------+
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
    D0 = GPIO_PIN(0x29,2),	//!< PIND:2
    D1 = GPIO_PIN(0x29,3),	//!< PIND:3
    D2 = GPIO_PIN(0x29,1),	//!< PIND:1/SDA
    D3 = GPIO_PIN(0x29,0),	//!< PIND:0/SCL
    D4 = GPIO_PIN(0x29,4),	//!< PIND:4
    D5 = GPIO_PIN(0x26,6),	//!< PINC:6
    D6 = GPIO_PIN(0x29,7),	//!< PIND:7
    D7 = GPIO_PIN(0x2c,6),	//!< PINE:6

    D8 = GPIO_PIN(0x23,4),	//!< PINB:4
    D9 = GPIO_PIN(0x23,5),	//!< PINB:5
    D10 = GPIO_PIN(0x23,6),	//!< PINB:6
    D11 = GPIO_PIN(0x23,7),	//!< PINB:7
    D12 = GPIO_PIN(0x29,6),	//!< PIND:6
    D13 = GPIO_PIN(0x26,7),	//!< PINC:7

    D14 = GPIO_PIN(0x2f,7),	//!< PINF:7/A0
    D15 = GPIO_PIN(0x2f,6),	//!< PINF:6/A1
    D16 = GPIO_PIN(0x2f,5),	//!< PINF:5/A2
    D17 = GPIO_PIN(0x2f,4),	//!< PINF:4/A3
    D18 = GPIO_PIN(0x2f,1),	//!< PINF:1/A4
    D19 = GPIO_PIN(0x2f,0),	//!< PINF:0/A5

    D20 = GPIO_PIN(0x23,0),	//!< PINB:0/SS/RXLED
    D21 = GPIO_PIN(0x23,2),	//!< PINB:2/MOSI/ICSP.4
    D22 = GPIO_PIN(0x23,3),	//!< PINB:3/MISO/ICSP.1
    D23 = GPIO_PIN(0x23,1),	//!< PINB:1/SCK/ICSP.3

    SS = D20,			//!< SPI Slave Select
    MOSI = D22,			//!< SPI Master Output Slave Input
    MISO = D20,			//!< SPI Master Input Slave Output
    SCK = D21,			//!< SPI Clock

    SDA = D2,			//!< TWI Data
    SCL = D3			//!< TWI Clock
  };
};
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
/**
 * GPIO digital pin symbols for ATmega1280/ATmega2560 based boards.
 * @section Board
 * @code
 *                       Arduino Mega
 *              -----                    -------
 *            +-|(o)|--------------------| USB |---+
 *            | |   |                    |     |   |
 *            | -----                    |     |   |
 *            |                          -------   |
 *            |                                    |
 *            |                                  []| SCL
 *            |                                  []| SDA
 *            |                                  []| AREF
 *            |                                  []| GND
 *         NC |[]                                []| D13
 *      IOREF |[]                                []| D12
 *      RESET |[]                                []| D11
 *        3V3 |[]                                []| D10
 *         5V |[]                                []| D9
 *        GND |[]                                []| D8
 *        GND |[]                                  |
 *        Vin |[]                                []| D7
 *            |                                  []| D6
 *         A0 |[]                                []| D5
 *         A1 |[]                                []| D4
 *         A2 |[]                                []| D3
 *         A3 |[]                                []| D2
 *         A4 |[]              ICSP              []| D1
 *         A5 |[]             [o-o-*]            []| D0
 *         A6 |[]             [o-o-o]              |
 *         A7 |[]                                []| D14
 *            |                                  []| D15
 *         A8 |[]                                []| D16
 *         A9 |[]                                []| D17
 *        A10 |[]                                []| D18
 *        A11 |[]                                []| D19
 *        A12 |[]                                []| D20/SDA
 *        A13 |[]                                []| D21/SCL
 *        A14 |[]                                  |
 *        A15 |[]52                    30      22  |
 *        GND |[][][][][][][][][][][][][][][][][][]| 5V
 *        GND |[][][][][][][][][][][][][][][][][][]| 5V
 *             \ 53                    31 /
 *              +------------------------+
 * @endcode
 */
class BOARD {
public:
  enum pin_t {
    D0 = GPIO_PIN(0x2c,0),	//!< PINE:0
    D1 = GPIO_PIN(0x2c,1),	//!< PINE:1
    D2 = GPIO_PIN(0x2c,4),	//!< PINE:4
    D3 = GPIO_PIN(0x2c,5),	//!< PINE:5
    D4 = GPIO_PIN(0x32,5),	//!< PING:5
    D5 = GPIO_PIN(0x2c,3),	//!< PINE:3
    D6 = GPIO_PIN(0x100,3),	//!< PINH:3
    D7 = GPIO_PIN(0x100,4),	//!< PINH:4

    D8 = GPIO_PIN(0x100,5),	//!< PINH:5
    D9 = GPIO_PIN(0x100,6),	//!< PINH:6
    D10 = GPIO_PIN(0x23,4),	//!< PINB:4
    D11 = GPIO_PIN(0x23,5),	//!< PINB:5
    D12 = GPIO_PIN(0x23,6),	//!< PINB:6
    D13 = GPIO_PIN(0x23,7),	//!< PINB:7

    D14 = GPIO_PIN(0x103,1),	//!< PINJ:1
    D15 = GPIO_PIN(0x103,0),	//!< PINJ:0
    D16 = GPIO_PIN(0x100,1),	//!< PINH:1
    D17 = GPIO_PIN(0x100,0),	//!< PINH:0
    D18 = GPIO_PIN(0x29,3),	//!< PIND:3
    D19 = GPIO_PIN(0x29,2),	//!< PIND:2
    D20 = GPIO_PIN(0x29,1),	//!< PIND:1
    D21 = GPIO_PIN(0x29,0),	//!< PIND:0

    D22 = GPIO_PIN(0x20,0),	//!< PINA:0
    D23 = GPIO_PIN(0x20,1),	//!< PINA:1
    D24 = GPIO_PIN(0x20,2),	//!< PINA:2
    D25 = GPIO_PIN(0x20,3),	//!< PINA:3
    D26 = GPIO_PIN(0x20,4),	//!< PINA:4
    D27 = GPIO_PIN(0x20,5),	//!< PINA:5
    D28 = GPIO_PIN(0x20,6),	//!< PINA:6
    D29 = GPIO_PIN(0x20,7),	//!< PINA:7
    D30 = GPIO_PIN(0x26,7),	//!< PINC:7
    D31 = GPIO_PIN(0x26,6),	//!< PINC:6
    D32 = GPIO_PIN(0x26,5),	//!< PINC:5
    D33 = GPIO_PIN(0x26,4),	//!< PINC:4
    D34 = GPIO_PIN(0x26,3),	//!< PINC:3
    D35 = GPIO_PIN(0x26,2),	//!< PINC:2
    D36 = GPIO_PIN(0x26,1),	//!< PINC:1
    D37 = GPIO_PIN(0x26,0),	//!< PINC:0
    D38 = GPIO_PIN(0x29,7),	//!< PIND:7
    D39 = GPIO_PIN(0x32,2),	//!< PING:2
    D40 = GPIO_PIN(0x32,1),	//!< PING:1
    D41 = GPIO_PIN(0x32,0),	//!< PING:0
    D42 = GPIO_PIN(0x109,7),	//!< PINL:7
    D43 = GPIO_PIN(0x109,6),	//!< PINL:6
    D44 = GPIO_PIN(0x109,5),	//!< PINL:5
    D45 = GPIO_PIN(0x109,4),	//!< PINL:4
    D46 = GPIO_PIN(0x109,3),	//!< PINL:3
    D47 = GPIO_PIN(0x109,2),	//!< PINL:2
    D48 = GPIO_PIN(0x109,1),	//!< PINL:1
    D49 = GPIO_PIN(0x109,0),	//!< PINL:0
    D50 = GPIO_PIN(0x23,3),	//!< PINB:3/MISO/ICSP.1
    D51 = GPIO_PIN(0x23,2),	//!< PINB:2/MOSI/ICSP.3
    D52 = GPIO_PIN(0x23,1),	//!< PINB:1/SCK/ICSP.4
    D53 = GPIO_PIN(0x23,0),	//!< PINB:0/SS

    D54 = GPIO_PIN(0x2f,0),	//!< PINF:0/A0
    D55 = GPIO_PIN(0x2f,1),	//!< PINF:1/A1
    D56 = GPIO_PIN(0x2f,2),	//!< PINF:2/A2
    D57 = GPIO_PIN(0x2f,3),	//!< PINF:3/A3
    D58 = GPIO_PIN(0x2f,4),	//!< PINF:4/A4
    D59 = GPIO_PIN(0x2f,5),	//!< PINF:5/A5
    D60 = GPIO_PIN(0x2f,6),	//!< PINF:6/A6
    D61 = GPIO_PIN(0x2f,7),	//!< PINF:7/A7

    D62 = GPIO_PIN(0x106,0),	//!< PINK:0/A8
    D63 = GPIO_PIN(0x106,1),	//!< PINK:1/A9
    D64 = GPIO_PIN(0x106,2),	//!< PINK:2/A10
    D65 = GPIO_PIN(0x106,3),	//!< PINK:3/A11
    D66 = GPIO_PIN(0x106,4),	//!< PINK:4/A12
    D67 = GPIO_PIN(0x106,5),	//!< PINK:5/A13
    D68 = GPIO_PIN(0x106,6),	//!< PINK:6/A14
    D69 = GPIO_PIN(0x106,7),	//!< PINK:7/A15

    SS = D53,			//!< SPI Slave Select
    MOSI = D51,			//!< SPI Master Output Slave Input
    MISO = D50,			//!< SPI Master Input Slave Output
    SCK = D52,			//!< SPI Clock

    SDA = D20,			//!< TWI Data
    SCL = D21			//!< TWI Clock
  };
};
#elif defined(__AVR_ATtiny24__)						\
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
 * (D10).....--------5-|PB2   PA3|-10-------(D3/A3/SS)
 * (D7/A7)-----------6-|PA7   PA4|-9---(D4/A4/SCL/SCK)
 * (MISO/SDA/D6/A6)--7-|PA6   PA5|-8------(D5/A5/MOSI)
 *                     +---------+
 * @endcode
 */
class BOARD {
public:
  enum pin_t {
    D0 = GPIO_PIN(0x39,0),	//!< PINA:0/A0
    D1 = GPIO_PIN(0x39,1),	//!< PINA:1/A1
    D2 = GPIO_PIN(0x39,2),	//!< PINA:2/A2
    D3 = GPIO_PIN(0x39,3),	//!< PINA:3/A3/SS
    D4 = GPIO_PIN(0x39,4),	//!< PINA:4/A4/SCL/SCK
    D5 = GPIO_PIN(0x39,5),	//!< PINA:5/A5/MOSI
    D6 = GPIO_PIN(0x39,6),	//!< PINA:6/A6/MISO/SDA
    D7 = GPIO_PIN(0x39,7),	//!< PINA:7/A7
    D8 = GPIO_PIN(0x36,2),	//!< PINB:2
    D9 = GPIO_PIN(0x36,1),	//!< PINB:1
    D10 = GPIO_PIN(0x36,0),	//!< PINB:0

    SS = D3,			//!< SPI Slave Select
    MOSI = D5,			//!< SPI Master Output Slave Input
    MISO = D6,			//!< SPI Master Input Slave Output
    SCK = D4			//!< SPI Clock
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
 * (D3/A3)-----------2-|PB3   PB2|-7-------(D2/A1/SCL/SCK)
 * (D4/A2)-----------3-|PB4   PB1|-6-------------(D1/MOSI)
 * (GND)-------------4-|GND   PB0|-5---------(D0/SDA/MISO)
 *                     +---------+
 * @endcode
 */
class BOARD {
public:
  enum pin_t {
    D0 = GPIO_PIN(0x36,0),	//!< PINB:0/SDA/MISO
    D1 = GPIO_PIN(0x36,1),	//!< PINB:1/MOSI
    D2 = GPIO_PIN(0x36,2),	//!< PINB:2/A1/SCL/SCK
    D3 = GPIO_PIN(0x36,3),	//!< PINB:3/A3
    D4 = GPIO_PIN(0x36,4),	//!< PINB:4/A2
    D5 = GPIO_PIN(0x36,5),	//!< PINB:5/A0

    SS = D3,			//!< SPI Slave Select
    MOSI = D1,			//!< SPI Master Output Slave Input
    MISO = D0,			//!< SPI Master Input Slave Output
    SCK = D2			//!< SPI Clock
  };
};
#else
#error Board.h: avr mcu not supported
#endif
#endif
