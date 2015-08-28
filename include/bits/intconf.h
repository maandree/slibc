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
#ifndef _BITS_INTCONF_H
#define _BITS_INTCONF_H


#define __MAX_TO_MIN(max)  (-(max) - 1)
#define __CHAR_BIT         8
#define __SHORT_BIT        16
#define __INT_BIT          32
#define __LONG_BIT         64
#define __LONG_LONG_BIT    64
#define __INT8             char
#define __INT16            short int
#define __INT32            int
#define __INT64            long int
#define __INT_FAST8        __INT8
#define __INT_FAST16       __INT64
#define __INT_FAST32       __INT64
#define __INT_FAST64       __INT64
#define __INT_FAST8_MAX    INT8_MAX
#define __INT_FAST16_MAX   INT64_MAX
#define __INT_FAST32_MAX   INT64_MAX
#define __INT_FAST64_MAX   INT64_MAX
#define __UINT_FAST8_MAX   UINT8_MAX
#define __UINT_FAST16_MAX  UINT64_MAX
#define __UINT_FAST32_MAX  UINT64_MAX
#define __UINT_FAST64_MAX  UINT64_MAX


#endif

