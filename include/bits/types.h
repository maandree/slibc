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
/* That's right. No inclusion-guard; we want multiple
 * headers to be able to define types by including this
 * header without the need of keeping in mind which
 * order headers are included. */


/**
 * Signed integer type of the result of subtracting two pointers.
 * May not be greater than the with of type long.
 */
#if defined(__NEED_ptrdiff_t) && !defined(__DEFINED_ptrdiff_t)
# define __DEFINED_ptrdiff_t
typedef signed long int ptrdiff_t;
#endif


/**
 * Unsigned version of `ptrdiff_t`
 */
#if defined(__NEED_uptrdiff_t) && !defined(__DEFINED_uptrdiff_t)
# define __DEFINED_uptrdiff_t
typedef unsigned long int uptrdiff_t;
#endif


/**
 * Integer type which can represent any character.
 * May not be greater than the with of type long.
 * 
 * Unicode originally had an, inclusive upper limit
 * of U+FFFF. UTF-8 however had 31-bits (U+7FFFFFFF).
 * Unicode is now limited to 0x10FFFF.
 * 
 * 32 bits should be sufficient (long is at least 32
 * bits), but why limit further than POSIX does.
 */
#if defined(__NEED_wchar_t) && !defined(__DEFINED_wchar_t)
# define __DEFINED_wchar_t
typedef long int wchar_t;
#endif


/**
 * Unsigned integer type of the result of the
 * `sizeof` operator. May not be greater than the
 * with of type long.
 */
#if defined(__NEED_size_t) && !defined(__DEFINED_size_t)
# define __DEFINED_size_t
typedef unsigned long int size_t;
#endif


/**
 * Signed version of `size_t`
 */
#if defined(__NEED_ssize_t) && !defined(__DEFINED_ssize_t)
# define __DEFINED_ssize_t
typedef signed long int ssize_t;
#endif


/**
 * A type, of unspecified construct, whose alignment requirement
 * is at least as strict as that of every scalar type.
 */
#if defined(__NEED_max_align_t) && !defined(__DEFINED_max_align_t)
# define __DEFINED_max_align_t
typedef struct
{
  long long int __lli __attribute__((__aligned__(__alignof__(long long int))));
  long double   __ld  __attribute__((__aligned__(__alignof__(long double))));
} max_align_t;
#endif

