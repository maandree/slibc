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
#include <string.h>



/**
 * Finds the first occurrence of a substring.
 * This search is case insensitive.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   haystack  The string to search.
 * @param   needle    The sought after substring.
 * @param   maxlen    The maximum number of character to search.
 * @return            Pointer to the first occurrence of the
 *                    substring, `NULL` if not found.
 * 
 * @since  Always.
 */
char* (strncasestr)(const char* haystack, const char* needle, size_t maxlen)
{
  return (memcasemem)(haystack, strnlen(haystack, maxlen), needle, strlen(needle));
}

