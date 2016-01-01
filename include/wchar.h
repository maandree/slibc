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
#ifndef _WCHAR_H
#define _WCHAR_H
#include <slibc/version.h>
#include <slibc/features.h>
#ifndef __PORTABLE /* `wchar_t` is not portable. */



/**
 * `NULL`'s canonical header is <stddef.h>
 */
#ifndef NULL
# define NULL  ((void*)0)
#endif


#define __NEED_size_t
#define __NEED_wchar_t
#define __NEED_wint_t

#include <bits/types.h>


/**
 * End of a wide-character stream
 */
#ifndef WEOF
# if __WCHAR_BIT == __CHAR_BIT
#  define WEOF  -1
# elif __WCHAR_BIT == __SHORT_BIT
#  define WEOF  -1
# elif __WCHAR_BIT == __INT_BIT
#  define WEOF  -1
# elif __WCHAR_BIT == __LONG_BIT
#  define WEOF  -1L
# else
#  define WEOF  -1LL
# endif
#endif


/**
 * `wchar_t` version of `strlen`.
 * 
 * @param   str  The string.
 * @return       The number of `wchar_t`:s before the
 *               first NUL character.
 * 
 * @since  Always.
 */
size_t wcslen(const wchar_t*)
  __GCC_ONLY(__attribute__((__nonnull__, __warn_unused_result__, __pure__)));

/**
 * `wchar_t` version of `strnlen`.
 * 
 * @param   str     The string.
 * @param   maxlen  The number of bytes to inspect, at most.
 * @return          The number of `wchar_t`:s before the
 *                  first NUL character. `maxlen` if no
 *                  NUL character was found.
 * 
 * @since  Always.
 */
size_t wcsnlen(const wchar_t*, size_t)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __pure__)));



/**
 * Override a memory segment with a repeated wide character.
 * 
 * @param   segment  The beginning of the memory segment.
 * @param   c        The wide character.
 * @param   size     The number of wide characters in the memory segment.
 * @return           `segment` is returned.
 * 
 * @since  Always.
 */
wchar_t* wmemset(wchar_t*, wchar_t, size_t);

/**
 * Copy a memory segment to another, non-overlapping, segment.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   size     The number of wide characters to copy.
 * @return           `whither` is returned.
 * 
 * @since  Always.
 */
wchar_t* wmemcpy(wchar_t* restrict, const wchar_t* restrict, size_t);

#if defined(__GNU_SOURCE)
/**
 * Copy a memory segment to another, non-overlapping, segment.
 * 
 * This is a GNU extension.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   size     The number of wide characters to copy.
 * @return           `whither + size` is returned.
 * 
 * @since  Always.
 */
wchar_t* wmempcpy(wchar_t* restrict, const wchar_t* restrict, size_t);

/**
 * Copy a memory segment to another, possibly overlapping, segment.
 * 
 * This is a GNU extension.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   size     The number of wide characters to copy.
 * @return           `whither` is returned.
 * 
 * @since  Always.
 */
wchar_t* wmemmove(wchar_t*, const wchar_t*, size_t);

# if defined(__SLIBC_SOURCE)
/**
 * Copy a memory segment to another, possibly overlapping, segment.
 * 
 * This is a slibc extension added for completeness.
 * It is only available if GNU extensions are available.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   size     The number of wide characters to copy.
 * @return           `whither + size` is returned.
 * 
 * @since  Always.
 */
wchar_t* wmempmove(wchar_t*, const wchar_t*, size_t);
# endif
#endif

#if defined(__SLIBC_SOURCE)
/**
 * Copy a memory segment to another, non-overlapping, segment,
 * but stop if a specific character is encountered.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   c        The character to stop at if encountered.
 * @param   size     The maximum number of wide characters to copy.
 * @return           `NULL` if `c` was not encountered, otherwise
 *                   the position of `c` translated to `whither`,
 *                   that is, the address of `whither` plus the
 *                   number of copied characters; the address of
 *                   one character passed the last written character.
 * 
 * @since  Always.
 */
wchar_t* wmemccpy(wchar_t* restrict, const wchar_t* restrict, wchar_t, size_t);

/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * but stop if a specific character is encountered.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   c        The character to stop at if encountered.
 * @param   size     The maximum number of wide characters to copy.
 * @return           `NULL` if `c` was not encountered, otherwise
 *                   the position of `c` translated to `whither`,
 *                   that is, the address of `whither` plus the
 *                   number of copied characters; the address of
 *                   one character passed the last written character.
 * 
 * @since  Always.
 */
wchar_t* wmemcmove(wchar_t*, const wchar_t*, wchar_t, size_t);

/**
 * Override a NUL character-terminated memory segment
 * with a repeated wide character.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   str  The beginning of the memory segment.
 * @param   c    The wide character.
 * @return       `str` is returned.
 * 
 * @since  Always.
 */
wchar_t* wcsset(wchar_t*, wchar_t)
  __GCC_ONLY(__attribute__((__returns_nonnull__, __nonnull__)));
