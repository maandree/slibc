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
#ifndef _STRING_H
#define _STRING_H
#include <slibc/version.h>
#include <slibc/features.h>


#if defined(__BSD_SOURCE) || defined(__GNU_SOURCE)
# include <strings.h>
#endif



/**
 * `NULL`'s canonical header is <stddef.h>
 */
#ifndef NULL
# define NULL  ((void*)0)
#endif


#define __NEED_size_t
#define __NEED_locale_t
#include <bits/types.h>



#if defined(__C89__) || (_POSIX_C_SOURCE >= 200112L)
/**
 * Return a textual representation of an error code.
 * This error code must from `errno`.
 * 
 * This implementation of `strerror` cannot fail. however
 * POSIX specifies that it can fail, any may only set `errno`
 * if it does fail. You should therefore, set `errno` to
 * zero before calling this function, and inspect `errno`
 * when it returns, as there is no reserved return value
 * that indicates and error.
 * 
 * The returned value must not be modified or freed.
 * 
 * As a slibc-specific modification, this function is MT-Safe.
 * 
 * @param   errnum  The error code.
 * @return          A description of the error.
 * 
 * @since  Always.
 */
char* strerror(int)
  __GCC_ONLY(__attribute__((__returns_nonnull__, __warn_unused_result__)));
#endif

#if _POSIX_C_SOURCE >= 200809L
/**
 * Return a textual representation of an error code.
 * This error code must from `errno`.
 * 
 * POSIX specifies `errno` may only be set on failure,
 * and reserves no return value to indicate such.
 * You should therefore, set `errno` to zero before calling
 * this function, and inspect `errno` when it returns.
 * 
 * The returned value must not be modified or freed.
 * 
 * @param   errnum  The error code.
 * @param   locale  The locale, must be a valid locale and not
 *                  `LC_GLOBAL_LOCALE`, lest the behaviour is undefined.
 * @return          A description of the error.
 * 
 * @since  Always.
 */
char* strerror_l(int, locale_t)
  __GCC_ONLY(__attribute__((__warn_unused_result__))); /* TODO attributes */
#endif


#if !defined(__PORTABLE)
/**
 * Reenterant variant of `strerror`.
 * 
 * This is an XSI-compliant extension. However the name
 * is not part of the XSI specification, `strerror_r`
 * should be used. It is defined to this function if
 * `(_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600) && !_GNU_SOURCE`.
 * However it is not defined if _SLIBC_SOURCE is defined.
 * 
 * @param   errnum  The error code.
 * @param   buf     Buffer where the description shall be stored.
 * @param   buflen  The allocation size of `buf`.
 * @return          Zero on success, value for `errno` on error
 * 
 * @throws  ERANGE  `buf` was too small to store the description.
 * 
 * @since  Always.
 */
int __xsi_strerror_r(int, char*, size_t); /* XSI-compliant strerror_r */

/**
 * Reenterant variant of `strerror`.
 * 
 * This is a GNU-specific extension. However the name
 * is not part of the GNU specification, `strerror_r` should
 * be used. It is defined to this function unless
 * `(_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600) && !_GNU_SOURCE`.
 * However it is not defined if _SLIBC_SOURCE is defined.
 * 
 * @param   errnum  The error code.
 * @param   buf     Buffer where the description shall be stored.
 * @param   buflen  The allocation size of `buf`.
 * @return          `buf` on success, `NULL` on error. On error, `errno`
 *                  is set to indicate the error.
 * 
 * @throws  ERANGE  `buf` was too small to store the description.
 * 
 * @since  Always.
 */
char* __gnu_strerror_r(int, char*, size_t); /* GNU-specific strerror_r */

# if (_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600) && !defined(_GNU_SOURCE)
#  define strerror_r  __xsi_strerror_r
# else
#  define strerror_r  __gnu_strerror_r
# endif
#endif



/**
 * Returns the number of bytes in a NUL-terminated
 * string. This excludes the NUL byte.
 * 
 * @param   str  The string.
 * @return       The number of bytes before the first NUL byte.
 * 
 * @since  Always.
 */
