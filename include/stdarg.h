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
#ifndef _STDARG_H
# ifndef __ONLY_va_list
#  define _STDARG_H
# endif
#include <slibc/version.h>
#include <slibc/features.h>

#if !defined(_SLIBC_SUPPRESS_WARNINGS)
# if !defined(__C89__)
#  warning "<stdargs.h> requires that C89 or newer revision is used."
# elif !defined(__C99__)
#  warning "'va_copy' was introduced to <stdargs.h> in C99."
# endif
#endif


#include <bits/stdarg.h>


/* If <bits/stdarg.h> does not define what is required,
 * fall back to compiler-builtin definitions. */



/**
 * State of variadic argument-reading.
 * 
 * @etymology  (V)ariadic (a)rguments-subsystem: argument-(list).
 * 
 * @since  Always.
 */
#ifndef __DEFINED_va_list
# define __DEFINED_va_list
typedef __builtin_va_list va_list;
#endif



#ifndef __ONLY_va_list



/**
 * Prologue to using a variadic arguments.
 * 
 * @etymology  (V)ariadic (a)rguments-subsystem: (start) of use.
 * 
 * @param  state:va_list    The state of the variadic argument-reading.
 * @param  last:identifier  The the last non-variadic argument.
 * 
 * @since  Always.
 */
#ifndef va_start
# ifndef __PORTABLE
#  define va_start(state, last)  __builtin_va_start(state, last)
# else
#  define va_start(state, last)  { __builtin_va_start(state, last)
# endif
#endif

/**
 * Epilogue to using a variadic arguments.
 * 
 * @etymology  (V)ariadic (a)rguments-subsystem: (end) of use.
 * 
 * @param  state:va_list  The state of the variadic argument-reading.
 * 
 * @since  Always.
 */
#ifndef va_end
# ifndef __PORTABLE
#  define va_end(state)  __builtin_va_end(state)
# else
#  define va_end(state)  } __builtin_va_end(state)
# endif
#endif

/**
 * Get the next variadic argument.
 * 
 * @etymology  (V)ariadic (a)rguments-subsystem: get (arg)ument.
 * 
 * @param   state:va_list    The state of the variadic argument-reading.
 * @param   type:identifier  The data type used in the called to the function,
 *                           must match exactly. Arguments smaller than `int`
 *                           are promoted in the cal, thus you must not use a
 *                           type smaller than `int`, lest bad things will happen.
 * @return  :`type`          The next argument.
 * 
 * @since  Always.
 */
#ifndef va_arg
# define va_arg(state, type)  __builtin_va_arg(state, type)
#endif

/**
 * Copy a state of variadic argument-reading.
 * 
 * @etymology  (V)ariadic (a)rguments-subsystem: (copy) list.
 * 
 * @param  destination:va_list  The copy if `source`.
 * @param  source:va_list       The state of the variadic argument-reading.
 * 
 * @since  Always.
 */
#ifndef va_copy
# define va_copy(destination, source)  __builtin_va_copy(destination, source)
#endif



#endif

#endif

