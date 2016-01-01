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
 * 
 * @since  Always.
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

