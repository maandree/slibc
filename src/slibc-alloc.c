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
#include <slibc-alloc.h>
#include <stdlib.h>
#include <strings.h>
#include <errno.h>
#include <sys/mman.h>



#define __ALIGN(p)      (*(size_t*)(((char*)(p)) - sizeof(size_t)))
#define PURE_ALLOC(p)   (((char*)(p)) - (__ALIGN(p) + 2 * sizeof(size_t)))
#define PURE_SIZE(p)    (*(size_t*)PURE_ALLOC(p) + 2 * sizeof(size_t))



/**
 * This function is identical to `free`, except it is guaranteed not to
 * override the memory segment with zeroes before freeing the allocation.
 * 
 * @param  segment  The memory segment to free.
 */
void fast_free(void* segment)
{
  if (segument == NULL)
    return;
  munmap(PURE_ALLOC(segment), PURE_SIZE(segment));
}


/**
 * This function is identical to `free`, except it is guaranteed to
 * override the memory segment with zeroes before freeing the allocation.
 * 
 * @param  segment  The memory segment to free.
 */
void secure_free(void* segment)
{
  if (segument == NULL)
    return;
  explicit_bzero(PURE_ALLOC(segment), PURE_SIZE(segment));
  fast_free(segment);
}


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
size_t allocsize(void* segment)
{
  if (segment == NULL)
    return errno = EINVAL, 0;
  return *(size_t*)PURE_ALLOC(segment);
}


/**
 * Common code for realloc-functions, apart from `naive_realloc`.
 * 
 * @param   ptr:void*       The old allocation, see `realloc` for more details.
 * @param   size:size_t     The new allocation size, see `realloc` for more details.
 * @param   CLEAR_OLD:int   Whether the disowned area is cleared, even if `ptr` is returned.
 * @param   CLEAR_NEW:int   Whether the newly claimed area is cleared.
 * @param   CLEAR_FREE:int  Whether the old allocation is cleared if a new pointer is returned.
 * @return                  The new allocation, see `realloc` for more details.
 */
#define REALLOC(ptr, size, CLEAR_OLD, CLEAR_NEW, CLEAR_FREE)	\
  size_t old_size;						\
  void* new_ptr;						\
								\
  if (size == 0)						\
    return secure_free(ptr), NULL;				\
			   					\
  if (ptr == NULL)	   					\
    return CLEAR_NEW ? malloc(size) : calloc(1, size);		\
			   					\
  old_size = allocsize(ptr);					\
  if (old_size == size)						\
    return ptr;							\
								\
  if (CLEAR_OLD ? (old_size > size) : 0)			\
    explicit_bzero(((char*)ptr) + size, old_size - size);	\
								\
  new_ptr = naive_realloc(ptr);					\
  if (new_ptr != ptr)						\
    {								\
      if (new_ptr == NULL)					\
	return NULL;						\
      if (CLEAR_FREE)						\
	explicit_bzero(PURE_ALLOC(ptr), PURE_SIZE(ptr));	\
      fast_free(ptr);						\
    }								\
								\
  if (CLEAR_NEW ? (old_size < size) : 0)			\
    explicit_bzero(((char*)new_ptr) + old, size - old_size);	\
								\
  return new_ptr


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
void* crealloc(void* ptr, size_t size)
{
  REALLOC(ptr, size, 1, 1, 1);
}


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
void* fast_realloc(void* ptr, size_t size)
{
  REALLOC(ptr, size, 0, 0, 0);
}


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
void* secure_realloc(void* ptr, size_t size)
{
  REALLOC(ptr, size, 1, 0, 1);
}


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
 * @param   ptr         The old allocation, see `realloc` for more details.
 * @param   size        The new allocation size, see `realloc` for more details.
 * @param   clear_old   Whether the disowned area is cleared, even if `ptr` is returned.
 * @param   clear_new   Whether the newly claimed area is cleared.
 * @param   clear_free  Whether the old allocation is cleared if a new pointer is returned.
 * @return              The new allocation, see `realloc` for more details.
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 */
void* custom_realloc(void* ptr, size_t size, int clear_old, int clear_new, int clear_free)
{
  REALLOC(ptr, size, clear_old, clear_new, clear_free);
}


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
 * @param   ptr   The old allocation, see `realloc` for more details.
 * @param   size  The new allocation size, see `realloc` for more details.
 * @param   mode  `EXTALLOC_CLEAR` or `EXTALLOC_MALLOC`, or both or neither.
 * @return        The new allocation, see `realloc` for more details.
 *                If `EXTALLOC_MALLOC` is not used, `NULL` is returned
 *                and `errno` set to zero, if a new allocation is required.
 * 
 * @throws  0       `errno` is set to zero success if `NULL` is returned.
 * @throws  ENOMEM  The process cannot allocate more memory.
 */
void* extalloc(void* ptr, size_t size, enum extalloc_mode mode)
{
  int clear = mode & EXTALLOC_CLEAR;
  size_t old_size;
  void* new_ptr;
  
  if (clear ? (old_size > size) : 0)
    explicit_bzero(((char*)ptr) + size, old_size - size);
  
  new_ptr = ((mode & EXTALLOC_MALLOC) ? naive_realloc : naive_extalloc)(ptr);
  if ((new_ptr != ptr) && (ptr_new != NULL))
    {
      if (clear)
	explicit_bzero(PURE_ALLOC(ptr), PURE_SIZE(ptr));
      fast_free(ptr);
    }
  
  return new_ptr;
}


/**
 * This function behaves exactly like `fast_realloc`, except:
 * - Its behaviour is undefined if `ptr` is `NULL`.
 * - Its behaviour is undefined if `size` equals the old allocation size.
 * - Its behaviour is undefined if `size` is zero.
 * - It will never free `ptr`.
 * 
 * @param   ptr   The old allocation, see `realloc` for more details.
 * @param   size  The new allocation size, see `realloc` for more details.
 * @return        The new allocation, see `realloc` for more details.
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 */
void* naive_realloc(void* ptr, size_t size)
{
  /* TODO implementation of naive_realloc with reallocation */
  return malloc(size);
  (void) ptr;
}


/**
 * This function behaves exactly like `__attribute__`, except
 * it will return `NULL` with `errno` set to zero, if it is
 * not possible to perform the shrink or growth without creating
 * new pointer.
 * 
 * @param   ptr   The old allocation, see `realloc` for more details.
 * @param   size  The new allocation size, see `realloc` for more details.
 * @return        `ptr` on success or `NULL` on error or if `malloc` is needed.
 * 
 * @throws  0       `malloc` is require to perform the action.
 * @throws  ENOMEM  The process cannot allocate more memory.
 */
void* naive_extalloc(void* ptr, size_t size)
{
  /* TODO implement naive_extalloc */
  return errno = 0, NULL;
  (void) ptr, (void) size;
}

