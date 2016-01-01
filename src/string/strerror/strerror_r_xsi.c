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
 * This is an XSI-compliant extension. However the name
 * is not part of the XSI specification, `strerror_r`
 * should be used. It is defined to this function if
 * `(_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600) && !_GNU_SOURCE`.
 * However it is not defined if _SLIBC_SOURCE is defined.
 * 
 * @param   errnum  The error code.
 * @param   buf     Buffer where the description shall be stored.
 * @param   buflen  The allocation size of `buf`.
 * @return          Zero on success, value for `errno` on error
 * 
 * @throws  ERANGE  `buf` was too small to store the description.
 * 
 * @since  Always.
 */
int __xsi_strerror_r(int errnum, char* buf, size_t buflen)
{
  char* description = strerror(errnum);
  size_t length = strlen(description);
  
  if (buflen == 0)
    return ERANGE;
  
  if (buflen <= length)
    {
      memcpy(buf, description, buflen - 1);
      buf[buflen - 1] = 0;
      return ERANGE;
    }
  
  return memcpy(buf, description, length + 1), 0;
}

