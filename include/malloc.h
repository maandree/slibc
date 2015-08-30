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
#ifndef _MALLOC_H
#define _MALLOC_H
#include <slibc/version.h>


#include <slibc/features.h>



#define __NEED_size_t
#include <bits/types.h>


/**
 * Create a new memory allocation on the heap.
 * The allocation will not be initialised.
 * 
 * @param   size  The size of the allocation.
 * @return        Pointer to the beginning of the new allocation.
 *                If `size` is zero, this function will either return
 *                `NULL` (that is what this implement does) or return
 *                a unique pointer that can later be freed with `free`.
 *                `NULL` is returned on error, and `errno` is set to
 *                indicate the error.
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 */
void* malloc(size_t)
  __GCC_ONLY(__attribute__((malloc, warn_unused_result)));

/**
 * Variant of `malloc` that clears the allocation with zeroes.
 * 
 * `p = calloc(n, m)` is equivalent to
 * `(p = malloc(n * m), p ? (explicit_bzero(p, n * m), p) : NULL)`
 * 
 * @param   elem_count  The number of elements to allocate.
 * @param   elem_size   The size of each element.
 * @return              Pointer to the beginning of the new allocation.
 *                      If `elem_count` or `elem_size` is zero, this function
 *                      will either return `NULL` (that is what this implement
 *                      does) or return a unique pointer that can later be
 *                      freed with `free`. `NULL` is returned on error, and
 *                      `errno` is set to indicate the error.
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 */
void* calloc(size_t, size_t)
  __GCC_ONLY(__attribute__((malloc, warn_unused_result)));

/**
 * Variant of `malloc` that extends, or shrinks, an existing allocation,
 * if beneficial and possible, or creates a new allocation with the new
 * size, copies the data, and frees the old allocation.
 * 
 * On error, `ptr` is not freed.
 * 
 * @param   ptr   Pointer to the beginning of the old memory allocation.
 *                The process may crash if it does not point to the
 *                beginning of a memory allocation on the heap.
 *                However, if it is `NULL`, this function will behave
 *                like `malloc`.
 * @param   size  The new allocation size. If zero, this function will
 *                behave like `free`, and will return `NULL`.
 * @return        Pointer to the beginning of the new allocation.
 *                If `size` is zero, `NULL` is returned. On error `NULL`
 *                is returned and `errno` is set to indicate the error.
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 */
void* realloc(void*, size_t)
   __GCC_ONLY(__attribute__((warn_unused_result)))
   __slibc_warning("Use 'fast_realloc', 'secure_realloc' or 'crealloc' instead.");

/**
 * Free a memory allocation.
 * 
 * @param  ptr  Pointer to the beginning of the memory allocation.
 *              The process may crash if it does not point to the
 *              beginning of a memory allocation on the heap.
 *              However, if it is `NULL`, nothing will happen.
 */
void free(void*)
  __slibc_warning("Use 'fast_free' or 'secure_free' instead.");

/**
 * This function is identical to `free`.
 * Any argument beyond the first argument, is ignored.
 * 
 * This function uses variadic arguments because there
 * there are multiple conflicting specifications for `cfree`.
 * 
 * @param  ptr  Pointer to the beginning of the memory allocation.
 *              The process may crash if it does not point to the
 *              beginning of a memory allocation on the heap.
 *              However, if it is `NULL`, nothing will happen.
 */
#ifndef _PORTABLE_SOURCE
void cfree(void*, ...)
  __deprecated("'cfree' is deprecated and not portable, use 'free' instead.");
#endif


#ifndef _PORTABLE_SOURCE
/**
 * Variant of `malloc` that returns an address with a
 * specified alignment.
 * 
 * It is unspecified how the function works. This implemention
 * will allocate a bit of extra memory and shift the returned
 * pointer so that it is aligned.
 * 
 * As a GNU-compliant slibc extension, memory allocated
 * with this function can be freed with `free`.
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
 */
void* memalign(size_t, size_t)
#ifdef __C11__
   __deprecated("'memalign' has be deprecated by 'aligned_alloc' in C11.")
#endif
  __GCC_ONLY(__attribute__((malloc, warn_unused_result)));
#endif

/**
 * `posix_memalign(p, b, n)` is equivalent to
 * `(*p = memalign(b, n), *p ? 0 : errno)`, except
 * `boundary` must also be a multiple of `sizeof(void*)`,
 * and `errno` is unspecified.
 * 
 * As a GNU-compliant slibc extension, memory allocated
 * with this function can be freed with `free`.
 * 
 * @param   ptrptr    Output parameter for the allocated memory.
 * @param   boundary  The alignment.
 * @param   size      The number of bytes to allocated.
 * @return            Zero on success, a value for `errno` on error.
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 * @throws  EINVAL  If `boundary` is not a power-of-two multiple of `sizeof(void*)`.
 */
int posix_memalign(void**, size_t, size_t)
  __GCC_ONLY(__attribute__((nonnull)));

#ifndef _PORTABLE_SOURCE
/**
 * `valloc(n)` is equivalent to `memalign(sysconf(_SC_PAGESIZE), n)`.
 * 
 * As a GNU-compliant slibc extension, memory allocated
 * with this function can be freed with `free`.
 * 
 * @param   size    The number of bytes to allocated.
 * @return          Pointer to the beginning of the new allocation.
 *                  If `size` is zero, this function will either return
 *                  `NULL` (that is what this implement does) or return
 *                  a unique pointer that can later be freed with `free`.
 *                  `NULL` is returned on error, and `errno` is set to
 *                  indicate the error.
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 */
void* valloc(size_t)
  __GCC_ONLY(__attribute__((malloc, warn_unused_result)))
  __deprecated("'valloc' is deprecated, use 'memalign' or 'posix_memalign' instead.");

#ifdef _GNU_SOURCE
/**
 * This function works like `valloc`, except the allocation size,
 * including auxiliary space, is rounded up to the next multiple
 * of the page size.
 * 
 * @param   size    The number of bytes to allocated.
 * @return          Pointer to the beginning of the new allocation.
 *                  If `size` is zero, this function will either return
 *                  `NULL` (that is what this implement does) or return
 *                  a unique pointer that can later be freed with `free`.
 *                  `NULL` is returned on error, and `errno` is set to
 *                  indicate the error.
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 */
void* pvalloc(size_t)
  __GCC_ONLY(__attribute__((malloc, warn_unused_result)))
  __deprecated("'pvalloc' is deprecated, use 'memalign' or 'posix_memalign' instead.");
#endif
#endif

#ifdef __C11__
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
 */
void* aligned_alloc(size_t, size_t)
  __GCC_ONLY(__attribute__((malloc, warn_unused_result)));
#endif


#if defined(_GNU_SOURCE) && !defined(_PORTABLE_SOURCE)
/**
 * This function returns the allocation size of
 * a memory segment.
 * 
 * `p = malloc(n), malloc_usable_size(p)` will return `n`.
 * 
 * @param   segment  The memory segment.
 * @return           The size of the memory segment, 0 if `segment` is `NULL`.
 */
size_t malloc_usable_size(void*)
  __GCC_ONLY(__attribute__((warn_unused_result)));
#endif



#endif

