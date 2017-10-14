/**
 * @file benchmark.h
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

#ifndef BENCHMARK_H
#define BENCHMARK_H

/** Benchmark timestamp variables. */
static uint32_t _start, _baseline = 0;
static uint32_t _benchmark;

/** Benchmark support function. */
inline void noop() __attribute__((always_inline));
inline void noop() { __asm__ __volatile__("nop"); }

/**
 * Calculate and set benchmark baseline. Should be called in setup().
 */
#define BENCHMARK_BASELINE(scale)					\
  Serial.flush();							\
  _start = micros();							\
  for (int _i = 1; _i; _i--, _baseline = micros() - _start - _baseline)	\
    for (int _j = scale; _j; _j--, noop())

/**
 * Benchmark support macro. Use in the form:
 * @code
 *   BENCHMARK("description") statement
 * @endcode
 * Prints description message and time to execute the statement in
 * micro-seconds. The maximum resolution depends on micros() and is
 * typically 4 us (F_CPU is 16 MHz). Message strings are stored in
 * program memory.
 * @param[in] msg description of the benchmark.
 */
#define BENCHMARK(msg,scale)						\
  Serial.print(F(msg ": "));						\
  Serial.flush();							\
  _start = micros();							\
  for (int _i = 1; _i; _i--, _benchmark = micros() - _start - _baseline,\
	 Serial.println(_benchmark / (float) scale, 3))			\
    for (int _j = scale; _j; _j--, noop())

/**
 * Execution time measurement support macro. Use in the form:
 * @code
 *   MEASURE(expr)
 * @endcode
 * Executes given expression and prints time to execute micro-
 * seconds. The maximum resolution depends on micros() and is
 * typically 4 us (F_CPU is 16 MHz).
 * @param[in] expr expression to execute and measure.
 */
#define MEASURE(expr) BENCHMARK(#expr,1) expr

#endif
