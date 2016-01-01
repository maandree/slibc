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
#include <unistd.h>



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
 * @etymology  Variant of (searchpath) that takes (2) arguments.
 * 
 * @param   name      The name of the sought executable. Must not be `NULL`.
 * @param   fallback  Value to use instead of the value of $PATH, if
 *                    path is not defined. If `NULL` the default value
 *                    for $PATH is used.
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
char* searchpath2(const char* name, const char* fallback)
{
  return searchpath3(name, fallback, "");
}

