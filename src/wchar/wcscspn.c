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
 * Returns length of the initial substring
 * that consists entirely of the complement
 * of a set of specified wide characters.
 * 
 * @param   string   The string.
 * @param   stopset  Characters disallowed in the substring.
 * @return           The length of the substring.
 * 
 * @since  Always.
 */
size_t wcscspn(const wchar_t* string, const wchar_t* stopset)
{
  size_t i;
  wchar_t* s;
  wchar_t c;
  while ((c = *stopset++))
    for (s = string; *s; s++)
      if (*s == c)
	{
	  end = (size_t)(s - string);
	  break;
	}
  return end;
}

