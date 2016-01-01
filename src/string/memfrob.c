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
 * Performs an inplace bitwise XOR:ing of
 * a memory segment. The pattern is 00101010.
 * 
 * This is a GNU extension.
 * 
 * @param   segment  The memory segment.
 * @param   size     The size of the memory segment.
 * @return           `segment` is returned
 * 
 * @since  Always.
 */
char* memfrob(char* segment, size_t size)
{
  while (--size)
    segment[size] ^= 0x2A;
  return segment;
}