size_t strlen(const char*)
  __GCC_ONLY(__attribute__((__nonnull__, __warn_unused_result__, __pure__)));

#if defined(__POSIX_SOURCE) || defined(__POSIX_C_SOURCE) || \
    defined(__XOPEN_SOURCE) || defined(__GNU_SOURCE) || \
    defined(__BSD_SOURCE)
/**
 * Variant of `strlen` that only inspects the
 * beginning of a string.
 * 
 * @param   str     The string.
 * @param   maxlen  The number of bytes to inspect, at most.
 * @return          The number of bytes before, the first NUL byte.
 *                  `maxlen` if no NUL byte was found.
 * 
 * @since  Always.
 */
size_t strnlen(const char*, size_t)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __pure__)));
#endif



/**
 * Override a memory segment with a repeated character.
 * 
 * @param   segment  The beginning of the memory segment.
 * @param   c        The character (8 bits wide.)
 * @param   size     The size of the memory segment.
 * @return           `segment` is returned.
 * 
 * @since  Always.
 */
void* memset(void*, int, size_t);

/**
 * Copy a memory segment to another, non-overlapping, segment.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   size     The number of bytes to copy.
 * @return           `whither` is returned.
 * 
 * @since  Always.
 */
void* memcpy(void* restrict, const void* restrict, size_t);

#if defined(__GNU_SOURCE)
/**
 * Copy a memory segment to another, non-overlapping, segment.
 * 
 * This is a GNU extension.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   size     The number of bytes to copy.
 * @return           `whither + size` is returned.
 * 
 * @since  Always.
 */
void* mempcpy(void* restrict, const void* restrict, size_t);
#endif

/**
 * Copy a memory segment to another, possibly overlapping, segment.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   size     The number of bytes to copy.
 * @return           `whither` is returned.
 * 
 * @since  Always.
 */
void* memmove(void*, const void*, size_t);

#if defined(__SLIBC_SOURCE) && defined(__GNU_SOURCE)
/**
 * Copy a memory segment to another, possibly overlapping, segment.
 * 
 * This is a slibc extension added for completeness.
 * It is only available if GNU extensions are available.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   size     The number of bytes to copy.
 * @return           `whither + size` is returned.
 * 
 * @since  Always.
 */
void* mempmove(void*, const void*, size_t);
#endif

/**
 * Copy a memory segment to another, non-overlapping, segment,
 * but stop if a specific byte is encountered.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   c        The byte to stop at if encountered.
 * @param   size     The maximum number of bytes to copy.
 * @return           `NULL` if `c` was not encountered, otherwise
 *                   the position of `c` translated to `whither`,
 *                   that is, the address of `whither` plus the
 *                   number of copied characters; the address of
 *                   one character passed the last written character.
 * 
 * @since  Always.
 */
void* memccpy(void* restrict, const void* restrict, int, size_t);

#if defined(__SLIBC_SOURCE)
/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * but stop if a specific byte is encountered.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   c        The byte to stop at if encountered.
 * @param   size     The maximum number of bytes to copy.
 * @return           `NULL` if `c` was not encountered, otherwise
 *                   the position of `c` translated to `whither`,
 *                   that is, the address of `whither` plus the
 *                   number of copied characters; the address of
 *                   one character passed the last written character.
 * 
 * @since  Always.
 */
void* memcmove(void*, const void*, int, size_t);

/**
 * Override a NUL byte-terminated memory segment
 * with a repeated character.
 * 
 * This is a slibc extension.
 * 
 * @param   str  The beginning of the memory segment.
 * @param   c    The character (8 bits wide.)
 * @return       `str` is returned.
 * 
 * @since  Always.
 */
char* strset(char* str, int c)
  __GCC_ONLY(__attribute__((__returns_nonnull__, __nonnull__)));
#endif

/**
 * Copy a memory segment to another, non-overlapping, segment,
 * stop when a NUL byte is encountered.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @return           `whither` is returned.
 * 
 * @since  Always.
 */
char* strcpy(char* restrict, const char* restrict)
  __GCC_ONLY(__attribute__((__returns_nonnull__, __nonnull__)));

