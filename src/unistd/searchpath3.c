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
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
/* TODO temporary contants from other headers { */
#define _CS_PATH 1
/* } */



/**
 * The default value for the PATH environment variable.
 */
#ifndef DEFAULT_PATH
# define DEFAULT_PATH  "/usr/local/bin:/bin:/usr/bin"
#endif



/**
 * Search the environment variable $PATH for an executable
 * file whose name is the specified name. Slashes are ignored
 * and treated as any other character. $PATH is searched
 * for left to right, and ':' is used as the path-delimiter.
 * If $PATH is not defined, a fallback value for $PATH will be
 * used.
 * 
 * $PATH is not inspected if `name` starts with './', '../', or '/'.
 * 
 * This function was added because it was useful in implementing
 * the `exec`-function family.
 * 
 * This is a slibc extension.
 * 
 * @etymology  Variant of (searchpath) that takes (3) arguments.
 * 
 * @param   name      The name of the sought executable. Must not be `NULL`.
 * @param   fallback  Value to use instead of the value of $PATH, if
 *                    path is not defined. If `NULL` the default value
 *                    for $PATH is used.
 * @param   first     If $PATH is not defined, and `fallback` is `NULL`,
 *                    these directories are tested before the default
 *                    directories. May be `NULL`.
 * @return            The pathname of the sought file, `NULL` on error,
 *                    or if not found. Files that are not executable
 *                    are (almost) ignored.
 * 
 * @throws  ENOMEM  The process cannot allocate enough memory.
 * @throws  ENOENT  There are no directories listed in $PATH, or
 *                  the sought file is not exist inside $PATH.
 * @throws  EACCES  None of the candidates (with at least one candidate)
 *                  are executable by the current user.
 * @throws          Any exception defined for access(3), except for `EROFS`,
 *                  these when encountered, the search is aborted, unless
 *                  the error is `ENOENT` or `EACCES`.
 * 
 * @since  Always.
 */
char* searchpath3(const char* name, const char* fallback, const char* first)
{
  char* path;
  size_t len = 0;
  char* pathname = NULL;
  char* p;
  char* q;
  int eacces = 0;
  int saved_errno;
  
  if (strstarts(name, "./") || strstarts(name, "../") || strstarts(name, "/"))
    {
      if (access(name, X_OK) == 0)
	return strdup(name);
      return NULL;
    }
  
  path = getenv("PATH");
  if ((path == NULL) && (fallback == NULL))
    {
      if (first == NULL)
	first = "";
      if ((len = confstr(_CS_PATH, NULL, 0)))
	{
	  path = malloc((strlen(first) + 1 + len) * sizeof(char));
	  if (path == NULL)
	    goto fail;
	  if (!confstr(_CS_PATH, stpcpy(stpcpy(path, first), ":"), len))
	    free(path), path = NULL;
	}
      if (path == NULL)
	{
	  path = malloc(strlen(first) * sizeof(char) + sizeof(":" DEFAULT_PATH));
	  if (path == NULL)
	    goto fail;
	  stpcpy(stpcpy(path, first), ":" DEFAULT_PATH);
	}
    }
  else
    path = strdup(path == NULL ? fallback : path);
  if (path == NULL)
    goto fail;
  
  pathname = malloc((strlen(path) + strlen(name) + 2) * sizeof(char));
  if (pathname == NULL)
    goto fail;
  
  for (p = path; *p; p = q + 1)
    {
      if (p == (q = strchr(p, ':')))
	continue;
      *q = '\0';
      
      stpcpy(stpcpy(stpcpy(pathname, p), "/"), name);
      
      if (access(pathname, X_OK) == 0)
	{
	  char* truncated = realloc(pathname, (strlen(pathname) + 1) * sizeof(char));
	  return truncated == NULL ? pathname : truncated;
	}
      else if (errno == EACCES)  eacces = 1;
      else if (errno != ENOENT)  goto fail;
    }
  
  free(path);
  free(pathname);
  return errno = (eacces ? EACCES : ENOENT), NULL;
  
 fail:
  saved_errno = errno;
  free(path);
  free(pathname);
  errno = saved_errno;
  return NULL;
}

