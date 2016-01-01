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
#include <unistd.h>
#include <alloca.h>


# pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"



/**
 * Finds the first occurrence of a substring.
 * This search is case sensitive.
 * 
 * This is a GNU-compliant slibc extension. It was useful
 * in implementing slibc itself.
 * 
 * @param   haystack         The string to search.
 * @param   haystack_length  The number of character to search.
 * @param   needle           The sought after substring.
 * @param   needle_length    The length of `needle`.
 * @return                   Pointer to the first occurrence of
 *                           the substring, `NULL` if not found.
 * 
 * @since  Always.
 */
void* (memmem)(const void* __haystack, size_t haystack_length,
	       const void* __needle, size_t needle_length)
{
  const char* haystack = __haystack;
  const char* needle = __needle;
  if (haystack_length < needle_length)
    return NULL;
  if (haystack_length == needle_length)
    return !(memcmp)(haystack, needle, haystack_length) ? haystack : NULL;
#include "substring.h"
}

