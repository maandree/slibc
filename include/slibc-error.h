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
#ifndef _SLIBC_ERROR_H
#define _SLIBC_ERROR_H
#include <slibc/version.h>
#include <slibc/features.h>
#ifndef __PORTABLE


#include <errno.h>



/**
 * Store the current line, so we know which line failed, when
 * `PRINT_CUSTOM_FAILURE`, `PRINT_FAILURE` or `slibc_perror`
 * is called. This expression will be evaluated.
 * 
 * Example usage:
 * ```
 * int my_function(void)
 * {
 *   size_t n;
 *   void* array;
 *   ...
 *   if (FAILABLE_CALL(array = malloc(n)) == NULL)
 *     goto fail;
 *   ...
 *   return 0;
 *   
 *  fail:
 *   PRINT_FAILURE(NULL);
 *   ...
 *   return errno = 0, -1;
 * }
 * ```
 * 
 * A more scalable example:
 * ```
 * #define fail_if (call_and_check)  \
 *   do { if (FAILABLE_CALL(call_and_check)) goto fail; } while (0)
 * // `try` or simply `t` may be even better.
 * 
 * #define fail_unless (call_and_check)  fail_if(!(call_and_check))
 * // `f` may be even better.
 * 
 * int my_function(void)
 * {
 *   size_t n;
 *   void* array;
 *   ...
 *   fail_if (!(array = malloc(n)));
 *   // or perhaps, fail_unless (array = malloc(n));
 *   ...
 *   return 0;
 *   
 *  fail:
 *   PRINT_FAILURE(NULL);
 *   ...
 *   return errno = 0, -1;
 * }
 * ```
 * 
 * This is a slibc extension.
 * 
 * @since  Always.
 */
#define FAILABLE_CALL(expression)  \
  ({ typeof(expression) __slibc_r = (expression); *__slibc_error_line() = __LINE__; __slibc_r; })

/**
 * Check whether an error occurred. If an error occurred,
 * stored the line, for `PRINT_CUSTOM_FAILURE`, `PRINT_FAILURE`
 * or `slibc_perror`, where the error occurred.
 * 
 * Example usage:
 * ```
 * int my_function(void)
 * {
 *   char* buf;
 *   size_t bufsize;
 *   ssize_t r;
 *   int fd;
 *   ...
 *   for (;;)
 *     {
 *       r = read(fd, buf, bufsize);
 *       if (FAILURE_CHECK(r < 0, 1))
 *         {
 *           if (errno != EINTR) // Possibly FAILURE_CHECK(errno != EINTR, 3) here instead.
 *             goto fail;
 *           continue;
 *         }
 *       ...
 *     }
 *   ...
 *   return 0;
 *   
 *  fail:
 *   PRINT_FAILURE(NULL);
 *   ...
 *   return errno = 0, -1;
 * }
 * ```
 * 
 * This is a slibc extension.
 * 
 * @param   condition  Should evaluate to non-zero on and only on error.
 * @param   offset     The number of lines above the current line
 *                     that was the line that failed, if `condition`
 *                     evaluates to non-zero.
 * @return             1 if `condition` evaluates to non-zero, 0 otherwise.
 * 
 * @since  Always.
 */
#define FAILURE_CHECK(condition, offset)  \
  ((condition) ? (*__slibc_error_line() = (__LINE__ - (offset)), 1) : 0)

