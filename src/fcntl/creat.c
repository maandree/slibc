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
#include <fcntl.h>



/**
 * Create a new file and open it for writing, or
 * if the file already exists, open it for rewriting,
 * in which the file will be emptied.
 * 
 * `creat(path, mode)` is identical to
 * `open(path, O_WRONLY | O_CREAT | O_TRUNC, mode)`.
 * 
 * @etymology  (Creat)e file!
 * 
 * @param   path  The pathname of the file to open.
 * @param   mode  File permissions for the new file.
 * @return        The file descriptor to the opened file, -1 on error.
 * 
 * @throws  Any error specified for open(3) except for `EEXIST`.
 * 
 * @since  Always.
 */
int creat(const char* path, mode_t mode)
{
  return open(path, O_WRONLY | O_CREAT | O_TRUNC, mode);
}

