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
#include <slibc/internals.h>
#include <slibc-error.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <stdarg.h>



/**
 * Print a description of an error, and where the error occurred.
 * This function is capable of printed the full call-stack.
 * 
 * It is not recommended to used this function direction.
 * Use the macros in <slibc-error.h> instead.
 * 
 * This is a slibc extension.
 * 
 * @param  progname      The name of the program, `NULL` or empty to use `program_invocation_name`.
 * @param  filename      The source code file where the error occurred.
 * @param  linenum       The line in the source code where the error occurred.
 * @param  function      The function in the source code where the error occurred.
 * @param  error_code    Pointer the variable that stores the error code, will zeroed.
 * @param  error_string  Textual description of the error code, `NULL` if `strerror` should be used.
 *                       This parameter is unused if `error_code` is zero.
 * @param  format        Formatting-string for a description of the action that failed. `NULL` if
 *                       no description other than the location and `error_string` should be printed.
 * @param  ...           Formatting-arguments for `format`.
 * 
 * @since  Always.
 */
void slibc_perror(const char* progname, const char* filename, int linenum, const char* function,
		  int* error_code, const char* error_string, const char* format, ...)
{
  int tty = isatty(STDERR_FILENO);
  va_list args;
  
  if ((progname == NULL) || !*progname)
    progname = program_invocation_name;
  
  if (*error_code)
    {
      if (error_string == NULL)
	error_string = strerror(*error_code);
      fflush(stdout);
      fprintf(stderr, _("%(\033[0;1;31m%)%s%(\033[21m%): %s%(\033[0m%)\n"),
              tty, progname, tty, error_string, tty);
    }
  
  fprintf(stderr, _("  at %(\033[1;34m%)%s%(\033[0m%) (%(\033[35m%)%s%(\033[0m%):%(\033[32m%)%i%(\033[0m%))"),
          tty, function, tty, tty, filename, tty, tty, linenum, tty);
  if (format != NULL)
    {
      fprintf(stderr, "\n    ");
      va_start(args, format);
      vfprintf(stderr, format, args);
      va_end(args);
    }
  
  fprintf(stderr, "\n");
  *error_code = 0;
}

