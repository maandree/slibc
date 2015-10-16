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
#ifndef _SLIBC_ALLOC_H
#define _SLIBC_ALLOC_H
#include <slibc/version.h>
#include <slibc/features.h>
#ifndef __PORTABLE



#define __NEED_size_t
#include <bits/types.h>


/**
 * This function is identical to `free`, except it is guaranteed not to
 * override the memory segment with zeroes before freeing the allocation.
 * 
 * @param  segment  The memory segment to free.
 */
void fast_free(void*);

/**
 * This function is identical to `free`, except it is guaranteed to
 * override the memory segment with zeroes before freeing the allocation.
 * 
 * @param  segment  The memory segment to free.
 */
void secure_free(void*);

/**
 * This function returns the allocation size of
 * a memory segment.
 * 
 * Note, this only works for the malloc-family of functions.
 * It does not work on `alloca`, `strdupa` (or similar
 * functions), memory maps (that are not created by `malloc`,)
 * or arrays.
 * 
 * `p = malloc(n), allocsize(p)` will return `n`.
 * 
 * @param   segment  The memory segment.
 * @return           The size of the memory segment, 0 on error.
 * 
 * @throws  EINVAL  If `segment` is `NULL`.
 * @throws  EFAULT  If `segment` is not a pointer to an allocation
 *                  on the heap, or was not allocated with a function
 *                  implemented in slibc. It is however not guaranteed
 *                  that this will happen, undefined behaviour may be
 *                  invoked instead.
 */
size_t allocsize(void*)
  __GCC_ONLY(__attribute__((warn_unused_result)));

/**
 * Variant of `realloc` that overrides newly allocated space
 * with zeroes. Additionally, it will override any freed space
 * with zeroes, including the old allocation if it creates a
 * new allocation.
 * 
 * @param   ptr   The old allocation, see `realloc` for more details.
 * @param   size  The new allocation size, see `realloc` for more details.
 * @return        The new allocation, see `realloc` for more details.
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 */
void* crealloc(void*, size_t)
  __GCC_ONLY(__attribute__((warn_unused_result)));

/**
 * This function behaves exactly like `realloc`, except it is
 * guaranteed to never initialise or errors data.
 * 
 * @param   ptr   The old allocation, see `realloc` for more details.
 * @param   size  The new allocation size, see `realloc` for more details.
 * @return        The new allocation, see `realloc` for more details.
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 */
void* fast_realloc(void*, size_t)
  __GCC_ONLY(__attribute__((warn_unused_result)));

/**
 * This function behaves exactly like `crealloc`, except it
 * does not initialise newly allocated size.
 * 
 * @param   ptr   The old allocation, see `realloc` for more details.
 * @param   size  The new allocation size, see `realloc` for more details.
 * @return        The new allocation, see `realloc` for more details.
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 */
void* secure_realloc(void*, size_t)
  __GCC_ONLY(__attribute__((warn_unused_result)));

/**
 * This function behaves exactly like `fast_realloc`, except:
 * - Its haviour is undefined if `ptr` is `NULL`.
 * - Its haviour is undefined `size` equals the old allocation size.
 * - Its haviour is undefined if `size` is zero.
 * - It will never free `ptr`.
 * 
 * @param   ptr   The old allocation, see `realloc` for more details.
 * @param   size  The new allocation size, see `realloc` for more details.
 * @return        The new allocation, see `realloc` for more details.
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 */
void* naive_realloc(void*, size_t) /* sic! we limit ourself to ASCII */
  __GCC_ONLY(__attribute__((nonnull, warn_unused_result)));


/**
 * This macro calls `fast_free` and then sets the pointer to `NULL`,
 * so that another attempt to free the segment will not crash the process.
 */
#define  FAST_FREE(segment)  (fast_free(segment), (segment) = NULL);

/**
 * This macro calls `secure_free` and then sets the pointer to `NULL`,
 * so that another attempt to free the segment will not crash the process.
 */
#define  SECURE_FREE(segment)  (secure_free(segment), (segment) = NULL);



#endif
#endif

