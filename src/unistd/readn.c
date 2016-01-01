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
 * Variant of `read` that will read until the request
 * amount of that has been read, or there is no more
 * data to read. This function will block signals so
 * that it cannot throw `EINTR`, which could mean that
 * read data is lost. Note however, it may fail for
 * any other reason resulting in lost data.
 * 
 * This is a Plan 9 from Bell Labs compliant slibc extension.
 * 
 * @etymology  (Read) all `(n)byte` bytes!
 * 
 * @param  fd     The file descriptor whence the data shall be read.
 * @param  buf    The buffer whither the read data shall be stored.
 * @param  nbyte  The number of bytes to read.
 * 
 * @throws  Any error specified for read(3), except `EINTR`.
 * 
 * @since  Always.
 */
ssize_t readn(int fd, void* buf, size_t nbyte)
{
  char *buffer = buf;
  ssize_t r, n = 0;
  sigset_t mask, oldmask;
  int saved_errno = 0;
  
  sigfillset(&mask);
  pthread_sigmask(SIG_BLOCK, &mask, &oldmask);
  
  while (nbyte)
    {
      r = read(fildes, buffer, nbyte);
      if (r < 0)
	goto fail;
      if (r == 0)
	break;
      n += r;
      nbyte -= (size_t)r;
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