/**
 * Copy a memory segment to another, non-overlapping, segment,
 * stop when a NUL byte is encountered.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @return           `whither + strlen(whence)` is returned.
 * 
 * @since  Always.
 */
char* stpcpy(char* restrict, const char* restrict)
  __GCC_ONLY(__attribute__((__returns_nonnull__, __nonnull__)));

#if defined(__SLIBC_SOURCE)
/**
 * Copy a memory segment to another, non-overlapping, segment,
 * stop when a NUL byte or a specified byte is encountered.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   c        The stop byte.
 * @return           `NULL` if `c` was not encountered, otherwise
 *                   the position of `c` translated to `whither`,
 *                   that is, the address of `whither` plus the
 *                   number of copied characters; the address of
 *                   one character passed the last written non-NUL
 *                   character.
 * 
 * @since  Always.
 */
char* strccpy(char* restrict, const char* restrict, int)
  __GCC_ONLY(__attribute__((__nonnull__)));

/**
 * Copy a memory segment to another, non-overlapping, segment,
 * stop when a NUL byte or a specified substring is encountered.
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
char* strstrcpy(char* restrict, const char* restrict, const char* restrict)
  __GCC_ONLY(__attribute__((__nonnull__(1, 2))));
#endif

/**
 * Copy a memory segment to another, non-overlapping, segment,
 * stop when a NUL byte is encountered.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   maxlen   The maximum number of bytes to copy.
 *                   NOTE that if the resulting string at least this
 *                   long, no NUL byte will be written to `whither'.
 *                   On the otherhand, if the resultnig string is
 *                   shorter, `whither` will be filled with NUL bytes
 *                   until this amount of bytes have been written.
 * @return           `whither` is returned.
 * 
 * @since  Always.
 */
char* strncpy(char* restrict, const char* restrict, size_t)
  __GCC_ONLY(__attribute__((__returns_nonnull__, __nonnull__)));

#if defined(__GNU_SOURCE)
/**
 * Copy a memory segment to another, non-overlapping, segment,
 * stop when a NUL byte is encountered.
 * 
 * This is a GNU extension.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   maxlen   The maximum number of bytes to copy.
 *                   NOTE that if the resulting string at least this
 *                   long, no NUL byte will be written to `whither'.
 *                   On the otherhand, if the resultnig string is
 *                   shorter, `whither` will be filled with NUL bytes
 *                   until this amount of bytes have been written.
 * @return           `whither` plus the number of written bytes,
 *                   excluding NUL bytes, is returned.
 * 
 * @since  Always.
 */
char* stpncpy(char* restrict, const char* restrict, size_t)
  __GCC_ONLY(__attribute__((__returns_nonnull__, __nonnull__)));

# if defined(__SLIBC_SOURCE)
/**
 * Copy a memory segment to another, non-overlapping, segment,
 * stop when a NUL byte or a specified byte is encountered.
 * 
 * This is a slibc extension added for completeness.
 * It is only available if GNU extensions are available.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   c        The stop byte.
 * @param   maxlen   The maximum number of bytes to copy.
 *                   NOTE that if the resulting string at least this
 *                   long, no NUL byte will be written to `whither'.
 *                   On the otherhand, if the resultnig string is
 *                   shorter, `whither` will be filled with NUL bytes
 *                   until this amount of bytes have been written.
 * @return           `NULL` if `c` was not encountered, otherwise
 *                   the position of `c` translated to `whither`,
 *                   that is, the address of `whither` plus the
 *                   number of copied characters; the address of
 *                   one character passed the last written non-NUL
 *                   character.
 * 
 * @since  Always.
 */
char* strcncpy(char* restrict, const char* restrict, int, size_t)
  __GCC_ONLY(__attribute__((__nonnull__)));

/**
 * Copy a memory segment to another, non-overlapping, segment,
 * stop when a NUL byte or a specified substring is encountered.
 * 
 * This is a slibc extension added for completeness.
 * It is only available if GNU extensions are available.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   str      The substring, ignored if `NULL`.
 * @param   maxlen   The maximum number of bytes to copy.
 *                   NOTE that if the resulting string at least this
 *                   long, no NUL byte will be written to `whither'.
 *                   On the otherhand, if the resultnig string is
 *                   shorter, `whither` will be filled with NUL bytes
 *                   until this amount of bytes have been written.
 * @return           `NULL` if `str` was not encountered, otherwise
 *                   the position of `str` translated to `whither`,
 *                   that is, the address of `whither` plus the
 *                   number of copied characters; the address of
 *                   one character passed the last written non-NUL
 *                   character.
 * 
 * @since  Always.
 */