#endif

/**
 * Copy a memory segment to another, non-overlapping, segment,
 * stop when a NUL wide character is encountered.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @return           `whither` is returned.
 * 
 * @since  Always.
 */
wchar_t* wcscpy(wchar_t* restrict, const wchar_t* restrict)
  __GCC_ONLY(__attribute__((__returns_nonnull__, __nonnull__)));

#if defined(__SLIBC_SOURCE) || defined(__GNU_SOURCE)
/**
 * Copy a memory segment to another, non-overlapping, segment,
 * stop when a NUL wide character is encountered.
 * 
 * This is a GNU-compliant slibc extension.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @return           `whither + wcslen(whence)` is returned.
 * 
 * @since  Always.
 */
wchar_t* wcpcpy(wchar_t* restrict, const wchar_t* restrict)
  __GCC_ONLY(__attribute__((__returns_nonnull__, __nonnull__)));
#endif

#if defined(__SLIBC_SOURCE)
/**
 * Copy a memory segment to another, non-overlapping, segment,
 * stop when a NUL wide character or a specified wide character
 * is encountered.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   c        The stop character.
 * @return           `NULL` if `c` was not encountered, otherwise
 *                   the position of `c` translated to `whither`,
 *                   that is, the address of `whither` plus the
 *                   number of copied characters; the address of
 *                   one character passed the last written non-NUL
 *                   character.
 * 
 * @since  Always.
 */
wchar_t* wcsccpy(wchar_t* restrict, const wchar_t* restrict, wchar_t)
  __GCC_ONLY(__attribute__((__nonnull__)));

/**
 * Copy a memory segment to another, non-overlapping, segment,
 * stop when a NUL wide character or a specified substring is encountered.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   str      The substring, ignored if `NULL`.
 * @return           `NULL` if `str` was not encountered, otherwise
 *                   the position of `str` translated to `whither`,
 *                   that is, the address of `whither` plus the
 *                   number of copied characters; the address of
 *                   one character passed the last written non-NUL
 *                   character.
 * 
 * @since  Always.
 */
wchar_t* wcsstrcpy(wchar_t* restrict, const wchar_t* restrict, const wchar_t* restrict)
  __GCC_ONLY(__attribute__((__nonnull__(1, 2))));
#endif

/**
 * Copy a memory segment to another, non-overlapping, segment,
 * stop when a NUL wide character is encountered.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   maxlen   The maximum number of wide characters to copy.
 *                   NOTE that if the resulting string at least this
 *                   long, no NUL character will be written to `whither'.
 *                   On the otherhand, if the resultnig string is
 *                   shorter, `whither` will be filled with NUL characters
 *                   until this amount of characters have been written.
 * @return           `whither` is returned.
 * 
 * @since  Always.
 */
wchar_t* wcsncpy(wchar_t* restrict, const wchar_t* restrict, size_t)
  __GCC_ONLY(__attribute__((__returns_nonnull__, __nonnull__)));

#if defined(__GNU_SOURCE)
/**
 * Copy a memory segment to another, non-overlapping, segment,
 * stop when a NUL wide character is encountered.
 * 
 * This is a GNU extension.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   maxlen   The maximum number of wide characters to copy.
 *                   NOTE that if the resulting string at least this
 *                   long, no NUL character will be written to `whither'.
 *                   On the otherhand, if the resultnig string is
 *                   shorter, `whither` will be filled with NUL characters
 *                   until this amount of characters have been written.
 * @return           `whither` plus the number of written characters,
 *                   excluding NUL characters, is returned.
 * 
 * @since  Always.
 */
wchar_t* wcpncpy(wchar_t* restrict, const wchar_t* restrict, size_t)
  __GCC_ONLY(__attribute__((__returns_nonnull__, __nonnull__)));

# if defined(__SLIBC_SOURCE)
/**
 * Copy a memory segment to another, non-overlapping, segment,
 * stop when a NUL wide character or a specified wide character
 * is encountered.
 * 
 * This is a slibc extension added for completeness.
 * It is only available if GNU extensions are available.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   c        The stop character.
 * @param   maxlen   The maximum number of wide characters to copy.
 *                   NOTE that if the resulting string at least this
 *                   long, no NUL character will be written to `whither'.
 *                   On the otherhand, if the resultnig string is
 *                   shorter, `whither` will be filled with NUL characters
 *                   until this amount of characters have been written.
 * @return           `NULL` if `c` was not encountered, otherwise
 *                   the position of `c` translated to `whither`,
 *                   that is, the address of `whither` plus the
 *                   number of copied characters; the address of
 *                   one character passed the last written non-NUL
 *                   character.
 * 
 * @since  Always.
 */
wchar_t* wcscncpy(wchar_t* restrict, const wchar_t* restrict, wchar_t, size_t)
  __GCC_ONLY(__attribute__((__nonnull__)));

