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
#include <err.h>
#include <error.h>
#include <errno.h>
#include <stdlib.h>



/**
 * Print a warning to stderr, followed by a description
 * of the value of `errno`.
 * 
 * This is a non-standard BSD extension.
 * 
 * @param  format  Formatting-string for the warning.
 * @param  ...     Formatting-arguments.
 */
void warn(const char* format, ...)
{
  va_list args;
  va_start(args, format);
  vwarn(format, args);
  va_end(args);
}


/**
 * Print a warning to stderr, followed by a description
 * of the value of `errno`.
 * 
 * This is a non-standard BSD extension.
 * 
 * @param  format  Formatting-string for the warning.
 * @param  args    Formatting-arguments.
 */
void vwarn(const char* format, va_list args)
{
  verror(0, errno, format, args);
}


/**
 * Print a warning to stderr, but do not print a
 * description of the value of `errno`.
 * 
 * This is a non-standard BSD extension.
 * 
 * @param  format  Formatting-string for the warning.
 * @param  ...     Formatting-arguments.
 */
void warnx(const char* format, ...)
{
  va_list args;
  va_start(args, format);
  vwarnx(format, args);
  va_end(args);
}


/**
 * Print a warning to stderr, but do not print a
 * description of the value of `errno`.
 * 
 * This is a non-standard BSD extension.
 * 
 * @param  format  Formatting-string for the warning.
 * @param  args    Formatting-arguments.
 */
void vwarnx(const char* format, va_list args)
{
  verror(0, 0, format, args);
}


/**
 * Print an error message to stderr, followed by a
 * description of the value of `errno`. Then exit the process.
 * 
 * This is a non-standard BSD extension.
 * 
 * @parma  status  The exit status the process should have.
 * @param  format  Formatting-string for the warning.
 * @param  ...     Formatting-arguments.
 */
void err(int status, const char* format, ...)
{
  va_list args;
  va_start(args, format);
  verr(status, format, args);
  va_end(args);
}


/**
 * Print an error message to stderr, followed by a
 * description of the value of `errno`. Then exit the process.
 * 
 * This is a non-standard BSD extension.
 * 
 * @parma  status  The exit status the process should have.
 * @param  format  Formatting-string for the warning.
 * @param  args    Formatting-arguments.
 */
void verr(int status, const char* format, va_list args)
{
  verror(status, errno, format, args);
  exit(status);
}


/**
 * Print an error message to stderr, but do not print a
 * description of the value of `errno`. Then exit the process.
 * 
 * This is a non-standard BSD extension.
 * 
 * @parma  status  The exit status the process should have.
 * @param  format  Formatting-string for the warning.
 * @param  ...     Formatting-arguments.
 */
void errx(int status, const char* format, ...)
{
  va_list args;
  va_start(args, format);
  verrx(status, format, args);
  va_end(args);
}


/**
 * Print an error message to stderr, but do not print a
 * description of the value of `errno`. Then exit the process.
 * 
 * This is a non-standard BSD extension.
 * 
 * @parma  status  The exit status the process should have.
 * @param  format  Formatting-string for the warning.
 * @param  args    Formatting-arguments.
 */
void verrx(int status, const char* format, va_list args)
{
  verror(status, 0, format, args);
  exit(status);
}

