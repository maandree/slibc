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
 * 
 * @etymology  (St)andar(d) (in)put (file)descriptor (number).
 * 
 * @since  Always.
 */
#define STDIN_FILENO  0

/**
 * The file descriptor for stdout.
 * The file for output.
 * 
 * @etymology  (St)andar(d) (out)put (file)descriptor (number).
 * 
 * @since  Always.
 */
#define STDOUT_FILENO  1

/**
 * The file descriptor for stderr.
 * The file for error messages and warnings.
 * 
 * @etymology  (St)andar(d) (err)or output (file)descriptor (number).
 * 
 * @since  Always.
 */
#define STDERR_FILENO  2


/**
 * Used in `access` and `faccessat`, to check
 * weather a file appears to exists for the
 * current user. It is impled for `X_OK`,
 * `W_OK` and `R_OK`.
 * 
 * Its value, 0, comes from that this check
 * is always performed.
 * 
 * @etymology  This constant is named in symmetry with
 *             `X_OK`, `W_OK`, and `R_OK`. The 'F' comes
 *             from "(f)ile exists", and '_OK' comes
 *             from the name of the other '?(_OK)'
 *             constants.
 * 
 * @since  Always.
 */
#define F_OK  0

/**
 * Used in `access` and `faccessat`, to check
 * weather a file is executable (for directories:
 * its content can be listed) for the current
 * user. Implies `F_OK`.
 * 
 * Its value, 1, comes from that for each user-octet
 * in the permission bits, the bit 1 signifies that
 * the file is executable.
 * 
 * @etymology  Is e(x)ecute (ok)ay?
 * 
 * @since  Always.
 */
#define X_OK  1

/**
 * Used in `access` and `faccessat`, to check
 * weather a file is writable for the current
 * user. Implies `F_OK`.
 * 
 * Its value, 2, comes from that for each user-octet
 * in the permission bits, the bit 2 signifies that
 * the file is writable.
 * 
 * @since  Always.
 * @etymology  Is (w)rite (ok)ay?
 */
#define W_OK  2

/**
 * Used in `access` and `faccessat`, to check
 * weather a file is readable for the current
 * user. Implies `F_OK`.
 * 
 * Its value, 4, comes from that for each user-octet
 * in the permission bits, the bit 4 signifies that
 * the file is readable.
 * 
 * @etymology  Is (r)ead (ok)ay?
 * 
 * @since  Always.
 */
#define R_OK  4



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
 * @etymology  Set (br)ea(k).
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
 * 
 * @since  Always.
 */
int brk(void*) /* TODO implement brk */
  __GCC_ONLY(__attribute__((__warn_unused_result__)));

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
 * @etymology  Shift (br)ea(k).
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
 * 
 * @since  Always.
 */
void* sbrk(ptrdiff_t) /* TODO implement sbrk */
  __GCC_ONLY(__attribute__((__warn_unused_result__)));



/* TODO implement exit-functions */
__noreturn void _exit(int);


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
 * 
 * @since  Always.
 */
int execl(const char*, ... /*, NULL */)
  __GCC_ONLY(__attribute__((__sentinel__(0), __nonnull__(1))));

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
 * 
 * @since  Always.
 */
int execlp(const char*, ... /*, NULL */)
  __GCC_ONLY(__attribute__((__sentinel__(0), __nonnull__(1))));

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
 * 
 * @since  Always.
 */
int execle(const char*, ... /*, NULL, char* const[] */)
  __GCC_ONLY(__attribute__((__sentinel__(1), __nonnull__(1))));

#if defined(__SLIBC_SOURCE)
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
 * 
 * @since  Always.
 */
int execlpe(const char*, ... /*, NULL, char* const[] */)
  __GCC_ONLY(__attribute__((__sentinel__(1), __nonnull__(1))));
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
 * 
 * @since  Always.
 */
int execv(const char*, char* const[])
  __GCC_ONLY(__attribute__((__nonnull__(1))));

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
 * 
 * @since  Always.
 */
int execvp(const char*, char* const[])
  __GCC_ONLY(__attribute__((__nonnull__(1))));

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
 * 
 * @since  Always.
 */
int execve(const char*, char* const[], char* const[])
  __GCC_ONLY(__attribute__((__nonnull__(1))));

#if defined(__GNU_SOURCE) || defined(__SLIBC_SOURCE)
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
 * 
 * @since  Always.
 */
int execvpe(const char*, char* const[], char* const[])
  __GCC_ONLY(__attribute__((__nonnull__(1))));
#endif


