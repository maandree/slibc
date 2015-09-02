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
#include <wchar.h>
#include <stdint.h>
#include <unistd.h>
#include <alloca.h>
#include <wctype.h>

#define WIDE


# pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"



/**
 * This function is identical to `wcsstr`.
 */
wchar_t* wcswcs(const wchar_t* haystack, const wchar_t* needle)
{
  return wcsstr(haystack, needle);
}


/**
 * Finds the first occurrence of a substring.
 * This search is case sensitive.
 * 
 * @param   haystack  The string to search.
 * @param   needle    The sought after substring.
 * @return            Pointer to the first occurrence of the
 *                    substring, `NULL` if not found.
 */
wchar_t* wcsstr(const wchar_t* haystack, const wchar_t* needle)
{
  return wmemmem(haystack, wcslen(haystack), needle, wcslen(needle));
}


/**
 * Finds the first occurrence of a substring.
 * This search is case insensitive.
 * 
 * This is a slibc extension.
 * 
 * @param   haystack  The string to search.
 * @param   needle    The sought after substring.
 * @return            Pointer to the first occurrence of the
 *                    substring, `NULL` if not found.
 */
wchar_t* wcscasestr(const wchar_t* haystack, const wchar_t* needle)
{
  return wmemcasemem(haystack, wcslen(haystack), needle, wcslen(needle));
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
wchar_t* wcsnstr(const wchar_t* haystack, const wchar_t* needle, size_t maxlen)
{
  return wmemmem(haystack, wcsnlen(haystack, maxlen), needle, wcslen(needle));
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
wchar_t* wcsncasestr(const wchar_t* haystack, const wchar_t* needle, size_t maxlen)
{
  return wmemcasemem(haystack, wcsnlen(haystack, maxlen), needle, wcslen(needle));
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
wchar_t* rawwcsstr(const wchar_t* haystack, const wchar_t* needle)
{
  return wmemmem(haystack, SIZE_MAX, needle, wcslen(needle));
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
wchar_t* rawwcscasestr(const wchar_t* haystack, const wchar_t* needle)
{
  return wmemcasemem(haystack, SIZE_MAX, needle, wcslen(needle));
}


/**
 * Finds the first occurrence of a substring
 * This search is case sensitive.
 * 
 * This is a slibc extension added for completeness,
 * and because it was it was useful in implementing
 * slibc itself.
 * 
 * @param   haystack         The string to search.
 * @param   haystack_length  The number of character to search.
 * @param   needle           The sought after substring.
 * @param   needle_length    The length of `needle`.
 * @return                   Pointer to the first occurrence of
 *                           the substring, `NULL` if not found.
 */
wchar_t* wmemmem(const wchar_t* haystack, size_t haystack_length,
		 const wchar_t* needle, size_t needle_length)
{
  if (haystack_length < needle_length)
    return NULL;
  if (haystack_length == needle_length)
    return !wmemcmp(haystack, needle, haystack_length) ? haystack : NULL;
#include "../string/substring.h"
}


/**
 * Finds the first occurrence of a substring
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
wchar_t* wmemcasemem(const wchar_t* haystack, size_t haystack_length,
		     const wchar_t* needle, size_t needle_length)
{
  if (haystack_length < needle_length)
    return NULL;
  if (haystack_length == needle_length)
    return !wmemcasecmp(haystack, needle, haystack_length) ? haystack : NULL;
#define CASE
#include "../string/substring.h"
#undef CASE
}

