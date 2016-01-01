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
#include <slibc-alloc.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
/* TODO #include <sys/mman.h> */



/**
 * Get the alignment-shift of a pointer.
 * 
 * @param   p:void*  The pointer.
 * @return  :size_t  The number of bytes added for alignment.
 *                   This excludes the information this macro
 *                   reads, and the storage of the allocation-size.
 */
#define __ALIGN(p)      (*(size_t*)(((char*)(p)) - sizeof(size_t)))

/**
 * Get the allocated pointer from a returned pointer.
 * 
 * @param   p:void*  The pointer returned by a `malloc`-family function.
 * @return           The pointer allocated by a `malloc`-family function.
 */
#define PURE_ALLOC(p)   (((char*)(p)) - (__ALIGN(p) + 2 * sizeof(size_t)))

/**
 * Get the real allocation is of a pointer, including
 * the size of the metadata storage and the alignment-padding.
 * 
 * @param   p:void*  The pointer.
 * @return  :size_t  The real allocation size of the pointer.
 */
#define PURE_SIZE(p)    (*(size_t*)PURE_ALLOC(p) + 2 * sizeof(size_t))



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
void fast_free(void* segment)
{
  int saved_errno = errno;
  if (segment == NULL)
    return;
  munmap(PURE_ALLOC(segment), PURE_SIZE(segment));
  errno = saved_errno;
}


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
void secure_free(void* segment)
{
  int saved_errno = errno;
  if (segment == NULL)
    return;
  explicit_bzero(PURE_ALLOC(segment), PURE_SIZE(segment));
  fast_free(segment);
  errno = saved_errno;
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
size_t allocsize(void* segment)
{
  if (segment == NULL)
    {
      errno = EINVAL;
      return 0;
    }
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
#define REALLOC(ptr, size, CLEAR_OLD, CLEAR_NEW, CLEAR_FREE)		\
  size_t old_size;							\
  void* new_ptr;							\
									\
  if (size == 0)							\
    return secure_free(ptr), NULL;					\
			   						\
  if (ptr == NULL)	   						\
    return CLEAR_NEW ? malloc(size) : calloc(1, size);			\
			   						\
  old_size = allocsize(ptr);						\
  if (old_size == size)							\
    return ptr;								\
									\
  if (CLEAR_OLD ? (old_size > size) : 0)				\
    explicit_bzero(((char*)ptr) + size, old_size - size);		\
									\
  new_ptr = naive_realloc(ptr, sizeof(max_align_t), size);		\
  if (new_ptr != ptr)							\
    {									\
      if (new_ptr == NULL)						\
	return NULL;							\
      if (CLEAR_FREE)							\
	explicit_bzero(PURE_ALLOC(ptr), PURE_SIZE(ptr));		\
      fast_free(ptr);							\
    }									\
									\
  if (CLEAR_NEW ? (old_size < size) : 0)				\
    explicit_bzero(((char*)new_ptr) + old_size, size - old_size);	\
									\
  return new_ptr


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
void* crealloc(void* ptr, size_t size)
{
  REALLOC(ptr, size, 1, 1, 1);
}


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
void* fast_realloc(void* ptr, size_t size)
{
  REALLOC(ptr, size, 0, 0, 0);
}


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
void* extalloc(void* ptr, size_t size, enum extalloc_mode mode)
{
  int clear = mode & EXTALLOC_CLEAR;
  size_t old_size = allocsize(ptr);
  void* new_ptr;
  
  if (clear ? (old_size > size) : 0)
    explicit_bzero(((char*)ptr) + size, old_size - size);
  
  new_ptr = (mode & EXTALLOC_MALLOC)
	     ? naive_realloc(ptr, sizeof(max_align_t), size)
	     : naive_extalloc(ptr, size);
  if ((new_ptr != ptr) && (new_ptr != NULL))
    {
      if (clear)
	explicit_bzero(PURE_ALLOC(ptr), PURE_SIZE(ptr));
      fast_free(ptr);
    }
  
  return new_ptr;
}


/**
 * This function is similar to `realloc`, however its
 * behaviour and pointer alignment can be tuned.
 * 
 * This function cannot be used to force realignment,
 * the aligment is applied when it is necessary to
 * create a new allocation.
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
void* rememalign(void* ptr, size_t boundary, size_t size, enum rememalign_mode mode)
{
  int conf_clear  = mode & REMEMALIGN_CLEAR;
  int conf_init   = mode & REMEMALIGN_INIT;
  int conf_memcpy = mode & REMEMALIGN_MEMCPY;
  size_t old_size;
  void* new_ptr;
  
  if ((enum rememalign_mode)(conf_clear | conf_init | conf_memcpy) != mode)
    return errno = EINVAL, NULL;
  
  if (size == 0)
    return secure_free(ptr), NULL;
  
  if (ptr == NULL)
    {
      new_ptr = memalign(boundary, size);
      if ((new_ptr != NULL) && conf_init)
	bzero(new_ptr, size);
      return new_ptr;
    }
  
  old_size = allocsize(ptr);
  if (old_size == size)
    return ptr;
  
  if (conf_clear ? (old_size > size) : 0)
    explicit_bzero(((char*)ptr) + size, old_size - size);
  
  if (conf_memcpy)
    new_ptr = naive_realloc(ptr, boundary, size);
  else
    {
      new_ptr = naive_extalloc(ptr, size);
      if ((new_ptr == NULL) && (errno == 0))
	new_ptr = memalign(boundary, size);
    }
  if (new_ptr != ptr)
    {
      if (new_ptr == NULL)
	return NULL;
      if (conf_clear)
	explicit_bzero(PURE_ALLOC(ptr), PURE_SIZE(ptr));
      fast_free(ptr);
    }
  
  if (conf_init ? (old_size < size) : 0)
    explicit_bzero(((char*)new_ptr) + old_size, size - old_size);
  
  return new_ptr;
}


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
 * @throws  EINVAL  `boundary` is not a power of two.
 * @throws  ENOMEM  The process cannot allocate more memory.
 * 
 * @since  Always.
 */
void* naive_realloc(void* ptr, size_t boundary, size_t size)
{
  /* TODO implementation of naive_realloc with reallocation */
  return memalign(boundary, size);
  (void) ptr;
}


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
void* naive_extalloc(void* ptr, size_t size)
{
  /* TODO implement naive_extalloc */
  return errno = 0, NULL;
  (void) ptr, (void) size;
}


/**
 * Reallocation procedure for `falloc`.
 * 
 * @param   ptr        The old pointer.
 * @param   ptrshift   Pointer that is used to keep track of the pointer's
 *                     shift for alignment.
 * @param   alignment  The aligment of both the new and old pointer.
 * @param   old_size   The old allocation size.
 * @param   new_size   The new allocation size.
 * @param   mode       `FALLOC_CLEAR`, `FALLOC_INIT`, or `FALLOC_MEMCPY`, or
 *                     both or neither.
 * @return             The new pointer, or the old pointer if it was reallocated
 *                     without creating a new allocation. `NULL` is returned
 *                     on error (errno is set to describe the error.)
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 * 
 * @since  Always.
 */
__GCC_ONLY(__attribute__((nonnull)))
static inline void* falloc_realloc(void* ptr, size_t* ptrshift, size_t alignment,
				   size_t old_size, size_t new_size, enum falloc_mode mode)
{
  void* new_ptr = NULL;
  size_t shift = *ptrshift;
  
  if ((mode & FALLOC_CLEAR) && (old_size > new_size))
    explicit_bzero(ptr + new_size, old_size - new_size);
  
  new_ptr = falloc_extalloc(ptr - shift, old_size + shift, new_size + shift);
  if ((new_ptr == NULL) && (errno == 0))
    {
      new_ptr = falloc_malloc(new_size + alignment - 1);
      if (new_ptr != NULL)
	{
	  if ((size_t)new_ptr % alignment)
	    shift = alignment - ((size_t)new_ptr % alignment);
	  *ptrshift = shift;
	  new_ptr = (void*)((char*)new_ptr + shift);
	  if (mode & FALLOC_MEMCPY)
	    memcpy(new_ptr, ptr, old_size);
	}
    }
  
  return new_ptr;
}


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
void* falloc(void* ptr, size_t* ptrshift, size_t alignment,
	     size_t old_size, size_t new_size, enum falloc_mode mode)
{
  /* TODO implement falloc_malloc, falloc_free, and falloc_extalloc */
  
  size_t shift = 0, _ptrshift = 0;
  void* new_ptr = NULL;
  
  if (mode & (enum falloc_mode)~(FALLOC_CLEAR | FALLOC_INIT | FALLOC_MEMCPY))
    goto invalid;
  
  if (new_size && old_size && ptr)
    {
      if ((alignment > 1) && !ptrshift)    goto invalid;
      new_ptr = falloc_realloc(ptr, ptrshift ? ptrshift : &_ptrshift,
			       alignment ? alignment : 1,
			       old_size, new_size, mode, &shift);
      shift = ptrshift ? *ptrshift : _ptrshift;
    }
  else if (new_size && (old_size || ptr))  goto invalid;
  else if (new_size)                       new_ptr = falloc_malloc(new_size);
  else if (old_size && ptr)                goto deallocate;
  else if (old_size || !ptr)               goto return_null;
  else                                     goto invalid;
  
  if (new_ptr != NULL)
    {
      if ((new_ptr != ptr) && (ptr != NULL))
	{
	  if (mode & FALLOC_CLEAR)
	    explicit_bzero(ptr, old_size);
	  falloc_free(ptr - shift);
	}
      if (mode & FALLOC_INIT)
	{
	  if (!(mode & FALLOC_MEMCPY))
	    old_size = 0;
	  if (new_size > old_size)
	    bzero(new_ptr + old_size, new_size - old_size);
	}
    }
  
  return errno = 0, new_ptr;
  
 deallocate:
  shift = ptrshift == NULL ? *ptrshift : 0;
  if ((alignment > 1) && (ptrshift == NULL))
    goto invalid;
  if (mode & FALLOC_CLEAR)
    explicit_bzero(ptr, old_size);
  falloc_free(ptr - shift);
 return_null:
  return errno = 0, NULL;
  
 invalid:
  return errno = EINVAL, NULL;
}

