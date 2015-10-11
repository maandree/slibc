/**
 * slibc — Yet another C library
 * Copyright © 2015  Mattias Andrée (maandree@member.fsf.org)
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
#ifndef _UNISTD_H
#define _UNISTD_H
#include <slibc/version.h>
#include <slibc/features.h>



#define __NEED_size_t
#define __NEED_ssize_t
#define __NEED_uid_t
#define __NEED_gid_t
#define __NEED_off_t
#define __NEED_pid_t
#define __NEED_ptrdiff_t
#define __NEED_intptr_t
#define __NEED_useconds_t
#include <bits/types.h>


/**
 * `NULL`'s canonical header is <stddef.h>.
 */
#ifndef NULL
# define NULL  ((void*)0)
#endif


/**
 * The file descriptor for stdin.
 * The file with input.
 */
#define STDIN_FILENO  0

/**
 * The file descriptor for stdout.
 * The file for output.
 */
#define STDOUT_FILENO  1

/**
 * The file descriptor for stderr.
 * The file for error messages and warnings.
 */
#define STDERR_FILENO  2


/**
 * Set the high end of the calling process's
 * data segment.
 * 
 * The high end is defined as the last byte
 * in the segment plus 1.
 * 
 * Using `brk` is highly discouraged. `malloc`,
 * `calloc` and `free`, and its related functions,
 * fall be used instead as they are much more
 * conformable. Use of `brk` can couse errors
 * when using `malloc`, `free`, &c. Thus, `brk`
 * shall (bascially) only be used if you are
 * writting an alterantive malloc-implementation.
 * 
 * `brk` was marked LEGACY in SUSv2, and it
 * was removed from the POSIX standard in revision
 * POSIX.1-2001. It is however fundamental in
 * implementing a fast `malloc`-implementation.
 * 
 * @param   address  The process's new high end of its data segment.
 *                   If lower than the current low end, nothing will
 *                   happen and the function will return with a success
 *                   status.
 * @return           Zero on succes, -1 on error. On error, `errno`
 *                   is set to indicate the error.
 * 
 * @throws  ENOMEM  The process can allocate the requested amount
 *                  of memory. Either the process store limit would
 *                  have been exceeded, RAM and swap memory would
 *                  have been exhausted, or the request would cause
 *                  the data segment to overlap another segment.
 */
int brk(void*) /* TODO implement brk */
  __GCC_ONLY(__attribute__((warn_unused_result)));

/**
 * Set and get the current high end of the calling
 * process's data segment.
 * 
 * There is some documents that state that the new,
 * rather than the previous, high end is returned.
 * Additionally, some documentions do not document
 * possible failure. Thus only `sbrk(0)` is guaranteed
 * to be portable. The return type differs between
 * implementations; common return types are `int`,
 * `ssize_t`, `ptrdiff_t`, `ptrdiff_t`, `intptr_t`,
 * and `void*`. Note that `int` is
 * microarchitecture-portable.
 * 
 * `sbrk` was marked LEGACY in SUSv2, and it
 * was removed from the POSIX standard in revision
 * POSIX.1-2001. It is however fundamental in
 * implementing a fast `malloc`-implementation.
 * 
 * @param   delta  The incremant of the size of the data segment,
 *                 zero means that the high end shall not be moved
 *                 (thus the current high end is returned,) a
 *                 positive value will cause the segment to grow,
 *                 a negative value will cause the segment to shrink.
 * @return         The previous high end. `(void*)-1` is returned on error.
 * 
 * @throws  ENOMEM  The process can allocate the requested amount
 *                  of memory. Either the process store limit would
 *                  have been exceeded, RAM and swap memory would
 *                  have been exhausted, or the request would cause
 *                  the data segment to overlap another segment.
 */
void* sbrk(ptrdiff_t) /* TODO implement sbrk */
  __GCC_ONLY(__attribute__((warn_unused_result)));



/* TODO implement exit-functions */
void _exit(int) __noreturn;


/* TODO implement I/O */
int isatty(int);



/**
 * Replace the current process image with a new process image.
 * 
 * @param   path  The pathname of the file to execute.
 * @param   ...   The arguments with which to execute the file.
 *                The arguments should have the type `const char*`.
 *                As a slibc extension, it can be empty.
 *                This list shall be terminated by a `NULL` sentinel.
 * @return        This function does not return on success,
 *                on error, -1 is returned and `errno` is
 *                set to describe the error.
 * 
 * @throws        Any error specified for execve(2).
 */
int execl(const char*, ... /*, NULL */)
  __GCC_ONLY(__attribute__((sentinel(0), nonnull(1))));

