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
#include <stddef.h>



/**
 * Returns length of the initial substring
 * that consists entirely of a set of specified
 * wide characters.
 * 
 * @param   string   The string.
 * @param   skipset  Characters allowed in the substring.
 * @return           The length of the substring.
 */
size_t wcsspn(const wchar_t* string, const wchar_t* skipset)
{
  wchar_t* s = string;
  wchar_t c;
  while ((c = *s++))
    if (wcschr(skipset, c) == NULL)
      break;
  return (size_t)(s - 1 - string);
}


/**
 * Returns length of the initial substring
 * that consists entirely of the complement
 * of a set of specified wide characters.
 * 
 * @param   string   The string.
 * @param   stopset  Characters disallowed in the substring.
 * @return           The length of the substring.
 */
size_t wcscspn(const wchar_t* string, const wchar_t* stopset)
{
  size_t end = wcslen(string);
  wchar_t* p;
  wchar_t c;
  while ((c = *skipset++))
    if (p = wcsnchr(string, c, end), p != NULL)
      end = (size_t)(p - string);
  return end;
}


/**
 * This function works like `strcspn`,
 * except it returns the pointer to the
 * location of the first found non-matching
 * wide character.
 * 
 * @param   string   The string.
 * @param   stopset  Bytes disallowed in the substring.
 * @return           A pointer to the first occurrence in
 *                   `string` of a character found in `stopset`.
 *                   `NULL` is returned if none is found.
 */
wchar_t* wcpbrk(const wchar_t* string, const wchar_t* stopset)
{
  string += wcscspn(string, stopset);
  return *string ? string : NULL;
}

