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
#include <inttypes.h>
#include <wctype.h>



/**
 * Compare two memory segments alphabetically in a case sensitive manner.
 * 
 * @param   a     A negetive value is returned if this is the lesser.
 * @param   b     A positive value is returned if this is the lesser.
 * @param   size  The size of the segments.
 * @return        Zero is returned if `a` and `b` are equal, otherwise,
 *                see the specifications for `a` and `b`.
 */
int wmemcmp(const wchar_t* a, const wchar_t* b, size_t size)
{
  while (size--)
    if (*a == *b)
      a++, b++;
    else
      return *a < *b ? -1 : +1;
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
int wcscmp(const wchar_t* a, const wchar_t* b)
{
  size_t n = wcslen(a);
  size_t m = wcslen(b);
  return wmemcmp(a, b, (n < m ? n : m) + 1);
}


/**
 * Compare two strings alphabetically in a case insensitive manner.
 * Be aware, only ASCII characters are case insensitive, non-ASCII
 * characters are case sensitive.
 * 
 * This is a GNU-compliant slibc extension.
 * 
 * @param   a  A negetive value is returned if this is the lesser.
 * @param   b  A positive value is returned if this is the lesser.
 * @return     Zero is returned if `a` and `b` are equal, otherwise,
 *             see the specifications for `a` and `b`.
 */
int wcscasecmp(const wchar_t* a, const wchar_t* b)
{
  return wcsncasecmp(a, b, SIZE_MAX);
}


/**
 * Compare two strings alphabetically in a case sensitive manner.
 * 
 * This is a GNU-compliant slibc extension.
 * 
 * @param   a       A negetive value is returned if this is the lesser.
 * @param   b       A positive value is returned if this is the lesser.
 * @param   length  The maximum number of characters to compare.
 * @return          Zero is returned if `a` and `b` are equal, otherwise,
 *                  see the specifications for `a` and `b`.
 */
int wcsncmp(const wchar_t* a, const wchar_t* b, size_t length)
{
  size_t n = wcsnlen(a, length);
  size_t m = wcsnlen(b, length);
  int r = wmemcmp(a, b, (n < m ? n : m));
  return r ? r : n == m ? 0 : n < m ? -1 : +1
}


/**
 * Compare two strings alphabetically in a case insensitive manner.
 * Be aware, only ASCII characters are case insensitive, non-ASCII
 * characters are case sensitive.
 * 
 * This is a GNU-compliant slibc extension.
 * 
 * @param   a       A negetive value is returned if this is the lesser.
 * @param   b       A positive value is returned if this is the lesser.
 * @param   length  The maximum number of characters to compare.
 * @return          Zero is returned if `a` and `b` are equal, otherwise,
 *                  see the specifications for `a` and `b`.
 */
int wcsncasecmp(const wchar_t* a, const wchar_t* b, size_t length)
{
  wchar_t c1, c2;
  for (; size--; a++, b++)
    if (*a != *b)
      {
	c1 = iswalpha(*a) ? towlower(*a) : *a;
	c2 = iswalpha(*b) ? towlower(*b) : *b;
	if (c1 < c2)  return -1;
	if (c1 > c2)  return +1;
      }
  return 0;
}