/**
 * Replace the current process image with a new process image.
 * 
 * @param   file  The pathname of the file to execute,
 *                or the filename of a file in $PATH,
 *                to execute. If $PATH is not set, the current
 *                working directory (yes, you read that right,)
 *                and a default value for $PATH will be used.
 * @param   ...   The arguments with which to execute the file.
 *                The arguments should have the type `const char*`.
 *                As a slibc extension, it can be empty.
 *                This list shall be terminated by a `NULL` sentinel.
 * @return        This function does not return on success,
 *                on error, -1 is returned and `errno` is
 *                set to describe the error.
 * 
 * @throws        Any error specified for execve(2).
 */
int execlp(const char*, ... /*, NULL */)
  __GCC_ONLY(__attribute__((sentinel(0), nonnull(1))));

/**
 * Replace the current process image with a new process image.
 * 
 * @param   path  The pathname of the file to execute.
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
 */
int execle(const char*, ... /*, NULL, char* const[] */)
  __GCC_ONLY(__attribute__((sentinel(1), nonnull(1))));

#if (defined(_SLIBC_SOURCE) && !defined(__PORTABLE))
/**
 * Replace the current process image with a new process image.
 * 
 * This is a slibc extension, added for completeness.
 * 
 * @param   file  The pathname of the file to execute,
 *                or the filename of a file in $PATH,
 *                to execute. If $PATH is not set, the current
 *                working directory (yes, you read that right,)
 *                and a default value for $PATH will be used.
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
 */
int execlpe(const char*, ... /*, NULL, char* const[] */)
  __GCC_ONLY(__attribute__((sentinel(1), nonnull(1))));
#endif

/**
 * Replace the current process image with a new process image.
 * 
 * @param   path  The pathname of the file to execute.
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
 */
int execv(const char*, char* const[])
  __GCC_ONLY(__attribute__((nonnull(1))));

/**
 * Replace the current process image with a new process image.
 * 
 * @param   file  The pathname of the file to execute,
 *                or the filename of a file in $PATH,
 *                to execute. If $PATH is not set, the current
 *                working directory (yes, you read that right,)
 *                and a default value for $PATH will be used.
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
 */
int execvp(const char*, char* const[])
  __GCC_ONLY(__attribute__((nonnull(1))));

/**
 * Replace the current process image with a new process image.
 * 
 * @param   path  The pathname of the file to execute.
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
 */
int execve(const char*, char* const[], char* const[])
  __GCC_ONLY(__attribute__((nonnull(1))));

#if (defined(_GNU_SOURCE) || defined(_SLIBC_SOURCE)) && !defined(__PORTABLE)
/**
 * Replace the current process image with a new process image.
 * 
 * This is a GNU-compliant slibc extension.
 * 
 * @param   file  The pathname of the file to execute,
 *                or the filename of a file in $PATH,
 *                to execute. If $PATH is not set, the current
 *                working directory (yes, you read that right,)
 *                and a default value for $PATH will be used.
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
 */
int execvpe(const char*, char* const[], char* const[])
  __GCC_ONLY(__attribute__((nonnull(1))));
#endif


#if defined(_SLIBC_SOURCE) && !defined(__PORTABLE)
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
 */
int execlat(int, const char*, ... /*, NULL, int */)
  __GCC_ONLY(__attribute__((sentinel(1), nonnull(2))));

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
 */
int execlpat(int, const char*, ... /*, NULL, int */)
  __GCC_ONLY(__attribute__((sentinel(1), nonnull(2))));

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
 */
int execleat(int, const char*, ... /*, NULL, char* const[], int */)
  __GCC_ONLY(__attribute__((sentinel(2), nonnull(2))));

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
 */
int execlpeat(int, const char*, ... /*, NULL, char* const[], int */)
  __GCC_ONLY(__attribute__((sentinel(2), nonnull(2))));

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
 */
int execvat(int, const char*, char* const[], int)
  __GCC_ONLY(__attribute__((nonnull(2))));

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
 */
int execvpat(int, const char*, char* const[], int)
  __GCC_ONLY(__attribute__((nonnull(2))));
#endif

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
 */
int execveat(int, const char*, char* const[], char* const[], int)
  __GCC_ONLY(__attribute__((nonnull(2))));

#if defined(_SLIBC_SOURCE) && !defined(__PORTABLE)
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
 */
int execvpeat(int, const char*, char* const[], char* const[], int)
  __GCC_ONLY(__attribute__((nonnull(2))));
#endif


#if defined(_SLIBC_SOURCE) && !defined(__PORTABLE)
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
 */
int fexecl(int, ... /*, NULL */)
  __GCC_ONLY(__attribute__((sentinel(0))));

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
 */
int fexecle(int, ... /*, NULL, char* const[] */)
  __GCC_ONLY(__attribute__((sentinel(1))));

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
 */
int fexecv(int, char* const[]);
#endif

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
 */
int fexecve(int, char* const[], char* const[]);



#endif

