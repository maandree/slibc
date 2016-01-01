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
#include <err.h>
#include <stdarg.h>



/**
 * Print a warning to stderr, but do not print a
 * description of the value of `errno`.
 * 
 * This is a non-standard BSD extension.
 * 
 * @etymology  (`warn`), [x=](lesser variant).
 * 
 * @param  format  Formatting-string for the warning.
 * @param  ...     Formatting-arguments.
 * 
 * @since  Always.
 */
void warnx(const char* format, ...)
{
  va_list args;
  va_start(args, format);
  vwarnx(format, args);
  va_end(args);
}

