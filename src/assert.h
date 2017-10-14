/**
 * @file assert.h
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

#ifndef ASSERT_H
#define ASSERT_H

/**
 * Trace support macro. Used in the form:
 * @code
 *   TRACE(expr)
 * @endcode
 * Prints message with expression, executes and prints value.
 * @param[in] expr expression to execute and print.
 */
#if defined(NDEBUG)
#define TRACE(expr) expr
#else
#define TRACE(expr)							\
  do {									\
    Serial.print(F(#expr "="));						\
    Serial.println(expr);						\
    Serial.flush();							\
  } while (0)
#endif

/**
 * Assert support macro. Used in the form:
 * @code
 *   ASSERT(expr)
 * @endcode
 * Checks that the expression is true, otherwise prints line number,
 * and assert message with expression, and stops execution.
 * @param[in] expr expression to execute and check.
 */
#if defined(NDEBUG)
#define ASSERT(expr) expr
#else
#define ASSERT(expr)							\
  do {									\
    if (!(expr)) {							\
      Serial.print(__LINE__);						\
      Serial.println(F(":assert:" #expr));				\
      Serial.flush();							\
      exit(0);								\
    }									\
  } while (0)
#endif

#endif
