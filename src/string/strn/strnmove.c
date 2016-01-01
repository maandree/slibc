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
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL byte is encountered.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   maxlen   The maximum number of bytes to copy.
 *                   NOTE that if the resulting string at least this
 *                   long, no NUL byte will be written to `whither'.
 *                   On the otherhand, if the resultnig string is
 *                   shorter, `whither` will be filled with NUL bytes
 *                   until this amount of bytes have been written.
 * @return           `whither` is returned.
 * 
 * @since  Always.
 */
char* strnmove(char* whither, const char* whence, size_t maxlen)
{
  size_t n = strnlen(whence, maxlen);
  memmove(whither, whence, n);
  memset(whither + n, 0, maxlen - n);
  return whither;
}

