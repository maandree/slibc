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
#include <stddef.h>



/**
 * Get the dirname of a filename.
 * 
 * @param   filename  The filename, may be edited by this function.
 * @return            The dirname, it is either a substring
 *                    of `filename` or, if `filename` is `NULL`
 *                    or does no contain a non-trailing slash,
 *                    a statically allocationed string, so it
 *                    must not freed or edited.
 * 
 * @since  Always.
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

