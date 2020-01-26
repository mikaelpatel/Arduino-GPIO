/**
 * @file GPIO.h
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

#ifndef IGPIO_H
#define IGPIO_H

#include <GPIO.h>

/**
 * A non-templated pure virtual interface base class for the processor-specific
 * General Purpose Digital I/O pin template classes. Those classes areighly
 * optimized pin access. The PIN address is a bit pointer to the port control
 * register. See Hardware/AVR/Board.h for details.
 * 
 * This base class allows GPIO objects to be passed as parameters to other
 * non-templated classes and functions.
 */

class IGPIO {
   public:
    /**
     * Default constructor
     */
    IGPIO(){};

    /**
     * Virtual destructor
     */
    virtual ~IGPIO(){};

    /**
     * Test if another IGPIO object uses the same pin.
     */
    inline bool operator==(IGPIO &that) const { return pin() == that.pin(); }

    /**
     * Get the assigned pin.
     */
    virtual unsigned int pin() const = 0;

    /**
     * Set pin to input mode.
     */
    virtual void input() const = 0;

    /**
     * Used with input() to activate internal pullup resistor on
     * input pin.
     */
    virtual void pullup() const = 0;

    /**
     * Set pin to output mode.
     */
    virtual void output() const = 0;

    /**
     * Open-drain pin. Use input() for high and output() for low.
     */
    virtual void open_drain() const = 0;

    /**
     * Return current pin state.
     * @return state.
     */
    virtual bool read() const = 0;

    /**
     * Return current pin state. Shorthand for read().
     * @return state.
     */
    virtual operator bool() const = 0;

    /**
     * Set pin low(0). Shorthand for write(LOW).
     */
    virtual void low() const = 0;

    /**
     * Set pin high(1). Shorthand for write(HIGH).
     */
    virtual void high() const = 0;

    /**
     * Toggle pin state. Shorthand for write(!read()).
     */
    virtual void toggle() const = 0;

    /**
     * Set pin to given state. Non-zero value will set the pin HIGH(1),
     * and zero value will set the pin LOW(0).
     * @param[in] value to set pin.
     */
    virtual void write(int value) const = 0;

    /**
     * Set pin to given state. Non-zero value will set the pin HIGH(1),
     * and zero value will set the pin LOW(0). Shorthand for write(value).
     * @param[in] value to set pin.
     */
    virtual void operator=(int value) const = 0;

    /**
     * Generate pulse with given width in micro-seconds. Interrupts
     * are disabled while generating the pulse.
     * @param[in] width in micro-seconds.
     */
    virtual void pulse(uint16_t width) const = 0;

    /**
     * Detect pulse and return width in micro-seconds.
     * @return width in micro-seconds.
     */
    virtual int pulse() const = 0;
};


template<BOARD::pin_t PIN>
class VGPIO : public IGPIO, public GPIO<PIN> {
  public:
    inline bool operator==(IGPIO &that) const { return pin() == that.pin(); }
    unsigned int pin() const { return GPIO<PIN>::pin(); }
    void input() const { GPIO<PIN>::input(); }
    void pullup() const { GPIO<PIN>::pullup(); }
    void output() const { GPIO<PIN>::output(); } 
    void open_drain() const { GPIO<PIN>::open_drain(); }
    bool read() const { return GPIO<PIN>::read(); }
    operator bool() const { return GPIO<PIN>::read(); }
    void low() const { GPIO<PIN>::low(); }
    void high() const { GPIO<PIN>::high(); }
    void toggle() const { GPIO<PIN>::toggle(); }
    void write(int value) const  { GPIO<PIN>::write(value); };
    void operator=(int value) const  { GPIO<PIN>::write(value); }
    void pulse(uint16_t width) const { GPIO<PIN>::pulse(width); }
    int pulse() const { return GPIO<PIN>::pulse(); }

};

#endif