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
#include <stdint.h>



/**
 * Finds the first occurrence of a substring.
 * This search is case sensitive.
 * It must already be known that such a substring exists.
 * 
 * This is a slibc extension.
 * 
 * @param   haystack  The string to search.
 * @param   needle    The sought after substring.
 * @return            Pointer to the first occurrence of the substring.
 * 
 * @since  Always.
 */
wchar_t* (rawwcsstr)(const wchar_t* haystack, const wchar_t* needle)
{
  return (wmemmem)(haystack, SIZE_MAX, needle, wcslen(needle));
}