char* strstrncpy(char* restrict, const char* restrict, const char* restrict, size_t)
  __GCC_ONLY(__attribute__((__nonnull__(1, 2))));
# endif
#endif

#if defined(__SLIBC_SOURCE)
/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL byte is encountered.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @return           `whither` is returned.
 * 
 * @since  Always.
 */
char* strmove(char*, const char*)
  __GCC_ONLY(__attribute__((__returns_nonnull__, __nonnull__)));

/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL byte is encountered.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @return           `whither + strlen(whence)` is returned.
 * 
 * @since  Always.
 */
char* stpmove(char*, const char*)
  __GCC_ONLY(__attribute__((__returns_nonnull__, __nonnull__)));

/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL byte or a specified byte is encountered.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   c        The stop byte.
 * @return           `NULL` if `c` was not encountered, otherwise
 *                   the position of `c` translated to `whither`,
 *                   that is, the address of `whither` plus the
 *                   number of copied characters; the address of
 *                   one character passed the last written non-NUL
 *                   character.
 * 
 * @since  Always.
 */
char* strcmove(char*, const char*, int)
  __GCC_ONLY(__attribute__((__nonnull__)));

/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL byte or a specified substring is encountered.
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
char* strstrmove(char*, const char*, const char* restrict)
  __GCC_ONLY(__attribute__((__nonnull__(1, 2))));

/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL byte is encountered.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   maxlen   The maximum number of bytes to copy.
 *                   NOTE that if the resulting string at least this
 *                   long, no NUL byte will be written to `whither'.
 *                   On the otherhand, if the resultnig string is
 *                   shorter, `whither` will be filled with NUL bytes
 *                   until this amount of bytes have been written.
 * @return           `whither` is returned.
 * 
 * @since  Always.
 */
char* strnmove(char*, const char*, size_t)
  __GCC_ONLY(__attribute__((__returns_nonnull__, __nonnull__)));

# if defined(__GNU_SOURCE)
/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL byte is encountered.
 * 
 * This is a slibc extension added for completeness.
 * It is only available if GNU extensions are available.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   maxlen   The maximum number of bytes to copy.
 *                   NOTE that if the resulting string at least this
 *                   long, no NUL byte will be written to `whither'.
 *                   On the otherhand, if the resultnig string is
 *                   shorter, `whither` will be filled with NUL bytes
 *                   until this amount of bytes have been written.
 * @return           `whither` plus the number of written bytes,
 *                   excluding NUL bytes, is returned.
 * 
 * @since  Always.
 */
char* stpnmove(char*, const char*, size_t)
  __GCC_ONLY(__attribute__((__returns_nonnull__, __nonnull__)));

/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL byte or a specified byte is encountered.
 * 
 * This is a slibc extension added for completeness.
 * It is only available if GNU extensions are available.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   c        The stop byte.
 * @param   maxlen   The maximum number of bytes to copy.
 *                   NOTE that if the resulting string at least this
 *                   long, no NUL byte will be written to `whither'.
 *                   On the otherhand, if the resultnig string is
 *                   shorter, `whither` will be filled with NUL bytes
 *                   until this amount of bytes have been written.
 * @return           `NULL` if `c` was not encountered, otherwise
 *                   the position of `c` translated to `whither`,
 *                   that is, the address of `whither` plus the
 *                   number of copied characters; the address of
 *                   one character passed the last written non-NUL
 *                   character.
 * 
 * @since  Always.
 */
char* strcnmove(char*, const char*, int, size_t)
  __GCC_ONLY(__attribute__((__nonnull__)));

/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL byte or a specified substring is encountered.
 * 
 * This is a slibc extension added for completeness.
 * It is only available if GNU extensions are available.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   str      The substring, ignored if `NULL`.
 * @param   maxlen   The maximum number of bytes to copy.
 *                   NOTE that if the resulting string at least this
 *                   long, no NUL byte will be written to `whither'.
 *                   On the otherhand, if the resultnig string is
 *                   shorter, `whither` will be filled with NUL bytes
 *                   until this amount of bytes have been written.
 * @return           `NULL` if `str` was not encountered, otherwise
 *                   the position of `str` translated to `whither`,
 *                   that is, the address of `whither` plus the
 *                   number of copied characters; the address of
 *                   one character passed the last written non-NUL
 *                   character.
 * 
 * @since  Always.
 */
