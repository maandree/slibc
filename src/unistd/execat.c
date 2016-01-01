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
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
/* TODO #include <sys/types.h> */
/* TODO #include <sys/stat.h> */
/* TODO temporary contants/structs from other headers { */
#define AT_FDCWD 1
#define AT_EMPTY_PATH 1
#define AT_SYMLINK_NOFOLLOW 1
#define _CS_PATH 1
struct stat { int st_mode; };
/* } */



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
 * Common code for the `execl*at` functions.
 * 
 * @param   dirfd       The first argument of said functions.
 * @param   file        The second argument of said functions.
 * @param   argv        The rest of the arguments of said functions;
 *                      may conclude `envp`.
 * @param   fetch_envp  Whether `argv` includes `envp`.
 * @param   use_path    Whether $PATH may be used.
 * 
 * @throws              Any error specified for execve(2).
 * 
 * @since  Always.
 */
static void vexecat(int dirfd, const char* file, va_list argv, int fetch_envp, int use_path)
{
  char* const* envp = environ;
  size_t n = 0, i;
  va_list args;
  char** argv_;
  int flags;
  
  va_copy(args, argv);
  while (n++, va_arg(args, char*) != NULL)
    break;
  
  if (fetch_envp)
    envp = va_arg(args, char* const*);
  flags = va_arg(args, int);
  
  argv_ = alloca(n * sizeof(char*));
  for (i = 0; i < n; i++)
    argv_[i] = va_arg(argv, char*);
  
  va_end(args);
  (void)(use_path ? execvpeat : execveat)(dirfd, file, argv_, envp, flags);
}



/**
 * Replace the current process image with a new process image.
 * 
 * This is a slibc extension.
 * 
 * @param   dirfd  File descriptor for a directory (opened with
 *                 with the open(2) `O_PATH` flag,) that will
 *                 act as the current working directory.
 *                 If `AT_FDCWD`, the current working directory
 *                 will be used.
 * @param   path   The pathname of the file to execute.
 * @param   ...    The arguments with which to execute the file.
 *                 The arguments should have the type `const char*`.
 *                 As a slibc extension, it can be empty.
 *                 This list shall be terminated by a `NULL` sentinel.
 * @param   flags  Bit mask that can include zero or more of the
 *                 following flags:
 *                   AT_EMPTY_PATH:
 *                     If `path` is an empty string, operate on the
 *                     file (not directory) referred to by `dirfd`.
 *                   AT_SYMLINK_NOFOLLOW:
 *                     If `path` is relative is a symbolic link,
 *                     fail with `errno` set to `ELOOP`.
 * @return         This function does not return on success,
 *                 on error, -1 is returned and `errno` is
 *                 set to describe the error.
 * 
 * @throws         Any error specified for execveat(2).
 * 
 * @since  Always.
 */
int execlat(int dirfd, const char* path, ... /*, NULL, int flags */)
{
  int saved_errno;
  va_list argv;
  va_start(argv, path);
  vexecat(dirfd, path, argv, 0, 0);
  saved_errno = errno;
  va_end(argv);
  return errno = saved_errno, -1;
}


/**
 * Replace the current process image with a new process image.
 * 
 * This is a slibc extension.
 * 
 * @param   dirfd  File descriptor for a directory (opened with
 *                 with the open(2) `O_PATH` flag,) that will
 *                 act as the current working directory.
 *                 If `AT_FDCWD`, the current working directory
 *                 will be used.
 * @param   file   The pathname of the file to execute,
 *                 or the filename of a file in $PATH,
 *                 to execute. If $PATH is not set, the current
 *                 working directory (yes, you read that right,)
 *                 and a default value for $PATH will be used.
 * @param   ...    The arguments with which to execute the file.
 *                 The arguments should have the type `const char*`.
 *                 As a slibc extension, it can be empty.
 *                 This list shall be terminated by a `NULL` sentinel.
 * @param   flags  Bit mask that can include zero or more of the
 *                 following flags:
 *                   AT_EMPTY_PATH:
 *                     If `file` is an empty string, operate on the
 *                     file (not directory) referred to by `dirfd`.
 *                   AT_SYMLINK_NOFOLLOW:
 *                     If `file` is relative is a symbolic link,
 *                     fail with `errno` set to `ELOOP`.
 * @return         This function does not return on success,
 *                 on error, -1 is returned and `errno` is
 *                 set to describe the error.
 * 
 * @throws         Any error specified for execveat(2).
 * 
 * @since  Always.
 */