/**
 * Copy a memory segment to another, non-overlapping, segment,
 * stop when a NUL wide character or a specified substring is encountered.
 * 
 * This is a slibc extension added for completeness.
 * It is only available if GNU extensions are available.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   str      The substring, ignored if `NULL`.
 * @param   maxlen   The maximum number of wide characters to copy.
 *                   NOTE that if the resulting string at least this
 *                   long, no NUL character will be written to `whither'.
 *                   On the otherhand, if the resultnig string is
 *                   shorter, `whither` will be filled with NUL characters
 *                   until this amount of characters have been written.
 * @return           `NULL` if `str` was not encountered, otherwise
 *                   the position of `str` translated to `whither`,
 *                   that is, the address of `whither` plus the
 *                   number of copied chartacters; the address of
 *                   one character passed the last written non-NUL
 *                   character.
 * 
 * @since  Always.
 */
wchar_t* wcsstrncpy(wchar_t* restrict, const wchar_t* restrict, const wchar_t* restrict, size_t)
  __GCC_ONLY(__attribute__((__nonnull__(1, 2))));
# endif
#endif

#if defined(__SLIBC_SOURCE)
/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL wide character is encountered.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @return           `whither` is returned.
 * 
 * @since  Always.
 */
wchar_t* wcsmove(wchar_t*, const wchar_t*)
  __GCC_ONLY(__attribute__((__returns_nonnull__, __nonnull__)));

/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL wide character is encountered.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @return           `whither + wcslen(whence)` is returned.
 * 
 * @since  Always.
 */
wchar_t* wcpmove(wchar_t*, const wchar_t*)
  __GCC_ONLY(__attribute__((__returns_nonnull__, __nonnull__)));

/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL wide character or a specified wide character
 * is encountered.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   c        The stop character.
 * @return           `NULL` if `c` was not encountered, otherwise
 *                   the position of `c` translated to `whither`,
 *                   that is, the address of `whither` plus the
 *                   number of copied characters; the address of
 *                   one character passed the last written non-NUL
 *                   character.
 * 
 * @since  Always.
 */
wchar_t* wcscmove(wchar_t*, const wchar_t*, wchar_t)
  __GCC_ONLY(__attribute__((__nonnull__)));

/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL wide character or a specified substring is encountered.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   str      The substring, ignored if `NULL`.
 * @return           `NULL` if `str` was not encountered, otherwise
 *                   the position of `str` translated to `whither`,
 *                   that is, the address of `whither` plus the
 *                   number of copied characters; the address of
 *                   one character passed the last written non-NUL
 *                   character.
 * 
 * @since  Always.
 */
wchar_t* wcsstrmove(wchar_t*, const wchar_t*, const wchar_t* restrict)
  __GCC_ONLY(__attribute__((__nonnull__(1, 2))));

/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL wide character is encountered.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   maxlen   The maximum number of wide characters to copy.
 *                   NOTE that if the resulting string at least this
 *                   long, no NUL character will be written to `whither'.
 *                   On the otherhand, if the resultnig string is
 *                   shorter, `whither` will be filled with NUL characters
 *                   until this amount of characters have been written.
 * @return           `whither` is returned.
 * 
 * @since  Always.
 */
wchar_t* wcsnmove(wchar_t*, const wchar_t*, size_t)
  __GCC_ONLY(__attribute__((__returns_nonnull__, __nonnull__)));

# if defined(__GNU_SOURCE)
/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL wide character is encountered.
 * 
 * This is a slibc extension added for completeness.
 * It is only available if GNU extensions are available.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   maxlen   The maximum number of wide characters to copy.
 *                   NOTE that if the resulting string at least this
 *                   long, no NUL character will be written to `whither'.
 *                   On the otherhand, if the resultnig string is
 *                   shorter, `whither` will be filled with NUL characters
 *                   until this amount of characters have been written.
 * @return           `whither` plus the number of written characters,
 *                   excluding NUL characters, is returned.
 * 
 * @since  Always.
 */
wchar_t* wcpnmove(wchar_t*, const wchar_t*, size_t)
  __GCC_ONLY(__attribute__((__returns_nonnull__, __nonnull__)));

/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL wide character or a specified wide character
 * is encountered.
 * 
 * This is a slibc extension added for completeness.
 * It is only available if GNU extensions are available.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   c        The stop character.
 * @param   maxlen   The maximum number of wide characters to copy.
 *                   NOTE that if the resulting string at least this
 *                   long, no NUL character will be written to `whither'.
 *                   On the otherhand, if the resultnig string is
 *                   shorter, `whither` will be filled with NUL characters
 *                   until this amount of characters have been written.
 * @return           `NULL` if `c` was not encountered, otherwise
 *                   the position of `c` translated to `whither`,
 *                   that is, the address of `whither` plus the
 *                   number of copied characters; the address of
 *                   one character passed the last written non-NUL
 *                   character.
 * 
 * @since  Always.
 */
wchar_t* wcscnmove(wchar_t*, const wchar_t*, wchar_t, size_t)
  __GCC_ONLY(__attribute__((__nonnull__)));

/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL wide character or a specified substring is encountered.
 * 
 * This is a slibc extension added for completeness.
 * It is only available if GNU extensions are available.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   str      The substring, ignored if `NULL`.
 * @param   maxlen   The maximum number of wide characters to copy.
 *                   NOTE that if the resulting string at least this
 *                   long, no NUL character will be written to `whither'.
 *                   On the otherhand, if the resultnig string is
 *                   shorter, `whither` will be filled with NUL characters
 *                   until this amount of characters have been written.
 * @return           `NULL` if `str` was not encountered, otherwise
 *                   the position of `str` translated to `whither`,
 *                   that is, the address of `whither` plus the
 *                   number of copied chartacters; the address of
 *                   one character passed the last written non-NUL
 *                   character.
 * 
 * @since  Always.
 */
