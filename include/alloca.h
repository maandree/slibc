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
#ifndef _ALLOCA_H
#define _ALLOCA_H
#include <slibc/version.h>
#include <slibc/features.h>
#ifndef __PORTABLE



#define __NEED_size_t
#include <bits/types.h>


/* alloca is machine- _and_ compiler-dependent, it is not
 * implemented in slibc, but in the compiler. */


/**
 * Allocation memory in the stack frame of the caller.
 * 
 * Undefined behaviour is invoked if the memory
 * cannot be allocated.
 * 
 * @etymology  (Alloca)te!
 * 
 * @param   size  The number of bytes to allocate.
 * @return        Pointer to the beginning of the allocated
 *                space. Do not free it, it will be freed
 *                automatically when the function returns.
 */
void* alloca(size_t);
#if defined(__GNUC__)
# define alloca(size)  __builtin_alloca(size)
#endif



#endif
#endif

