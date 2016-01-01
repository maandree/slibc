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
#include <slibc/internals.h>
#include <stddef.h>
#include <slibc-alloc.h>
#include <strings.h>
/* TODO #include <sys/mman.h> */
#include <unistd.h>
#include <errno.h>
/* TODO temporary constants from other headers { */
#define PROT_READ 0
#define PROT_WRITE 0
#define MAP_PRIVATE 0
#define MAP_ANONYMOUS 0
#define _SC_PAGESIZE 0
/* } */


/**
 * Implementation of `malloc`.
 */
#define MALLOC(size)  memalign(sizeof(max_align_t), size)



/**
 * Return the pagesize. If it it cannot be retrieved,
 * use a fallback value.
 * 
 * @return  The pagesize, or a fallback value.
 */
__attribute__((__warn_unused_result__, const))
static size_t get_pagesize(void)
{
  static size_t pagesize = 0;
  if (pagesize == 0)
    {
      /* TODO This should be done i crt0. */
      long r = sysconf(_SC_PAGESIZE);
      pagesize = (size_t)(r == -1 ? 4096 : r);
    }
  return pagesize;
}


/**
 * Create a new memory allocation on the heap.
 * The allocation will not be initialised.
 * The returned pointer is unaligned.
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
static void* unaligned_malloc(size_t size)
{
  char* ptr;
  size_t full_size;
  
  if (size == 0)
    return NULL;
  MEM_OVERFLOW(uaddl, 2 * sizeof(size_t), size, &full_size);
  
  ptr = mmap(NULL, full_size, (PROT_READ | PROT_WRITE),
	     (MAP_PRIVATE | MAP_ANONYMOUS), -1, 0);
  if (ptr == MAP_FAILED)
    return NULL;
  
  ((size_t*)ptr)[0] = size;
  ((size_t*)ptr)[1] = 0;
  return ptr + 2 * sizeof(size_t);
}


/**
 * Create a new memory allocation on the heap.
 * The allocation will not be initialised.
 * The returned pointer has an alignment usable
 * for any compiler-independent intrinsic data type.
 * 
 * @etymology  (M)emory (alloc)ation.
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
 * 
 * @since  Always.
 */
void* malloc(size_t size)
{
  return MALLOC(size);
}


/**
 * Variant of `malloc` that clears the allocation with zeroes.
 * 
 * `p = calloc(n, m)` is equivalent to
 * `(p = malloc(n * m), p ? (explicit_bzero(p, n * m), p) : NULL)`
 * 
 * @etymology  (C)leared memory (alloc)ation.
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
 * 
 * @since  Always.
 */
void* calloc(size_t elem_count, size_t elem_size)
{
  void* ptr;
  size_t size;
  
  MEM_OVERFLOW(umull, elem_count, elem_size, &size);
  ptr = MALLOC(size);
  if (ptr != NULL)
    explicit_bzero(ptr, size);
  
  return ptr;
}


/**
 * Variant of `malloc` that conditionally clears the allocation with zeroes.
 * 
 * `mallocz(size, clear)` is equivalent to
 *  both `(clear ? zalloc : malloc)(size)`
 *  and `(clear ? calloc(1, size) : malloc(size))`.
 * 
 * This is a Plan 9 from Bell Labs extension.
 * 
 * @etymology  (M)emory (alloc)ation with potential (z)eroing.
 * 
 * @param   size   The size of the allocation.
 * @param   clear  Clear the allocation unless this value is zero.
 * @return         Pointer to the beginning of the new allocation.
 *                 If `size` is zero, this function will either return
 *                 `NULL` (that is what this implement does) or return
 *                 a unique pointer that can later be freed with `free`.
 *                 `NULL` is returned on error, and `errno` is set to
 *                 indicate the error.
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 * 
 * @since  Always.
 */
void* mallocz(size_t size, int clear)
{
  void* ptr = MALLOC(size);
  if ((ptr != NULL) && clear)
    explicit_bzero(ptr, size);
  return ptr;
}


/**
 * Variant of `malloc` that clears the allocation with zeroes.
 * 
 * `zalloc(n)` is equivalent to `calloc(1, n)`, or equivalently,
 * `calloc(n, m)` is equivalent to `zalloc(n * m)` assuming `n * m`
 * does not overflow (in which case `calloc(n, m)` returns `ENOMEM`.)
 * 
 * This is a klibc extension.
 * 
 * @etymology  (Z)eroed memory (alloc)ation.
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
 * 
 * @since  Always.
 */
void* zalloc(size_t size)
{
  void* ptr = MALLOC(size);
  if (ptr != NULL)
    explicit_bzero(ptr, size);
  return ptr;
}


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
 * @etymology  (Mem)ory alignment.
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
void* memalign(size_t boundary, size_t size)
{
  char* ptr;
  size_t full_size;
  size_t address;
  size_t shift = 0;
  
  if (!boundary || (__builtin_ffsl((long int)boundary) != boundary))
    /* `size_t` mat not be wider than `long int`. */
    return errno = EINVAL, NULL;
  MEM_OVERFLOW(uaddl, boundary - 1, size, &full_size);
  
  ptr = unaligned_malloc(full_size);
  if (ptr == NULL)
    return NULL;
  
  address = (size_t)ptr;
  if (address % boundary != 0)
    {
      shift = boundary - (address % boundary);
      ptr += shift;
      *(size_t*)(ptr - sizeof(size_t)) = shift;
    }
  
  return ptr;
}


/**
 * `valloc(n)` is equivalent to `memalign(sysconf(_SC_PAGESIZE), n)`.
 * 
 * As a GNU-compliant slibc extension, memory allocated
 * with this function can be freed with `free`.
 * 
 * @etymology  Whole-(v)irtual-memory-page aligned memory (alloc)ation.
 * 
 * @param   size  The number of bytes to allocated.
 * @return        Pointer to the beginning of the new allocation.
 *                If `size` is zero, this function will either return
 *                `NULL` (that is what this implement does) or return
 *                a unique pointer that can later be freed with `free`.
 *                `NULL` is returned on error, and `errno` is set to
 *                indicate the error.
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 * 
 * @since  Always.
 */
void* valloc(size_t size)
{
  return memalign(get_pagesize(), size);
}


/**
 * This function works like `valloc`, except the allocation size,
 * including auxiliary space, is rounded up to the next multiple
 * of the page size.
 * 
 * @etymology  Whole-(p)age-allocation variant of (`valloc`).
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
 * 
 * @since  Always.
 */
void* pvalloc(size_t size)
{
  size_t boundary = get_pagesize();
  size_t full_size = 2 * sizeof(size_t) + boundary - 1 + size;
  size_t rounding = 0;
  
  if (full_size % boundary != 0)
      rounding = boundary - (full_size % boundary);
  
  MEM_OVERFLOW(uaddl, size, rounding, &full_size);
  return memalign(boundary, full_size);
}

