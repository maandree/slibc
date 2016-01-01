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
 * Override a memory segment with a repeated character.
 * 
 * @param   segment  The beginning of the memory segment.
 * @param   c        The character (8 bits wide.)
 * @param   size     The size of the memory segment.
 * @return           `segment` is returned.
 * 
 * @since  Always.
 */
void* memset(void* segment, int c, size_t size)
{
  char* s = segment;
  while (size--)
    *s++ = (char)c;
  return segment;
}

