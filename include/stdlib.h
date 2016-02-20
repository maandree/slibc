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
#ifndef _STDLIB_H
#define _STDLIB_H
#include <slibc/version.h>
#include <slibc/features.h>


#include <malloc.h>



#define __NEED_size_t
#define __NEED_wchar_t
#define __NEED_div_t
#define __NEED_ldiv_t
#define __NEED_lldiv_t

#include <bits/types.h>


/**
 * `NULL`'s canonical header is <stddef.h>.
 */
#ifndef NULL
# define NULL  ((void*)0)
#endif


/**
 * The value a process shall exit with upon
 * success completion.
 * 
 * @since  Always.
 */
#define EXIT_SUCCESS  0

/**
 * A standard value a process can exit with
 * if it terminates because of failure.
 * 
 * @since  Always.
 */
#define EXIT_FAILURE  1



/**
 * Perform an integer division and return
 * both the quotient and the remainder.
 * 
 * @param   numerator    The numerator.
 * @param   denominator  The denominator, must not be 0 lest
 *                       the process will be killed by SIGFPE.
 * @return               The quotient in `.quot`, and
 *                       the remainder in `.rem`.
 * 
 * @since  Always.
 */
div_t div(int, int)
  __GCC_ONLY(__attribute__((__const__)));

/**
 * Perform an integer division and return
 * both the quotient and the remainder.
 * 
 * @param   numerator    The numerator.
 * @param   denominator  The denominator, must not be 0 lest
 *                       the process will be killed by SIGFPE.
 * @return               The quotient in `.quot`, and
 *                       the remainder in `.rem`.
 * 
 * @since  Always.
 */
ldiv_t ldiv(long, long)
  __GCC_ONLY(__attribute__((__const__)));

/**
 * Perform an integer division and return
 * both the quotient and the remainder.
 * 
 * @param   numerator    The numerator.
 * @param   denominator  The denominator, must not be 0 lest
 *                       the process will be killed by SIGFPE.
 * @return               The quotient in `.quot`, and
 *                       the remainder in `.rem`.
 * 
 * @since  Always.
 */
lldiv_t lldiv(long long, long long)
  __GCC_ONLY(__attribute__((__const__)));


/**
 * Return the absolute value of an integer.
 * 
 * Be aware, if the value is `INT_MIN` and
 * `-INT_MAX != -INT_MIN`, the result will
 * overflow, and `INT_MIN` will (probably)
 * be returned.
 * 
 * @param   value  The integer.
 * @return         The absolute value of the integer.
 * 
 * @since  Always.
 */
int (abs)(int)
  __GCC_ONLY(__attribute__((__const__)));
#define abs(value)  ((int)value < 0 ? -(int)value : (int)value)

/**
 * Return the absolute value of an integer.
 * 
 * Be aware, if the value is `LONG_MIN` and
 * `-LONG_MAX != -LONG_MIN`, the result will
 * overflow, and `LONG_MIN` will (probably)
 * be returned.
 * 
 * @param   value  The integer.
 * @return         The absolute value of the integer.
 * 
 * @since  Always.
 */
long int (labs)(long int)
  __GCC_ONLY(__attribute__((__const__)));
#define labs(value)  ((long int)value < 0 ? -(long int)value : (long int)value)

/**
 * Return the absolute value of an integer.
 * 
 * Be aware, if the value is `LLONG_MIN` and
 * `-LLONG_MAX != -LLONG_MIN`, the result will
 * overflow, and `LLONG_MIN` will (probably)
 * be returned.
 * 
 * @param   value  The integer.
 * @return         The absolute value of the integer.
 * 
 * @since  Always.
 */
long long int (llabs)(long long int)
  __GCC_ONLY(__attribute__((__const__)));
#define llabs(value)  ((long long int)value < 0 ? -(long long int)value : (long long int)value)


#if !defined(__PORTABLE)
/**
 * Get the absolute path of a file.
 * It will remove all redundant slashes, all "./":s,
 * and all "../":s, but not resolve symbolic links.
 * 
 * This is a slibc extension.
 * 
 * @param   file  The file.
 * @param   ref   The directory the file's specified path is
 *                relative, `NULL` for the current working directory.
 * @return        The file's absolute pathname. Will end with a slash
 *                if `file` does. (Or if `ref` does but file is empty.)
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 * 
 * @since  Always.
 */
char* abspath(const char*, const char*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__(1), __malloc__)));

/**
 * Get the relative path of a file.
 * 
 * This is a slibc extension.
 * 
 * @param   file  The file.
 * @param   ref   The file the result shall be relative to,
 *                `NULL` for the current working directory.
 *                If and only if this path ends with a slash,
 *                (or if it is `NULL`,) it will be treated as
 *                a directory in which a symbolic link, with
 *                the result as it target, can be located to
 *                point to `file`.
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 * 
 * @since  Always.
 */
char* relpath(const char*, const char*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__(1), __malloc__)));
#endif


