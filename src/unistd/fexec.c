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
#include <stdarg.h>
#include <errno.h>
#include <alloca.h>
#include <stdio.h>



/**
 * The directory where all the process's file descriptors are available.
 */
#if defined(_LINUX_)
# define FD_PATH  "/proc/self/fd"  /* /dev/fd works but it is a symbolic link. */
#else
# define FD_PATH  "/dev/fd"
#endif



/**
 * The current environment variables.
 * 
 * @since  Always.
 */
extern char** environ;



/**
 * Common code for the `fexecl*` functions.
 * 
 * @param   fd          The first argument of said functions.
 * @param   argv        The rest of the arguments of said functions;
 *                      may conclude `envp`.
 * @param   fetch_envp  Whether `argv` includes `envp`.
 * 
 * @throws              Any error specified for execve(2).
 * 
 * @since  Always.
 */
static void vfexec(int fd, va_list argv, int fetch_envp)
{
  char* const* envp = environ;
  size_t n = 0, i;
  va_list args;
  char** argv_;
  
  va_copy(args, argv);
  while (n++, va_arg(args, char*) != NULL)
    break;
  
  if (fetch_envp)
    envp = va_arg(args, char* const*);
  
  argv_ = alloca(n * sizeof(char*));
  for (i = 0; i < n; i++)
    argv_[i] = va_arg(argv, char*);
  
  va_end(args);
  fexecve(fd, argv_, envp);
}



/**
 * Replace the current process image with a new process image.
 * 
 * This is a slibc extension.
 * 
 * @param   fd   File descriptor for the file to execute.
 * @param   ...  The arguments with which to execute the file.
 *               The arguments should have the type `const char*`.
 *               As a slibc extension, it can be empty.
 *               This list shall be terminated by a `NULL` sentinel.
 * @return       This function does not return on success,
 *               on error, -1 is returned and `errno` is
 *               set to describe the error.
 * 
 * @throws       Any error specified for execve(2).
 * 
 * @since  Always.
 */
int fexecl(int fd, ... /*, NULL */)
{
  int saved_errno;
  va_list argv;
  va_start(argv, fd);
  vfexec(fd, argv, 0);
  saved_errno = errno;
  va_end(argv);
  return errno = saved_errno, -1;
}


/**
 * Replace the current process image with a new process image.
 * 
 * This is a slibc extension.
 * 
 * @param   fd    File descriptor for the file to execute.
 * @param   ...   The arguments with which to execute the file.
 *                The arguments should have the type `const char*`.
 *                As a slibc extension, it can be empty.
 *                This list shall be terminated by a `NULL` sentinel.
 * @param   envp  The list of environment variables the new program shall
 *                have set. Each element shall be formatted $name=$value.
 *                This list shall be `NULL`-terminated. The behaviour
 *                is system-dependant if this argument is `NULL`.
 * @return        This function does not return on success,
 *                on error, -1 is returned and `errno` is
 *                set to describe the error.
 * 
 * @throws        Any error specified for execve(2).
 * 
 * @since  Always.
 */
int fexecle(int fd, ... /*, NULL, char* const envp[] */)
{
  int saved_errno;
  va_list argv;
  va_start(argv, fd);
  vfexec(fd, argv, 1);
  saved_errno = errno;
  va_end(argv);
  return errno = saved_errno, -1;
}


/**
 * Replace the current process image with a new process image.
 * 
 * This is a slibc extension.
 * 
 * @param   fd    File descriptor for the file to execute.
 * @param   argv  The arguments with which to execute the file.
 *                This parameter should really have the type
 *                `const char* const[]`, but that probably not
 *                so because compiles take issue with casts
 *                adding const to any pointer in the type
 *                except the outmost pointer. This list shall
 *                be `NULL`-terminated. The behaviour is
 *                system-dependant if this argument is `NULL`.
 * @return        This function does not return on success,
 *                on error, -1 is returned and `errno` is
 *                set to describe the error.
 * 
 * @throws        Any error specified for execve(2).
 * 
 * @since  Always.
 */
int fexecv(int fd, char* const argv[])
{
  return fexecve(fd, argv, environ);
}


/**
 * Replace the current process image with a new process image.
 * 
 * @param   fd    File descriptor for the file to execute.
 * @param   argv  The arguments with which to execute the file.
 *                This parameter should really have the type
 *                `const char* const[]`, but that probably not
 *                so because compiles take issue with casts
 *                adding const to any pointer in the type
 *                except the outmost pointer. This list shall
 *                be `NULL`-terminated. The behaviour is
 *                system-dependant if this argument is `NULL`.
 * @param   envp  The list of environment variables the new program shall
 *                have set. Each element shall be formatted $name=$value.
 *                This list shall be `NULL`-terminated. The behaviour
 *                is system-dependant if this argument is `NULL`.
 * @return        This function does not return on success,
 *                on error, -1 is returned and `errno` is
 *                set to describe the error.
 * 
 * @throws        Any error specified for execve(2).
 * 
 * @since  Always.
 */
int fexecve(int fd, char* const argv[], char* const envp[])
{
  char pathname[sizeof(FD_PATH "//") + 3 * sizeof(int)];
  int saved_errno;
  
  sprintf(pathname, FD_PATH "/%i/", fd);
  
  execve(pathname, argv, envp);
  saved_errno = errno;
  
  if (access(FD_PATH "/", X_OK))
    saved_errno = ENOSYS;
  
  errno = saved_errno == ENOENT ? EBADF : saved_errno;
  return -1;
}