char* strstrnmove(char*, const char*, const char* restrict, size_t)
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
char* strcat(char* restrict, const char* restrict)
  __GCC_ONLY(__attribute__((__nonnull__)));

/* stpcat does not exsits because use of it would be very inefficient. */

/**
 * Concatenate a string to the end of another string.
 * The resulting strings must not overlap with the appended string.
 * 
 * The use of this function is often a really bad idea.
 * 
 * @param   whither  The string to extend.
 * @param   whence   The string to append.
 * @param   maxlen   The maximum number of bytes to copy.
 *                   NOTE that if the resulting string at least this
 *                   long, no NUL byte will be written to `whither'.
 *                   On the otherhand, if the resultnig string is
 *                   shorter, `whither` will be filled with NUL bytes
 *                   until this amount of bytes have been written.
 * @return           `whither` is returned.
 * 
 * @since  Always.
 */
char* strncat(char* restrict, const char* restrict, size_t)
  __GCC_ONLY(__attribute__((__nonnull__)));

/* stpncat does not exsits because use of it would be very inefficient. */


/**
 * Duplicate a string.
 * 
 * @param   string  The string to duplicate.
 * @return          The new string. `NULL` is returned on error
 *                  and `errno` is set to indicate the error.
 * 
 * @throws  ENOMEM  The process could not allocate sufficient amount of memory.
 * 
 * @since  Always.
 */
char* strdup(const char*)
  __GCC_ONLY(__attribute__((__malloc__, __nonnull__, __warn_unused_result__)));

#if defined(__GNU_SOURCE)
/**
 * Duplicate a string.
 * 
 * This is a GNU extension.
 * 
 * @param   string  The string to duplicate.
 * @param   maxlen  Truncate the string to this length, if it is longer.
 *                  A NUL byte is guaranteed to always be written
 *                  upon successful completion.
 * @return          The new string. `NULL` is returned on error
 *                  and `errno` is set to indicate the error.
 * 
 * @throws  ENOMEM  The process could not allocate sufficient amount of memory.
 * 
 * @since  Always.
 */
char* strndup(const char*, size_t)
  __GCC_ONLY(__attribute__((__malloc__, __nonnull__, __warn_unused_result__)));
#endif

#if defined(__SLIBC_SOURCE)
/**
 * Duplicate a memory segment.
 * 
 * This is a slibc extension.
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
void* memdup(const void*, size_t)
  __GCC_ONLY(__attribute__((__malloc__, __nonnull__, __warn_unused_result__)));
#endif

#if defined (__GNUC__)
# if defined(__GNU_SOURCE) || defined(__SLIBC_SOURCE)
/**
 * Duplicate a string, using dymanic stack allocation (`alloca`).
 * 
 * This is a GNU-compliant slibc extension.
 * This macro is only available when using GCC.
 * 
 * @param   string:const char*  The string to duplicate.
 * @return  :size_t             The new string. There is no way to
 *                              detect whether the allocation failed.
 * 
 * @since  Always.
 */
#  define strdupa(string)				\
  ({							\
    const char* __s = (string);				\
    size_t __n = strlen(__s) + 1;			\
    char* __r = __builtin_alloca(__n * sizeof(char));	\
    memcpy(__r, __s, __n * sizeof(char));		\
  })
# endif

