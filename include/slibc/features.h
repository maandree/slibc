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
#ifndef _SLIBC_FEATURES_H
#define _SLIBC_FEATURES_H


/* These definitions are only to be used in slibc header-files. */


#include "portability.h"
#include "c-version.h"
#include "attributes.h"



/**
 * Update existance of `__const_correct*` macros
 */
#ifdef __CONST_CORRECT
# undef __CONST_CORRECT
# undef __const_correct
# undef __const_correct2
# undef __const_correct2p
#endif


/**
 * Macro for any function with at least 2 arguments,
 * that shall return with `const` qualifier if and only
 * if the first argument is `const`-qualifier.
 * 
 * Other qualifiers could be dropped.
 * 
 * Usage example:
 * ```
 * char* strchr(const char*, int)
 * #ifdef __CONST_CORRECT
 * # define strchr(...)  __const_correct(strchr, __VA_ARGS__)
 * #endif
 * ```
 * 
 * @param   function  The name of the function.
 * @param   first     The first argument.
 * @param   ...       The rest of the arguments.
 * @return            The result casted to the same type as `first`.
 */
#if defined(__GNUC__) && defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
# define __CONST_CORRECT
# define __const_correct(function, first, ...) \
  (_Generic(&(first), \
            const wchar_t(*)[]: (const wchar_t*)function(first, __VA_ARGS__), \
            const char(*)[]:    (const char*)   function(first, __VA_ARGS__), \
            const void**:       (const void*)   function(first, __VA_ARGS__), \
            void**:                             function(first, __VA_ARGS__), \
            default:       (__typeof__(&*first))function(first, __VA_ARGS__)))
#elif defined(__GNUC__)
# define __CONST_CORRECT
# define __const_correct(function, first, ...) \
  ((__typeof__(&*first))function(first, __VA_ARGS__))
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
# define __CONST_CORRECT
# define __const_correct(function, first, ...) \
  (_Generic(&(first), \
            const wchar_t(*)[]: (const wchar_t*)function(first, __VA_ARGS__), \
            const char(*)[]:    (const char*)   function(first, __VA_ARGS__), \
            const wchar_t**:    (const wchar_t*)function(first, __VA_ARGS__), \
            const char**:       (const char*)   function(first, __VA_ARGS__), \
            const void**:       (const void*)   function(first, __VA_ARGS__), \
            default:                            function(first, __VA_ARGS__)))
#endif
/* Note, string literals are compiler-dependent. Does not work too well in GCC. */
/* Note, __VA_ARGS__ requires, C99, therefore we need __CONST_CORRECT, rather
 * than using a fall back. */


/**
 * Macro for any function with at least 3 arguments,
 * that shall return with `const` qualifier if and only
 * if the second argument is `const`-qualifier.
 * 
 * Other qualifiers could be dropped.
 * 
 * @param   function  The name of the function.
 * @param   first     The first argument.
 * @param   second    The second argument.
 * @param   ...       The rest of the arguments.
 * @return            The result casted to the same type as `second`.
 */
#if defined(__GNUC__) && defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
# define __CONST_CORRECT
# define __const_correct2(function, first, second, ...) \
  (_Generic(&(second), \
            const wchar_t(*)[]: (const wchar_t*)function(first, second, __VA_ARGS__), \
            const char(*)[]:    (const char*)   function(first, second, __VA_ARGS__), \
            const void**:       (const void*)   function(first, second, __VA_ARGS__), \
            void**:                             function(first, second, __VA_ARGS__), \
            default:       (__typeof__(&*first))function(first, second, __VA_ARGS__)))
#elif defined(__GNUC__)
# define __CONST_CORRECT
# define __const_correct2(function, first, second, ...) \
  ((__typeof__(&*second))function(first, second, __VA_ARGS__))
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
# define __CONST_CORRECT
# define __const_correct2(function, first, second, ...) \
  (_Generic(&(second), \
            const wchar_t(*)[]: (const wchar_t*)function(first, second, __VA_ARGS__), \
            const char(*)[]:    (const char*)   function(first, second, __VA_ARGS__), \
            const wchar_t**:    (const wchar_t*)function(first, second, __VA_ARGS__), \
            const char**:       (const char*)   function(first, second, __VA_ARGS__), \
            const void**:       (const void*)   function(first, second, __VA_ARGS__), \
            default:                            function(first, second, __VA_ARGS__)))
#endif


/**
 * Macro for any function with precisely 2 arguments,
 * that shall return with `const` qualifier if and only
 * if the second argument is `const`-qualifier.
 * 
 * Other qualifiers could be dropped.
 * 
 * @param   function  The name of the function.
 * @param   first     The first argument.
 * @param   second    The second argument.
 * @return            The result casted to the same type as `second`.
 */
