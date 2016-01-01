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
#include <stddef.h>



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
void verror(int status, int errnum, const char* format, va_list args)
{
  verror_at_line(status, errnum, NULL, 0, format, args);
}