wchar_t* wcsstrnmove(wchar_t*, const wchar_t*, const wchar_t* restrict, size_t)
  __GCC_ONLY(__attribute__((__nonnull__(1, 2))));
# endif
#endif

/**
 * Concatenate a string to the end of another string.
 * The resulting strings must not overlap with the appended string.
 * 
 * The use of this function is often a bad idea.
 * 
 * @param   whither  The string to extend.
 * @param   whence   The string to append.
 * @return           `whither` is returned.
 * 
 * @since  Always.
 */
wchar_t* wcscat(wchar_t* restrict whither, const wchar_t* restrict whence)
  __GCC_ONLY(__attribute__((__nonnull__)));

/* wcpcat does not exsits because use of it would be very inefficient. */

/**
 * Concatenate a string to the end of another string.
 * The resulting strings must not overlap with the appended string.
 * 
 * The use of this function is often a really bad idea.
 * 
 * @param   whither  The string to extend.
 * @param   whence   The string to append.
 * @param   maxlen   The maximum number of wide characters to copy.
 *                   NOTE that if the resulting string at least this
 *                   long, no NUL character will be written to `whither'.
 *                   On the otherhand, if the resultnig string is
 *                   shorter, `whither` will be filled with NUL characters
 *                   until this amount of characters have been written.
 * @return           `whither` is returned.
 * 
 * @since  Always.
 */
wchar_t* wcsncat(wchar_t* restrict whither, const wchar_t* restrict whence, size_t maxlen)
  __GCC_ONLY(__attribute__((__nonnull__)));

/* wcpncat does not exsits because use of it would be very inefficient. */


#if defined(__SLIBC_SOURCE) || defined(__GNU_SOURCE)
/**
 * Duplicate a string.
 * 
 * This is a GNU-compliant slibc extension.
 * 
 * @param   string  The string to duplicate.
 * @return          The new string. `NULL` is returned on error
 *                  and `errno` is set to indicate the error.
 * 
 * @throws  ENOMEM  The process could not allocate sufficient amount of memory.
 * 
 * @since  Always.
 */
wchar_t* wcsdup(const wchar_t*)
  __GCC_ONLY(__attribute__((__malloc__, __nonnull__, __warn_unused_result__)));
#endif

#if defined(__SLIBC_SOURCE)
# if defined(__GNU_SOURCE)
/**
 * Duplicate a string.
 * 
 * This is a slibc extension added for completeness.
 * It is only available if GNU extensions are available.
 * 
 * @param   string  The string to duplicate.
 * @param   maxlen  Truncate the string to this length, if it is longer.
 *                  A NUL wide character is guaranteed to always be
 *                  written upon successful completion.
 * @return          The new string. `NULL` is returned on error
 *                  and `errno` is set to indicate the error.
 * 
 * @throws  ENOMEM  The process could not allocate sufficient amount of memory.
 * 
 * @since  Always.
 */
wchar_t* wcsndup(const wchar_t*, size_t)
  __GCC_ONLY(__attribute__((__malloc__, __nonnull__, __warn_unused_result__)));
# endif

/**
 * Duplicate a memory segment.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   segment  The memory segment to duplicate.
 * @param   size     The size of the memory segment.
 * @return           The new segment. `NULL` is returned on error
 *                   and `errno` is set to indicate the error.
 * 
 * @throws  ENOMEM  The process could not allocate sufficient amount of memory.
 * 
 * @since  Always.
 */
wchar_t* wmemdup(const wchar_t*, size_t)
  __GCC_ONLY(__attribute__((__malloc__, __nonnull__, __warn_unused_result__)));

# if defined(__GNUC__)
#  if defined(__GNU_SOURCE)
/**
 * Duplicate a string, using dymanic stack allocation (`alloca`).
 * 
 * This is a slibc extension added for completeness.
 * It is only available if GNU extensions are available.
 * This macro is only available when using GCC.
 * 
 * @param   string:const wchar_t*  The string to duplicate.
 * @return  :size_t                The new string. There is no way to
 *                                 detect whether the allocation failed.
 * 
 * @since  Always.
 */