# if defined(__GNU_SOURCE)
/**
 * Duplicate a string, using dymanic stack allocation (`alloca`).
 * 
 * This is a GNU extension.
 * This macro is only available when using GCC.
 * 
 * @param   string:const char*  The string to duplicate.
 * @param   maxlen:size_t       Truncate the string to this length, if it is longer.
 *                              A NUL byte is guaranteed to always be written.
 * @return  :size_t             The new string. There is no way to
 *                              detect whether the allocation failed.
 * 
 * @since  Always.
 */
#  define strndupa(string, maxlen)			\
  ({							\
    const char* __s = (string);				\
    size_t __n = strnlen(__s, (maxlen)) + 1;		\
    char* __r = __builtin_alloca(__n * sizeof(char));	\
    memcpy(__r, __s, __n * sizeof(char));		\
  })
# endif

# if defined(__SLIBC_SOURCE)
/**
 * Duplicate a memory segment, using dymanic stack allocation (`alloca`).
 * 
 * This is a slibc extension.
 * This macro is only available when using GCC.
 * 
 * @param   segment:const void*  The memory segment to duplicate.
 * @param   size:size_t          The size of the memory segment.
 * @return  :size_t              The new segment. There is no way to
 *                               detect whether the allocation failed.
 * 
 * @since  Always.
 */
#  define memdupa(segment, size)	\
  ({					\
    size_t __n = (size);		\
    void* __r = __builtin_alloca(__n);	\
    memcpy(__r, (segment), __n);	\
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
int memcmp(const void*, const void*, size_t)
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
int memcasecmp(const void*, const void*, size_t)
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
int strcmp(const char*, const char*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));

/**
 * Compare two strings alphabetically in a case sensitive manner.
 * 
 * @param   a       A negative value is returned if this is the lesser.
 * @param   b       A positive value is returned if this is the lesser.
 * @param   length  The maximum number of characters to compare.
 * @return          Zero is returned if `a` and `b` are equal, otherwise,
 *                  see the specifications for `a` and `b`.
 * 
 * @since  Always.
 */
int strncmp(const char*, const char*, size_t)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));


#if defined(__GNU_SOURCE)
int strverscmp(const char*, const char*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));
/* TODO document and implement strverscmp */
#endif


/**
 * Find the first occurrence of a byte in a memory segment.
 * 
 * @param   segment  The memory segment to search.
 * @param   c        The sought after character.
 * @param   size     The size of the memory segment.
 * @return           Pointer to the first occurrence of `c`,
 *                   `NULL` if none were found.
 * 
 * @since  Always.
 */
void* memchr(const void*, int, size_t)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __pure__)));
#ifdef __CONST_CORRECT
# define memchr(...)  (__const_correct(memchr, __VA_ARGS__))
#endif


#if defined(__GNU_SOURCE) || defined(__SLIBC_SOURCE)
/**
 * Find the first occurrence of a byte in a memory segment.
 * The memory segment must be known to contain the sought after byte.
 * 
 * This is a GNU-compliant slibc extension.
 * 
 * @param   segment  The memory segment to search.
 * @param   c        The sought after character.
 * @return           Pointer to the first occurrence of `c`.
 * 
 * @since  Always.
 */
void* rawmemchr(const void*, int)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __returns_nonnull__, __nonnull__, __pure__)));
# ifdef __CONST_CORRECT
#  define rawmemchr(...)  (__const_correct(rawmemchr, __VA_ARGS__))
# endif
#endif

/**
 * Find the last occurrence of a byte in a memory segment.
 * 
 * For improved performace, use this function instead
 * of `strrchr` if you already know the length of the
 * string.
 * 
 * @param   segment  The memory segment to search.
 * @param   c        The sought after character.
 * @param   size     The size of the memory segment.
 * @return           Pointer to the last occurrence of `c`,
 *                   `NULL` if none were found.
 * 
 * @since  Always.
 */
void* memrchr(const void*, int, size_t)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __pure__)));
#ifdef __CONST_CORRECT
# define memrchr(...)  (__const_correct(memrchr, __VA_ARGS__))
#endif

