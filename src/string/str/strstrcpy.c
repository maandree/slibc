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
 * Copy a memory segment to another, non-overlapping, segment,
 * stop when a NUL byte or a specified substring is encountered.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   str      The substring, ignored if `NULL`.
 * @return           `NULL` if `str` was not encountered, otherwise
 *                   the position of `str` translated to `whither`,
 *                   that is, the address of `whither` plus the
 *                   number of copied characters; the address of
 *                   one character passed the last written non-NUL
 *                   character.
 * 
 * @since  Always.
 */
char* strstrcpy(char* restrict whither, const char* restrict whence, const char* restrict str)
{
  const char* stop = str == NULL ? NULL : strstr(whence, str);
  size_t n = stop == NULL ? strlen(whence) : (size_t)(stop - whence);
  char* r = stop == NULL ? NULL : (whither + n);
  memcpy(whither, whence, n);
  whither[n] = 0;
  return r;
}

