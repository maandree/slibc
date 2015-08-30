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



#define PURE_ALLOC(p)  (((char*)(p)) - sizeof(size_t))
#define PURE_SIZE(z)  ((z) + sizeof(size_t))



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
  munmap(PURE_ALLOC(segment), PURE_SIZE(*(size_t*)segment));
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
  explicit_bzero(PURE_ALLOC(segment), PURE_SIZE(allocsize(segment)));
  fast_free(segment);
}


/**
 * This function returns the allocation size of
 * a memory segment.
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
      if (CLEAR_FREE)						\
	explicit_bzero(PURE_ALLOC(ptr), PURE_SIZE(old_size));	\
      fast_free(new_ptr);					\
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
void* naive_realloc(void* ptr, size_t size)
{
  /* TODO improve implementation of naive_realloc */
  return malloc(size);
  (void) ptr;
}

