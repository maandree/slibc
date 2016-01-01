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
#include <fcntl.h>



/**
 * Detach the process from the controlling terminal
 * and run in the background.
 * 
 * The function shall change the working directory
 * to '/' to avoid block a mountpoint from being
 * unmounted. It shall also change direct stdin,
 * stdout, and stderr to '/dev/null'. It shall
 * then double-fork, and between the fork, become
 * a session leader, temporarily, so that the
 * it no longer has a controlling terminal.
 * 
 * Note well, this function does not implement a
 * reliable or particularly correct mechanism for
 * daemonising a process. It shall not be used!
 * Note, the GNU implementation is slightly
 * different because of a bug.
 * 
 * @etymology  (Daemon)ise!
 * 
 * @param   nochdir  The not change working directory to '/'.
 * @param   noclose  The not redirect stdin, stdout, and stderr to '/dev/null'.
 * @return           Zero on success, -1 on error.
 * 
 * @throws  EACCES  If `nochdir` is zero, and the user is denied access to '/'.
 * @throws          Any error specified for open(3).
 * @throws          Any error specified for dup2(3).
 * @throws          Any error specified for fork(3).
 * @throws          Any error specified for setsid(3).
 * 
 * @since  Always.
 */
int daemon(int nochdir, int noclose)
{
  int fd = -1;
  int saved_errno;
  
  if (nochdir ? 0 : chdir("/"))
    return -1;
  
  if (noclose == 0)
    {
      if (fd = open("/dev/null", O_RDWR), fd < 0)
	return -1;
      
      if (dup2(fd, 0) < 0)  goto fail;
      if (dup2(fd, 1) < 0)  goto fail;
      if (dup2(fd, 2) < 0)  goto fail;
      
      if (fd > 2)
	close(fd);
    }
  
  switch (fork())
    {
    case  0:  break;
    case -1:  return -1;
    default:  _exit(0);
    }

  if (setsid() < 0)
    return -1;

  switch (fork())
    {
    case  0:  break;
    case -1:  return -1;
    default:  _exit(0);
    }
  
  return 0;
 fail:
  saved_errno = errno;
  if (fd > 2)
    close (fd);
  errno = saved_errno;
  return -1;
}

