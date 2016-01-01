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
 * 
 * $PATH is not inspected if `name` starts with './', '../', or '/'.
 * 
 * This is a Plan 9 from Bell Labs compliant slibc extension.
 * 
 * @etymology  (Search) ($PATH) for an executable.
 * 
 * @param   name  The name of the sought executable.
 * @return        The pathname of the sought file, `NULL` on error,
 *                or if not found. Files that are not executable
 *                are (almost) ignored.
 * 
 * @throws  ENOMEM  The process cannot allocate enough memory.
 * @throws  ENOENT  $PATH is not defined, there are no directories
 *                  listed in $PATH, or the sought file is not
 *                  exist inside $PATH.
 * @throws  EACCES  None of the candidates (with at least one candidate)
 *                  are executable by the current user.
 * @throws          Any exception defined for access(3), except for `EROFS`,
 *                  these when encountered, the search is aborted, unless
 *                  the error is `ENOENT` or `EACCES`.
 * 
 * @since  Always.
 */
char* searchpath(const char* name)
{
  return searchpath3(name, "", "");
}

