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
 * Get the absolute path of a file.
 * It will remove all redundant slashes, all "./":s,
 * and all "../":s, but not resolve symbolic links.
 * 
 * This is a slibc extension.
 * 
 * @param   file  The file.
 * @param   ref   The directory the file's specified path is
 *                relative, `NULL` for the current working directory.
 * @return        The file's absolute pathname. Will end with a slash
 *                if `file` does. (Or if `ref` does but file is empty.)
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 * 
 * @since  Always.
 */
char* abspath(const char* file, const char* ref) /* XXX may also fail as get_current_dir_name */
{
  char* ref_ = NULL;
  char* rc;
  char* rc_;
  size_t p, q;
  int saved_errno;
  
  if (ref == NULL)
    {
      ref = ref_ = get_current_dir_name();
      if (ref == NULL)
	return NULL;
    }
  
  rc = malloc((strlen(file) + strlen(ref) + 3) * sizeof(char));
  if (rc_ = rc, rc == NULL)
    {
      saved_errno = errno;
      free(ref_);
      errno = saved_errno;
      return NULL;
    }
  
  /* Create absolute path, with //, /./, and /../. */
  if (*file != '/')
    {
      rc_ = stpcpy(rc_, ref);
      *rc_++ = '/';
    }
  strcpy(rc_, file);
  
  /* Remove redundant slashes. */
  p = q = 1;
  while (rc[p])
    if ((rc[p] == '/') && (rc[p - 1] == '/'))
      p++;
    else
      rc[q++] = rc[p++];
  rc[q] = '\0';
  
  /* Remove ./:s. */
  p = q = 0;
  while (rc[p])
    if ((rc[p] == '/') && (rc[p + 1] == '.') && (rc[p + 2] == '/'))
      p += 2;
    else
      rc[q++] = rc[p++];
  rc[q] = '\0';
  
  /* Remove ../:s. */
  for (;;)
    {
      rc_ = strstr(rc, "/../");
      if (rc_ == NULL)
        break;
      memmove(rc_, rc_ + 3, strlen(rc_ + 2) * sizeof(char));
      if (rc_ == rc)
        continue;
      for (p = 0; rc_[-p] != '/'; p++);
      memmove(rc_ - p, rc_, (strlen(rc_) + 1) * sizeof(char));
    }
  
  free(ref_);
  return rc;
}

