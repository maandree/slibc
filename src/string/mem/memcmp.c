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
#include <string.h>



/**
 * Compare two memory segments alphabetically in a case sensitive manner.
 * 
 * @param   a     A negative value is returned if this is the lesser.
 * @param   b     A positive value is returned if this is the lesser.
 * @param   size  The size of the segments.
 * @return        Zero is returned if `a` and `b` are equal, otherwise,
 *                see the specifications for `a` and `b`.
 * 
 * @since  Always.
 */
int memcmp(const void* a, const void* b, size_t size)
{
  const unsigned char* s1 = a;
  const unsigned char* s2 = b;
  while (size--)
    if (*s1 == *s2)
      s1++, s2++;
    else
      return (int)(*s1 - *s2);
  return 0;
}

