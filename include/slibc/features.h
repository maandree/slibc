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
#ifndef _SLIBC_FEATURES_H
#define _SLIBC_FEATURES_H


/* These definitions are only to be used in slibc header-files. */


#include "portability.h"
#include "c-version.h"
#include "attributes.h"



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