#   define wcsdupa(string)					\
  ({								\
    const char* __s = (string);					\
    size_t __n = wcslen(__s) + 1;				\
    wchar_t* __r = __builtin_alloca(__n * sizeof(char));	\
    wmemcpy(__r, __s, __n);					\
  })

/**
 * Duplicate a string, using dymanic stack allocation (`alloca`).
 * 
 * This is a slibc extension added for completeness.
 * It is only available if GNU extensions are available.
 * This macro is only available when using GCC.
 * 
 * @param   string:const wchar_t*  The string to duplicate.
 * @param   maxlen:size_t          Truncate the string to this length, if it is longer.
 *                                 A NUL byte is guaranteed to always be written.
 * @return  :size_t                The new string. There is no way to
 *                                 detect whether the allocation failed.
 * 
 * @since  Always.
 */
#   define wstrndupa(string, maxlen)				\
  ({								\
    const char* __s = (string);					\
    size_t __n = wcsnlen(__s, (maxlen)) + 1;			\
    wchar_t* __r = __builtin_alloca(__n * sizeof(wchar_t));	\
    wmemcpy(__r, __s, __n);					\
  })
#  endif

/**
 * Duplicate a memory segment, using dymanic stack allocation (`alloca`).
 * 
 * This is a slibc extension added for completeness.
 * This macro is only available when using GCC.
 * 
 * @param   segment:const wchar_t*  The memory segment to duplicate.
 * @param   size:size_t             The size of the memory segment.
 * @return  :size_t                 The new segment. There is no way to
 *                                  detect whether the allocation failed.
 * 
 * @since  Always.
 */
#  define wmemdupa(segment, size)				\
  ({								\
    size_t __n = (size);					\
    wchar_t* __r = __builtin_alloca(__n * sizeof(wchar_t));	\
    wmemcpy(__r, (segmetn), __n);				\
  })
# endif
#endif



/**
 * Compare two memory segments alphabetically in a case sensitive manner.
 * 
 * @param   a     A negative value is returned if this is the lesser.
 * @param   b     A positive value is returned if this is the lesser.
 * @param   size  The size of the segments.
 * @return        Zero is returned if `a` and `b` are equal, otherwise,
 *                see the specifications for `a` and `b`.
 * 
 * @since  Always.
 */
int wmemcmp(const wchar_t*, const wchar_t*, size_t)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __pure__)));

#if defined(__SLIBC_SOURCE)
/**
 * Compare two memory segments alphabetically in a case insensitive manner.
 * 
 * This is a slibc extension added because it was useful
 * in implementing slibc itself.
 * 
 * @param   a     A negative value is returned if this is the lesser.
 * @param   b     A positive value is returned if this is the lesser.
 * @param   size  The size of the segments.
 * @return        Zero is returned if `a` and `b` are equal, otherwise,
 *                see the specifications for `a` and `b`.
 * 
 * @since  Always.
 */
int wmemcasecmp(const wchar_t*, const wchar_t*, size_t)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __pure__)));
#endif

/**
 * Compare two strings alphabetically in a case sensitive manner.
 * 
 * @param   a  A negative value is returned if this is the lesser.
 * @param   b  A positive value is returned if this is the lesser.
 * @return     Zero is returned if `a` and `b` are equal, otherwise,
 *             see the specifications for `a` and `b`.
 * 
 * @since  Always.
 */
int wcscmp(const wchar_t*, const wchar_t*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));

#if defined(__GNU_SOURCE) || defined(__SLIBC_SOURCE)
/**
 * Compare two strings alphabetically in a case insensitive manner.
 * Be aware, only ASCII characters are case insensitive, non-ASCII
 * characters are case sensitive.
 * 
 * This is a GNU-compliant slibc extension.
 * 
 * @param   a  A negative value is returned if this is the lesser.
 * @param   b  A positive value is returned if this is the lesser.
 * @return     Zero is returned if `a` and `b` are equal, otherwise,
 *             see the specifications for `a` and `b`.
 * 
 * @since  Always.
 */
int wcscasecmp(const wchar_t*, const wchar_t*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));

/**
 * Compare two strings alphabetically in a case sensitive manner.
 * 
 * This is a GNU-compliant slibc extension.
 * 
 * @param   a       A negative value is returned if this is the lesser.
 * @param   b       A positive value is returned if this is the lesser.
 * @param   length  The maximum number of characters to compare.
 * @return          Zero is returned if `a` and `b` are equal, otherwise,
 *                  see the specifications for `a` and `b`.
 * 
 * @since  Always.
 */
int wcsncmp(const wchar_t*, const wchar_t*, size_t)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));

/**
 * Compare two strings alphabetically in a case insensitive manner.
 * Be aware, only ASCII characters are case insensitive, non-ASCII
 * characters are case sensitive.
 * 
 * This is a GNU-compliant slibc extension.
 * 
 * @param   a       A negative value is returned if this is the lesser.
 * @param   b       A positive value is returned if this is the lesser.
 * @param   length  The maximum number of characters to compare.
 * @return          Zero is returned if `a` and `b` are equal, otherwise,
 *                  see the specifications for `a` and `b`.
 * 
 * @since  Always.
 */
