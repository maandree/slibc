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


# pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"



/**
 * Returns the number of bytes in a NUL-terminated
 * string. This excludes the NUL byte.
 * 
 * @param   str  The string.
 * @return       The number of bytes before the first NUL byte.
 */
size_t strlen(const char* str)
{
  char* s = str;
  while (*str++);
  return (size_t)(s - 1 - str);
}


/**
 * Variant of `strlen` that only inspects the
 * beginning of s string.
 * 
 * @param   str     The string.
 * @param   maxlen  The number of bytes to inspect, at most.
 * @return          The number of bytes before, the first NUL byte.
 *                  `maxlen` if no NUL byte was found.
 */
size_t strnlen(const char* str, size_t maxlen)
{
  const char* end = memchr(str, 0, maxlen);
  return end == NULL ? maxlen : (size_t)(end - str);
}

