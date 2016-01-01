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
 * Returns length of the initial substring
 * that consists entirely of a set of specified
 * bytes.
 * 
 * @param   string   The string.
 * @param   skipset  Bytes allowed in the substring.
 * @return           The length of the substring.
 * 
 * @since  Always.
 */
size_t strspn(const char* string, const char* skipset)
{
  char set[256];
  char c;
  const char* s = string;
  memset(set, 0, 256);
  while ((c = *skipset++))
    set[(size_t)c] = 1;
  while ((c = *s++))
    if (set[(size_t)c])
      break;
  return (size_t)(s - 1 - string);
}

