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
#include <stdlib.h>



/**
 * Duplicate a memory segment.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   segment  The memory segment to duplicate.
 * @param   size     The size of the memory segment.
 * @return           The new segment. `NULL` is returned on error
 *                   and `errno` is set to indicate the error.
 * 
 * @throws  ENOMEM  The process could not allocate sufficient amount of memory.
 * 
 * @since  Always.
 */
wchar_t* wmemdup(const wchar_t* segment, size_t size)
{
  wchar_t* r = malloc(size * sizeof(wchar_t));
  return r == NULL ? NULL : wmemcpy(r, segment, size);
}

