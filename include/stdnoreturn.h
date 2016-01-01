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
#ifndef _STDNORETURN_H
#define _STDNORETURN_H
#include <slibc/version.h>
#include <slibc/features.h>

#if !defined(_SLIBC_SUPPRESS_WARNINGS) && !defined(__C99__)
# warning "<stdnoreturn.h> requires that C11 or newer revision is used."
#endif
#if !defined(_SLIBC_SUPPRESS_WARNINGS) && defined(__PORTABLE)
# warning "<stdnoreturn.h> is not portable because it conflicts with some compilers."
#endif



#if !defined(__PORTABLE)
/**
 * Specifies that a function never returns, that is,
 * the process exits or changes process image before
 * the function returns.
 * 
 * @since  Always.
 */
# if !defined(__C11__) && defined(__GNUC__)
#  define _Noreturn  __attribute__((__noreturn__))
# endif
# define noreturn  _Noreturn
#endif



#endif

