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
#ifndef _STDDEF_H
#define _STDDEF_H
#include <slibc/version.h>
#include <slibc/features.h>



/**
 * `NULL` is a zero-values constant, conventionally
 * a `void`-pointer (it is specified this way in
 * POSIX, it does not really matter as long as it has
 * the same width and ISO C does not specify it this
 * way), use to indicate that a pointer does not point
 * to anything.
 * 
 * Note on considerations of `NULL` being harmful:
 *   It is important to remember than `sizeof(NULL)`
 *   does not equal `sizeof(int)` on all machines.
 *   Therefore, in variadic arguments, it is important
 *   not to substitute `x` for `x != NULL`. This
 *   would cause horrible bugs. If you insist on not
 *   using `NULL`, correct substitutions would be
 *   `!!x` or `x != 0`.
 * Note that `NULL` is genuinely harmful in C++,
 * but excessive use of C++, and especially it
 * features, is harmful too.
 * 
 * Strictly speaking, to deference `NULL` is not an
 * illegal action, but the operating system will
 * kill you with `SIGSEGV` (segmentation fault or
 * acess violation), and makes your you have no reason
 * to my never mapping any memory there. However, the
 * operating system itself, and programs running
 * before the operating system, that is, any program
 * not abstracted away from the hardware by virtual
 * memory, have use of the address 0.
 * 
 * @etymology  Pointer with numerical value (0).
 * 
 * @since  Always.
 */
#ifndef NULL
# define NULL  ((void*)0)
#endif


/**
 * Get the offset of a member in a `struct`, in bytes.
 * 
 * For example. Consider the structure
 * ```
 * struct example
 * {
 *   char offset_is_0[16];
 *   char offset_is_16[16];
 * }
 * ```
 * `offsetof(struct example, offset_is_0)` evaluates to
 * 0 because it is at the top of the structure.
 * `offsetof(struct example, offset_is_16)` evaluates to
 * 16 because the member above it in the structure
 * has offset 0 and size 16. 0 + 16 = 16.
 * 
 * @etymology  Address-(offset of) member.
 * 
 * @param   type:identifier    The identifier for a structure.
 * @param   member:identifier  The identifier for a member, direct or indirect,
 *                             of the structure.
 * @return  :size_t            The offset of the member.
 * 
 * @since  Always.
 */
#define offsetof(type, member)  \
  ((size_t)((char*)&(((type*)NULL)->member) - (char*)NULL))
/* TODO The behaviour of this is undefined, and a builtin function
 * shall be used when available. That would also improve diagnostics.
 * If compilers that support ({  }), NULL could be replaced with a
 * temporary variable, this would only remove the undefined behaviour,
 * but any serious compiler should support the current implementation. */



#define __NEED_ptrdiff_t
#define __NEED_wchar_t
#define __NEED_size_t
#if defined(__C11__) || defined(__BUILDING_SLIBC)
# define __NEED_max_align_t
#endif

#include <bits/types.h>



#endif

