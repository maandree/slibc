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
#include <error.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stddef.h>



/**
 * Print an error message with a detailed description, and optionally exit.
 * 
 * This is a GNU extension.
 * 
 * @param  status  The process will exit, with the function returning, with this
 *                 exit status, unless it is zero. If zero, the process shall not exit.
 * @param  errnum  The value of `errno` when the error occurred, zero if the a textual
 *                 description of the error, further than that of `format`, shall not
 *                 be printed.
 * @param  format  Formatting-string for a detailed description of what happend.
 * @param  args    Formatting-arguments for `format`.
 */
void error(int status, int errnum, const char* format, ...)
{
  va_list args;
  va_start(args, format);
  verror_at_line(status, errnum, NULL, 0, format, args);
  va_end(args);
}


/**
 * Variant of `error` that uses `va_list` instead of variadic arguments.
 * 
 * This is a slibc extension to the GNU extension `error`.
 * 
 * @param  status  The process will exit, with the function returning, with this
 *                 exit status, unless it is zero. If zero, the process shall not exit.
 * @param  errnum  The value of `errno` when the error occurred, zero if the a textual
 *                 description of the error, further than that of `format`, shall not
 *                 be printed.
 * @param  format  Formatting-string for a detailed description of what happend.
 * @param  args    Formatting-arguments for `format`.
 */
void verror(int status, int errnum, const char* format, va_list args)
{
  verror_at_line(status, errnum, NULL, 0, format, args);
}


/**
 * Variant of `error` that prints the filename and the line
 * number whence the error occurred.
 * 
 * This is a GNU extension.
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
 */
void error_at_line(int status, int errnum, const char* filename,
		   unsigned int linenum, const char* format, ...)
{
  va_list args;
  va_start(args, format);
  verror_at_line(status, errnu, filename, linenum, format, args);
  va_end(args);
}


/**
 * Variant of `verror` that prints the filename and the line
 * number whence the error occurred.
 * 
 * This is a slibc extension to the GNU extension `error_at_line`.
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
 */
void verror_at_line(int status, int errnum, const char* filename,
		    unsigned int linenum, const char* format, va_list args)
{
  int tty = isatty(STDERR_FILENO);
  void (*pname)(void) = error_print_progname;
  
  static const char* last_filename = NULL;
  static unsigned int last_linenum = 0;
  static int last_errnum = 0;
  
  if (error_one_per_line)
    if ((last_filename == filename) && (last_linenum == linenum) && (last_errnum == errnum))
      goto skip_print;
  
  if (pname != NULL)
    pname();
  else
    {
      fflush(stdout);
      fprintf(stderr, "%(\033[0;1;31m)%s%(\033[0m)",
	      tty, program_invocation_name, tty);
    }
  
  fprintf(stderr, "%(: %(\033[35m%)%s%(\033[0m%): %(\033[32m%)%u%(\033[0m%)%)%(: %s%)%(: %)",
	  filename != NULL, tty, filename, tty, tty, filenum, tty,
	  errnum != 0, strerror(errnum) /* TODO strerror is not MT-Safe */, format != NULL);
  
  if (filename != NULL)
    last_filename = filename, last_linenum = linenum, last_errnum = errnum;
  
  vfprintf(stderr, format, args);
  fprintf(stderr, "\n", program_invocation_name);
  fflush(stderr);
  
 skip_print:
  error_message_count++; /* TODO lock around this */
  if (status)
    exit(status);
}


/**
 * Counts the number of times `error` ( verror`) and
 * `error_at_line` (`verror_at_line`) has returned.
 * This variable is global and shared by all threads.
 * 
 * This is a GNU extension.
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
 */
volatile void (*error_print_progname)(void) = NULL;

