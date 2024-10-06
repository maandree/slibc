/**
 * slibc — Yet another C library
 * Copyright © 2015, 2016  Mattias Andrée (m@maandree.se)
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
#include <stdlib.h>



/**
 * Print an error message to stderr, but do not print a
 * description of the value of `errno`. Then exit the process.
 * 
 * This is a non-standard BSD extension.
 * 
 * @etymology  (V)ariadic version of (`errx`).
 * 
 * @param  status  The exit status the process should have.
 * @param  format  Formatting-string for the warning.
 * @param  args    Formatting-arguments.
 * 
 * @since  Always.
 */
void verrx(int status, const char* format, va_list args)
{
  verror(status, 0, format, args);
  exit(status);
}

