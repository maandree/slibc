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

#define __MAX_TO_MIN(max)  (-(max) - 1)
#if //(bin/gen/bits/intconf char-signed)
# define __CHAR_SIGNED
# define __CHAR_SIGNESS  signed
#endif
# define __CHAR_SIGNESS  unsigned
#endif
#if //(bin/gen/bits/intconf wchar-signed)
# define __WCHAR_SIGNED
# define __WCHAR_SIGNESS  signed
#else
# define __WCHAR_SIGNESS  unsigned
#endif
#define __CHAR_BIT         //(bin/gen/bits/intconf | grep ^CHAR_BIT      | sed "s/^[^ ]* //")
#define __SHORT_BIT        //(bin/gen/bits/intconf | grep ^SHORT_BIT     | sed "s/^[^ ]* //")
#define __INT_BIT          //(bin/gen/bits/intconf | grep ^INT_BIT       | sed "s/^[^ ]* //")
#define __LONG_BIT         //(bin/gen/bits/intconf | grep ^LONG_BIT      | sed "s/^[^ ]* //")
#define __LONG_LONG_BIT    //(bin/gen/bits/intconf | grep ^LONG_LONG_BIT | sed "s/^[^ ]* //")
#define __PTR_BIT          //(bin/gen/bits/intconf | grep ^PTR_BIT       | sed "s/^[^ ]* //")
#define __WCHAR_BIT        //(bin/gen/bits/intconf | grep ^WCHAR_BIT     | sed "s/^[^ ]* //")
#define __INT8             //(bin/gen/bits/intconf | grep ^INT8          | sed "s/^[^ ]* //" | sed 1q)
#define __INT16            //(bin/gen/bits/intconf | grep ^INT16         | sed "s/^[^ ]* //" | sed 1q)
#define __INT32            //(bin/gen/bits/intconf | grep ^INT32         | sed "s/^[^ ]* //" | sed 1q)
#define __INT64            //(bin/gen/bits/intconf | grep ^INT64         | sed "s/^[^ ]* //" | sed 1q)
#define __INT_FAST8        __INT//{FAST8}
#define __INT_FAST16       __INT//{FAST16}
#define __INT_FAST32       __INT//{FAST32}
#define __INT_FAST64       __INT//{FAST64}
#define __INT_FAST8_MAX    INT//{FAST8}_MAX
#define __INT_FAST16_MAX   INT//{FAST16}_MAX
#define __INT_FAST32_MAX   INT//{FAST32}_MAX
#define __INT_FAST64_MAX   INT//{FAST64}_MAX
#define __UINT_FAST8_MAX   UINT//{FAST8}_MAX
#define __UINT_FAST16_MAX  UINT//{FAST16}_MAX
#define __UINT_FAST32_MAX  UINT//{FAST32}_MAX
#define __UINT_FAST64_MAX  UINT//{FAST64}_MAX


#endif

