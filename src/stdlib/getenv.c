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
#include <errno.h>



/**
 * The process's environment variables.
 */
extern char** environ;



/**
 * This function returns the value assoicated with a
 * specified environment variable.
 * 
 * Portable program must not check `errno`. No errors
 * are defined by POSIX.
 * 
 * @etymology  (Get) the value of an (env)ironment variable!
 * 
 * @param   name  The name of the sought environment variable.
 *                Must not be `NULL`.
 * @return        The value of the environment variable.
 *                `NULL` on error, or if not found. This
 *                pointer is subpointer, and must not be
 *                modified except for in-place changes.
 * 
 * @throws  0       No such environment variable found.
 *                  This is a slibc extensions.
 * @throws  EINVAL  `name` is `NULL` (must not be the case), empty,
 *                  or contains a '='. This is a slibc extensions.
 * 
 * @since  Always.
 */
char* getenv(const char* name)
{
  size_t i, n;
  
  if (!name || !*name || strchr(name, '='))
    return errno = EINVAL, NULL;
  
  errno = 0;
  if (environ == NULL)
    return NULL;
  
  n = strlen(name);
  for (i = 0; environ[i] != NULL; i++)
    if (!strncmp(name, environ[i], n))
      if (environ[i][n] == '=')
	return environ[i] + n + 1;
  
  return NULL;
}

