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
#ifndef _WCHAR_H
#define _WCHAR_H
#ifndef _PORTABLE_SOURCE /* `wchar_t` is not portable. */
#include <slibc/version.h>


#include <slibc/features.h>



#define __NEED_size_t
#define __NEED_wchar_t

#include <bits/types.h>


/**
 * `wchar_t` version of `strlen`.
 * 
 * @param   str  The string.
 * @return       The number of `wchar_t`:s before the
 *               first NUL character.
 */
size_t wcslen(const wchar_t*)
  __GCC_ONLY(__attribute__((nonnull, warn_unused_result)));

#if defined(_POSIX_SOURCE) || defined(_POSIX_C_SOURCE) || \
    defined(_XOPEN_SOURCE) || defined(_GNU_SOURCE) || \
    defined(_BSD_SOURCE)
/**
 * `wchar_t` version of `strnlen`.
 * 
 * @param   str     The string.
 * @param   maxlen  The number of bytes to inspect, at most.
 * @return          The number of `wchar_t`:s before the
 *                  first NUL character. `maxlen` if no
 *                  NUL character was found.
 */
size_t wcsnlen(const wchar_t*, size_t)
  __GCC_ONLY(__attribute__((warn_unused_result)));
#endif



#endif
#endif

