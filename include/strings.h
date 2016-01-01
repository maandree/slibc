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
#ifndef _STRINGS_H
#define _STRINGS_H
#include <slibc/version.h>
#include <slibc/features.h>



#define __NEED_size_t
#define __NEED_locale_t
#include <bits/types.h>



/**
 * Override a memory segment with zeroes.
 * 
 * @etymology  (B)ytes: (zero) out.
 * 
 * @param  segment  The memory segment to override.
 * @param  size     The size of the memory segment.
 * 
 * @since  Always.
 */
void bzero(void*, size_t)
  __deprecated("Use 'memset', 'explicit_bzero' or 'secure_free' instead.");

#if defined(__SLIBC_SOURCE) || defined(__BSD_SOURCE)
/**
 * Override a memory segment with zeroes.
 * 
 * Unlike `bzero` and `memset`, calls to this function
 * cannot be removed, as an optimisation, by the compiler.
 * 
 * @etymology  (Explicit) version of (`bzero`).
 * 
 * @param  segment  The memory segment to override.
 * @param  size     The size of the memory segment.
 * 
 * @since  Always.
 */
void explicit_bzero(void*, size_t);
#endif

/**
 * Copy a memory segment to another, possibly overlapping, segment.
 * 
 * @etymology  (B)ytes: (copy).
 * 
 * @param  whence   The source memory segment.
 * @param  whither  The destination memory segment.
 * @param  size     The number of bytes to copy.
 * 
 * @since  Always.
 */
void bcopy(const void*, void*, size_t)
  __deprecated("Use 'memmove', or similar function, instead, but be aware of reordered parameters.");

/**
 * This function is identical to `memcmp`.
 * 
 * @etymology  (B)ytes: (c)o(mp)are.
 * 
 * @since  Always.
 */
int bcmp(const void*, const void*, size_t)
  __deprecated("Use 'memcmp' instead.")
  __GCC_ONLY(__attribute__((__warn_unused_result__, __pure__)));


/**
 * Compare two strings alphabetically in a case insensitive manner.
 * Be aware, only ASCII characters are case insensitive, non-ASCII
 * characters are case sensitive.
 * 
 * @etymology  (Str)ing-function: (case) insensitive (c)o(mp)arison.
 * 
 * @param   a  A negative value is returned if this is the lesser.
 * @param   b  A positive value is returned if this is the lesser.
 * @return     Zero is returned if `a` and `b` are equal, otherwise,
 *             see the specifications for `a` and `b`.
 * 
 * @since  Always.
 */
int strcasecmp(const char*, const char*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));

/**
 * Compare two strings alphabetically in a case insensitive manner.
 * Be aware, only ASCII characters are case insensitive, non-ASCII
 * characters are case sensitive.
 * 
 * @etymology  (Str)ing-function: (n)-bytes, (case) insensitive (c)o(mp)arison.
 * 
 * @param   a       A negative value is returned if this is the lesser.
 * @param   b       A positive value is returned if this is the lesser.
 * @param   length  The maximum number of characters to compare.
 * @return          Zero is returned if `a` and `b` are equal, otherwise,
 *                  see the specifications for `a` and `b`.
 * 
 * @since  Always.
 */
int strncasecmp(const char*, const char*, size_t)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));


/**
 * Compare two strings alphabetically in a case insensitive manner.
 * Be aware, only ASCII characters are case insensitive, non-ASCII
 * characters are case sensitive.
 * 
 * @etymology  (`strcasecmp`) variant with (l)ocale-consideration.
 * 
 * @param   a       A negative value is returned if this is the lesser.
 * @param   b       A positive value is returned if this is the lesser.
 * @param   locale  The locale.
 * @return          Zero is returned if `a` and `b` are equal, otherwise,
 *                  see the specifications for `a` and `b`.
 * 
 * @since  Always.
 */
int strcasecmp_l(const char*, const char*, locale_t) /* TODO */
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));

/**
 * Compare two strings alphabetically in a case insensitive manner.
 * Be aware, only ASCII characters are case insensitive, non-ASCII
 * characters are case sensitive.
 * 
 * @etymology  (`strncasecmp`) variant with (l)ocale-consideration.
 * 
 * @param   a       A negative value is returned if this is the lesser.
 * @param   b       A positive value is returned if this is the lesser.
 * @param   length  The maximum number of characters to compare.
 * @param   locale  The locale.
 * @return          Zero is returned if `a` and `b` are equal, otherwise,
 *                  see the specifications for `a` and `b`.
 * 
 * @since  Always.
 */
int strncasecmp_l(const char*, const char*, size_t, locale_t) /* TODO */
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));


/**
 * This function is identical to `strchr`.
 * 
 * This is a deprecated BSD extension.
 * 
 * @etymology  (Index) of character.
 * 
 * @since  Always.
 */
char* index(const char*, int)
  __deprecated("Use 'strchr' instead.")
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));
#ifdef __CONST_CORRECT
# define index(...)  (__const_correct(index, __VA_ARGS__))
#endif

/**
 * This function is identical to `strrchr`.
 * 
 * This is a deprecated BSD extension.
 * 
 * @etymology  (R)ight-most (index) of character.
 * 
 * @since  Always.
 */
char* rindex(const char*, int)
  __deprecated("Use 'strrchr' instead.")
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));
#ifdef __CONST_CORRECT
# define rindex(...)  (__const_correct(rindex, __VA_ARGS__))
#endif


/**
 * Find the first set bit in an integer.
 * 
 * @etymology  (F)ind (f)irst (s)et bit on `int`.
 * 
 * @param   i  The integer.
 * @return     The value of the least significant set bit, zero if none.
 * 
 * @since  Always.
 */
int ffs(int)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __const__)));

/**
 * Find the first set bit in an integer.
 * 
 * @etymology  (F)ind (f)irst (s)et bit on `(l)ong int`.
 * 
 * @param   i  The integer.
 * @return     The value of the least significant set bit, zero if none.
 * 
 * @since  Always.
 */
int ffsl(long)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __const__)));

/**
 * Find the first set bit in an integer.
 * 
 * @etymology  (F)ind (f)irst (s)et bit on `(l)ong (l)ong int`.
 * 
 * @param   i  The integer.
 * @return     The value of the least significant set bit, zero if none.
 * 
 * @since  Always.
 */
int ffsll(long long)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __const__)));



#endif

