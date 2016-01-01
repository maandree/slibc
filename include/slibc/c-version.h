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


/**
 * Is C11, or newer, used?
 */
#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)) || defined(__ISOC11_SOURCE)
# if !defined(__C11__)
#  define __C11__
# endif
# if !defined(__ISOC11_SOURCE)
#  define __ISOC11_SOURCE
# endif
#endif

/**
 * Is C99, or newer, used?
 */
#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || defined(__ISOC99_SOURCE) || defined(__C11__)
# if !defined(__C99__)
#  define __C99__
# endif
# if !defined(__ISOC99_SOURCE)
#  define __ISOC99_SOURCE
# endif
#endif

/**
 * Is C95, or newer, used?
 */
#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199409L)) || defined(__ISOC95_SOURCE) || defined(__C99__)
# if !defined(__C95__)
#  define __C95__
# endif
# if !defined(__ISOC95_SOURCE)
#  define __ISOC95_SOURCE
# endif
#endif

/**
 * Is C90, or newer, used?
 */
#if defined(__STDC_VERSION__) || defined(__STDC__) || defined(__C95__) || defined(__ISOC90_SOURCE)
# if !defined(__C90__)
#  define __C90__
# endif
# if !defined(__ISOC90_SOURCE)
#  define __ISOC90_SOURCE
# endif
#endif

/**
 * Is C89, or newer, used?
 */
#if defined(__C90__) || defined(__ISOC89_SOURCE)
# if !defined(__C89__)
#  define __C89__
# endif
# if !defined(__ISOC89_SOURCE)
#  define __ISOC89_SOURCE
# endif
#endif

/**
 * C89, C90, ANSI C and Standard C are all the
 * same standard.
 */
#if defined(__C89__) && !defined(__C90__)
# define __C90__
#endif
#if defined(__C90__) && !defined(__C89__)
# define __C89__
#endif
#if defined(__ISOC89_SOURCE) && !defined(__ISOC90_SOURCE)
# define __ISOC90_SOURCE
#endif
#if defined(__ISOC90_SOURCE) && !defined(__ISOC89_SOURCE)
# define __ISOC89_SOURCE
#endif