int wcsncasecmp(const wchar_t*, const wchar_t*, size_t)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));
#endif


/**
 * Find the first occurrence of a wide character
 * in a memory segment.
 * 
 * @param   segment  The memory segment to search.
 * @param   c        The sought after character.
 * @param   size     The size of the memory segment.
 * @return           Pointer to the first occurrence of `c`,
 *                   `NULL` if none were found.
 * 
 * @since  Always.
 */
wchar_t* wmemchr(const wchar_t*, wchar_t, size_t)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __pure__)));
#ifdef __CONST_CORRECT
# define wmemchr(...)  (__const_correct(wmemchr, __VA_ARGS__))
#endif

#if defined(__SLIBC_SOURCE)
/**
 * Find the first occurrence of a wide character in a
 * memory segment. The memory segment must be known to
 * contain the sought after character.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   segment  The memory segment to search.
 * @param   c        The sought after character.
 * @return           Pointer to the first occurrence of `c`.
 * 
 * @since  Always.
 */
wchar_t* rawwmemchr(const wchar_t*, wchar_t)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __returns_nonnull__, __nonnull__, __pure__)));
#ifdef __CONST_CORRECT
# define rawwmemchr(...)  (__const_correct(rawwmemchr, __VA_ARGS__))
#endif

/**
 * Find the last occurrence of a wide character in
 * a memory segment.
 * 
 * For improved performace, use this function instead
 * of `wcssrchr` if you already know the length of the
 * string.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   segment  The memory segment to search.
 * @param   c        The sought after character.
 * @param   size     The size of the memory segment.
 * @return           Pointer to the last occurrence of `c`,
 *                   `NULL` if none were found.
 * 
 * @since  Always.
 */
wchar_t* wmemrchr(const wchar_t*, wchar_t, size_t)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __pure__)));
# ifdef __CONST_CORRECT
#  define wmemrchr(...)  (__const_correct(wmemrchr, __VA_ARGS__))
# endif
#endif

/**
 * Find the first occurrence of a wide character in a string.
 * 
 * @param   string  The string to search.
 *                  The terminating NUL character is
 *                  considered a part of the string.
 * @param   c       The sought after character.
 * @return          Pointer to the first occurrence of `c`,
 *                  `NULL` if none were found.
 * 
 * @since  Always.
 */
wchar_t* wcschr(const wchar_t*, wchar_t)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));
#ifdef __CONST_CORRECT
# define wcschr(...)  (__const_correct(wcschr, __VA_ARGS__))
#endif

#if defined(__GNU_SOURCE)
/**
 * Find the first occurrence of a wide character in a
 * string, or if there is no such character, the end of
 * the string.
 * 
 * This is a GNU-compliant slibc extension.
 * 
 * @param   string  The string to search.
 *                  The terminating NUL character is
 *                  considered a part of the string.
 * @param   c       The sought after character.
 * @return          Pointer to the first occurrence of `c`,
 *                  Pointer to the terminating NUL character
 *                  if none were found.
 * 
 * @since  Always.
 */
wchar_t* wcschrnul(const wchar_t*, wchar_t)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __returns_nonnull__, __nonnull__, __pure__)));
# ifdef __CONST_CORRECT
#  define wcschrnul(...)  (__const_correct(wcschrnul, __VA_ARGS__))
# endif
#endif

/**
 * Find the last occurrence of a wide character in a string.
 * 
 * For improved performace, use `wmemrchr` instead of
 * this function if you already know the length of the
 * string.
 * 
 * @param   string  The string to search.
 *                  The terminating NUL character is
 *                  considered a part of the string.
 * @param   c       The sought after character.
 * @return          Pointer to the last occurrence of `c`,
 *                  `NULL` if none were found.
 * 
 * @since  Always.
 */
wchar_t* wcsrchr(const wchar_t*, wchar_t)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));
#ifdef __CONST_CORRECT
# define wcsrchr(...)  (__const_correct(wcsrchr, __VA_ARGS__))
#endif


/**
 * This function is identical to `wcsstr`.
 * 
 * @since  Always.
 */
wchar_t* wcswcs(const wchar_t*, const wchar_t*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)))
  __deprecated("Use 'wcsstr' instead.");
#ifdef __CONST_CORRECT
# define wcswcs(...)  (__const_correct(wcswcs, __VA_ARGS__))
#endif

/**
 * Finds the first occurrence of a substring.
 * This search is case sensitive.
 * 
 * @param   haystack  The string to search.
 * @param   needle    The sought after substring.
 * @return            Pointer to the first occurrence of the
 *                    substring, `NULL` if not found.
 * 
 * @since  Always.
 */
wchar_t* wcsstr(const wchar_t*, const wchar_t*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));
#ifdef __CONST_CORRECT
# define wcsstr(...)  (__const_correct(wcsstr, __VA_ARGS__))
#endif

