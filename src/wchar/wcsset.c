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
 * Override a NUL character-terminated memory segment
 * with a repeated wide character.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   str  The beginning of the memory segment.
 * @param   c    The wide character.
 * @return       `str` is returned.
 * 
 * @since  Always.
 */
wchar_t* wcsset(wchar_t* str, wchar_t c)
{
  wchar_t* r = str;
  while (*str)
    *str++ = c;
  return r;
}

