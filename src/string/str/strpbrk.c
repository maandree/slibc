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


# pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"



/**
 * This function works like `strcspn`,
 * except it returns the pointer to the
 * location of the first found non-matching
 * byte.
 * 
 * @param   string   The string.
 * @param   stopset  Bytes disallowed in the substring.
 * @return           A pointer to the first occurrence in
 *                   `string` of a byte found in `stopset`.
 *                   `NULL` is returned if none is found.
 * 
 * @since  Always.
 */
char* (strpbrk)(const char* string, const char* stopset)
{
  char set[256];
  char c;
  const char* s = string;
  memset(set, 0, 256 * sizeof(char));
  while ((c = *stopset++))
    set[(size_t)c] = 1;
  while ((c = *s++))
    if (!set[(size_t)c])
      break;
  return c ? (s - 1) : NULL;
}

