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
#include <string.h>
#include <strings.h>
#include <inttypes.h>
#include <ctype.h>



/**
 * Compare two memory segments alphabetically in a case sensitive manner.
 * 
 * @param   a     A negetive value is returned if this is the lesser.
 * @param   b     A positive value is returned if this is the lesser.
 * @param   size  The size of the segments.
 * @return        Zero is returned if `a` and `b` are equal, otherwise,
 *                see the specifications for `a` and `b`.
 */
int memcmp(const void* a, const void* b, size_t size)
{
  const signed char* s1 = a;
  const signed char* s2 = b;
  while (size--)
    if (*s1 == *s2)
      s1++, s2++;
    else
      return (int)(*s1 - *s2);
  return 0;
}


/**
 * Compare two strings alphabetically in a case sensitive manner.
 * 
 * @param   a  A negetive value is returned if this is the lesser.
 * @param   b  A positive value is returned if this is the lesser.
 * @return     Zero is returned if `a` and `b` are equal, otherwise,
 *             see the specifications for `a` and `b`.
 */
int strcmp(const char* a, const char* b)
{
  size_t n = strlen(a);
  size_t m = strlen(b);
  return memcmp(a, b, (n < m ? n : m) + 1);
}


/**
 * Compare two strings alphabetically in a case insensitive manner.
 * Be aware, only ASCII characters are case insensitive, non-ASCII
 * characters are case sensitive.
 * 
 * @param   a  A negetive value is returned if this is the lesser.
 * @param   b  A positive value is returned if this is the lesser.
 * @return     Zero is returned if `a` and `b` are equal, otherwise,
 *             see the specifications for `a` and `b`.
 */
int strcasecmp(const char* a, const char* b)
{
  return strncasecmp(a, b, SIZE_MAX);
}


/**
 * Compare two strings alphabetically in a case sensitive manner.
 * 
 * @param   a       A negetive value is returned if this is the lesser.
 * @param   b       A positive value is returned if this is the lesser.
 * @param   length  The maximum number of characters to compare.
 * @return          Zero is returned if `a` and `b` are equal, otherwise,
 *                  see the specifications for `a` and `b`.
 */
int strncmp(const char* a, const char* b, size_t length)
{
  size_t n = strnlen(a, length);
  size_t m = strnlen(b, length);
  int r = memcmp(a, b, (n < m ? n : m));
  return r ? r : n == m ? 0 : n < m ? -1 : +1;
}


/**
 * Compare two strings alphabetically in a case insensitive manner.
 * Be aware, only ASCII characters are case insensitive, non-ASCII
 * characters are case sensitive.
 * 
 * @param   a       A negetive value is returned if this is the lesser.
 * @param   b       A positive value is returned if this is the lesser.
 * @param   length  The maximum number of characters to compare.
 * @return          Zero is returned if `a` and `b` are equal, otherwise,
 *                  see the specifications for `a` and `b`.
 */
int strncasecmp(const char* a, const char* b, size_t length)
{
  int c1, c2;
  for (; size--; a++, b++)
    if (*a != *b)
      {
	c1 = isalpha(*a) ? tolower(*a) : (int)*a;
	c2 = isalpha(*b) ? tolower(*b) : (int)*b;
	if ((c1 -= c2))
	  return c1;
      }
  return 0;
}

