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
#include <wchar.h>



/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * but stop if a specific byte is encountered.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   c        The character to stop at if encountered.
 * @param   size     The maximum number of wide characters to copy.
 * @return           `NULL` if `c` was not encountered, otherwise
 *                   the position of `c` translated to `whither`,
 *                   that is, the address of `whither` plus the
 *                   number of copied characters; the address of
 *                   one character passed the last written character.
 * 
 * @since  Always.
 */
wchar_t* wmemcmove(wchar_t* whither, const wchar_t* whence, wchar_t c, size_t size)
{
  wchar_t* stop = (wmemchr)(whence, c, size);
  wchar_t* r = NULL;
  if (stop != NULL)
    size = (size_t)(stop - whence), r = whither + size;
  wmemmove(whither, whence, size);
  return r;
}

