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
#include <error.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>



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
	  filename != NULL, tty, filename, tty, tty, linenum, tty,
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

