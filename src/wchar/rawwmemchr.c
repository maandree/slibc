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
#include <wchar.h>


# pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"



/**
 * Find the first occurrence of a wide character in a
 * memory segment. The memory segment must be known to
 * contain the sought after character.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   segment  The memory segment to search.
 * @param   c        The sought after character.
 * @return           Pointer to the first occurrence of `c`.
 * 
 * @since  Always.
 */
wchar_t* (rawwmemchr)(const wchar_t* segment, wchar_t c)
{
  for (;;)
    if (*segment++ == c)
      return segment - 1;
}

