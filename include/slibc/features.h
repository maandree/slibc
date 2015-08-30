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
#ifndef _SLIBC_FEATURES_H
#define _SLIBC_FEATURES_H


/* These definitions are only to be used in slibc header-files. */


/**
 * Is C11, or newer, used?
 */
#if __STDC_VERSION__ >= 201112L
# define __C11__
#endif

/**
 * Is C99, or newer, used?
 */
#if __STDC_VERSION__ >= 199901L
# define __C99__
#endif

/**
 * Is C90, or newer, used?
 */
#if defined(__STDC_VERSION__) || defined(__STDC__)
# define __C90__
#endif



/**
 * Macro used to exclude code unless GCC is used.
 */
#if defined(__GNUC__)
# define __GCC_ONLY(...)   __VA_ARGS__
#else
# define __GCC_ONLY(...)   /* ignore */
#endif


/**
 * Specifies that a function never returns, that is,
 * the process exits before the function returns.
 */
#if !defined(__C11__) && defined(__GNUC__)
# define __noreturn  __attribute__((noreturn))
#elif defined(__C11__)
# define __noreturn  _Noreturn
#else
# define __noreturn  /* ignore */
#endif


/**
 * Mark a function, variable or type as deprecated,
 * with a message that tells the user why the the
 * function is deprecated, or functions to use instead.
 */
#if !defined(_SLIBC_SUPPRESS_WARNINGS)
# define __deprecated(msg)  __GCC_ONLY(__attribute__((deprecated(msg))))
#else
# define __deprecated(msg)  /* ignore */
#endif



#endif

