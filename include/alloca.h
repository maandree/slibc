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
 * 
 * @since  Always.
 */
void* alloca(size_t)
  __GCC_ONLY(__attribute__((__warn_unused_result__)));
#if defined(__GNUC__)
# define alloca(size)  __builtin_alloca(size)
#endif


#if defined(__PLAN9_SOURCE)
/**
 * Check for execution stack overflow. If the stack of
 * overflow, or will overflow, the program shall abort.
 * 
 * It is possible that the process is killed by SIGSEGV
 * instead of aborting.
 * 
 * This is a Plan 9 from Bell Labs extension.
 * 
 * @etymology  I (need) addition (stack) space.
 * 
 * @param  n  The number of bytes the stack will grow by.
 *            0 can be used to check for a current stack
 *            overflow. Must be non-negative.
 * 
 * @since  Always.
 */
void (needstack)(int);
# if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#  define needstack(n)  __needstack(n, __FILE__, __LINE__, __func__)
# else
#  define needstack(n)  __needstack(n, __FILE__, __LINE__, NULL)
# endif
#endif


/**
 * This function is called if the `needstack` macro is called.
 * It enhances the `needstack` function with detail on where
 * the program failed.
 * 
 * You should not use this function directly.
 * 
 * @param  n     The number of bytes the stack will grow by. 0 can be used
 *               to check for a current stack overflow. Must be non-negative.
 * @param  file  The filename of the source cose whence the check was made.
 * @param  line  The line in the source code whence the check was made.
 * @param  func  The function in the source code whence the check was made,
 *               `NULL` if unknown (C99 is required.)
 */
void __needstack(int, const char*, int, const char*);



#endif
#endif

