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
 * Override a memory segment with a repeated wide character.
 * 
 * @param   segment  The beginning of the memory segment.
 * @param   c        The wide character.
 * @param   size     The number of wide characters in the memory segment.
 * @return           `segment` is returned.
 * 
 * @since  Always.
 */
wchar_t* wmemset(wchar_t* segment, wchar_t c, size_t size)
{
  wchar_t* r = segment;
  while (size--)
    *segment++ = c;
  return r;
}

