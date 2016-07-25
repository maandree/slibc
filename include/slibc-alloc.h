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
#ifndef _SLIBC_ALLOC_H
#define _SLIBC_ALLOC_H
#include <slibc/version.h>
#include <slibc/features.h>
#ifndef __PORTABLE



#define __NEED_size_t
#include <bits/types.h>


/**
 * Configurations for `extalloc`.
 * They are independent of each other, and
 * multiple can be selected by using bitwise or
 * between them.
 * 
 * @since  Always.
 */
enum extalloc_mode
  {
    /**
     * Clear disowned memory.
     * 
     * @since  Always.
     */
    EXTALLOC_CLEAR = 1,
    
    /**
     * Create new allocation with `malloc` if necessary.
     * 
     * @since  Always.
     */
    EXTALLOC_MALLOC = 2,
    
  };


/**
 * Configurations for `rememalign`.
 * They are independent of each other, and
 * multiple can be selected by using bitwise or
 * between them.
 * 
 * @since  Always.
 */
enum rememalign_mode
  {
    /**
     * Clear disowned memory.
     * 
     * @since  Always.
     */
    REMEMALIGN_CLEAR = 1,
    
    /**
     * Initialise new memory.
     * 
     * @since  Always.
     */
    REMEMALIGN_INIT = 2,
    
    /**
     * If a new allocation is created, copy the data
     * from the old allocation over to the new allocation.
     * 
     * @since  Always.
     */
    REMEMALIGN_MEMCPY = 4,
    
  };


/**
 * Configurations for `falloc`.
 * They are independent of each other, and
 * multiple can be selected by using bitwise or
 * between them.
 * 
 * @since  Always.
 */
enum falloc_mode
  {
    /**
     * Clear disowned memory.
     * 
     * @since  Always.
     */
    FALLOC_CLEAR = 1,
    
    /**
     * Initialise new memory.
     * 
     * @since  Always.
     */
    FALLOC_INIT = 2,
    
    /**
     * If a new allocation is created, copy the data
     * from the old allocation over to the new allocation.
     * 
     * @since  Always.
     */
    FALLOC_MEMCPY = 4,
    
  };


/**
 * This function is identical to `free`, except it is guaranteed not to
 * override the memory segment with zeroes before freeing the allocation.
 * 
 * `errno` is guaranteed not to be set.
 * 
 * @etymology  (Fast) variant of (`free`).
 * 
 * @param  segment  The memory segment to free.
 * 
 * @since  Always.
 */
void fast_free(void*);

/**
 * This function is identical to `free`, except it is guaranteed to
 * override the memory segment with zeroes before freeing the allocation.
 * 
 * `errno` is guaranteed not to be set.
 * 
 * @etymology  (Secure) variant of (`free`).
 * 
 * @param  segment  The memory segment to free.
 * 
 * @since  Always.
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
 * @etymology  Memory (alloc)ation (size).
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
 * 
 * @since  Always.
 */
size_t allocsize(void*)
  __GCC_ONLY(__attribute__((__warn_unused_result__)))
  __warning("This function is dangerous, avoid using it instead of manual bookkeeping.");

/**
 * Variant of `realloc` that overrides newly allocated space
 * with zeroes. Additionally, it will override any freed space
 * with zeroes, including the old allocation if it creates a
 * new allocation.
 * 
 * @etymology  (C)lear and (realloc)ate memory.
 * 
 * @param   ptr   The old allocation, see `realloc` for more details.
 * @param   size  The new allocation size, see `realloc` for more details.
 * @return        The new allocation, see `realloc` for more details.
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 * 
 * @since  Always.
 */
void* crealloc(void*, size_t)
  __GCC_ONLY(__attribute__((__warn_unused_result__)));

/**
 * This function behaves exactly like `realloc`, except it is
 * guaranteed to never initialise or errors data.
 * 
 * @etymology  (Fast) variant of (`realloc`).
 * 
 * @param   ptr   The old allocation, see `realloc` for more details.
 * @param   size  The new allocation size, see `realloc` for more details.
 * @return        The new allocation, see `realloc` for more details.
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 * 
 * @since  Always.
 */
void* fast_realloc(void*, size_t)
  __GCC_ONLY(__attribute__((__warn_unused_result__)));

/**
 * This function behaves exactly like `crealloc`, except it
 * does not initialise newly allocated size.
 * 
 * @etymology  (Secure) variant of (`realloc`).
 * 
 * @param   ptr   The old allocation, see `realloc` for more details.
 * @param   size  The new allocation size, see `realloc` for more details.
 * @return        The new allocation, see `realloc` for more details.
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 * 
 * @since  Always.
 */
