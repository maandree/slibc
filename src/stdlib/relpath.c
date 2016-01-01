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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>



/**
 * Get the relative path of a file.
 * 
 * This is a slibc extension.
 * 
 * @param   file  The file.
 * @param   ref   The file the result shall be relative to,
 *                `NULL` for the current working directory.
 *                If and only if this path ends with a slash,
 *                (or if it is `NULL`,) it will be treated as
 *                a directory in which a symbolic link, with
 *                the result as it target, can be located to
 *                point to `file`.
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 * 
 * @since  Always.
 */
char* relpath(const char* file, const char* ref) /* XXX may also fail as get_current_dir_name */
{
  int saved_errno;
  char* cwd = NULL;
  char* absfile = NULL;
  char* absref = NULL;
  char* rc;
  char* prc;
  size_t ptr, p, n = 0;
  
  if ((cwd      = get_current_dir_name()) == NULL)  goto fail;
  if ((absfile  = abspath(file, cwd))     == NULL)  goto fail;
  if (ref)
    if ((absref = abspath(ref, cwd))      == NULL)  goto fail;
  if (absref == NULL)
    {
      p = strlen(cwd);
      absref = malloc((p + 2) * sizeof(char));
      if (absref == NULL)
	goto fail;
      memcpy(absref, cwd, p);
      absref[p] = '/';
      absref[p + 1] = '\0';
    }
  else
    strrchr(absref, '/')[1] = '\0';
  
  ptr = 0;
  while (absfile[ptr] && (absfile[ptr] == absref[ptr]))
    ptr++;
  while (absfile[ptr] != '/')
    ptr--;
  ptr++;
  
  for (p = ptr; absref[p]; p++)
    if (absref[p] == '/')
      n += 1;
  
  rc = malloc((strlen(absfile + ptr) + 1 + 3 * n) * sizeof(char));
  if (prc = rc, rc == NULL)
    goto fail;
  
  while (n--)
    prc = stpcpy(prc, "../");
  strcpy(prc, absfile + ptr);
  
  free(cwd);
  free(absfile);
  free(absref);
  return rc;
  
 fail:
  saved_errno = errno;
  free(cwd);
  free(absfile);
  free(absref);
  errno = saved_errno;
  return NULL;
}

