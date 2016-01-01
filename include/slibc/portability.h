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
/* This file should be included from and only from <slibc/features.h>. */
/* These definitions are only to be used in slibc header-files. */


/* Clear old definitions. */
#ifdef __PORTABLE
# undef __PORTABLE
#endif
#ifdef __ISOC89_SOURCE
# undef __ISOC89_SOURCE
#endif
#ifdef __ISOC90_SOURCE
# undef __ISOC90_SOURCE
#endif
#ifdef __ISOC95_SOURCE
# undef __ISOC95_SOURCE
#endif
#ifdef __ISOC99_SOURCE
# undef __ISOC99_SOURCE
#endif
#ifdef __ISOC11_SOURCE
# undef __ISOC11_SOURCE
#endif
#ifdef __POSIX_SOURCE
# undef __POSIX_SOURCE
#endif
#ifdef __POSIX_C_SOURCE
# undef __POSIX_C_SOURCE
#endif
#ifdef __SVID_SOURCE
# undef __SVID_SOURCE
#endif
#ifdef __XOPEN_SOURCE
# undef __XOPEN_SOURCE
#endif
#ifdef __XOPEN_SOURCE_EXTENDED
# undef __XOPEN_SOURCE_EXTENDED
#endif
#ifdef __SUS_SOURCE
# undef __SUS_SOURCE
#endif
#ifdef __PLAN9_SOURCE
# undef __PLAN9_SOURCE
#endif
#ifdef __GNU_SOURCE
# undef __GNU_SOURCE
#endif
#ifdef __DEFAULT_SOURCE
# undef __DEFAULT_SOURCE
#endif
#ifdef __ATFILE_SOURCE
# undef __ATFILE_SOURCE
#endif
#ifdef __LARGEFILE_SOURCE
# undef __LARGEFILE_SOURCE
#endif
#ifdef __LARGEFILE64_SOURCE
# undef __LARGEFILE64_SOURCE
#endif
#ifdef __FILE_OFFSET_BITS
# undef __FILE_OFFSET_BITS
#endif
#ifdef __REENTRANT
# undef __REENTRANT
#endif




/**
 * Macro that is defined if portability shall be ensured.
 */
#if defined(_PORTABLE_SOURCE) || defined(_LIBRARY_HEADER)
# define __PORTABLE
#endif

/**
 * Internal feature-test macros that also check
 * that `_PORTABLE_SOURCE` and `_LIBRARY_HEADER`
 * is not defined.
 */
#if !defined(__PORTABLE)
# if defined(_PLAN9_SOURCE)
#  define __PLAN9_SOURCE  _PLAN9_SOURCE
# endif
# if defined(_GNU_SOURCE)
#  define __GNU_SOURCE  _GNU_SOURCE
# endif
# if defined(_SLIBC_SOURCE)
#  define __SLIBC_SOURCE  _SLIBC_SOURCE
# endif
# if defined(_BSD_SOURCE)
#  define __BSD_SOURCE  _BSD_SOURCE
# endif
# if defined(_XOPEN_SOURCE)
#  define __XOPEN_SOURCE  (_XOPEN_SOURCE - 0L)
# endif
# if defined(_XOPEN_SOURCE_EXTENDED)
#  define __XOPEN_SOURCE_EXTENDED  _XOPEN_SOURCE_EXTENDED
# endif
# if defined(_ISOC11_SOURCE)
#  define __ISOC11_SOURCE  _ISOC11_SOURCE
# endif
# if defined(_ATFILE_SOURCE)
#  define __ATFILE_SOURCE  _ATFILE_SOURCE
# endif
# if defined(_DEFAULT_SOURCE)
#  define __DEFAULT_SOURCE  _DEFAULT_SOURCE
# endif
# if defined(_LARGEFILE_SOURCE)
#  define __LARGEFILE_SOURCE  _LARGEFILE_SOURCE
# endif
# if defined(_LARGEFILE64_SOURCE)
#  define __LARGEFILE64_SOURCE  _LARGEFILE64_SOURCE
# endif
# if defined(_FILE_OFFSET_BITS)
#  define __FILE_OFFSET_BITS  _FILE_OFFSET_BITS
# endif
# if defined(_REENTRANT) || defined(_THREADSAFE)
#  define __REENTRANT  1L
# endif
#endif

/**
 * Internal feature-test macros that also check that
 * not check `_PORTABLE_SOURCE` or `_LIBRARY_HEADER`.
 */
#if defined(_POSIX_SOURCE)
# define __POSIX_SOURCE  _POSIX_SOURCE
#endif
#if defined(_POSIX_C_SOURCE)
# define __POSIX_C_SOURCE  _POSIX_C_SOURCE
#endif
#if defined(_ISOC89_SOURCE)
# define __ISOC89_SOURCE  _ISOC89_SOURCE
#endif
#if defined(_ISOC90_SOURCE)
# define __ISOC90_SOURCE  _ISOC90_SOURCE
#endif
#if defined(_ISOC95_SOURCE)
# define __ISOC95_SOURCE  _ISOC95_SOURCE
#endif
#if defined(_ISOC11_SOURCE)
# define __ISOC99_SOURCE  _ISOC99_SOURCE
#endif


/**
 * _POSIX_C_SOURCE has no effect if it is
 * zero, set it to zero if it is undefined.
 */
#if !defined(__POSIX_C_SOURCE)
# define __POSIX_C_SOURCE  0L
#endif

/**
 * Add __SUS_SOURCE as an alias for
 * __XOPEN_SOURCE >= 500, to simplify
 * feature tests
 */
#if defined(__XOPEN_SOURCE) && (__XOPEN_SOURCE >= 500)
# define __SUS_SOURCE  1L
#endif


/**
 * _BSD_COMPATIBLE_SOURCE requires _BSD_SOURCE.
 */
#if defined(_BSD_COMPATIBLE_SOURCE) && !defined(_BSD_SOURCE)
# if !defined(_SLIBC_SUPPRESS_WARNINGS)
#  warning "_BSD_COMPATIBLE_SOURCE is defined, but _BSD_SOURCE is undefined."
# endif
#endif

/**
 * _BSD_COMPATIBLE_SOURCE and _POSIX_COMPATIBLE_SOURCE
 * are incompatible.
 */
#if defined(_BSD_COMPATIBLE_SOURCE) && defined(_POSIX_COMPATIBLE_SOURCE)
# if !defined(_SLIBC_SUPPRESS_WARNINGS)
#  warning "You should not define both _BSD_COMPATIBLE_SOURCE and _POSIX_COMPATIBLE_SOURCE."
# endif
#endif

