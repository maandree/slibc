/**
 * slibc — Yet another C library
 * Copyright © 2015  Mattias Andrée (maandree@member.fsf.org)
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
#include <libgen.h>
#include <stddef.h>


# pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"



/**
 * Get the basename of a filename.
 * 
 * This is a GNU extension, include <libgen.h>
 * to override it with the XPG-compliant implementation.
 * 
 * @param   filename  The filename.
 * @return            The basename, it is either a substring
 *                    of `filename` or, if `filename` is `NULL`
 *                    or is empty, a statically allocationed string,
 *                    so it must not freed or edited.
 */
char* __gnu_basename(const char* filename)
{
  char* r = filename;
  char last = '/';
  if (filename == NULL)
    return ".";
  while (*filename)
    {
      if ((*filename != '/') && (last == '/'))
	r = filename;
      last = *filename++;
    }
  return r;
}


/**
 * Get the basename of a filename, remove
 * trailing slashes.
 * 
 * @param   filename  The filename, may be edited by this function.
 * @return            The basename, it is either a substring
 *                    of `filename` or, if `filename` is `NULL`
 *                    or is empty, a statically allocationed string,
 *                    so it must not freed or edited.
 */
char* __xpg_basename(char* filename)
{
  char* r = __gnu_basename(filename);
  char* p;
  if (strcmp(r, "."))
    for (p = r + 1; *p; p++)
      if (*p == '/')
	*p = 0;
  return r;
}


/**
 * Get the dirname of a filename.
 * 
 * @param   filename  The filename, may be edited by this function.
 * @return            The dirname, it is either a substring
 *                    of `filename` or, if `filename` is `NULL`
 *                    or does no contain a non-trailing slash,
 *                    a statically allocationed string, so it
 *                    must not freed or edited.
 */
char* dirname(char* filename)
{
  int have_nonslash = 0;
  char* last_slash = NULL;
  char c, d;
  if ((filename == NULL) || (!*filename))
    return ".";
  for (; (c = *filename); filename++)
    {
      d = filename[1];
      have_nonslash |= c - '/';
      if ((c == '/') && d && (d != '/'))
	last_slash = filename;
    }
  if (!have_nonslash)      return "/";
  if (last_slash == NULL)  return ".";
  return *last_slash = 0, filename;
}


/**
 * Removes all trailing slashes (that is not the first character
 * in the filename,), all duplicate slashes, all '.' directory
 * components, and when possible using only lexical analysis,
 * resolves '..' directory components.
 * 
 * '..' directory components that should resolve up beyond '/',
 * are removed. Note that this can in fact mean that the resulting
 * path is not the same file if the processes is `chroot`:ed.
 * 
 * This is a slibc extension.
 * 
 * @param   filename  The filename, may be edited by this function.
 * @return            The dirname, it is either `filename` or,
 *                    if `filename` is `NULL` or does no contain a
 *                    non-trailing slash, a statically allocationed
 *                    string, so it must not freed or edited.
 */
char* cleanname(char* filename)
{
  size_t parts = 0;
  int start;
  char* w;
  char* r;
  
  if ((filename == NULL) || (!*filename))
    return ".";
  
  /* Remove unnecessary slashes and '.' directory components. */
  for (w = r = filename, start = 1; *r; r++)
    if (*r == '/')
      {
	if ((w == filename) || (w[-1] != '/'))
	  *w++ = '/';
	start = 1;
      }
    else if (start && (r[0] == '.') && ((r[1] == '/') || (r[1] == 0)))
      r += (r[1] == '/');
    else
      *w++ = *r, start = 0;
  if ((w > filename + 1) && (w[-1] == '/'))
    *--w = 0;
  if (w == filename)
    *w++ = '.';
  *w = 0;
  
  /* Resolve '..' directory components. */
  for (w = r = filename, start = 1; *r; r++)
    if (*r == '/')
      *w++ = '/', start = 1, parts++;
    else if (start && (r[0] == '.') && (r[1] == '.') && ((r[2] == '/') || (r[2] == 0)))
      {
	if (parts == 0)
	  {
	    *w++ = '.', *w++ = '.';
	    if (r[2])
	      *w++ = '/';
	    r += 1 + (r[2] == '/');
	    continue;
	  }
	r += 1 + (r[2] == '/');
	parts -= *filename != '/';
	if (w > filename + 1)
	  {
	    *--w = 0;
	    while (w[-1] != '/')
	      *--w = 0;
	  }
      }
    else
      *w++ = *r, start = 0;
  if ((w > filename + 1) && (w[-1] == '/'))
    *--w = 0;
  if (!*filename)
    w = filename, *w++ = '/';
  *w = 0;
  
  return filename;
}