void* secure_realloc(void*, size_t)
  __GCC_ONLY(__attribute__((__warn_unused_result__)));

/**
 * This function behaves exactly like `realloc`,
 * except you can freely select what memory it clears.
 * 
 * `crealloc(p, n)` is equivalent to (but slightly fast than)
 * `custom_realloc(p, n, 1, 1, 1)`.
 * 
 * `fast_realloc(p, n)` is equivalent to (but slightly fast than)
 * `custom_realloc(p, n, 0, 0, 0)`.
 * 
 * `secure_realloc(p, n)` is equivalent to (but slightly fast than)
 * `custom_realloc(p, n, 1, 0, 1)`.
 * 
 * @etymology  (Custom)isable variant of (`realloc`).
 * 
 * @param   ptr         The old allocation, see `realloc` for more details.
 * @param   size        The new allocation size, see `realloc` for more details.
 * @param   clear_old   Whether the disowned area is cleared, even if `ptr` is returned.
 * @param   clear_new   Whether the newly claimed area is cleared.
 * @param   clear_free  Whether the old allocation is cleared if a new pointer is returned.
 * @return              The new allocation, see `realloc` for more details.
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 * 
 * @since  Always.
 */
void* custom_realloc(void*, size_t, int, int, int)
  __GCC_ONLY(__attribute__((__warn_unused_result__)));

/**
 * This function is similar to `realloc`, however it
 * does not copy the data in the memory segment when
 * a new pointer is created. Additionally, the
 * behaviour is undefined if `ptr` is `NULL`, `size`
 * is zero, or `size` equals the old allocation size.
 * These additional quirks were added to improve
 * performance; after all, this function was added
 * to improve performance.
 * 
 * The behaviour is undefined if `mode` does not
 * contain a valid flag-combination.
 * 
 * @etymology  (Ext)end memory (alloc)ation.
 * 
 * @param   ptr   The old allocation, see `realloc` for more details.
 * @param   size  The new allocation size, see `realloc` for more details.
 * @param   mode  `EXTALLOC_CLEAR` or `EXTALLOC_MALLOC`, or both or neither.
 * @return        The new allocation, see `realloc` for more details.
 *                If `EXTALLOC_MALLOC` is not used, `NULL` is returned
 *                and `errno` set to zero, if a new allocation is required.
 * 
 * @throws  0       `errno` is set to zero success if `NULL` is returned.
 * @throws  ENOMEM  The process cannot allocate more memory.
 * 
 * @since  Always.
 */
void* extalloc(void*, size_t, enum extalloc_mode)
  __GCC_ONLY(__attribute__((__nonnull__, __warn_unused_result__)));

/**
 * This function is similar to `realloc`, however its
 * behaviour and pointer alignment can be tuned.
 * 
 * @etymology  (Re)allocate (mem)ory and (align).
 * 
 * @param   ptr       The old allocation, see `realloc` for more details.
 * @param   boundary  The alignment, not checked before necessary.
 * @param   size      The new allocation size, see `realloc` for more details.
 * @param   mode      `REMEMALIGN_CLEAR`, `REMEMALIGN_INIT`, or
 *                    `REMEMALIGN_MEMCPY`, or both or neither.
 * @return            The new allocation, see `realloc` for more details.
 * 
 * @throws  0       `errno` is set to zero success if `NULL` is returned.
 * @throws  EINVAL  `mode` is invalid, or `boundary` is not a power of two.
 * @throws  ENOMEM  The process cannot allocate more memory.
 * 
 * @since  Always.
 */
void* rememalign(void*, size_t, size_t, enum rememalign_mode)
  __GCC_ONLY(__attribute__((__warn_unused_result__)));

/**
 * This function behaves exactly like `fast_realloc`, except:
 * - Its behaviour is undefined if `ptr` is `NULL`.
 * - Its behaviour is undefined if `size` equals the old allocation size.
 * - Its behaviour is undefined if `size` is zero.
 * - It will never free `ptr`.
 * - The alignment of new pointers can be specified.
 * 
 * This function cannot be used to force realignment,
 * the aligment is applied when it is necessary to
 * create a new allocation.
 * 
 * @etymology  (Naïve) variant of (`realloc`).
 * 
 * @param   ptr       The old allocation, see `realloc` for more details.
 * @param   boundary  The alignment, not checked before necessary.
 * @param   size      The new allocation size, see `realloc` for more details.
 * @return            The new allocation, see `realloc` for more details.
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 * 
 * @since  Always.
 */
void* naive_realloc(void*, size_t, size_t) /* sic! we limit ourself to ASCII */
  __GCC_ONLY(__attribute__((__nonnull__, __warn_unused_result__)));

