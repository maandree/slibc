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
#include <slibc-human.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>



/**
 * Convert file permission from machine representation to human representation.
 * 
 * @param   buffer  Sufficiently large buffer for the output, or `NULL`.
 *                  18 characters is always sufficient, regardless of `mode`.
 * @param   perm    Machine representation of the permissions, will be masked with 07777.
 * @param   mode    Representation style, 0 for default.
 * @return          Human representation of the file permissions, `NULL` on error.
 *                  On success, the caller is responsible for deallocating the
 *                  returned pointer, if and only if `buffer` is `NULL`.
 * 
 * @throws  EINVAL  If `mode` is invalid.
 * @throws  ENOMEM  The process cannot allocate more memory.
 * 
 * @since  Always.
 */
char* humanmode(char* restrict buffer, mode_t perm, enum humanmode_mode mode)
{
  mode_t perm_ = perm | (mode != HUMANMODE_MASK ? 07777 : 0);
  int name = mode & HUMANMODE_MASK;
  char* w;
  
  if (mode & ~(mode_t)3)
    return errno = EINVAL, NULL;
  if (!mode)
    mode = HUMANMODE_STAT;
  
  if (buffer == NULL)
    buffer = malloc((mode == HUMANMODE_STAT ? 10 : 18) * sizeof(char));
  if (buffer == NULL)
    return NULL;
  w = buffer;
  
  if (name)                  *w++ = 'u', *w++ = '=';
  if (perm_ & S_IRUSR)       *w++ = (perm & S_IRUSR) ? 'r' : '-';
  if (perm_ & S_IWUSR)       *w++ = (perm & S_IWUSR) ? 'w' : '-';
  if (perm & S_ISUID)        *w++ = (perm & S_IXUSR) ? 's' : 'S';
  else if (perm_ & S_IXUSR)  *w++ = (perm & S_IXUSR) ? 'x' : '-';
  
  if (name)                  *w++ = ',', *w++ = 'g', *w++ = '=';
  if (perm_ & S_IRGRP)       *w++ = (perm & S_IRGRP) ? 'r' : '-';
  if (perm_ & S_IWGRP)       *w++ = (perm & S_IWGRP) ? 'w' : '-';
  if (perm & S_ISGID)        *w++ = (perm & S_IXGRP) ? 's' : 'S';
  else if (perm_ & S_IXGRP)  *w++ = (perm & S_IXGRP) ? 'x' : '-';
  
  if (name)                  *w++ = ',', *w++ = 'o', *w++ = '=';
  if (perm_ & S_IROTH)       *w++ = (perm & S_IROTH) ? 'r' : '-';
  if (perm_ & S_IWOTH)       *w++ = (perm & S_IWOTH) ? 'w' : '-';
  if (perm & S_ISVTX)        *w++ = (perm & S_IXOTH) ? 't' : 'T';
  else if (perm_ & S_IXOTH)  *w++ = (perm & S_IXOTH) ? 'x' : '-';
  
  return *w = 0, buffer;
}

