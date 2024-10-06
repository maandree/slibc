/**
 * slibc — Yet another C library
 * Copyright © 2015, 2016  Mattias Andrée (m@maandree.se)
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
 * Override a NUL byte-terminated memory segment
 * with a repeated character.
 * 
 * This is a slibc extension.
 * 
 * @param   str  The beginning of the memory segment.
 * @param   c    The character (8 bits wide.)
 * @return       `str` is returned.
 * 
 * @since  Always.
 */
char* strset(char* str, int c)
{
  char* s = str;
  while (*s)
    *s++ = (char)c;
  return str;
}

