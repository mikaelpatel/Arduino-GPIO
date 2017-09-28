/**
 * @file Software/Serial.h
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

#ifndef SOFTWARE_SERIAL_H
#define SOFTWARE_SERIAL_H

#include "GPIO.h"

/**
 * Output only Software Serial template class using GPIO.
 * May be used with baudrates up to 250.000 bps.
 * @param[in] TX_PIN board pin for transmit signal.
 */
namespace Software {
template<BOARD::pin_t TX_PIN>
class Serial : public ::Stream {
public:
  /**
   * Construct Output only Software Serial instance with
   * given template parameters. Initiate GPIO transmit pin
   * to output mode and set default baudrate (57600 bps).
   */
  Serial() :
    m_count(((F_CPU / 57600) / 4) - 4)
  {
    m_tx.output();
    m_tx.high();
  }

  /**
   * Start the Output only Software Serial with the given
   * baudrate.
   * @param[in] baudrate in bits per second.
   */
  void begin(uint32_t baudrate)
  {
#if defined(AVR)
    m_count = ((F_CPU / baudrate) / 4) - 4;
#elif defined(SAM)
    m_count = 1000000 / baudrate;
#endif
  }

  /**
   * Check if Serial is ready (see Arduino/HardwareSerial).
   * @return true(1);
   */
  operator bool()
  {
    return (true);
  }

  /**
   * @override{Stream}
   * Write given byte to serial output with one start and stop
   * bit. Interrupts are disabled during the transmission. Returns
   * number of bytes transmitted(1).
   * @param[in] byte to transmit.
   * @return number of bytes transmitted(1).
   */
  virtual size_t write(uint8_t byte)
  {
    uint16_t data = ((0xff00 | byte) << 1);
    uint8_t bits = 10;
    noInterrupts();
    do {
      m_tx = data & 0x01;
#if defined(AVR)
      _delay_loop_2(m_count);
#elif defined(SAM)
      delayMicroseconds(m_count);
#endif
      data >>= 1;
    } while (--bits);
    interrupts();
    return (1);
  }

  /**
   * @override{Stream}
   * Returns always zero(0) as this stream is output only.
   * @return zero(0).
   */
  virtual int available()
  {
    return (0);
  }

  /**
   * @override{Stream}
   * Returns always error code(-1) as this stream is output only.
   * @return error code(-1);
   */
  virtual int peek()
  {
    return (-1);
  }

  /**
   * @override{Stream}
   * Returns always error code(-1) as this stream is output only.
   * @return error code(-1);
   */
  virtual int read()
  {
    return (-1);
  }

  /**
   * @override{Stream}
   * Output only stream.
   */
  virtual void flush()
  {
  }

protected:
  /** Asynchronous Serial Output pin. */
  GPIO<TX_PIN> m_tx;

  /** Bit delay counter for given baudrate. */
  uint16_t m_count;
};
};
#endif
