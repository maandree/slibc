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
//>set -e

//>FAST8=$(bin/gen/bits/intconf fast8)
//>FAST16=$(bin/gen/bits/intconf fast16)
//>FAST32=$(bin/gen/bits/intconf fast32)
//>FAST64=$(bin/gen/bits/intconf fast64)


/**
 * Converts an integer's maximum value to
 * its [the integer's] minimum value.
 */
#define __MAX_TO_MIN(max)  (-(max) - 1) /* TODO compiler-flag-dependent */

/* TODO compiler-flag-dependent */
#if //(bin/gen/bits/intconf char-signed)
/**
 * Set if and only if `char` is signed by default.
 */
# define __CHAR_SIGNED

/**
 * The default signness-modifiers for `char`.
 */
# define __CHAR_SIGNNESS  signed
#else
# define __CHAR_SIGNNESS  unsigned
#endif

#if //(bin/gen/bits/intconf wchar-signed)
/**
 * Set if and only if `wchar_t` is signed by default.
 */
# define __WCHAR_SIGNED

/**
 * The default signness-modifiers for `wchar_t`.
 */
# define __WCHAR_SIGNNESS  signed
#else
# define __WCHAR_SIGNNESS  unsigned
#endif

/**
 * The number of bits in `char`.
 * (8 is mandatates, but I did it thus way for uniformity.)
 */
#define __CHAR_BIT         //(bin/gen/bits/intconf | grep ^CHAR_BIT      | sed "s/^[^ ]* //")

/**
 * The number of bits in `short int`.
 */
#define __SHORT_BIT        //(bin/gen/bits/intconf | grep ^SHORT_BIT     | sed "s/^[^ ]* //")

/**
 * The number of bits in `int`.
 */
#define __INT_BIT          //(bin/gen/bits/intconf | grep ^INT_BIT       | sed "s/^[^ ]* //")

/**
 * The number of bits in `long int`.
 */
#define __LONG_BIT         //(bin/gen/bits/intconf | grep ^LONG_BIT      | sed "s/^[^ ]* //")

/**
 * The number of bits in `long long int`.
 */
#define __LONG_LONG_BIT    //(bin/gen/bits/intconf | grep ^LONG_LONG_BIT | sed "s/^[^ ]* //")

/**
 * The number of bits in `void*`.
 */
#define __PTR_BIT          //(bin/gen/bits/intconf | grep ^PTR_BIT       | sed "s/^[^ ]* //")

/**
 * The number of bits in `wchar`.
 */
#define __WCHAR_BIT        //(bin/gen/bits/intconf | grep ^WCHAR_BIT     | sed "s/^[^ ]* //")

/**
 * The 16-bit integer 0x0102 but with the
 * bytes swapped to the storage order.
 */
#define __INT16_BYTEORDER  //(bin/gen/bits/intconf | grep ^INT16_BYTEORDER | sed "s/^[^ ]* //")

/**
 * The 32-bit integer 0x01020304 but with
 * the bytes swapped to the storage order.
 */
#define __INT32_BYTEORDER  //(bin/gen/bits/intconf | grep ^INT32_BYTEORDER | sed "s/^[^ ]* //")

/**
 * The 64-bit integer 0x0102030405060708 but with
 * the bytes swapped to the storage order.
 */
#define __INT64_BYTEORDER  //(bin/gen/bits/intconf | grep ^INT64_BYTEORDER | sed "s/^[^ ]* //")

/**
 * The underlaying intrinsic type for `int8_t` or `uint8_t`.
 */
#define __INT8             //(bin/gen/bits/intconf | grep ^INT8\         | sed "s/^[^ ]* //" | sed 1q)

/**
 * The underlaying intrinsic type for `int16_t` or `uint16_t`.
 */
#define __INT16            //(bin/gen/bits/intconf | grep ^INT16\        | sed "s/^[^ ]* //" | sed 1q)

/**
 * The underlaying intrinsic type for `int32_t` or `uint32_t`.
 */
#define __INT32            //(bin/gen/bits/intconf | grep ^INT32\        | sed "s/^[^ ]* //" | sed 1q)

/**
 * The underlaying intrinsic type for `int64_t` or `uint64_t`.
 */
#define __INT64            //(bin/gen/bits/intconf | grep ^INT64\        | sed "s/^[^ ]* //" | sed 1q)

/**
 * The underlaying intrinsic type for `int8_t` or `uint8_t`.
 */
#define __INT_FAST8        __INT//{FAST8}

/**
 * The underlaying intrinsic type for `int16_t` or `uint16_t`.
 */
#define __INT_FAST16       __INT//{FAST16}

/**
 * The underlaying intrinsic type for `int32_t` or `uint32_t`.
 */
#define __INT_FAST32       __INT//{FAST32}

/**
 * The underlaying intrinsic type for `int64_t` or `uint64_t`.
 */
#define __INT_FAST64       __INT//{FAST64}

/**
 * The maximum value of `int_fast8_t`.
 */
#define __INT_FAST8_MAX    INT//{FAST8}_MAX

/**
 * The maximum value of `int_fast16_t`.
 */
#define __INT_FAST16_MAX   INT//{FAST16}_MAX

/**
 * The maximum value of `int_fast32_t`.
 */
#define __INT_FAST32_MAX   INT//{FAST32}_MAX

/**
 * The maximum value of `int_fast64_t`.
 */
#define __INT_FAST64_MAX   INT//{FAST64}_MAX

/**
 * The maximum value of `uint_fast8_t`.
 */
#define __UINT_FAST8_MAX   UINT//{FAST8}_MAX

/**
 * The maximum value of `uint_fast16_t`.
 */
#define __UINT_FAST16_MAX  UINT//{FAST16}_MAX

/**
 * The maximum value of `uint_fast32_t`.
 */
#define __UINT_FAST32_MAX  UINT//{FAST32}_MAX

/**
 * The maximum value of `uint_fast64_t`.
 */
#define __UINT_FAST64_MAX  UINT//{FAST64}_MAX


#endif

