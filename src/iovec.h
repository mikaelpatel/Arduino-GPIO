/**
 * @file iovec.h
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

#ifndef IOVEC_H
#define IOVEC_H

/**
 * Buffer structure for scatter/gather.
 */
struct iovec_t {
  void* buf;			//!< Buffer pointer.
  size_t size;			//!< Size of buffer in bytes.
};

/**
 * Return total size of null terminated io buffer vector.
 * @param[in] vec io vector pointer
 * @return size.
 */
inline size_t iovec_size(const iovec_t* vec) __attribute__((always_inline));
inline size_t iovec_size(const iovec_t* vec)
{
  size_t len = 0;
  for (const iovec_t* vp = vec; vp->buf != NULL; vp++)
    len += vp->size;
  return (len);
}

/**
 * Set next io-vector buffer. Used in to form:
 * @code
 * iovec_t vec[N];
 * iovec_t* vp = vec;
 * iovec_arg(vp, buf, size);
 * ..
 * iovec_end(vp);
 * @endcode
 * @param[in,out] vp io vector pointer
 * @param[in] buf buffer.
 * @param[in] size number of bytes.
 */
inline void iovec_arg(iovec_t* &vp, const void* buf, size_t size)
  __attribute__((always_inline));
inline void iovec_arg(iovec_t* &vp, const void* buf, size_t size)
{
  vp->buf = (void*) buf;
  vp->size = size;
  vp++;
}

/**
 * Mark end of io-vector buffer at given index. Used in the form:
 * @code
 * iovec_t vec[N];
 * iovec_t* vp = vec;
 * iovec_arg(vp, buf, size);
 * ..
 * iovec_end(vp);
 * @endcode
 * @param[in,out] vp io vector.
 */
inline void iovec_end(iovec_t* &vp) __attribute__((always_inline));
inline void iovec_end(iovec_t* &vp)
{
  vp->buf = 0;
  vp->size = 0;
}
#endif
