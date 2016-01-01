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
#include <stddef.h>



/**
 * Counts the number of times `error` ( verror`) and
 * `error_at_line` (`verror_at_line`) has returned.
 * This variable is global and shared by all threads.
 * 
 * This is a GNU extension.
 * 
 * @etymology  (`error`)-subsystem: (message count).
 * 
 * @since  Always.
 */
volatile unsigned int error_message_count = 0;


/**
 * If set to non-zero (the default), `error_at_line`
 * and `verror_at_line` restrict themself to only
 * print an error the first time it appears. This
 * is determined by the uniqueness of the combination
 * of the values on `filename` and `linenum`. However
 * it will forget the line the next time the function
 * is called from a different line. This variable is
 * global and shared by all threads. Has a slibc
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
volatile int error_one_per_line = 1;


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
void (*volatile error_print_progname)(void) = NULL;

