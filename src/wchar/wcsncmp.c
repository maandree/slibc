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



/**
 * Compare two strings alphabetically in a case sensitive manner.
 * 
 * This is a GNU-compliant slibc extension.
 * 
 * @param   a       A negative value is returned if this is the lesser.
 * @param   b       A positive value is returned if this is the lesser.
 * @param   length  The maximum number of characters to compare.
 * @return          Zero is returned if `a` and `b` are equal, otherwise,
 *                  see the specifications for `a` and `b`.
 * 
 * @since  Always.
 */
int wcsncmp(const wchar_t* a, const wchar_t* b, size_t length)
{
  size_t n = wcsnlen(a, length);
  size_t m = wcsnlen(b, length);
  int r = wmemcmp(a, b, (n < m ? n : m));
  return r ? r : n == m ? 0 : n < m ? -1 : +1;
}

