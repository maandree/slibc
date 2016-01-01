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


# pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"



/**
 * Find the first occurrence of a wide character in a
 * string, or if there is no such character, the end of
 * the string.
 * 
 * This is a GNU-compliant slibc extension.
 * 
 * @param   string  The string to search.
 *                  The terminating NUL character is
 *                  considered a part of the string.
 * @param   c       The sought after character.
 * @return          Pointer to the first occurrence of `c`,
 *                  Pointer to the terminating NUL character
 *                  if none were found.
 * 
 * @since  Always.
 */
wchar_t* (wcschrnul)(const wchar_t* string, wchar_t c)
{
  for (;; string++)
    if (*string == c)
      return string;
    else if (!*string)
      return string;
}

