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
#include <wchar.h>
/* TODO #include <wctype.h> */



/**
 * Compare two memory segments alphabetically in a case insensitive manner.
 * 
 * @param   a     A negative value is returned if this is the lesser.
 * @param   b     A positive value is returned if this is the lesser.
 * @param   size  The size of the segments.
 * @return        Zero is returned if `a` and `b` are equal, otherwise,
 *                see the specifications for `a` and `b`.
 * 
 * @since  Always.
 */
int wmemcasecmp(const wchar_t* a, const wchar_t* b, size_t size)
{
  wchar_t c1, c2;
  for (; size--; a++, b++)
    if (*a != *b)
      {
	c1 = iswalpha(*a) ? towlower(*a) : *a;
	c2 = iswalpha(*b) ? towlower(*b) : *b;
	if (c1 != c2)
	  return c1 < c2 ? -1 : +1;
      }
  return 0;
}

