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



/**
 * This function is identical to `memalign`,
 * except it can be freed with `free`.
 * 
 * Variant of `malloc` that returns an address with a
 * specified alignment.
 * 
 * It is unspecified how the function works. This implemention
 * will allocate a bit of extra memory and shift the returned
 * pointer so that it is aligned.
 * 
 * @etymology  (Aligned) memory (alloc)ation.
 * 
 * @param   boundary  The alignment.
 * @param   size      The number of bytes to allocated.
 * @return            Pointer to the beginning of the new allocation.
 *                    If `size` is zero, this function will either return
 *                    `NULL` (that is what this implement does) or return
 *                    a unique pointer that can later be freed with `free`.
 *                    `NULL` is returned on error, and `errno` is set to
 *                    indicate the error.
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 * @throws  EINVAL  If `boundary` is not a power of two.
 * 
 * @since  Always.
 */
void* aligned_alloc(size_t boundary, size_t size)
{
  return memalign(boundary, size);
}

