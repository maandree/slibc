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
 * Copy a memory segment to another, possibly overlapping, segment.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   size     The number of bytes to copy.
 * @return           `whither` is returned.
 * 
 * @since  Always.
 */
void* memmove(void* whither, const void* whence, size_t size)
{
  char* d = whither;
  const char* s = whence;
  if ((size_t)(d - s) < size)
    while (size--)
      d[size] = s[size];
  else
    while (size--)
      *d++ = *s++;
  return whither;
}

