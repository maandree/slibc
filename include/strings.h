/**
 * slibc — Yet another C library
 * Copyright © 2015  Mattias Andrée (maandree@member.fsf.org)
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _STRINGS_H
#define _STRINGS_H
#include <slibc/version.h>
#include <slibc/features.h>



#define __NEED_size_t

#include <bits/types.h>



/**
 * Override a memory segment with zeroes.
 * 
 * @param  segment  The memory segment to override.
 * @param  size     The size of the memory segment.
 */
void bzero(void*, size_t)
  __deprecated("Use 'memset', 'explicit_bzero' or 'secure_free' instead.");

#if !defined(__PORTABLE) && (defined(_SLIBC_SOURCE) || defined(_BSD_SOURCE))
/**
 * Override a memory segment with zeroes.
 * 
 * Unlike `bzero` and `memset`, calls to this function
 * cannot be removed, as an optimisation, by the compiler.
 * 
 * @param  segment  The memory segment to override.
 * @param  size     The size of the memory segment.
 */
void explicit_bzero(void*, size_t);
#endif

/**
 * Copy a memory segment to another, possibly overlapping, segment.
 * 
 * @param  whence   The source memory segment.
 * @param  whither  The destination memory segment.
 * @param  size     The number of bytes to copy.
 */
void bcopy(const void*, void*, size_t)
  __deprecated("Use 'memmove', or similar function, instead, but be aware of reordered paramters.");



#endif