#if defined(__SLIBC_SOURCE)
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
int execlat(int, const char*, ... /*, NULL, int */)
  __GCC_ONLY(__attribute__((__sentinel__(1), __nonnull__(2))));

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
int execlpat(int, const char*, ... /*, NULL, int */)
  __GCC_ONLY(__attribute__((__sentinel__(1), __nonnull__(2))));

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
int execleat(int, const char*, ... /*, NULL, char* const[], int */)
  __GCC_ONLY(__attribute__((__sentinel__(2), __nonnull__(2))));

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
int execlpeat(int, const char*, ... /*, NULL, char* const[], int */)
  __GCC_ONLY(__attribute__((__sentinel__(2), __nonnull__(2))));

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
int execvat(int, const char*, char* const[], int)
  __GCC_ONLY(__attribute__((__nonnull__(2))));

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
int execvpat(int, const char*, char* const[], int)
  __GCC_ONLY(__attribute__((__nonnull__(2))));
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
 * 
 * @since  Always.
 */
int execveat(int, const char*, char* const[], char* const[], int)
  __GCC_ONLY(__attribute__((__nonnull__(2))));

#if defined(__SLIBC_SOURCE)
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
int execvpeat(int, const char*, char* const[], char* const[], int)
  __GCC_ONLY(__attribute__((__nonnull__(2))));
#endif


#if defined(__SLIBC_SOURCE)
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
int fexecl(int, ... /*, NULL */)
  __GCC_ONLY(__attribute__((__sentinel__(0))));

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
int fexecle(int, ... /*, NULL, char* const[] */)
  __GCC_ONLY(__attribute__((__sentinel__(1))));

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
 * 
 * @since  Always.
 */
int fexecve(int, char* const[], char* const[]);


#if defined(__PLAN9_SOURCE) || defined(__SLIBC_SOURCE)
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
 * @param   name  The name of the sought executable. Must not be `NULL`.
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
char* searchpath(const char*)
  __GCC_ONLY(__attribute__((__nonnull__(1), __warn_unused_result__)));
#endif

#if defined(__SLIBC_SOURCE)
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
char* searchpath2(const char*, const char*)
  __GCC_ONLY(__attribute__((__nonnull__(1), __warn_unused_result__)));

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
 * @param   first     If $PATH is not defined, and `fallback` is `NULL`,
 *                    these directories are tested before the default
 *                    directories. May be `NULL`.
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
char* searchpath3(const char*, const char*, const char*)
  __GCC_ONLY(__attribute__((__nonnull__(1), __warn_unused_result__)));
#endif


#if defined(__BSD_SOURCE) || defined(__XOPEN_SOURCE)
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
int daemon(int, int)
  __deprecated("Portable programs should implement this mechanism "
	       "manually. Non-portable programs may use 'daemonise'.");
#endif


#if defined(__SLIBC_SOURCE)
/**
 * Leave all opened files open.
 */
#define DAEMONISE_NO_CLOSE  1

/**
 * Leave all signal handlers rather than
 * appling default signal handlers.
 */
#define DAEMONISE_NO_SIG_DFL  2

/**
 * Leave the signal block mask as-is.
 */
#define DAEMONISE_KEEP_SIGMASK  4

/**
 * Do not remove malformatted environment entries.
 */
#define DAEMONISE_KEEP_ENVIRON  8

/**
 * Do not set umask to zero.
 */
#define DAEMONISE_KEEP_UMASK  16

/**
 * Do not create a PID file.
 * 
 * Cannot be combined with `DAEMONISE_NEW_PID`.
 */
#define DAEMONISE_NO_PID_FILE  32

/**
 * Do not close stderr even if it is
 * a terminal device.
 * 
 * Cannot be combined with `DAEMONISE_CLOSE_STDERR`.
 */
#define DAEMONISE_KEEP_STDERR  64

/**
 * Close stderr even if it is
 * not a terminal device.
 * 
 * Cannot be combined with `DAEMONISE_KEEP_STDERR`.
 */
#define DAEMONISE_CLOSE_STDERR  128

/**
 * Do not close stdin.
 */
#define DAEMONISE_KEEP_STDIN  256

/**
 * Do not close stdout.
 */
#define DAEMONISE_KEEP_STDOUT  512

/**
 * Enables you to select additional
 * file descritors to keep open.
 */
#define DAEMONISE_KEEP_FDS  1024

/**
 * Override the PID file if it already exists,
 * rather than failing. It is a bad idea to do
 * this unless you already made sure that the
 * daemon is not already running.
 * 
 * Cannot be combined with `DAEMONISE_NO_PID_FILE`.
 */
#define DAEMONISE_NEW_PID  2048

