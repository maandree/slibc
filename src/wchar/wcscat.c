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
#include <wchar.h>



/**
 * Concatenate a string to the end of another string.
 * The resulting strings must not overlap with the appended string.
 * 
 * The use of this function is often a bad idea.
 * 
 * @param   whither  The string to extend.
 * @param   whence   The string to append.
 * @return           `whither` is returned.
 * 
 * @since  Always.
 */
wchar_t* wcscat(wchar_t* restrict whither, const wchar_t* restrict whence)
{
  wcscpy(whither + wcslen(whither), whence);
  return whither;
}

