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
 * Concatenate a string to the end of another string.
 * The resulting strings must not overlap with the appended string.
 * 
 * The use of this function is often a really bad idea.
 * 
 * @param   whither  The string to extend.
 * @param   whence   The string to append.
 * @param   maxlen   The maximum number of wide characters to copy.
 *                   NOTE that if the resulting string at least this
 *                   long, no NUL character will be written to `whither'.
 *                   On the otherhand, if the resultnig string is
 *                   shorter, `whither` will be filled with NUL characters
 *                   until this amount of characters have been written.
 * @return           `whither` is returned.
 * 
 * @since  Always.
 */
wchar_t* wcsncat(wchar_t* restrict whither, const wchar_t* restrict whence, size_t maxlen)
{
  wcsncpy(whither + wcslen(whither), whence, maxlen);
  return whither;
}

