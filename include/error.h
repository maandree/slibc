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
#ifndef _ERROR_H
#define _ERROR_H
#include <slibc/version.h>
#include <slibc/features.h>

#ifndef _SLIBC_SUPPRESS_WARNINGS
# warning "Please consider not using <error.h>."
#endif


#define __NEED_va_list
#include <bits/types.h>



#if defined(__GNU_SOURCE)
/**
 * Print an error message with a detailed description, and optionally exit.
 * 
 * This is a GNU extension.
 * 
 * @etymology  Report (error)!
 * 
 * @param  status  The process will exit, with the function returning, with this
 *                 exit status, unless it is zero. If zero, the process shall not exit.
 * @param  errnum  The value of `errno` when the error occurred, zero if the a textual
 *                 description of the error, further than that of `format`, shall not
 *                 be printed.
 * @param  format  Formatting-string for a detailed description of what happend.
 * @param  args    Formatting-arguments for `format`.
 * 
 * @since  Always.
 */
void error(int, int, const char*, ...)
  __GCC_ONLY(__attribute__((__format__(__slibc_printf__, 3, 4))));

/**
 * Variant of `error` that uses `va_list` instead of variadic arguments.
 * 
 * This is a slibc extension to the GNU extension `error`.
 * 
 * @etymology  (V)ariadic version of (`error`).
 * 
 * @param  status  The process will exit, with the function returning, with this
 *                 exit status, unless it is zero. If zero, the process shall not exit.
 * @param  errnum  The value of `errno` when the error occurred, zero if the a textual
 *                 description of the error, further than that of `format`, shall not
 *                 be printed.
 * @param  format  Formatting-string for a detailed description of what happend.
 * @param  args    Formatting-arguments for `format`.
 * 
 * @since  Always.
 */
# if defined(__SLIBC_SOURCE)
void verror(int, int, const char*, va_list);
# endif


/**
 * Variant of `error` that prints the filename and the line
 * number whence the error occurred.
 * 
 * This is a GNU extension.
 * 
 * @etymology  Report (error at line) in source code!
 * 
 * @param  status    The process will exit, with the function returning, with this
 *                   exit status, unless it is zero. If zero, the process shall not exit.
 * @param  errnum    The value of `errno` when the error occurred, zero if the a textual
 *                   description of the error, further than that of `format`, shall not
 *                   be printed.
 * @param  filename  The filename of the source code file where the error occurred.
 * @param  linenum   The line number of in the source code file where the error occurred.
 * @param  format    Formatting-string for a detailed description of what happend.
 * @param  args      Formatting-arguments for `format`.
 * 
 * @since  Always.
 */
void error_at_line(int, int, const char*, unsigned int, const char*, ...)
  __GCC_ONLY(__attribute__((__format__(__slibc_printf__, 5, 6))));

/**
 * Variant of `verror` that prints the filename and the line
 * number whence the error occurred.
 * 
 * This is a slibc extension to the GNU extension `error_at_line`.
 * 
 * @etymology  (V)ariadic version of (`error_at_line`).
 * 
 * @param  status    The process will exit, with the function returning, with this
 *                   exit status, unless it is zero. If zero, the process shall not exit.
 * @param  errnum    The value of `errno` when the error occurred, zero if the a textual
 *                   description of the error, further than that of `format`, shall not
 *                   be printed.
 * @param  filename  The filename of the source code file where the error occurred.
 * @param  linenum   The line number of in the source code file where the error occurred.
 * @param  format    Formatting-string for a detailed description of what happend.
 * @param  args      Formatting-arguments for `format`.
 * 
 * @since  Always.
 */
# if defined(__SLIBC_SOURCE)
void verror_at_line(int, int, const char*, unsigned int, const char*, va_list);
# endif


/**
 * Counts the number of times `error` (`verror`) and
 * `error_at_line` (`verror_at_line`) has returned.
 * This variable is global and shared by all threads.
 * 
 * This is a GNU extension.
 * 
 * @etymology  (`error`)-subsystem: (message count).
 * 
 * @since  Always.
 */
extern volatile unsigned int error_message_count;

/**
 * If set to non-zero (the default), `error_at_line`
 * and `verror_at_line` restrict themself to only
 * print an error the first time it appears. This
 * is determined by the uniqueness of the combination
 * of the values on `filename` and `linenum`. However
 * it will forget the line the next time the function
 * is called from a different line. This variable is
 * global and shared by all threads. As a slibc
 * modification, `errnum` is also remembered, meaning
 * if the error code is different (zero is considered
 * an error code), the error is printed even if it
 * occurred on the same line as the last time.
 * 
 * This is a GNU extension.
 * 
 * @etymology  (`error`)-subsystem: print (one) time (per line).
 * 
 * @since  Always.
 */
extern volatile int error_one_per_line;

/**
 * If not `NULL`, this function is used instead of
 * flushing stdout and printing the process name to
 * stderr, by `error` (`verror`) and `verror_at_line`
 * (`verror_at_line`). This variable is global and
 * shared by all threads.
 * 
 * This is a GNU extension.
 * 
 * @etymology  (`error`)-subsystem function: (print) the (prog)ram's (name).
 * 
 * @since  Always.
 */
extern void (*volatile error_print_progname)(void);
#endif



#endif

