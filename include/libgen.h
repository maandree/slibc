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
#ifndef _LIBGEN_H
#define _LIBGEN_H
#include <slibc/version.h>
#include <slibc/features.h>



/* Override GNU-specific `basename` from <string.h>. */
#ifdef basename
# undef basename
#endif


/**
 * Get the basename of a filename, remove
 * trailing slashes.
 * 
 * @etymology  File's (basename).
 * 
 * @param   filename  The filename, may be edited by this function.
 * @return            The basename, it is either a substring
 *                    of `filename` or, if `filename` is `NULL`
 *                    or is empty, a statically allocationed string,
 *                    so it must not freed or edited.
 * 
 * @since  Always.
 */
char* __xpg_basename(char*)
  __GCC_ONLY(__attribute__((__warn_unused_result__)));
#define basename  __xpg_basename

/**
 * Get the dirname of a filename.
 * 
 * @etymology  Parent (dir)ectory's path(name).
 * 
 * @param   filename  The filename, may be edited by this function.
 * @return            The dirname, it is either a substring
 *                    of `filename` or, if `filename` is `NULL`
 *                    or does no contain a non-trailing slash,
 *                    a statically allocationed string, so it
 *                    must not freed or edited.
 * 
 * @since  Always.
 */
char* dirname(char*)
  __GCC_ONLY(__attribute__((__warn_unused_result__)));

#if defined(__SLIBC_SOURCE)
/**
 * Removes all trailing slashes (that is not the first character
 * in the filename,) all '.' directory components, and when possible
 * using only lexical analysis, resolves '..' directory components.
 * 
 * '..' directory components that should resolve up beyond '/',
 * are removed. Note that this can in fact mean that the resulting
 * path is not the same file if the processes is `chroot`:ed.
 * Additionally, and more important, there is no consideration for
 * symbolic links. For example, '/a/b/c/..' resolves to '/a/b',
 * but if any of the directors are symbolic links, the real path
 * is not necessarily '/a/b'.
 * 
 * This is a slibc extension.
 * 
 * @etymology  (Clean) path(name).
 * 
 * @param   filename  The filename, may be edited by this function.
 * @return            The dirname, it is either `filename` or,
 *                    if `filename` is `NULL` or does no contain a
 *                    non-trailing slash, a statically allocationed
 *                    string, so it must not freed or edited.
 * 
 * @since  Always.
 */
char* cleanname(char*)
#endif



#endif

