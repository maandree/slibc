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
 * Returns the number of bytes in a NUL-terminated
 * string. This excludes the NUL byte.
 * 
 * @param   str  The string.
 * @return       The number of bytes before the first NUL byte.
 * 
 * @since  Always.
 */
size_t strlen(const char* str)
{
  const char* s = str;
  while (*str++);
  return (size_t)(s - 1 - str);
}