/**
 * Find the first occurrence of a byte in a string.
 * 
 * `s = strchr(s, 0)` is a faster alternative to
 * `s = s + strlen(s)`.
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
char* strchr(const char*, int)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));
#ifdef __CONST_CORRECT
# define strchr(...)  (__const_correct(strchr, __VA_ARGS__))
#endif

#if defined(__GNU_SOURCE) || defined(__SLIBC_SOURCE)
/**
 * Find the first occurrence of a byte in a string, or
 * if there is no such byte, the end of the string.
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
char* strchrnul(const char*, int)
   __GCC_ONLY(__attribute__((__warn_unused_result__, __returns_nonnull__, __nonnull__, __pure__)));
# ifdef __CONST_CORRECT
#  define strchrnul(...)  (__const_correct(strchrnul, __VA_ARGS__))
# endif
#endif

/**
 * Find the last occurrence of a byte in a string.
 * 
 * For improved performace, use `memrchr` instead of
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
char* strrchr(const char*, int)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));
#ifdef __CONST_CORRECT
# define strrchr(...)  (__const_correct(strrchr, __VA_ARGS__))
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
char* strstr(const char*, const char*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));
#ifdef __CONST_CORRECT
# define strstr(...)  (__const_correct(strstr, __VA_ARGS__))
#endif

/**
 * Finds the first occurrence of a substring.
 * This search is case insensitive.
 * 
 * @param   haystack  The string to search.
 * @param   needle    The sought after substring.
 * @return            Pointer to the first occurrence of the
 *                    substring, `NULL` if not found.
 * 
 * @since  Always.
 */
char* strcasestr(const char*, const char*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));
#ifdef __CONST_CORRECT
# define strcasestr(...)  (__const_correct(strcasestr, __VA_ARGS__))
#endif

#if defined(__SLIBC_SOURCE)
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
char* strnstr(const char*, const char*, size_t)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));
# ifdef __CONST_CORRECT
#  define strnstr(...)  (__const_correct(strnstr, __VA_ARGS__))
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
char* strncasestr(const char*, const char*, size_t)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));
# ifdef __CONST_CORRECT
#  define strncasestr(...)  (__const_correct(strncasestr, __VA_ARGS__))
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
char* rawstrstr(const char*, const char*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __returns_nonnull__, __pure__)));
# ifdef __CONST_CORRECT
#  define rawstrstr(...)  (__const_correct(rawstrstr, __VA_ARGS__))
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
char* rawstrcasestr(const char*, const char*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __returns_nonnull__, __pure__)));
# ifdef __CONST_CORRECT
#  define rawstrcasestr(...)  (__const_correct(rawstrcasestr, __VA_ARGS__))
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
void* memcasemem(const void*, size_t, const void*, size_t)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __pure__)));
# ifdef __CONST_CORRECT
#  define memcasemem(...)  (__const_correct(memcasemem, __VA_ARGS__))
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
char* strstarts(const char*, const char*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));
# ifdef __CONST_CORRECT
#  define strstarts(...)  (__const_correct(strstarts, __VA_ARGS__))
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
char* strends(const char*, const char*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));
# ifdef __CONST_CORRECT
#  define strends(...)  (__const_correct(strends, __VA_ARGS__))
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
char* strcasestarts(const char*, const char*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));
# ifdef __CONST_CORRECT
#  define strcasestarts(...)  (__const_correct(strcasestarts, __VA_ARGS__))
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
char* strcaseends(const char*, const char*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));
# ifdef __CONST_CORRECT
#  define strcaseends(...)  (__const_correct(strcaseends, __VA_ARGS__))
# endif
#endif

#if defined(__GNU_SOURCE) || defined(__SLIBC_SOURCE)
/**
 * Finds the first occurrence of a substring.
 * This search is case sensitive.
 * 
 * This is a GNU-compliant slibc extension. It was useful
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
void* memmem(const void*, size_t, const void*, size_t)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __pure__)));
# ifdef __CONST_CORRECT
#  define memmem(...)  (__const_correct(memmem, __VA_ARGS__))
# endif
#endif


/* TODO Add case right-to-left substring searching functions. */


/**
 * Returns length of the initial substring
 * that consists entirely of a set of specified
 * bytes.
 * 
 * @param   string   The string.
 * @param   skipset  Bytes allowed in the substring.
 * @return           The length of the substring.
 * 
 * @since  Always.
 */