/**
 * Print an error message describing the error, and where the error
 * happened. Optionally with detailed description of the action that
 * failed.
 * 
 * This function must be called in the same file and function as the
 * the expansion of `FAILABLE_CALL` or `FAILURE_CHECK`. It is recommended
 * that this is done all the way down the call-stack to `main'. This is
 * however problematic (although it is possible) if you do not want the
 * process to exit.
 * 
 * Example of recursion:
 * ```
 * static int b(void)
 * {
 *   if (FAILABLE_CALL(some_function()) < 0) goto fail;
 *   return 0; fail: PRINT_FAILURE(NULL); return -1;
 * }
 * static int a(void)
 * {
 *   if (FAILABLE_CALL(b()) < 0) goto fail;
 *   return 0; fail: PRINT_FAILURE(NULL); return -1;
 * }
 * int main(void)
 * {
 *   if (FAILABLE_CALL(a()) < 0) goto fail;
 *   return 0; fail: PRINT_FAILURE(NULL); return 1;
 * }
 * ```
 * 
 * This function will set `errno` to zero. If you have statements
 * after the call to this function that may modify `errno`, be sure
 * to set `errno` to zero before returning. A good way to do this
 * is to have the return statement look like `return errno = 0, -1`.
 * 
 * This is a slibc extension.
 * 
 * @param  ...  Formatting-string followed by formatting-arguments used
 *              to describe what action failed. If the first argument is
 *              `NULL`, this is not printed and only the location of the
 *              error and `errno` is used to describe the error.
 * 
 * @since  Always.
 */
#define PRINT_FAILURE(...)  \
  (PRINT_CUSTOM_FAILURE(errno, NULL, __VA_ARGS__))

/**
 * Variant of `PRINT_FAILURE` that allows another function than `strerror`
 * to be used to get a textual description of the error code.
 * (This function will not set `errno` to zero unless it is the first argument.)
 * 
 * Example: `PRINT_CUSTOM_FAILURE(r, gai_strerror(r), _("fail to connect to server: %s"), host)`
 * 
 * This is a slibc extension.
 * 
 * @param  error_code    The error code, must be a modifiable lvalue, as it will be
 *                       modified to zero to indicate that the error string has
 *                       already been printed. Thus, on the original error location
 *                       this value must not be zero.
 * @param  error_string  Textual representation of the error. If `errno` indicates
 *                       the error, this should usually be `strerror(errno)`.
 * @param  ...           Formatting-string followed by formatting-arguments used
 *                       to describe what action failed. If the first argument is
 *                       `NULL`, this is not printed and only the location of the
 *                       error and `error_string` is used to describe the error.
 * 
 * @since  Always.
 */
#define PRINT_CUSTOM_FAILURE(error_code, error_string, ...)  \
  (slibc_perror(NULL, __FILE__, *__slibc_error_line(), __func__, &(error_code), error_string, __VA_ARGS__))

/**
 * Helper function to keep track of the line of origin, in a
 * thread-safe manner, without requiring new revisions of C.
 * 
 * @since  Always.
 */
int* __slibc_error_line(void) __GCC_ONLY(__attribute__((__const__))); /* TODO not implemented */

/**
 * Print a description of an error, and where the error occurred.
 * This function is capable of printed the full call-stack.
 * 
 * It is not recommended to used this function directly.
 * Use the macros in <slibc-error.h> instead.
 * 
 * This is a slibc extension.
 * 
 * @etymology  (slibc)-enhancement of (`perror`).
 * 
 * @param  progname      The name of the program, `NULL` or empty to use `program_invocation_name`.
 * @param  filename      The source code file where the error occurred.
 * @param  linenum       The line in the source code where the error occurred.
 * @param  function      The function in the source code where the error occurred.
 * @param  error_code    Pointer the variable that stores the error code, will zeroed.
 * @param  error_string  Textual description of the error code, `NULL` if `strerror` should be used.
 *                       This parameter is unused if `error_code` is zero.
 * @param  format        Formatting-string for a description of the action that failed. `NULL` if
 *                       no description other than the location and `error_string` should be printed.
 * @param  ...           Formatting-arguments for `format`.
 * 
 * @since  Always.
 */
void slibc_perror(const char*, const char*, int, const char*, int*, const char*, const char*, ...)
  __GCC_ONLY(__attribute__((__nonnull__(2, 4), __format__(__slibc_printf__, 7, 8))));



#endif
#endif