/**
 * Daemonise the process. This means to:
 * 
 * -  close all file descritors except for those to
 *    stdin, stdout, and stderr,
 * 
 * -  remove all custom signal handlers, and apply
 *    the default handlers.
 * 
 * -  unblock all signals,
 * 
 * -  remove all malformatted entries in the
 *    environment (this not containing an '=',)
 * 
 * -  set the umask to zero, to be ensure that all
 *    file permissions are set as specified,
 * 
 * -  change directory to '/', to ensure that the
 *    process does not block any mountpoint from being
 *    unmounted,
 * 
 * -  fork to become a background process,
 * 
 * -  temporarily become a session leader to ensure
 *    that the process does not have a controlling
 *    terminal.
 * 
 * -  fork again to become a child of the daemon
 *    supervisor, (subreaper could however be in the
 *    say, so one should not merely rely on this when
 *    writing a daemon supervisor,) (the first child
 *    shall exit after this,)
 * 
 * -  create, exclusively, a PID file to stop the daemon
 *    to be being run twice concurrently, and to let
 *    the daemon supervicer know the process ID of the
 *    daemon,
 * 
 * -  redirect stdin and stdout to /dev/null,
 *    as well as stderr if it is currently directed
 *    to a terminal, and
 * 
 * -  exit in the original process to let the daemon
 *    supervisor know that the daemon has been
 *    initialised.
 * 
 * Before calling this function, you should remove any
 * environment variable that could negatively impact
 * the runtime of the process.
 * 
 * After calling this function, you should remove
 * unnecessary privileges.
 * 
 * Do not try do continue the process in failure unless
 * you make sure to only do this in the original process.
 * But not that things will not necessarily be as when
 * you make the function call. The process can have become
 * partially deamonised.
 * 
 * If $XDG_RUNTIME_DIR is set and is not empty, its value
 * should be used instead of /run for the runtime data-files
 * directory, in which the PID file is stored.
 * 
 * This is a slibc extension.
 * 
 * @etymology  (Daemonise) the process!
 * 
 * @param   name   The name of the daemon. Use a hardcoded value,
 *                 not the process name. Must not be `NULL`.
 * @param   flags  Flags to modify the behaviour of the function.
 *                 A bitwise OR combination of the constants:
 *                 -  `DAEMONISE_NO_CLOSE`
 *                 -  `DAEMONISE_NO_SIG_DFL`
 *                 -  `DAEMONISE_KEEP_SIGMASK`
 *                 -  `DAEMONISE_KEEP_ENVIRON`
 *                 -  `DAEMONISE_KEEP_UMASK`
 *                 -  `DAEMONISE_NO_PID_FILE`
 *                 -  `DAEMONISE_KEEP_STDERR`
 *                 -  `DAEMONISE_CLOSE_STDERR`
 *                 -  `DAEMONISE_KEEP_STDIN`
 *                 -  `DAEMONISE_KEEP_STDOUT`
 *                 -  `DAEMONISE_KEEP_FDS`
 *                 -  `DAEMONISE_NEW_PID`
 * @param   ...    Enabled if `DAEMONISE_KEEP_FDS` is used,
 *                 do not add anything if `DAEMONISE_KEEP_FDS`
 *                 is unused. This is a `-1`-terminated list
 *                 of file descritors to keep open. 0, 1, and 2
 *                 are implied by `DAEMONISE_KEEP_STDIN`,
 *                 `DAEMONISE_KEEP_STDOUT`, and `DAEMONISE_KEEP_STDERR`,
 *                 respectively. All arguments are of type `int`.
 * @return         Zero on success, -1 on error.
 * 
 * @throws  EEXIST  The PID file already exists on the system.
 *                  Unless your daemon supervisor removs old
 *                  PID files, this could mean that the daemon
 *                  has exited without removing the PID file.
 * @throws  EINVAL  `flags` contains an unsupported bit, both
 *                  `DAEMONISE_KEEP_STDERR` and `DAEMONISE_CLOSE_STDERR`
 *                  are set, both `DAEMONISE_NO_PID_FILE` and
 *                  `DAEMONISE_NEW_PID`, or both `DAEMONISE_CLOSE_STDERR`
 *                  and `DAEMONISE_KEEP_FDS` are set whilst `2` is
 *                  in the list of file descriptor not to close.
 * @throws          Any error specified for signal(3).
 * @throws          Any error specified for sigemptyset(3).
 * @throws          Any error specified for sigprocmask(3).
 * @throws          Any error specified for chdir(3).
 * @throws          Any error specified for pipe(3).
 * @throws          Any error specified for dup(3).
 * @throws          Any error specified for dup2(3).
 * @throws          Any error specified for fork(3).
 * @throws          Any error specified for setsid(3).
 * @throws          Any error specified for open(3).
 * @throws          Any error specified for malloc(3).
 * 
 * @since  Always.
 */
int daemonise(const char*, int, ...)
  __GCC_ONLY(__attribute__((__nonnull__, __warn_unused_result__)));

/**
 * Remove the PID file created by `daemonise`. This shall
 * always be called before exiting after calling `daemonise`,
 * even if it failed.
 * 
 * This is a slibc extension.
 * 
 * @etymology  (Un)link PID file created by `(daemonise)`!
 * 
 * @return  Zero on success, -1 on error.
 * 
 * @throws  Any error specified for unlink(3).
 * 
 * @since  Always.
 */
