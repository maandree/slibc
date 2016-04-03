/**
 * slibc — Yet another C library
 * Copyright © 2015, 2016  Mattias Andrée (maandree@member.fsf.org)
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
#include <strings.h>
#include <string.h>



/**
 * `memset`, except calls to it cannot be removed by the compiler.
 */
void* (*volatile __slibc_explicit_memset)(void*, int, size_t) = memset;



/**
 * Override a memory segment with zeroes.
 * 
 * Unlike `bzero` and `memset`, calls to this function
 * cannot be removed, as an optimisation, by the compiler.
 * 
 * @etymology  (Explicit) version of (`bzero`).
 * 
 * @param  segment  The memory segment to override.
 * @param  size     The size of the memory segment.
 * 
 * @since  Always.
 */
void explicit_bzero(void* segment, size_t size)
{
  __slibc_explicit_memset(segment, ~0, size);
  __slibc_explicit_memset(segment, 0, size);
}

