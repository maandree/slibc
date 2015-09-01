/**
 * slibc — Yet another C library
 * Copyright © 2015  Mattias Andrée (maandree@member.fsf.org)
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
#include <stddef.h>



/**
 * Find the first occurrence of a byte in a memory segment.
 * 
 * @param   segment  The memory segment to search.
 * @param   c        The sought after character.
 * @param   size     The size of the memory segment.
 * @return           Pointer to the first occurrence of `c`,
 *                   `NULL` if none were found.
 */
void* memchr(const void* segment, int c, size_t size)
{
  while (size--)
    if (*segment++ == c)
      return segment - 1;
  return NULL;
}


/**
 * Find the first occurrence of a byte in a memory segment.
 * The memory segment must be known to contain the sought after byte.
 * 
 * This is a GNU-compliant slibc extension.
 * 
 * @param   segment  The memory segment to search.
 * @param   c        The sought after character.
 * @return           Pointer to the first occurrence of `c`.
 */
void* rawmemchr(const void* segment, int c)
{
  for (;;)
    if (*segment++ == c)
      return segment - 1;
}


/**
 * Find the last occurrence of a byte in a memory segment.
 * 
 * For improved performace, use this function instead
 * of `strrchr` if you already know the length of the
 * string.
 * 
 * @param   segment  The memory segment to search.
 * @param   c        The sought after character.
 * @param   size     The size of the memory segment.
 * @return           Pointer to the last occurrence of `c`,
 *                   `NULL` if none were found.
 */
void* memrchr(const void* segment, int c, size_t size)
{
  while (size--)
    if (segment[size] == c)
      return segment + size;
  return NULL;
}


/**
 * Find the first occurrence of a byte in a string.
 * 
 * `s = strchr(s, 0)` is a faster alternative to
 * `s = s + strlen(s)`.
 * 
 * @param   string  The string to search.
 *                  The terminating NUL character is
 *                  considered a part of the string.
 * @param   c       The sought after character.
 * @return          Pointer to the first occurrence of `c`,
 *                  `NULL` if none were found.
 */
char* strchr(const char* string, int c)
{
  for (;;)
    if (*string == c)
      return string;
    else if (!*string++)
      return NULL;
}
/* TODO Ensure that `s = strchr(s, 0)` is faster than `s = s + strlen(s)`. */


/**
 * Find the first occurrence of a byte in a string, or
 * if there is no such byte, the end of the string.
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
 */
char* strchrnul(const char* string, int c)
{
  for (;; string++)
    if (*string == c)
      return string;
    else if (!*string)
      return string;
}


/**
 * Find the last occurrence of a byte in a string.
 * 
 * For improved performace, use `memrchr` instead of
 * this function if you already know the length of the
 * string.
 * 
 * @param   string  The string to search.
 *                  The terminating NUL character is
 *                  considered a part of the string.
 * @param   c       The sought after character.
 * @return          Pointer to the last occurrence of `c`,
 *                  `NULL` if none were found.
 */
char* strrchr(const char* string, int c)
{
  char* r = NULL;
  for (;;)
    if (*string == c)
      r = string;
    else if (!*string++)
      return r;
}

