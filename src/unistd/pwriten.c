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
#include <signal.h>



/**
 * Variant of `pwrite` that will write until all given
 * data has been written. This function will block signals
 * so that it cannot throw `EINTR`, which could mean that
 * you do not know how much data has been successfully
 * written. Note however, it may fail for any other reason
 * resulting in the same problem.
 * 
 * This is a slibc extension.
 * 
 * @etymology  Variant of `(pwrite)` that writes all `(n)byte` bytes!
 * 
 * @param  fd      The file descriptor whither the data shall be write.
 * @param  buf     The data to write.
 * @param  nbyte   The number of bytes to write.
 * @param  offset  Whence in the file the write begins.
 * 
 * @throws  Any error specified for pwrite(3), except `EINTR`.
 * 
 * @since  Always.
 */
ssize_t pwriten(int fd, const void* buf, size_t nbyte, off_t offset)
{
  const char *buffer = buf;
  ssize_t r, n = 0;
  sigset_t mask, oldmask;
  int saved_errno = 0;
  
  sigfillset(&mask);
  pthread_sigmask(SIG_BLOCK, &mask, &oldmask);
  
  while (nbyte)
    {
      r = pwrite(fildes, buffer, nbyte, offset);
      if (r < 0)
	goto fail;
      if (r == 0)
	break;
      n += r;
      nbyte -= (size_t)r;
      offset += (off_t)r;
      buffer += r;
    }

  pthread_sigmask(SIG_SETMASK, &oldmask, NULL);
  return n;
 fail:
  errno = saved_errno;
  pthread_sigmask(SIG_SETMASK, &oldmask, NULL);
  saved_errno = errno;
  return -1;
}

