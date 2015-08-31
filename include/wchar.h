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
#ifndef _WCHAR_H
#define _WCHAR_H
#ifndef _PORTABLE_SOURCE /* `wchar_t` is not portable. */
#include <slibc/version.h>


#include <slibc/features.h>



#define __NEED_size_t
#define __NEED_wchar_t

#include <bits/types.h>


/**
 * `wchar_t` version of `strlen`.
 * 
 * @param   str  The string.
 * @return       The number of `wchar_t`:s before the
 *               first NUL character.
 */
size_t wcslen(const wchar_t*)
  __GCC_ONLY(__attribute__((nonnull, warn_unused_result)));

#if (defined(_POSIX_SOURCE) || defined(_POSIX_C_SOURCE) || \
     defined(_XOPEN_SOURCE) || defined(_GNU_SOURCE) || \
     defined(_BSD_SOURCE)) && !defined(_PORTABLE_SOURCE)
/**
 * `wchar_t` version of `strnlen`.
 * 
 * @param   str     The string.
 * @param   maxlen  The number of bytes to inspect, at most.
 * @return          The number of `wchar_t`:s before the
 *                  first NUL character. `maxlen` if no
 *                  NUL character was found.
 */
size_t wcsnlen(const wchar_t*, size_t)
  __GCC_ONLY(__attribute__((warn_unused_result)));
#endif



/**
 * Override a memory segment with a repeated wide character.
 * 
 * @param   segment  The beginning of the memory segment.
 * @param   c        The wide character.
 * @param   size     The number of wide characters in the memory segment.
 * @return           `segment` is returned.
 */
wchar_t* wmemset(wchar_t*, wchar_t, size_t);

/**
 * Copy a memory segment to another, non-overlapping, segment.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   size     The number of wide characters to copy.
 * @return           `whither` is returned.
 */
wchar_t* wmemcpy(wchar_t* restrict, const wchar_t* restrict, size_t);

#if defined(_GNU_SOURCE) && !defined(_PORTABLE_SOURCE)
/**
 * Copy a memory segment to another, non-overlapping, segment.
 * 
 * This is a GNU extension.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   size     The number of wide characters to copy.
 * @return           `whither + size` is returned.
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
 */
wchar_t* wmemmove(wchar_t*, const wchar_t*, size_t);

# if defined(_SLIBC_SOURCE)
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
 */
wchar_t* wmempmove(wchar_t*, const wchar_t*, size_t);
# endif
#endif

#if defined(_SLIBC_SOURCE) && !defined(_PORTABLE_SOURCE)
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
 *                   the possition of `c` translated to `whither`,
 *                   that is, the address of `whither` plus the
 *                   number of copied characters; the address of
 *                   one character passed the last written character.
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
 *                   the possition of `c` translated to `whither`,
 *                   that is, the address of `whither` plus the
 *                   number of copied characters; the address of
 *                   one character passed the last written character.
 */
wchar_t* wmemcmove(wchar_t*, const wchar_t*, wchar_t, size_t);
#endif

/**
 * Copy a memory segment to another, non-overlapping, segment,
 * stop when a NUL wide character is encountered.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @return           `whither` is returned.
 */
wchar_t* wcscpy(wchar_t* restrict, const wchar_t* restrict)
  __GCC_ONLY(__attribute__((returns_nonnull, nonnull)));

#if (defined(_SLIBC_SOURCE) || defined(_GNU_SOURCE)) && !defined(_PORTABLE_SOURCE)
/**
 * Copy a memory segment to another, non-overlapping, segment,
 * stop when a NUL wide character is encountered.
 * 
 * This is a GNU-compliant slibc extension.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @return           `whither + wcslen(whence)` is returned.
 */
wchar_t* wcpcpy(wchar_t* restrict, const wchar_t* restrict)
  __GCC_ONLY(__attribute__((returns_nonnull, nonnull)));
#endif

#if defined(_SLIBC_SOURCE) && !defined(_PORTABLE_SOURCE)
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
 */
wchar_t* wcsccpy(wchar_t* restrict, const wchar_t* restrict, wchat_t)
  __GCC_ONLY(__attribute__((nonnull)));

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
 */
wchar_t* wcswcscpy(wchar_t* restrict, const wchar_t* restrict, const wchar_t* restrict)
  __GCC_ONLY(__attribute__((nonnull(1, 2))));
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
 */
