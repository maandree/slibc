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
 * Check whether a string ends with a specific string.
 * This check is case sensitive.
 * 
 * This is a slibc extension.
 * 
 * @param   string   The string to inspect.
 * @param   desired  The desired ending of the string.
 * @return           The `string`, where `desired` beings if
 *                   `string` ends with `desired`, `NULL` otherwise.
 * 
 * @since  Always.
 */
wchar_t* (wcsends)(const wchar_t* string, const wchar_t* desired)
{
  size_t n = wcslen(string);
  size_t m = wcslen(desired);
  if (n < m)
    return NULL;
  return wmemcmp(string + (n - m), desired, m) ? NULL : (string + n);
}

