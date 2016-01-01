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
#include <ctype.h>



/**
 * Compare two strings alphabetically in a case insensitive manner.
 * Be aware, only ASCII characters are case insensitive, non-ASCII
 * characters are case sensitive.
 * 
 * @etymology  (Str)ing-function: (n)-bytes, (case) insensitive (c)o(mp)arison.
 * 
 * @param   a       A negative value is returned if this is the lesser.
 * @param   b       A positive value is returned if this is the lesser.
 * @param   length  The maximum number of characters to compare.
 * @return          Zero is returned if `a` and `b` are equal, otherwise,
 *                  see the specifications for `a` and `b`.
 * 
 * @since  Always.
 */
int strncasecmp(const char* a, const char* b, size_t length)
{
  int c1, c2;
  for (; length--; a++, b++)
    if (*a != *b)
      {
	c1 = isalpha(*a) ? tolower(*a) : (int)*a;
	c2 = isalpha(*b) ? tolower(*b) : (int)*b;
	if ((c1 -= c2))
	  return c1;
      }
    else if (!*a && !*b)  return 0;
    else if (!*a)         return -1;
    else if (!*b)         return +1;
  return 0;
}

