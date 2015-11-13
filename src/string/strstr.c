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
#include <stdint.h>
#include <unistd.h>
#include <alloca.h>
#include <ctype.h>


# pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"



/**
 * Finds the first occurrence of a substring.
 * This search is case sensitive.
 * 
 * @param   haystack  The string to search.
 * @param   needle    The sought after substring.
 * @return            Pointer to the first occurrence of the
 *                    substring, `NULL` if not found.
 */
char* (strstr)(const char* haystack, const char* needle)
{
  if (*needle && !(needle[1]))
    return (strchr)(haystack, *needle);
  return (memmem)(haystack, strlen(haystack), needle, strlen(needle));
}


/**
 * Finds the first occurrence of a substring.
 * This search is case insensitive.
 * 
 * @param   haystack  The string to search.
 * @param   needle    The sought after substring.
 * @return            Pointer to the first occurrence of the
 *                    substring, `NULL` if not found.
 */
char* (strcasestr)(const char* haystack, const char* needle)
{
  return (memcasemem)(haystack, strlen(haystack), needle, strlen(needle));
}


/**
 * Finds the first occurrence of a substring.
 * This search is case sensitive.
 * 
 * This is a slibc extension added for because it was useful
 * in implementing slibc itself.
 * 
 * @param   haystack  The string to search.
 * @param   needle    The sought after substring.
 * @param   maxlen    The maximum number of character to search.
 * @return            Pointer to the first occurrence of the
 *                    substring, `NULL` if not found.
 */
char* (strnstr)(const char* haystack, const char* needle, size_t maxlen)
{
  return (memmem)(haystack, strnlen(haystack, maxlen), needle, strlen(needle));
}


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
 */
char* (strncasestr)(const char* haystack, const char* needle, size_t maxlen)
{
  return (memcasemem)(haystack, strnlen(haystack, maxlen), needle, strlen(needle));
}


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
 */
char* (rawstrstr)(const char* haystack, const char* needle)
{
  return (memmem)(haystack, SIZE_MAX, needle, strlen(needle));
}


/**
 * Finds the first occurrence of a substring.
 * This search is case insensitive.
 * It must already be known that such a substring exists.
 * 
 * This is a slibc extension.
 * 
 * @param   haystack  The string to search.
 * @param   needle    The sought after substring.
 * @return            Pointer to the first occurrence of the substring.
 */
char* (rawstrcasestr)(const char* haystack, const char* needle)
{
  return (memcasemem)(haystack, SIZE_MAX, needle, strlen(needle));
}


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


/**
 * Finds the first occurrence of a substring.
 * This search is case insensitive.
 * 
 * This is a slibc extension added because it was useful
 * in implementing slibc itself.
 * 
 * @param   haystack         The string to search.
 * @param   haystack_length  The number of character to search.
 * @param   needle           The sought after substring.
 * @param   needle_length    The length of `needle`.
 * @return                   Pointer to the first occurrence of
 *                           the substring, `NULL` if not found.
 */
void* (memcasemem)(const void* __haystack, size_t haystack_length,
		   const void* __needle, size_t needle_length)
{
  const char* haystack = __haystack;
  const char* needle = __needle;
  if (haystack_length < needle_length)
    return NULL;
  if (haystack_length == needle_length)
    return !(memcasecmp)(haystack, needle, haystack_length) ? haystack : NULL;
#define CASE
#include "substring.h"
#undef CASE
}


/**
 * Check whether a string starts with a specific string.
 * This check is case sensitive.
 * 
 * This is a slibc extension.
 * 
 * @param   string   The string to inspect.
 * @param   desired  The desired beginning of the string.
 * @return           `string` if `string` begins with
 *                   `desired`, `NULL` otherwise.
 */
char* (strstarts)(const char* string, const char* desired)
{
  size_t n = strlen(string);
  size_t m = strlen(desired);
  if (n < m)
    return NULL;
  return (memcmp)(string, desired, m) ? NULL : string;
}


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
 */
char* (strends)(const char* string, const char* desired)
{
  size_t n = strlen(string);
  size_t m = strlen(desired);
  if (n < m)
    return NULL;
  return (memcmp)(string + (n - m), desired, m) ? NULL : (string + n);
}


/**
 * Check whether a string starts with a specific string.
 * This check is case insensitive.
 * 
 * This is a slibc extension.
 * 
 * @param   string   The string to inspect.
 * @param   desired  The desired beginning of the string.
 * @return           `string` if `string` begins with
 *                   `desired`, `NULL` otherwise.
 */
char* (strcasestarts)(const char* string, const char* desired)
{
  size_t n = strlen(string);
  size_t m = strlen(desired);
  if (n < m)
    return NULL;
  return (memcasecmp)(string, desired, m) ? NULL : string;
}


/**
 * Check whether a string ends with a specific string.
 * This check is case insensitive.
 * 
 * This is a slibc extension.
 * 
 * @param   string   The string to inspect.
 * @param   desired  The desired ending of the string.
 * @return           The `string`, where `desired` beings if
 *                   `string` ends with `desired`, `NULL` otherwise.
 */
char* (strcaseends)(const char* string, const char* desired)
{
  size_t n = strlen(string);
  size_t m = strlen(desired);
  if (n < m)
    return NULL;
  return (memcasecmp)(string + (n - m), desired, m) ? NULL : (string + n);
}