wchar_t* wcsncpy(wchar_t* restrict, const wchar_t* restrict, size_t)
  __GCC_ONLY(__attribute__((returns_nonnull, nonnull)));

#if defined(_GNU_SOURCE) && !defined(_PORTABLE_SOURCE)
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
 */
wchar_t* wcpncpy(wchar_t* restrict, const wchar_t* restrict, size_t)
  __GCC_ONLY(__attribute__((returns_nonnull, nonnull)));

# if defined(_SLIBC_SOURCE)
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
 */
wchar_t* wcscncpy(wchar_t* restrict, const wchar_t* restrict, wchat_t, size_t)
  __GCC_ONLY(__attribute__((nonnull)));

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
 */
wchar_t* wcswcsncpy(wchar_t* restrict, const wchar_t* restrict, const wchar_t* restrict, size_t)
  __GCC_ONLY(__attribute__((nonnull(1, 2))));
# endif
#endif

#if defined(_SLIBC_SOURCE) && !defined(_PORTABLE_SOURCE)
/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL wide character is encountered.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @return           `whither` is returned.
 */
wchar_t* wcsmove(wchar_t*, const wchar_t*)
  __GCC_ONLY(__attribute__((returns_nonnull, nonnull)));

/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL wide character is encountered.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @return           `whither + wcslen(whence)` is returned.
 */
wchar_t* wcpmove(wchar_t*, const wchar_t*)
  __GCC_ONLY(__attribute__((returns_nonnull, nonnull)));

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
 */
wchar_t* wcscmove(wchar_t*, const wchar_t*, wchat_t)
  __GCC_ONLY(__attribute__((nonnull)));

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
 */
wchar_t* wcswcsmove(wchar_t*, const wchar_t*, const wchar_t* restrict)
  __GCC_ONLY(__attribute__((nonnull(1, 2))));

/**
 * Copy a memory segment to another, possibly overlapping, segment,
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
 */
wchar_t* wcsnmove(wchar_t*, const wchar_t*, size_t)
  __GCC_ONLY(__attribute__((returns_nonnull, nonnull)));

# if defined(_GNU_SOURCE)
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
 */
wchar_t* wcpnmove(wchar_t*, const wchar_t*, size_t)
  __GCC_ONLY(__attribute__((returns_nonnull, nonnull)));

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
 */
wchar_t* wcscnmove(wchar_t*, const wchar_t*, wchat_t, size_t)
  __GCC_ONLY(__attribute__((nonnull)));

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
 */
wchar_t* wcswcsnmove(wchar_t*, const wchar_t*, const wchar_t* restrict, size_t)
  __GCC_ONLY(__attribute__((nonnull(1, 2))));
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
 */
wchar_t* wcscat(wchar_t* restrict whither, const wchar_t* restrict whence)
  __GCC_ONLY(__attribute__((nonnull)));

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
 */
wchar_t* wcsncat(wchar_t* restrict whither, const wchar_t* restrict whence, size_t maxlen)
  __GCC_ONLY(__attribute__((nonnull)));

/* wcpncat does not exsits because use of it would be very inefficient. */


#if !defined(_PORTABLE_SOURCE)
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
 */
wchar_t* wcsdup(const wchar_t*)
  __GCC_ONLY(__attribute__((malloc, nonnull, warn_unused_result)));

# if defined(_SLIBC_SOURCE)
#  if defined(_GNU_SOURCE)
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
 */
wchar_t* wcsndup(const wchar_t*, size_t)
  __GCC_ONLY(__attribute__((malloc, nonnull, warn_unused_result)));
#  endif

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
 */
wchar_t* wmemdup(const wchar_t*, size_t)
  __GCC_ONLY(__attribute__((malloc, nonnull, warn_unused_result)));

#  if defined(__GNUC__)
#   if defined(_GNU_SOURCE)
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
 */
#    define wcsdupa(string)					\
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
 */
#    define wstrndupa(string, maxlen)				\
  ({								\
    const char* __s = (string);					\
    size_t __n = wcsnlen(__s, (maxlen)) + 1;			\
    wchar_t* __r = __builtin_alloca(__n * sizeof(wchar_t));	\
    wmemcpy(__r, __s, __n);					\
  })
#   endif

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
 */
#   define wmemdupa(segment, size)				\
  ({								\
    size_t __n = (size);					\
    wchar_t* __r = __builtin_alloca(__n * sizeof(wchar_t));	\
    wmemcpy(__r, (segmetn), __n);				\
  })
#  endif
# endif
#endif



#endif
#endif

