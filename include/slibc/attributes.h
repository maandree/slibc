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
#ifdef __noreturn
# undef __noreturn
#endif
#ifdef __GCC_ONLY
# undef __GCC_ONLY
#endif
#ifdef __SLIBC_ONLY
# undef __SLIBC_ONLY
#endif
#ifdef __deprecated
# undef __deprecated
#endif
#ifdef __warning
# undef __warning
#endif
#ifdef __slibc_warning
# undef __slibc_warning
#endif
#ifdef __bsd_posix_conflict
# undef __bsd_posix_conflict
#endif



/**
 * Specifies that a function never returns, that is,
 * the process exits before the function returns.
 */
#if !defined(__C11__) && defined(__GNUC__)
# define __noreturn  __attribute__((__noreturn__))
#elif defined(__C11__)
# define __noreturn  _Noreturn
#else
# define __noreturn  /* ignore */
#endif


/**
 * Macro used to exclude code unless GCC is used.
 */
#if defined(__GNUC__)
# define __GCC_ONLY(...)   __VA_ARGS__
#else
# define __GCC_ONLY(...)   /* ignore */
#endif


/**
 * Macro used to exclude code unless `_SLIBC_SOURCE` is set.
 */
#if defined(_SLIBC_SOURCE)
# define __SLIBC_ONLY(...)  __VA_ARGS__
#else
# define __SLIBC_ONLY(...)  /* ignore */
#endif


/**
 * Mark a function, variable or type as deprecated,
 * with a message that tells the user why the the
 * function is deprecated, or functions to use instead.
 */
#if !defined(_SLIBC_SUPPRESS_WARNINGS)
# define __deprecated(msg)  __GCC_ONLY(__attribute__((__deprecated__(msg))))
#else
# define __deprecated(msg)  /* ignore */
#endif


/**
 * Warn if a function, variable or type is used.
 */
#if !defined(_SLIBC_SUPPRESS_WARNINGS)
# define __warning(msg)        __GCC_ONLY(__attribute__((__warning__(msg))))
# define __slibc_warning(msg)  __SLIBC_ONLY(__warning(msg))
#else
# define __warning(msg)        /* ignore */
# define __slibc_warning(msg)  /* ignore */
#endif


/**
 * Functions that have a BSD-specification that is conficting
 * with the POSIX-specification shall have this attribute.
 */
#if defined(_BSD_SOURCE) && !defined(_POSIX_COMPATIBLE_SOURCE) && !defined(_BSD_COMPATIBLE_SOURCE)
# define __bsd_posix_conflict  \
  __warning("The BSD-version of this function is incompatible with the POSIX-version.")
#else
# define __bsd_posix_conflict  /* ignore*/
#endif



/**
 * Format for the `format` GCC function attribute,
 * for `*printf` functions.
 */
#ifdef slibc_printf
# undef slibc_printf
#endif
#if defined(__SLIB_SOURCE) && defined(__GNUC__)
# define __slibc_printf__  __gnu_printf__ /* TODO write GCC extension */
#elif defined(__GNU_SOURCE) && defined(__GNUC__)
# define __slibc_printf__  __gnu_printf__
#else
# define __slibc_printf__  __printf__
#endif

/**
 * Format for the `format` GCC function attribute,
 * for `*scanf` functions.
 */
#ifdef slibc_scanf
# undef slibc_scanf
#endif
#if defined(__SLIB_SOURCE) && defined(__GNUC__)
# define __slibc_scanf__  __gnu_scanf__ /* TODO write GCC extension */
#elif defined(__GNU_SOURCE) && defined(__GNUC__)
# define __slibc_scanf__  __gnu_scanf__
#else
# define __slibc_scanf__  __scanf__
#endif

/**
 * Format for the `format` GCC function attribute,
 * for `strftime`.
 */
#ifdef slibc_strftime
# undef slibc_strftime
#endif
#if defined(__SLIB_SOURCE) && defined(__GNUC__)
# define __slibc_strftime__  __gnu_strftime__ /* TODO write GCC extension */
#elif defined(__GNU_SOURCE) && defined(__GNUC__)
# define __slibc_strftime__  __gnu_strftime__
#else
# define __slibc_strftime__  __strftime__
#endif

/**
 * Format for the `format` GCC function attribute,
 * for `strfmon`.
 */
#ifdef slibc_strfmon
# undef slibc_strfmon
#endif
#if defined(__SLIB_SOURCE) && defined(__GNUC__)
# define __slibc_strfmon__  __strfmon__ /* TODO write GCC extension */
#elif defined(__GNU_SOURCE) && defined(__GNUC__)
# define __slibc_strfmon__  __strfmon__
#else
# define __slibc_strfmon__  __strfmon__
#endif