int execlpat(int dirfd, const char* file, ... /*, NULL, int flags */)
{
  int saved_errno;
  va_list argv;
  va_start(argv, file);
  vexecat(dirfd, file, argv, 0, 1);
  saved_errno = errno;
  va_end(argv);
  return errno = saved_errno, -1;
}


/**
 * Replace the current process image with a new process image.
 * 
 * This is a slibc extension.
 * 
 * @param   dirfd  File descriptor for a directory (opened with
 *                 with the open(2) `O_PATH` flag,) that will
 *                 act as the current working directory.
 *                 If `AT_FDCWD`, the current working directory
 *                 will be used.
 * @param   path   The pathname of the file to execute.
 * @param   ...    The arguments with which to execute the file.
 *                 The arguments should have the type `const char*`.
 *                 As a slibc extension, it can be empty.
 *                 This list shall be terminated by a `NULL` sentinel.
 * @param   envp   The list of environment variables the new program shall
 *                 have set. Each element shall be formatted $name=$value.
 *                 This list shall be `NULL`-terminated. The behaviour
 *                 is system-dependant if this argument is `NULL`.
 * @param   flags  Bit mask that can include zero or more of the
 *                 following flags:
 *                   AT_EMPTY_PATH:
 *                     If `path` is an empty string, operate on the
 *                     file (not directory) referred to by `dirfd`.
 *                   AT_SYMLINK_NOFOLLOW:
 *                     If `path` is relative is a symbolic link,
 *                     fail with `errno` set to `ELOOP`.
 * @return         This function does not return on success,
 *                 on error, -1 is returned and `errno` is
 *                 set to describe the error.
 * 
 * @throws         Any error specified for execveat(2).
 * 
 * @since  Always.
 */
int execleat(int dirfd, const char* path, ... /*, NULL, char* const[] envp, int flags */)
{
  int saved_errno;
  va_list argv;
  va_start(argv, path);
  vexecat(dirfd, path, argv, 1, 0);
  saved_errno = errno;
  va_end(argv);
  return errno = saved_errno, -1;
}


/**
 * Replace the current process image with a new process image.
 * 
 * This is a slibc extension.
 * 
 * @param   dirfd  File descriptor for a directory (opened with
 *                 with the open(2) `O_PATH` flag,) that will
 *                 act as the current working directory.
 *                 If `AT_FDCWD`, the current working directory
 *                 will be used.
 * @param   file   The pathname of the file to execute,
 *                 or the filename of a file in $PATH,
 *                 to execute. If $PATH is not set, the current
 *                 working directory (yes, you read that right,)
 *                 and a default value for $PATH will be used.
 * @param   ...    The arguments with which to execute the file.
 *                 The arguments should have the type `const char*`.
 *                 As a slibc extension, it can be empty.
 *                 This list shall be terminated by a `NULL` sentinel.
 * @param   envp   The list of environment variables the new program shall
 *                 have set. Each element shall be formatted $name=$value.
 *                 This list shall be `NULL`-terminated. The behaviour
 *                 is system-dependant if this argument is `NULL`.
 * @param   flags  Bit mask that can include zero or more of the
 *                 following flags:
 *                   AT_EMPTY_PATH:
 *                     If `file` is an empty string, operate on the
 *                     file (not directory) referred to by `dirfd`.
 *                   AT_SYMLINK_NOFOLLOW:
 *                     If `file` is relative is a symbolic link,
 *                     fail with `errno` set to `ELOOP`.
 * @return         This function does not return on success,
 *                 on error, -1 is returned and `errno` is
 *                 set to describe the error.
 * 
 * @throws         Any error specified for execveat(2).
 * 
 * @since  Always.
 */
int execlpeat(int dirfd, const char* file, ... /*, NULL, char* const[] envp, int flags */)
{
  int saved_errno;
  va_list argv;
  va_start(argv, file);
  vexecat(dirfd, file, argv, 1, 1);
  saved_errno = errno;
  va_end(argv);
  return errno = saved_errno, -1;
}


