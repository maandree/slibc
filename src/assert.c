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
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>



/**
 * The function that is called if an assertion fails.
 * 
 * @param  expression  The expression that failed, `NULL` if `assert_perror` failed.
 * @param  errnum      The code of the fatal error, 0 if `assert` failed.
 * @param  file        The filename of the source cose whence the assertion was made.
 * @param  line        The line in the source code whence the assertion was made.
 * @param  func        The function in the source code whence the assertion was made,
 *                     `NULL` if unknown (C99 is required.)
 */
void __assert_fail(const char* expression, int errnum, const char* file, int line, const char* func)
{
  int tty = isatty(STDERR_FILENO);
  
  fprintf(stderr,
	  _("%(\033[00;01m%)%s%(\033[00m%): "
	    "%(\033[31m%)assertion error%(\033[00m%) "
	    "at line %(\033[33m%)%i%(\033[00m%) "
	    "of file %(\033[35m%)%s%(\033[00m%)"
	    "%(, function %(\033[1;34m%)%s%(\033[00m%)%): "
	    "%(\033[31m%)%(exression failed: %)%s%(\033[00m%)\n"),
	  tty, program_invocation_name, tty,
	  tty, tty,
	  tty, line, tty,
	  tty, file, tty,
	  func != NULL, tty, func, tty,
	  tty, expression != NULL, (expression ? expression : strerror(errnum)), tty);
  
  fflush(NULL); /* Flush all streams. */
  abort();
}

