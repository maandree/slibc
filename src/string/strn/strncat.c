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
 * Concatenate a string to the end of another string.
 * The resulting strings must not overlap with the appended string.
 * 
 * The use of this function is often a really bad idea.
 * 
 * @param   whither  The string to extend.
 * @param   whence   The string to append.
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
char* strncat(char* restrict whither, const char* restrict whence, size_t maxlen)
{
  strncpy(whither + strlen(whither), whence, maxlen);
  return whither;
}