size_t strspn(const char*, const char*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));

/**
 * Returns length of the initial substring
 * that consists entirely of the complement
 * of a set of specified bytes.
 * 
 * @param   string   The string.
 * @param   stopset  Bytes disallowed in the substring.
 * @return           The length of the substring.
 * 
 * @since  Always.
 */
size_t strcspn(const char*, const char*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));

/**
 * This function works like `strcspn`,
 * except it returns the pointer to the
 * location of the first found non-matching
 * byte.
 * 
 * @param   string   The string.
 * @param   stopset  Bytes disallowed in the substring.
 * @return           A pointer to the first occurrence in
 *                   `string` of a byte found in `stopset`.
 *                   `NULL` is returned if none is found.
 * 
 * @since  Always.
 */
char* strpbrk(const char*, const char*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__, __pure__)));
#ifdef __CONST_CORRECT
# define strpbrk(...)  (__const_correct(strpbrk, __VA_ARGS__))
#endif


/**
 * Tokenise a string.
 * 
 * @param   string      The string to tokenise on the first,
 *                      `NULL` on subsequent calls.
 *                      All bytes found in `delimiters` will
 *                      be overriden with NUL bytes.
 * @param   delimiters  Delimiting bytes (not characters).
 * @return              The next non-empty string that does not
 *                      contain a byte from `delimiters`. The
 *                      returned string will be as long as possible.
 *                      `NULL` is returned the search as reached
 *                      the end of the string, and there therefore
 *                      are no more tokens.
 * 
 * @since  Always.
 */
char* strtok(char* restrict, const char* restrict)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__(2))));

/**
 * Tokenise a string.
 * 
 * @param   string      The string to tokenise on the first,
 *                      `NULL` on subsequent calls.
 *                      All bytes found in `delimiters` will
 *                      be overriden with NUL bytes.
 * @param   delimiters  Delimiting bytes (not characters).
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
char* strtok_r(char* restrict, const char* restrict, char** restrict)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__(2, 3))));

/**
 * Tokenise a string.
 * 
 * @param   string      Pointer to the string to tokenise on the first call,
 *                      will be updated to keep track of the state.
 *                      All bytes found in `delimiters` will
 *                      be overriden with NUL bytes.
 * @param   delimiters  Delimiting bytes (not characters).
 * @return              The next, possibly empty, string that does
 *                      not contain a byte from `delimiters`. The
 *                      returned string will be as long as possible.
 *                      `NULL` is returned the search as reached
 *                      the end of the string, and there therefore
 *                      are no more tokens.
 * 
 * @since  Always.
 */
char* strsep(char** restrict, const char* restrict)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __nonnull__)));


#if defined(__GNU_SOURCE) && !defined(basename)
/**
 * Get the basename of a filename.
 * 
 * This is a GNU extension, include <libgen.h>
 * to override it with the XPG-compliant implementation.
 * 
 * @param   filename  The filename.
 * @return            The basename, it is either a substring
 *                    of `filename` or, if `filename` is `NULL`
 *                    or is empty, a statically allocationed string,
 *                    so it must not freed or edited.
 * 
 * @since  Always.
 */
char* __gnu_basename(const char*)
  __GCC_ONLY(__attribute__((__warn_unused_result__, __pure__)));
# define basename  __gnu_basename
/* It does not look like it is possible to solve the const-correctness problem here. */
#endif


#if defined(__GNU_SOURCE)
/**
 * Shuffles all bytes in a string.
 * 
 * You should have called `srand` before
 * calling this function.
 * 
 * This is a GNU joke extension.
 * 
 * @param   anagram  An anagram of the output, will be modified.
 * @retrun           The string, which will `== anagram`.
 * 
 * @since  Always.
 */
char* strfry(char*);

/**
 * Performs an inplace bitwise XOR:ing of
 * a memory segment. The pattern is 00101010.
 * 
 * This is a GNU extension.
 * 
 * @param   segment  The memory segment.
 * @param   size     The size of the memory segment.
 * @return           `segment` is returned
 * 
 * @since  Always.
 */
char* memfrob(char*, size_t);
#endif



#endif