#if defined(__SLIBC_SOURCE)
/**
 * Finds the first occurrence of a substring.
 * This search is case insensitive.
 * 
 * This is a slibc extension.
 * 
 * @param   haystack  The string to search.
 * @param   needle    The sought after substring.
 * @return            Pointer to the first occurrence of the
 *                    substring, `NULL` if not found.
 * 
 * @since  Always.
 */
wchar_t* wcscasestr(const wchar_t*, const wchar_t*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));
# ifdef __CONST_CORRECT
#  define wcscasestr(...)  (__const_correct(wcscasestr, __VA_ARGS__))
# endif

/**
 * Finds the first occurrence of a substring.
 * This search is case sensitive.
 * 
 * This is a slibc extension added for because it was useful
 * in implementing slibc itself.
 * 
 * @param   haystack  The string to search.
 * @param   needle    The sought after substring.
 * @param   maxlen    The maximum number of character to search.
 * @return            Pointer to the first occurrence of the
 *                    substring, `NULL` if not found.
 * 
 * @since  Always.
 */
wchar_t* wcsnstr(const wchar_t*, const wchar_t*, size_t)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));
# ifdef __CONST_CORRECT
#  define wcsnstr(...)  (__const_correct(wcsnstr, __VA_ARGS__))
# endif

/**
 * Finds the first occurrence of a substring.
 * This search is case insensitive.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   haystack  The string to search.
 * @param   needle    The sought after substring.
 * @param   maxlen    The maximum number of character to search.
 * @return            Pointer to the first occurrence of the
 *                    substring, `NULL` if not found.
 * 
 * @since  Always.
 */
wchar_t* wcsncasestr(const wchar_t*, const wchar_t*, size_t)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));
# ifdef __CONST_CORRECT
#  define wcsncasestr(...)  (__const_correct(wcsncasestr, __VA_ARGS__))
# endif

/**
 * Finds the first occurrence of a substring.
 * This search is case sensitive.
 * It must already be known that such a substring exists.
 * 
 * This is a slibc extension.
 * 
 * @param   haystack  The string to search.
 * @param   needle    The sought after substring.
 * @return            Pointer to the first occurrence of the substring.
 * 
 * @since  Always.
 */
wchar_t* rawwcsstr(const wchar_t*, const wchar_t*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __returns_nonnull__, __pure__)));
# ifdef __CONST_CORRECT
#  define rawwcsstr(...)  (__const_correct(rawwcsstr, __VA_ARGS__))
# endif

/**
 * Finds the first occurrence of a substring.
 * This search is case insensitive.
 * It must already be known that such a substring exists.
 * 
 * This is a slibc extension.
 * 
 * @param   haystack  The string to search.
 * @param   needle    The sought after substring.
 * @return            Pointer to the first occurrence of the substring.
 * 
 * @since  Always.
 */
wchar_t* rawwcscasestr(const wchar_t*, const wchar_t*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __returns_nonnull__, __pure__)));
# ifdef __CONST_CORRECT
#  define rawwcscasestr(...)  (__const_correct(rawwcscasestr, __VA_ARGS__))
# endif

/**
 * Finds the first occurrence of a substring.
 * This search is case insensitive.
 * 
 * This is a slibc extension added because it was useful
 * in implementing slibc itself.
 * 
 * @param   haystack         The string to search.
 * @param   haystack_length  The number of character to search.
 * @param   needle           The sought after substring.
 * @param   needle_length    The length of `needle`.
 * @return                   Pointer to the first occurrence of
 *                           the substring, `NULL` if not found.
 * 
 * @since  Always.
 */
wchar_t* wmemcasemem(const wchar_t*, size_t, const wchar_t*, size_t)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __pure__)));
# ifdef __CONST_CORRECT
#  define wmemcasemem(...)  (__const_correct(wmemcasemem, __VA_ARGS__))
# endif

/**
 * Check whether a string starts with a specific string.
 * This check is case sensitive.
 * 
 * This is a slibc extension.
 * 
 * @param   string   The string to inspect.
 * @param   desired  The desired beginning of the string.
 * @return           `string` if `string` begins with
 *                   `desired`, `NULL` otherwise.
 * 
 * @since  Always.
 */
wchar_t* wcsstarts(const wchar_t*, const wchar_t*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));
# ifdef __CONST_CORRECT
#  define wcsstarts(...)  (__const_correct(wcsstarts, __VA_ARGS__))
# endif

/**
 * Check whether a string ends with a specific string.
 * This check is case sensitive.
 * 
 * This is a slibc extension.
 * 
 * @param   string   The string to inspect.
 * @param   desired  The desired ending of the string.
 * @return           The `string`, where `desired` beings if
 *                   `string` ends with `desired`, `NULL` otherwise.
 * 
 * @since  Always.
 */
wchar_t* wcsends(const wchar_t*, const wchar_t*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));
# ifdef __CONST_CORRECT
#  define wcsends(...)  (__const_correct(wcsends, __VA_ARGS__))
# endif