int undaemonise(void);
#endif


/**
 * Get password input from the terminal.
 * 
 * The exact behaviour of this function depends on the implementations.
 * However you can assume that, the controlling terminal (/dev/tty) is
 * opened and used for input and output, and that echoing is disabled.
 * You cannot assume that arbitrary lengths are supported. However, in
 * this implementation, line editing is enabled and arbitrary lengths
 * are supported. If the length of the input (excluding termination) is
 * less than 8192 a statically allocated string is returned, otherwise
 * a dynamically allocated string is returned.
 * 
 * @etymology  (Get) (pass)word from terminal!
 * 
 * @param   prompt  Text to print at the beginning of the line.
 *                  Used to tell the user what is expected of her.
 *                  Must not be `NULL`.
 * @return          The entered line. You should override it with zeroes as
 *                  soon as possible to avoid leaving cleartest passphrases
 *                  visible in memory, or potentially stored to unencrypted
 *                  swap. The returned string is statically allocated, do
 *                  not deallocate it, unless you know that you are using
 *                  slibc and the length of the string is at least 8192.
 *                  `NULL` on error. If a statically allocated string is
 *                  returned, it will be overwritten at the next call.
 * 
 * @throws  Any error specified for open(3).
 * @throws  Any error specified for malloc(3).
 * @throws  Any error specified for read(3).
 * @throws  Any error specified for tcgetattr(3).
 * @throws  Any error specified for tcsetattr(3).
 * @throws  Any error specified for tcdrain(3).
 * 
 * @since  Always.
 */
char* getpass(const char*)
  __GCC_ONLY(__attribute__((__nonnull__, __warn_unused_result__)))
  __deprecated("'getpass' has been deprecated without any "
	       "replacement. You could use libpassphrase instead. :)");



#if defined(__PLAN9_SOURCE) || defined(__SLIBC_SOURCE)
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
ssize_t readn(int, void*, size_t);
#endif

#if defined(__SLIBC_SOURCE)
/**
 * Variant of `write` that will write until all given
 * data has been written. This function will block signals
 * so that it cannot throw `EINTR`, which could mean that
 * you do not know how much data has been successfully
 * written. Note however, it may fail for any other reason
 * resulting in the same problem.
 * 
 * This is a slibc extension.
 * 
 * @etymology  (Write) all `(n)byte` bytes!
 * 
 * @param  fd     The file descriptor whither the data shall be write.
 * @param  buf    The data to write.
 * @param  nbyte  The number of bytes to write.
 * 
 * @throws  Any error specified for write(3), except `EINTR`.
 * 
 * @since  Always.
 */
ssize_t writen(int, const void*, size_t);

/**
 * Variant of `pread` that will read until the request
 * amount of that has been read, or there is no more
 * data to read. This function will block signals so
 * that it cannot throw `EINTR`, which could mean that
 * read data is lost. Note however, it may fail for
 * any other reason resulting in lost data.
 * 
 * This is a slibc extension.
 * 
 * @etymology  Variant of `(pread)` that reads all `(n)byte` bytes!
 * 
 * @param  fd      The file descriptor whence the data shall be read.
 * @param  buf     The buffer whither the read data shall be stored.
 * @param  nbyte   The number of bytes to read.
 * @param  offset  Whence in the file the read begins.
 * 
 * @throws  Any error specified for pread(3), except `EINTR`.
 * 
 * @since  Always.
 */
ssize_t preadn(int, void*, size_t, off_t);

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
ssize_t pwriten(int, const void*, size_t);
#endif


#if defined(__SLIBC_SOURCE)
/**
 * Halt the process in definitely.
 * This function never returns.
 * 
 * This is a slibc extension.
 * 
 * @etymology  (Halt)!
 * 
 * @since  Always.
 */
__noreturn void halt(void);

/**
 * Halt and catch fire!
 * This function never returns.
 * 
 * This is a slibc extension.
 * 
 * @etymology  (H)alt and (c)atch (f)ire!
 * 
 * @since  Always.
 */
__noreturn void hcf(void);
#endif



#endif

/*
  TODO ssize_t writeatleast(int, const void*, size_t min, size_t max, size_t*);
  TODO ssize_t pwriteatleast(int, const void*, size_t min, size_t max, off_t, size_t*);
  TODO ssize_t readatleast(int, void**, size_t min, size_t max, size_t*);
  TODO ssize_t preadatleast(int, void**, size_t min, size_t max, off_t, size_t*);
  TODO int dup2atleast(int, int);
  TODO int dup3atleast(int, int, int);
  TODO for dup3 and dup3atleast, a flag to specify the the oldfd shall close
  TODO for dup3 and dup3atleast, a flag to specify the the oldfd shall be /dev/null
*/

