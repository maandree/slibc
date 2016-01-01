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
#include <stdlib.h>
#include <errno.h>



/**
 * `posix_memalign(p, b, n)` is equivalent to
 * `(*p = memalign(b, n), *p ? 0 : errno)`, except
 * `boundary` must also be a multiple of `sizeof(void*)`,
 * and `errno` is unspecified.
 * 
 * As a GNU-compliant slibc extension, memory allocated
 * with this function can be freed with `free`.
 * 
 * @etymology  (POSIX)-extension: (mem)ory alignment.
 * 
 * @param   ptrptr    Output parameter for the allocated memory.
 * @param   boundary  The alignment.
 * @param   size      The number of bytes to allocated.
 * @return            Zero on success, a value for `errno` on error.
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 * @throws  EINVAL  If `boundary` is not a power-of-two multiple of `sizeof(void*)`.
 * 
 * @since  Always.
 */
int posix_memalign(void** ptrptr, size_t boundary, size_t size)
{
  if (boundary < sizeof(void*))
    return EINVAL;
  *ptrptr = memalign(boundary, size);
  return *ptrptr ? 0 : errno;
}

