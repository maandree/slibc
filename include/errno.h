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
#ifndef _ERRNO_H
#define _ERRNO_H
#include <slibc/version.h>
#include <slibc/features.h>



/* TODO include error definitions */
#define ENOMEM 1
#define EINVAL 1
#define ERANGE 1
#define ENOENT 1
#define EBADF 1
#define ENOSYS 1
#define ELOOP 1
#define EISDIR 1
#define EACCES 1
#define ENOTSUP 1



/**
 * A modifiable lvalue used to describe an error
 * that has occurred in the thread.
 * 
 * @etymology  (Err)or (number).
 * 
 * @since  Always.
 */
#define errno  (*__errno())


/**
 * Helper definition to `errno` used to
 * assured that the value is thread-dependent
 * and supported on all revisions of C.
 */
volatile int* __errno(void) /* TODO not implemented */
  __GCC_ONLY(__attribute__((__const__)));


/**
 * This is the name that was used to invoke the program
 * running in the current process. This is the value
 * of `argv[0]` from the `main` function (where `argv`
 * is the second parameter). If `argc` is zero, this
 * variable will have the value `NULL`. This is not
 * necessarily a proper command name. For example,
 * login shells are usually prefixes with a dash,
 * for example "-bash", despite that there is no such
 * command. Often, but not always, this will not contain
 * directory.
 * 
 * This string may be edited if `program_invocation_short_name`
 * or `argv[0]` is edited.
 * 
 * This is a GNU and slibc extension.
 * 
 * @since  Always.
 */
#if defined(__GNU_SOURCE) || defined(__SLIBC_SOURCE)
extern char* program_invocation_name; /* TODO not implemented */
#endif

/**
 * Variant of `program_invocation_name` that is
 * guaranteed to not include the directory.
 * 
 * This string may be edited if `program_invocation_name`
 * or `argv[0]` is edited.
 * 
 * This is a GNU extension.
 * 
 * @since  Always.
 */
#if defined(__GNU_SOURCE)
extern char* program_invocation_short_name; /* TODO not implemented */
#endif



#endif