/**
 * Replace the current process image with a new process image.
 * 
 * This is a slibc extension.
 * 
 * @param   dirfd  File descriptor for a directory (opened with
 *                 with the open(2) `O_PATH` flag,) that will
 *                 act as the current working directory.
 *                 If `AT_FDCWD`, the current working directory
 *                 will be used.
 * @param   path   The pathname of the file to execute.
 * @param   argv   The arguments with which to execute the file.
 *                 This parameter should really have the type
 *                 `const char* const[]`, but that probably not
 *                 so because compiles take issue with casts
 *                 adding const to any pointer in the type
 *                 except the outmost pointer. This list shall
 *                 be `NULL`-terminated. The behaviour is
 *                 system-dependant if this argument is `NULL`.
 * @param   flags  Bit mask that can include zero or more of the
 *                 following flags:
 *                   AT_EMPTY_PATH:
 *                     If `path` is an empty string, operate on the
 *                     file (not directory) referred to by `dirfd`.
 *                   AT_SYMLINK_NOFOLLOW:
 *                     If `path` is relative is a symbolic link,
 *                     fail with `errno` set to `ELOOP`.
 * @return         This function does not return on success,
 *                 on error, -1 is returned and `errno` is
 *                 set to describe the error.
 * 
 * @throws         Any error specified for execveat(2).
 * 
 * @since  Always.
 */
int execvat(int dirfd, const char* path, char* const argv[], int flags)
{
  return execveat(dirfd, path, argv, environ, flags);
}


/**
 * Replace the current process image with a new process image.
 * 
 * This is a slibc extension.
 * 
 * @param   dirfd  File descriptor for a directory (opened with
 *                 with the open(2) `O_PATH` flag,) that will
 *                 act as the current working directory.
 *                 If `AT_FDCWD`, the current working directory
 *                 will be used.
 * @param   file   The pathname of the file to execute,
 *                 or the filename of a file in $PATH,
 *                 to execute. If $PATH is not set, the current
 *                 working directory (yes, you read that right,)
 *                 and a default value for $PATH will be used.
 * @param   argv   The arguments with which to execute the file.
 *                 This parameter should really have the type
 *                 `const char* const[]`, but that probably not
 *                 so because compiles take issue with casts
 *                 adding const to any pointer in the type
 *                 except the outmost pointer. This list shall
 *                 be `NULL`-terminated. The behaviour is
 *                 system-dependant if this argument is `NULL`.
 * @param   flags  Bit mask that can include zero or more of the
 *                 following flags:
 *                   AT_EMPTY_PATH:
 *                     If `file` is an empty string, operate on the
 *                     file (not directory) referred to by `dirfd`.
 *                   AT_SYMLINK_NOFOLLOW:
 *                     If `file` is relative is a symbolic link,
 *                     fail with `errno` set to `ELOOP`.
 * @return         This function does not return on success,
 *                 on error, -1 is returned and `errno` is
 *                 set to describe the error.
 * 
 * @throws         Any error specified for execveat(2).
 * 
 * @since  Always.
 */
int execvpat(int dirfd, const char* file, char* const argv[], int flags)
{
  return execvpeat(dirfd, file, argv, environ, flags);
}


/**
 * Replace the current process image with a new process image.
 * 
 * @param   dirfd  File descriptor for a directory (opened with
 *                 with the open(2) `O_PATH` flag,) that will
 *                 act as the current working directory.
 *                 If `AT_FDCWD`, the current working directory
 *                 will be used.
 * @param   path   The pathname of the file to execute.
 * @param   argv   The arguments with which to execute the file.
 *                 This parameter should really have the type
 *                 `const char* const[]`, but that probably not
 *                 so because compiles take issue with casts
 *                 adding const to any pointer in the type
 *                 except the outmost pointer. This list shall
 *                 be `NULL`-terminated. The behaviour is
 *                 system-dependant if this argument is `NULL`.
 * @param   envp   The list of environment variables the new program shall
 *                 have set. Each element shall be formatted $name=$value.
 *                 This list shall be `NULL`-terminated. The behaviour
 *                 is system-dependant if this argument is `NULL`.
 * @param   flags  Bit mask that can include zero or more of the
 *                 following flags:
 *                   AT_EMPTY_PATH:
 *                     If `path` is an empty string, operate on the
 *                     file (not directory) referred to by `dirfd`.
 *                   AT_SYMLINK_NOFOLLOW:
 *                     If `path` is relative is a symbolic link,
 *                     fail with `errno` set to `ELOOP`.
 * @return         This function does not return on success,
 *                 on error, -1 is returned and `errno` is
 *                 set to describe the error.
 * 
 * @throws         Any error specified for execveat(2).
 * 
 * @since  Always.
 */