/**
 * Convert a string to a floating-point value,
 * without checking for errors.
 * 
 * The string may being with an arbitrary number
 * of whitespace characters. Convertion will end
 * when a character is encountered that is not a
 * decimal digit, and is not an absolutely leading
 * '-' or '+', or the first '.'.
 * 
 * @param   string  The string to convert.
 * @return          The number encoded by the string.
 * 
 * @since  Always.
 */
double atof(const char*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));

/**
 * Convert a string to an integer,
 * without checking for errors.
 * 
 * The string may being with an arbitrary number
 * of whitespace characters. Convertion will end
 * when a character is encountered that is not a
 * decimal digit, and is not an absolutely leading
 * '-' or '+'.
 * 
 * @param   string  The string to convert.
 * @return          The integer encoded by the string.
 * 
 * @since  Always.
 */
int atoi(const char*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));

/**
 * Convert a string to an integer,
 * without checking for errors.
 * 
 * The string may being with an arbitrary number
 * of whitespace characters. Convertion will end
 * when a character is encountered that is not a
 * decimal digit, and is not an absolutely leading
 * '-' or '+'.
 * 
 * @param   string  The string to convert.
 * @return          The integer encoded by the string.
 * 
 * @since  Always.
 */
long int atol(const char*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));

/**
 * Convert a string to an integer,
 * without checking for errors.
 * 
 * The string may being with an arbitrary number
 * of whitespace characters. Convertion will end
 * when a character is encountered that is not a
 * decimal digit, and is not an absolutely leading
 * '-' or '+'.
 * 
 * @param   string  The string to convert.
 * @return          The integer encoded by the string.
 * 
 * @since  Always.
 */
long long int atoll(const char*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));

#if !defined(__PORTABLE)
/**
 * This function is identical to `atoll`.
 * 
 * This is a Linux libc extension.
 * 
 * @since  Always.
 */
long long int atoq(const char*)
  __deprecated("'atoq' is obsolete and not portable, use 'atoll' instead.")
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));
#endif


#if defined(__SVID_SOURCE) || defined(__BSD_SOURCE)
/**
 * This function shall in some manner clear the environment.
 * 
 * To minimise the risk of fatal race conditions, this
 * implementation will set the first element in
 * `extern char** environ` to `NULL`, unless `environ`
 * itself is `NULL`. This also reduces that risk that
 * programs stop working when switching to slibc.
 * 
 * The exact behaviour of this function depeneds of the
 * implementations. Depending on the implementation,
 * this may or may not entail setting `environ` to `NULL`.
 * 
 * This function is a very common non-standard extension.
 * 
 * @etymology  (Clear) the (env)ironment!
 * 
 * @returns  This function is always successful, and will
 *           always return zero. However, according to the
 *           specifications, it shall return -1 on failure.
 * 
 * @since  Always.
 */
int clearenv(void)
  __warning("It may be better to use `if (environ) *environ = NULL;`.");
#endif

/**
 * This function returns the value assoicated with a
 * specified environment variable.
 * 
 * Portable program must not check `errno`. No errors
 * are defined by POSIX.
 * 
 * @etymology  (Get) the value of an (env)ironment variable!
 * 
 * @param   name  The name of the sought environment variable.
 *                Must not be `NULL`.
 * @return        The value of the environment variable.
 *                `NULL` on error, or if not found. This
 *                pointer is subpointer, and must not be
 *                modified except for in-place changes.
 * 
 * @throws  0       No such environment variable found.
 *                  This is a slibc extensions.
 * @throws  EINVAL  `name` is `NULL` (must not be the case), empty,
 *                  or contains a '='. This is a slibc extensions.
 * 
 * @since  Always.
 */
char* getenv(const char*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__)));


/**
 * Search for an item in a sorted list of comparable
 * elements. The list must be sorted in ascending order.
 * The function usually implements binary search,
 * as is done in this implementation.
 * 
 * @etymology  (B)inary (search).
 * 
 * @param   sought  The sought item.
 * @param   list    The beginning of the list to search.
 * @param   n       The number of elements in the list.
 * @param   width   The width, in bytes, of each element in the list.
 * @param   compar  A function that shall compare two items, and return
 *                  a value less than, equal to, or greater than zero
 *                  if the first argument is less than, equal to, or
 *                  greater than the second argument, respectively.
 * @return          The address of an arbritrart element in `list` that
 *                  is equal to `sought`, or `NULL` if no such element
 *                  can be found (does not exist, or because `list`
 *                  is not properly sorted.)
 * 
 * @since  Always.
 */
void* bsearch(const void*, const void*, size_t, size_t, int (*)(const void*, const void*))
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__(1, 5), __pure__)));
#ifdef __CONST_CORRECT
# define bsearch(...)  (__const_correct2(bsearch, __VA_ARGS__))
#endif



/* TODO implement rand-functions */
#define RAND_MAX  1
int rand(void);
int rand_r(unsigned int* seed);
void srand(unsigned int seed);



/* TODO implement exit-functions */
__noreturn void abort(void);
__noreturn void _Exit(int);
int atexit(void (*)(void));
int on_exit(void (*)(int, void*), void*);
__noreturn void exit(int);
int at_quick_exit (void (*) (void));
__noreturn void quick_exit(int);



#endif