/**
 * This function behaves exactly like `naive_realloc`, except
 * it will return `NULL` with `errno` set to zero, if it is
 * not possible to perform the shrink or grow without creating
 * new pointer.
 * 
 * @etymology  (Naïve) variant of (`extalloc`).
 * 
 * @param   ptr   The old allocation, see `realloc` for more details.
 * @param   size  The new allocation size, see `realloc` for more details.
 * @return        `ptr` on success or `NULL` on error or if `malloc` is needed.
 * 
 * @throws  0       `malloc` is require to perform the action.
 * @throws  ENOMEM  The process cannot allocate more memory.
 * 
 * @since  Always.
 */
void* naive_extalloc(void*, size_t) /* sic! we limit ourself to ASCII */
  __GCC_ONLY(__attribute__((__nonnull__, __warn_unused_result__)));

/**
 * Allocates, deallocates, or reallocates memory without
 * bookkeeping. The created allocation may not be inspected,
 * deallocated, or reallocated with any other function than
 * this function.
 * 
 * If `new_size` is zero and `ptr` is `NULL`,
 *   nothing happens, but `errno` is set to zero and `NULL`
 *   is returned.
 * If `new_size` is non-zero, `old_size` is zero, and `ptr`
 *   is not `NULL` or if `new_size` and `old_size` is non-zero,
 *   and `ptr` is `NULL`, `errno` is set to `EINVAL` and `NULL`
 *   is returned.
 * If `new_size` and `old_size` is zero and `ptr` is not `NULL`,
 *   `errno` is set to `EINVAL` and `NULL` is returned.
 * If `new_size` is zero, `old_size` is non-zero, and `ptr`
 *   is not `NULL`, `ptr` is deallocated, and `NULL` is returned
 *   with `errno` set to zero. The memory cleared before it is
 *   deallocated if `mode & FALLOC_CLEAR`.
 * If `new_size` is non-zero, `old_size` is zero, and `ptr` is
 *   `NULL`, a new allocation is created of `new_size` bytes.
 *   It will be zero-initialised if `mode & FALLOC_INIT`.
 * If `new_size` and `old_size` is non-zero and `ptr` is not
 *   `NULL`, `ptr` is reallocated. if the allocation is shrunk,
 *   the disowned area is cleared if `mode & FALLOC_CLEAR`.
 *   Newly available memory is zero-initialised if
 *   `mode & FALLOC_INIT`. If a new allocation is required,
 *   the data from the old allocation is only copied over to
 *   the new allocation if `mode & FALLOC_MEMCPY`. If
 *   `(mode & FALLOC_INIT) && !(mode & FALLOC_MEMCPY)`, the
 *   entire allocation will be cleared.
 * 
 * @etymology  (F)ast memory (alloc)ation.
 * 
 * @param   ptr        The old pointer, `NULL` if a new shall be created.
 * @param   ptrshift   Pointer that is used to keep track of the pointer's
 *                     shift for alignment. `NULL` if the shift shall not
 *                     be tracked. If this is the case, `falloc` cannot
 *                     be used to reallocate or deallocate an allocation,
 *                     unless the pointer is unaligned (`alignment <= 1`).
 * @param   alignment  The aligment of both the new and old pointer, zero
 *                     or one if it should not be aligned.
 * @param   old_size   The old allocation size, zero if a new shall be created.
 * @param   new_size   The new allocation size, zero if it shall be freed.
 * @param   mode       `FALLOC_CLEAR`, `FALLOC_INIT`, or `FALLOC_MEMCPY`, or
 *                     both or neither.
 * @return             The new pointer, or the old pointer if it was reallocated
 *                     without creating a new allocation. `NULL` is returned
 *                     if `new_size` (errno is set to zero) is zero, or on error
 *                     (errno is set to describe the error.)
 * 
 * @throws  0       `new_size` is zero.
 * @throws  EINVAL  The arguments are invalid.
 * @throws  ENOMEM  The process cannot allocate more memory.
 * 
 * @since  Always.
 */
void* falloc(void*, size_t*, size_t, size_t, size_t, enum falloc_mode);


/**
 * This macro calls `fast_free` and then sets the pointer to `NULL`,
 * so that another attempt to free the segment will not crash the process.
 * 
 * @etymology  Macro version of (`fast_free`).
 * 
 * @since  Always.
 */
#define FAST_FREE(segment)  (fast_free(segment), (void)((segment) = NULL));

/**
 * This macro calls `secure_free` and then sets the pointer to `NULL`,
 * so that another attempt to free the segment will not crash the process.
 * 
 * @etymology  Macro version of (`secure_free`).
 * 
 * @since  Always.
 */
#define SECURE_FREE(segment)  (secure_free(segment), (void)((segment) = NULL));



#endif
#endif