/**
 * Check whether a string starts with a specific string.
 * This check is case insensitive.
 * 
 * This is a slibc extension.
 * 
 * @param   string   The string to inspect.
 * @param   desired  The desired beginning of the string.
 * @return           `string` if `string` begins with
 *                   `desired`, `NULL` otherwise.
 * 
 * @since  Always.
 */
wchar_t* wcscasestarts(const wchar_t*, const wchar_t*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));
# ifdef __CONST_CORRECT
#  define wcscasestarts(...)  (__const_correct(wcscasestarts, __VA_ARGS__))
# endif

/**
 * Check whether a string ends with a specific string.
 * This check is case insensitive.
 * 
 * This is a slibc extension.
 * 
 * @param   string   The string to inspect.
 * @param   desired  The desired ending of the string.
 * @return           The `string`, where `desired` beings if
 *                   `string` ends with `desired`, `NULL` otherwise.
 * 
 * @since  Always.
 */
wchar_t* wcscaseends(const wchar_t*, const wchar_t*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));
# ifdef __CONST_CORRECT
#  define wcscaseends(...)  (__const_correct(wcscaseends, __VA_ARGS__))
# endif
#endif

#if defined(__GNU_SOURCE) || defined(__SLIBC_SOURCE)
/**
 * Finds the first occurrence of a substring.
 * This search is case sensitive.
 * 
 * This is a slibc extension added for completeness,
 * and because it was it was useful in implementing
 * slibc itself.
 * 
 * @param   haystack         The string to search.
 * @param   haystack_length  The number of character to search.
 * @param   needle           The sought after substring.
 * @param   needle_length    The length of `needle`.
 * @return                   Pointer to the first occurrence of
 *                           the substring, `NULL` if not found.
 * 
 * @since  Always.
 */
wchar_t* wmemmem(const wchar_t*, size_t, const wchar_t*, size_t)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __pure__)));
# ifdef __CONST_CORRECT
#  define wmemmem(...)  (__const_correct(wmemmem, __VA_ARGS__))
# endif
#endif


/* TODO Add case right-to-left substring searching functions. */


/**
 * Returns length of the initial substring
 * that consists entirely of a set of specified
 * wide characters.
 * 
 * @param   string   The string.
 * @param   skipset  Characters allowed in the substring.
 * @return           The length of the substring.
 * 
 * @since  Always.
 */
size_t wcsspn(const wchar_t*, const wchar_t*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));

/**
 * Returns length of the initial substring
 * that consists entirely of the complement
 * of a set of specified wide characters.
 * 
 * @param   string   The string.
 * @param   stopset  Characters disallowed in the substring.
 * @return           The length of the substring.
 * 
 * @since  Always.
 */
size_t wcscspn(const wchar_t*, const wchar_t*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));

/**
 * This function works like `strcspn`,
 * except it returns the pointer to the
 * location of the first found non-matching
 * wide character.
 * 
 * @param   string   The string.
 * @param   stopset  Bytes disallowed in the substring.
 * @return           A pointer to the first occurrence in
 *                   `string` of a character found in `stopset`.
 *                   `NULL` is returned if none is found.
 * 
 * @since  Always.
 */
wchar_t* wcspbrk(const wchar_t*, const wchar_t*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));
#ifdef __CONST_CORRECT
# define wcspbrk(...)  (__const_correct(wcspbrk, __VA_ARGS__))
#endif


/**
 * Tokenise a string.
 * 
 * @param   string      The string to tokenise on the first,
 *                      `NULL` on subsequent calls.
 *                      All characters found in `delimiters` will
 *                      be overriden with NUL characters.
 * @param   delimiters  Delimiting characters.
 * @param   state       Pointer to a `char*` that the function
 *                      can use to keep track of its state.
 *                      It is reasonable to make it point to `NULL`
 *                      on the first call.
 * @return              The next non-empty string that does not
 *                      contain a byte from `delimiters`. The
 *                      returned string will be as long as possible.
 *                      `NULL` is returned the search as reached
 *                      the end of the string, and there therefore
 *                      are no more tokens.
 * 
 * @since  Always.
 */
wchar_t* wcstok(wchar_t* restrict, const wchar_t* restrict, wchar_t** restrict)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__(2, 3))));

#if defined(__SLIBC_SOURCE)
/**
 * Tokenise a string.
 * 
 * This is a slibc extension.
 * 
 * @param   string      Pointer to the string to tokenise on the first call,
 *                      will be updated to keep track of the state.
 *                      All characters found in `delimiters` will
 *                      be overriden with NUL characters.
 * @param   delimiters  Delimiting characters.
 * @return              The next, possibly empty, string that does
 *                      not contain a byte from `delimiters`. The
 *                      returned string will be as long as possible.
 *                      `NULL` is returned the search as reached
 *                      the end of the string, and there therefore
 *                      are no more tokens.
 * 
 * @since  Always.
 */
wchar_t* wcssep(wchar_t** restrict, const wchar_t* restrict)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__)));
#endif



#endif
#endif

