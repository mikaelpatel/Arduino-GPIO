/**
 * @file Hardware/SAM/Board.h
 * @version 1.1
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

#ifndef HARDWARE_SAM_BOARD_H
#define HARDWARE_SAM_BOARD_H

/**
 * Board pin values are constructed from port control register index
 * and pin bit position.
 * @param[in] index control register index.
 * @param[in] pin pin bit position in control register.
 */
#define GPIO_PIN(index,pin) (((index) << 8) | (pin))

/**
 * Return port control register index from board pin value.
 * @return io port address
 */
#define GPIO_REG(pin) ((pin) >> 8)

/**
 * Return pin mask from board pin value.
 * @return pin mask
 */
#define GPIO_MASK(pin) (1U << ((pin) & 0xff))

#if defined(__SAM3X8E__)
/**
 * GPIO digital pin symbols for SAM3X8E based boards.
 * @section Board
 * @code
 *                       Arduino Due
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
 *        A12 |[]                                []| D20
 *        A13 |[]                                []| D21
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
    D0 = GPIO_PIN(0,8),			//!<PIOA:8/RX
    D1 = GPIO_PIN(0,9),			//!<PIOA:9/TX
    D2 = GPIO_PIN(1,25),		//!<PIOB:25
    D3 = GPIO_PIN(2,28),		//!<PIOC:28
    D4 = GPIO_PIN(2,26),		//!<PIOC:26
    D5 = GPIO_PIN(2,25),		//!<PIOC:25
    D6 = GPIO_PIN(2,24),		//!<PIOC:24
    D7 = GPIO_PIN(2,23),		//!<PIOC:23

    D8 = GPIO_PIN(2,22),		//!<PIOC:22
    D9 = GPIO_PIN(2,21),		//!<PIOC:21
    D10 = GPIO_PIN(2,29),		//!<PIOC:29
    D11 = GPIO_PIN(3,7),		//!<PIOD:7
    D12 = GPIO_PIN(3,8),		//!<PIOD:8
    D13 = GPIO_PIN(1,27),		//!<PIOB:27

    D14 = GPIO_PIN(3,4),		//!<PIOD:4
    D15 = GPIO_PIN(3,5),		//!<PIOD:5
    D16 = GPIO_PIN(0,13),		//!<PIOA:13
    D17 = GPIO_PIN(0,12),		//!<PIOA:12
    D18 = GPIO_PIN(0,11),		//!<PIOA:11
    D19 = GPIO_PIN(0,10),		//!<PIOA:10
    D20 = GPIO_PIN(1,12),		//!<PIOB:12
    D21 = GPIO_PIN(1,13),		//!<PIOB:13

    D22 = GPIO_PIN(1,26),		//!<PIOB:26
    D23 = GPIO_PIN(0,14),		//!<PIOA:14
    D24 = GPIO_PIN(0,15),		//!<PIOA:16
    D25 = GPIO_PIN(3,0),		//!<PIOD:0
    D26 = GPIO_PIN(3,1),		//!<PIOD:1
    D27 = GPIO_PIN(3,2),		//!<PIOD:2
    D28 = GPIO_PIN(3,3),		//!<PIOD:3
    D29 = GPIO_PIN(3,6),		//!<PIOD:6
    D30 = GPIO_PIN(3,9),		//!<PIOD:9
    D31 = GPIO_PIN(0,7),		//!<PIOA:7
    D32 = GPIO_PIN(3,10),		//!<PIOD:10
    D33 = GPIO_PIN(2,1),		//!<PIOC:1
    D34 = GPIO_PIN(2,2),		//!<PIOC:2
    D35 = GPIO_PIN(2,3),		//!<PIOC:3
    D36 = GPIO_PIN(2,4),		//!<PIOC:4
    D37 = GPIO_PIN(2,5),		//!<PIOC:5
    D38 = GPIO_PIN(2,6),		//!<PIOC:6
    D39 = GPIO_PIN(2,7),		//!<PIOC:7
    D40 = GPIO_PIN(2,8),		//!<PIOC:8
    D41 = GPIO_PIN(2,9),		//!<PIOC:9
    D42 = GPIO_PIN(0,19),		//!<PIOA:19
    D43 = GPIO_PIN(0,20),		//!<PIOA:20
    D44 = GPIO_PIN(2,19),		//!<PIOC:19
    D45 = GPIO_PIN(2,18),		//!<PIOC:18
    D46 = GPIO_PIN(2,17),		//!<PIOC:17
    D47 = GPIO_PIN(2,16),		//!<PIOC:16
    D48 = GPIO_PIN(2,15),		//!<PIOC:15
    D49 = GPIO_PIN(2,14),		//!<PIOC:14
    D50 = GPIO_PIN(2,13),		//!<PIOC:13
    D51 = GPIO_PIN(2,12),		//!<PIOC:12
    D52 = GPIO_PIN(1,21),		//!<PIOB:21
    D53 = GPIO_PIN(1,14)		//!<PIOB:14
  };
};
#else
#error Board.h: sam mcu not supported
#endif
#endif
