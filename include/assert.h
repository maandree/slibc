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
#include <slibc/version.h>
#include <slibc/features.h>



/* The `assert` macro shall be redefined according to the the
 * current state of `NDEBUF` each time <assert.h> is included. */
#ifdef assert
# undef assert
#endif


/**
 * Unless `NDEBUG` is defined, print an error message
 * and abort the process, if the expression evaluates to
 * non-zero.
 * 
 * POSIX specifies that `assert` shall not evaluate the
 * expression if `NDEBUG` is defined. This is probably
 * to save CPU-cycles.
 * 
 * @etymology  (Assert)ion.
 * 
 * @since  Always.
 */
#ifdef NDEBUG
# define assert(expression)   ((void)0)
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
# define assert(expression)  \
  ((void)((expression) ? 0 : (__assert_fail(#expression, 0, __FILE__, __LINE__, __func__), 0)))
#else
# define assert(expression)  \
  ((void)((expression) ? 0 : (__assert_fail(#expression, 0, __FILE__, __LINE__, NULL), 0)))
#endif


#if defined(__SLIBC_SOURCE) || defined(__GNU_SOURCE)
/**
 * Unless `NDEBUG` is defined, print an error message
 * and abort the process, if `errnum` is non-zero.
 * 
 * `assert_perror` is a GNU-compliant slibc extension.
 * 
 * @etymology  (`assert`) version of (`perror`).
 * 
 * @param  errnum:int  The error code, describing the error that occurred.
 * 
 * @since  Always.
 */
# ifdef assert_perror
#  undef assert_perror
# endif
# if defined(NDEBUG)
#  define assert_perror(errnum)  ((void)0)
# elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
#  define assert_perror(errnum)  \
  ((void)((errnum == 0) ? 0 : (__assert_fail(NULL, errnum, __FILE__, __LINE__, __func__), 0)))
# else
#  define assert_perror(errnum)  \
  ((void)((errnum == 0) ? 0 : (__assert_fail(NULL, errnum, __FILE__, __LINE__, NULL), 0)))
# endif
#endif



/* The definitions above shall be redefined at any time this header file
 * is included. The definitions below are static, and thus guarded. */
#ifndef _ASSERT_H
#define _ASSERT_H



#if defined(__C11__)
/**
 * A compile-time error should occur if the expression
 * evaluates to zero.
 * 
 * @etymology  (Static) (assert)tion.
 * 
 * @param  expression:scalar    The expression to evaluate.
 * @param  message:const char*  The message to print on error.
 * 
 * @since  Always.
 */
# define static_assert _Static_assert
#endif


/**
 * The function that is called if an assertion fails.
 * 
 * @param  expression  The expression that failed, `NULL` if `assert_perror` failed.
 * @param  errnum      The code of the fatal error, 0 if `assert` failed.
 * @param  file        The filename of the source cose whence the assertion was made.
 * @param  line        The line in the source code whence the assertion was made.
 * @param  func        The function in the source code whence the assertion was made,
 *                     `NULL` if unknown (C99 is required.)
 * 
 * @since  Always.
 */
__noreturn void __assert_fail(const char*, int, const char*, int, const char*)
  __GCC_ONLY(__attribute__((__nonnull__(3, 5))));



#endif