#if defined(__GNUC__) && defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
# define __CONST_CORRECT
# define __const_correct2p(function, first, second) \
  (_Generic(&(second), \
            const wchar_t(*)[]: (const wchar_t*)function(first, second), \
            const char(*)[]:    (const char*)   function(first, second), \
            const void**:       (const void*)   function(first, second), \
            void**:                             function(first, second), \
            default:       (__typeof__(&*first))function(first, second)))
#elif defined(__GNUC__)
# define __CONST_CORRECT
# define __const_correct2p(function, first, second) \
  ((__typeof__(&*second))function(first, second))
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
# define __CONST_CORRECT
# define __const_correct2p(function, first, second) \
  (_Generic(&(second), \
            const wchar_t(*)[]: (const wchar_t*)function(first, second), \
            const char(*)[]:    (const char*)   function(first, second), \
            const wchar_t**:    (const wchar_t*)function(first, second), \
            const char**:       (const char*)   function(first, second), \
            const void**:       (const void*)   function(first, second), \
            default:                            function(first, second)))
#endif



/**
 * _BSD_SOURCE || _SVID_SOURCE || _GNU_SOURCE implies _POSIX_C_SOURCE = 2.
 */
#if defined(__BSD_SOURCE) || defined(__SVID_SOURCE) || defined(__GNU_SOURCE)
# if (__POSIX_C_SOURCE <= 1L)
#  undef __POSIX_C_SOURCE
# endif
# if !defined(__POSIX_C_SOURCE)
#  define __POSIX_C_SOURCE  2L
# endif
#endif

/**
 * _SVID_SOURCE implies _XOPEN_SOURCE.
 */
#if defined(__SVID_SOURCE) && !defined(__XOPEN_SOURCE)
# define __XOPEN_SOURCE  1L
#endif

/**
 * _GNU_SOURCE implies _XOPEN_SOURCE = 500.
 */
#if defined(__GNU_SOURCE)
# if __XOPEN_SOURCE <= 499L
#  undef __XOPEN_SOURCE
# endif
# if !defined(__XOPEN_SOURCE)
#  define __XOPEN_SOURCE  500L
# endif
#endif

/**
 * _XOPEN_SOURCE >= 500 implies _XOPEN_SOURCE_EXTENDED.
 */
#if (__XOPEN_SOURCE >= 500L) && !defined(__XOPEN_SOURCE_EXTENDED)
# define __XOPEN_SOURCE_EXTENDED  1L
#endif

/**
 * _XOPEN_SOURCE_EXTENDED implies _XOPEN_SOURCE.
 */
#if defined(__XOPEN_SOURCE_EXTENDED) && !defined(__XOPEN_SOURCE)
# define __XOPEN_SOURCE  1L
#endif

/**
 * _XOPEN_SOURCE implies _POSIX_C_SOURCE = 2.
 */
#if defined(__XOPEN_SOURCE)
# if __POSIX_C_SOURCE <= 1L
#  undef __POSIX_C_SOURCE
# endif
# if !defined(__POSIX_C_SOURCE)
#  define __POSIX_C_SOURCE  2L
# endif
#endif

/**
 * _POSIX_SOURCE is implied if _POSIX_C_SOURCE >= 1.
 */
#if !defined(__POSIX_SOURCE) && (__POSIX_C_SOURCE >= 1L)
# define __POSIX_SOURCE  1L
#endif
#if (__POSIX_C_SOURCE <= 0) && !defined(__POSIX_SOURCE)
# define __POSIX_C_SOURCE  1L
#endif

/**
 * _GNU_SOURCE implies _ISOC89_SOURCE.
 */
#if defined(__GNU_SOURCE) && !defined(__ISOC89_SOURCE)
# define __ISOC89_SOURCE
#endif

/**
 * _GNU_SOURCE implies _ISOC90_SOURCE.
 */
#if defined(__GNU_SOURCE) && !defined(__ISOC90_SOURCE)
# define __ISOC90_SOURCE
#endif

/**
 * _GNU_SOURCE implies _ISOC95_SOURCE.
 */
#if defined(__GNU_SOURCE) && !defined(__ISOC95_SOURCE)
# define __ISOC95_SOURCE
#endif

/**
 * _GNU_SOURCE implies _ISOC99_SOURCE.
 */
#if defined(__GNU_SOURCE) && !defined(__ISOC99_SOURCE)
# define __ISOC99_SOURCE
#endif

/**
 * _GNU_SOURCE implies _LARGEFILE_SOURCE.
 */
#if defined(__GNU_SOURCE) && !defined(__LARGEFILE_SOURCE)
# define __LARGEFILE_SOURCE  1L
#endif

/**
 * _GNU_SOURCE implies _LARGEFILE64_SOURCE.
 */
#if defined(__GNU_SOURCE) && !defined(__LARGEFILE64_SOURCE)
# define __LARGEFILE64_SOURCE  1L
#endif

/**
 * _GNU_SOURCE implies _ATFILE_SOURCE.
 */
#if defined(__GNU_SOURCE) && !defined(__ATFILE_SOURCE)
# define __ATFILE_SOURCE  1L
#endif


#endif

