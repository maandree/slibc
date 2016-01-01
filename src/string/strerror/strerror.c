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
#include <string.h>



/**
 * Return a textual representation of an error code.
 * This error code must from `errno`.
 * 
 * This implementation of `strerror` cannot fail. however
 * POSIX specifies that it can fail, any may only set `errno`
 * if it does fail. You should therefore, set `errno` to
 * zero before calling this function, and inspect `errno`
 * when it returns, as there is no reserved return value
 * that indicates and error.
 * 
 * The returned value must not be modified or freed.
 * 
 * As a slibc-specific modification, this function is MT-Safe.
 * 
 * @param   errnum  The error code.
 * @return          A description of the error.
 * 
 * @since  Always.
 */
char* strerror(int errnum)
{
  return strerror_l(errnum, 0 /* TODO CURRENT_LOCALE, not defined */);
}

