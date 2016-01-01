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
#include <libgen.h>
#include <string.h>
#include <stddef.h>



/**
 * Removes all trailing slashes (that is not the first character
 * in the filename,), all duplicate slashes, all '.' directory
 * components, and when possible using only lexical analysis,
 * resolves '..' directory components.
 * 
 * '..' directory components that should resolve up beyond '/',
 * are removed. Note that this can in fact mean that the resulting
 * path is not the same file if the processes is `chroot`:ed.
 * Additionally, and more important, there is no consideration for
 * symbolic links. For example, '/a/b/c/..' resolves to '/a/b',
 * but if any of the directors are symbolic links, the real path
 * is not necessarily '/a/b'.
 * 
 * This is a slibc extension.
 * 
 * @param   filename  The filename, may be edited by this function.
 * @return            The dirname, it is either `filename` or,
 *                    if `filename` is `NULL` or does no contain a
 *                    non-trailing slash, a statically allocationed
 *                    string, so it must not freed or edited.
 * 
 * @since  Always.
 */
char* cleanname(char* filename)
{
#define SLASH(c)       (((c) == '/') || !(c))
#define UNSLASH_END()  if ((w > filename + 1) && (w[-1] == '/'))  *--w = 0
#define DOTS(n)        ((r[0] == '.') && (r[n - 1] == '.') && SLASH(r[n]))
  
  size_t parts = 0;
  int start;
  char* w;
  char* r;
  
  if ((filename == NULL) || !*filename)
    return ".";
  
  /* Remove unnecessary slashes and '.' directory components. */
  for (w = r = filename, start = 1; *r; r++)
    if (*r == '/')
      {
	if ((w == filename) || (w[-1] != '/'))
	  *w++ = '/';
	start = 1;
      }
    else if (start && DOTS(1))
      r += r[1] ? 1 : 0;
    else
      *w++ = *r, start = 0;
  UNSLASH_END();
  if (w == filename)
    *w++ = '.';
  *w = 0;
  
  /* Resolve '..' directory components. */
  for (w = r = filename, start = 1; *r; r++)
    if (*r == '/')
      *w++ = '/', start = 1, parts++;
    else if (start && DOTS(2))
      {
	if (!parts)
	  w = stpcpy(w, r[2] ? "../" : "..");
	r += r[2] ? 2 : 1;
	if (!parts)
	  continue;
	parts -= (*filename != '/');
	if (w > filename + 1)
	  do  *--w = 0;
	  while (w[-1] != '/');
      }
    else
      *w++ = *r, start = 0;
  UNSLASH_END();
  if (!*filename)
    w = filename, *w++ = '/';
  *w = 0;
  
  return filename;
}