int execveat(int dirfd, const char* path, char* const argv[], char* const envp[], int flags)
{
/* TODO use linux system call if available */
  struct stat attr;
  char* pathname = NULL;
  int saved_errno;
  
  if (*path == '/')
    return execve(path, argv, envp);
  
  if ((dirfd == AT_FDCWD) && (flags & AT_EMPTY_PATH) && !*path)
    return errno = EISDIR, -1;
  
  if ((dirfd == AT_FDCWD) && (flags & AT_SYMLINK_NOFOLLOW))
    {
      if (lstat(path, &attr))
	return -1;
      if (S_IFLNK(attr.st_mode))
	return errno = ELOOP, -1;
    }
  
  pathname = malloc(sizeof(FD_PATH "//") + (3 * sizeof(int) + strlen(path)) * sizeof(char));
  if (pathname == NULL)
    return -1;
  
  sprintf(pathname, FD_PATH "/%i%s%s", dirfd, *path ? "/" : "", path);
  execve(pathname, argv, envp);
  
  saved_errno = errno;
  free(pathname);
  errno = saved_errno;
  return -1;
}


/**
 * Replace the current process image with a new process image.
 * 
 * This is a slibc extension.
 * 
 * @param   dirfd  File descriptor for a directory (opened with
 *                 with the open(2) `O_PATH` flag,) that will
 *                 act as the current working directory.
 *                 If `AT_FDCWD`, the current working directory
 *                 will be used.
 * @param   file   The pathname of the file to execute,
 *                 or the filename of a file in $PATH,
 *                 to execute. If $PATH is not set, the current
 *                 working directory (yes, you read that right,)
 *                 and a default value for $PATH will be used.
 * @param   argv   The arguments with which to execute the file.
 *                 This parameter should really have the type
 *                 `const char* const[]`, but that probably not
 *                 so because compiles take issue with casts
 *                 adding const to any pointer in the type
 *                 except the outmost pointer. This list shall
 *                 be `NULL`-terminated. The behaviour is
 *                 system-dependant if this argument is `NULL`.
 * @param   envp   The list of environment variables the new program shall
 *                 have set. Each element shall be formatted $name=$value.
 *                 This list shall be `NULL`-terminated. The behaviour
 *                 is system-dependant if this argument is `NULL`.
 * @param   flags  Bit mask that can include zero or more of the
 *                 following flags:
 *                   AT_EMPTY_PATH:
 *                     If `file` is an empty string, operate on the
 *                     file (not directory) referred to by `dirfd`.
 *                   AT_SYMLINK_NOFOLLOW:
 *                     If `file` is relative is a symbolic link,
 *                     fail with `errno` set to `ELOOP`.
 * @return         This function does not return on success,
 *                 on error, -1 is returned and `errno` is
 *                 set to describe the error.
 * 
 * @throws         Any error specified for execveat(2).
 * 
 * @since  Always.
 */
int execvpeat(int dirfd, const char* file, char* const argv[], char* const envp[], int flags)
{
  char* pathname = NULL;
  int eacces = 0;
  int saved_errno;
  
  if (strchr(file, '/') || !*file)
    return execveat(dirfd, file, argv, envp, flags);
  
  if (getenv("PATH") == NULL)
    {
      execveat(dirfd, file, argv, envp, flags);
      if      (errno == EACCES)  eacces = 1;
      else if (errno != ENOENT)  return -1;
    }
  
  pathname = searchpath3(file, NULL, "");
  if (pathname == NULL)
    return -1;
  
  execve(pathname, argv, envp);
  
  saved_errno = errno;
  free(pathname);
  if (eacces && (saved_errno == ENOENT))
    saved_errno = EACCES;
  errno = saved_errno;
  return -1;
}

