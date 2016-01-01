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
#ifndef _ERR_H
#define _ERR_H
#include <slibc/version.h>
#include <slibc/features.h>

#ifndef _SLIBC_SUPPRESS_WARNINGS
# warning "Please consider not using <err.h>."
#endif


#define __NEED_va_list
#include <bits/types.h>



#if defined(__BSD_SOURCE)
/**
 * Print a warning to stderr, followed by a description
 * of the value of `errno`.
 * 
 * This is a non-standard BSD extension.
 * 
 * @etymology  Print (warn)ing!
 * 
 * @param  format  Formatting-string for the warning.
 * @param  ...     Formatting-arguments.
 * 
 * @since  Always.
 */
void warn(const char*, ...)
  __GCC_ONLY(__attribute__((__format__(__slibc_printf__, 1, 2))));

/**
 * Print a warning to stderr, followed by a description
 * of the value of `errno`.
 * 
 * This is a non-standard BSD extension.
 * 
 * @etymology  (V)ariadic version of (`warn`).
 * 
 * @param  format  Formatting-string for the warning.
 * @param  args    Formatting-arguments.
 * 
 * @since  Always.
 */
void vwarn(const char*, va_list);

/**
 * Print a warning to stderr, but do not print a
 * description of the value of `errno`.
 * 
 * This is a non-standard BSD extension.
 * 
 * @etymology  (`warn`), [x=](lesser variant).
 * 
 * @param  format  Formatting-string for the warning.
 * @param  ...     Formatting-arguments.
 * 
 * @since  Always.
 */
void warnx(const char*, ...)
  __GCC_ONLY(__attribute__((__format__(__slibc_printf__, 1, 2))));

/**
 * Print a warning to stderr, but do not print a
 * description of the value of `errno`.
 * 
 * This is a non-standard BSD extension.
 * 
 * @etymology  (V)ariadic version of (`warnx`).
 * 
 * @param  format  Formatting-string for the warning.
 * @param  args    Formatting-arguments.
 * 
 * @since  Always.
 */
void vwarnx(const char*, va_list);

/**
 * Print an error message to stderr, followed by a
 * description of the value of `errno`. Then exit the process.
 * 
 * This is a non-standard BSD extension.
 * 
 * @etymology  Report (err)or!
 * 
 * @param  status  The exit status the process should have.
 * @param  format  Formatting-string for the warning.
 * @param  ...     Formatting-arguments.
 * 
 * @since  Always.
 */
__noreturn void err(int, const char*, ...)
  __GCC_ONLY(__attribute__((__format__(__slibc_printf__, 2, 3))));

/**
 * Print an error message to stderr, followed by a
 * description of the value of `errno`. Then exit the process.
 * 
 * This is a non-standard BSD extension.
 * 
 * @etymology  (V)ariadic version of (`err`).
 * 
 * @param  status  The exit status the process should have.
 * @param  format  Formatting-string for the warning.
 * @param  args    Formatting-arguments.
 * 
 * @since  Always.
 */
__noreturn void verr(int, const char*, va_list);

/**
 * Print an error message to stderr, but do not print a
 * description of the value of `errno`. Then exit the process.
 * 
 * This is a non-standard BSD extension.
 * 
 * @etymology  (`err`), [x=](lesser variant).
 * 
 * @param  status  The exit status the process should have.
 * @param  format  Formatting-string for the warning.
 * @param  ...     Formatting-arguments.
 * 
 * @since  Always.
 */
__noreturn void errx(int, const char*, ...)
  __GCC_ONLY(__attribute__((__format__(__slibc_printf__, 2, 3))));

/**
 * Print an error message to stderr, but do not print a
 * description of the value of `errno`. Then exit the process.
 * 
 * This is a non-standard BSD extension.
 * 
 * @etymology  (V)ariadic version of (`errx`).
 * 
 * @param  status  The exit status the process should have.
 * @param  format  Formatting-string for the warning.
 * @param  args    Formatting-arguments.
 * 
 * @since  Always.
 */
__noreturn void verrx(int, const char*, va_list);
#endif



#endif

