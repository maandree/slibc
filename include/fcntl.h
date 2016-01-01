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
#ifndef _FCNTL_H
#define _FCNTL_H
#include <slibc/version.h>
#include <slibc/features.h>



#define __NEED_off_t
#define __NEED_pid_t
#define __NEED_mode_t
#include <bits/types.h>



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
int creat(const char*, mode_t)
  __GCC_ONLY(__attribute__((__nonnull__, __warn_unused_result__)))
  __deprecated("Use 'open' instead.");


#if defined(__SLIBC_SOURCE)
/**
 * Reopen a file via its file descriptor. The old file descriptor
 * is closed and replace with the new open file descriptor.
 * 
 * This function call is different from the `dup` function-family
 * in two ways: (1) you can select news flags, for example, if
 * `fd` was read-only, the new file descriptor can be write-only,
 * and (2) the file descriptor is not duplicated, the file is
 * reopened.
 * 
 * This function is useful if you want to reopen a file you do
 * now know the pathname, you do not want to create a new string
 * with the pathname, or if the the file no longer has a pathname
 * because it has been unlinked.
 * 
 * Because the file is reopened, the file position is reset and
 * is not shared with any duplicates of `fd`, unlike a call to
 * dup(3). it is visible to the filesystem as a new open file
 * descriptor and is distinguished from the duplocates of `fd`,
 * and all file locks associated with `fd` are lost, except for
 * on the duplicates of `fd`, which means that you can create
 * new locks without removing locks from the duplicates of `fd`.
 * 
 * This is a slibc extension.
 * 
 * @etymology  (Reopen) file!
 * 
 * @param   fd     The file descriptor.
 * @param   oflag  How the file shall be opened, see open(3).
 *                 `O_CREAT` is not allowed.
 * @return         Zero on success, -1 on error.
 * 
 * @throws  EINVAL  `oflag` contains `O_CREAT`.
 * @throws  EINVAL  `fd` is negative.
 * @throws          Any error specified for open(3).
 * @throws          Any error specified for dup2(3).
 * 
 * @since  Always.
 */
int reopen(int, int);
#endif


#endif

