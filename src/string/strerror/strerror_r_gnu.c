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
#include <errno.h>



/**
 * Reenterant variant of `strerror`.
 * 
 * This is a GNU-specific extension. However the name
 * is not part of the GNU specification, `strerror_r` should
 * be used. It is defined to this function unless
 * `(_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600) && !_GNU_SOURCE`.
 * However it is not defined if _SLIBC_SOURCE is defined.
 * 
 * @param   errnum  The error code.
 * @param   buf     Buffer where the description shall be stored.
 * @param   buflen  The allocation size of `buf`.
 * @return          `buf` on success, `NULL` on error. On error, `errno`
 *                  is set to indicate the error.
 * 
 * @throws  ERANGE  `buf` was too small to store the description.
 * 
 * @since  Always.
 */
char* __gnu_strerror_r(int errnum, char* buf, size_t buflen)
{
  errno = __xsi_strerror_r(errnum, buf, buflen);
  return errno ? NULL : buf;
}

