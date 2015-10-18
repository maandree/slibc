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
#include <stdlib.h>
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
  if (__builtin_uaddl_overflow(2 * sizeof(size_t), size, &full_size))
    return errno = ENOMEM, NULL;
  
  ptr = mmap(NULL, full_size, (PROT_READ | PROT_WRITE),
	     (MAP_PRIVATE | MAP_ANONYMOUS), -1, 0);
  
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
void* malloc(size_t size)
{
  return memalign(sizeof(max_align_t), size);
}


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
void* calloc(size_t elem_count, size_t elem_size)
{
  void* ptr;
  size_t size;
  
  if (__builtin_umull_overflow(elem_count, elem_size, &size))
    return errno = ENOMEM, NULL;
  
  ptr = malloc(size);
  if (ptr != NULL)
    explicit_bzero(ptr, size);
  
  return ptr;
}


/**
 * Variant of `malloc` that clears the allocation with zeroes.
 * 
 * `zalloc(n)` is equivalent to `calloc(1, n)`, or equivalently,
 * `calloc(n, m)` is equivalent to `zalloc(n * m)` assumming `n * m`
 * does not overflow (in which case `calloc(n, m)` returns `ENOMEM`.)
 * 
 * This is a klibc extension.
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
void* zalloc(size_t size)
{
  return calloc(1, size);
}


/**
 * Variant of `malloc` that extends, or shrinks, an existing allocation,
 * if beneficial and possible, or creates a new allocation with the new
 * size, copies the data, and frees the old allocation. The returned
 * pointer has an alignment usable for any compiler-independent intrinsic
 * data type, if a new pointer is returned.
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
void* realloc(void* ptr, size_t size)
{
  return fast_realloc(ptr, size);
}


/**
 * Free a memory allocation.
 * 
 * @param  ptr  Pointer to the beginning of the memory allocation.
 *              The process may crash if it does not point to the
 *              beginning of a memory allocation on the heap.
 *              However, if it is `NULL`, nothing will happen.
 */
void free(void* ptr)
{
  fast_free(ptr);
}


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
void cfree(void* ptr, ...)
{
  fast_free(ptr);
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
void* memalign(size_t boundary, size_t size)
{
  char* ptr;
  size_t full_size;
  size_t address;
  size_t shift = 0;
  
  if (!boundary || (__builtin_ffsl((long int)boundary) != boundary))
    /* `size_t` mat not be wider than `long int`. */
    return errno = EINVAL, NULL;
  if (__builtin_uaddl_overflow(boundary - 1, size, &full_size))
    return errno = ENOMEM, NULL;
  
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
int posix_memalign(void** ptrptr, size_t boundary, size_t size)
{
  if (boundary < sizeof(void*))
    return EINVAL;
  *ptrptr = memalign(boundary, size);
  return *ptrptr ? 0 : errno;
}


/**
 * `valloc(n)` is equivalent to `memalign(sysconf(_SC_PAGESIZE), n)`.
 * 
 * As a GNU-compliant slibc extension, memory allocated
 * with this function can be freed with `free`.
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
 */
void* valloc(size_t size)
{
  return memalign((size_t)sysconf(_SC_PAGESIZE), size);
}


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
void* pvalloc(size_t size)
{
  size_t boundary = (size_t)sysconf(_SC_PAGESIZE);
  size_t full_size = 2 * sizeof(size_t) + boundary - 1 + size;
  size_t rounding = 0;
  
  if (full_size % boundary != 0)
      rounding = boundary - (full_size % boundary);
  
  if (__builtin_uaddl_overflow(size, rounding, &full_size))
    return errno = ENOMEM, NULL;
  
  return memalign(boundary, full_size);
}


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
void* aligned_alloc(size_t boundary, size_t size)
{
  return memalign(boundary, size);
}


/**
 * This function returns the allocation size of
 * a memory segment.
 * 
 * `p = malloc(n), malloc_usable_size(p)` will return `n`.
 * 
 * @param   segment  The memory segment.
 * @return           The size of the memory segment, 0 if `segment` is `NULL`.
 */
size_t malloc_usable_size(void* segment)
{
  return allocsize(segment);  
}

