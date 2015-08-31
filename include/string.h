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
#ifndef _STRING_H
#define _STRING_H
#include <slibc/version.h>
#include <slibc/features.h>



#define __NEED_size_t
#define __NEED_locale_t /* TODO not defined */

#include <bits/types.h>



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
 */
char* strerror(int)
  __GCC_ONLY(__attribute__((returns_nonnull, warn_unused_result)));

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
 */
char* strerror_l(int, locale_t)
  __GCC_ONLY(__attribute__((warn_unused_result)));


#if !defined(__PORTABLE) && !defined(_SLIBC_SOURCE)
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
 */
size_t strlen(const char*)
  __GCC_ONLY(__attribute__((nonnull, warn_unused_result)));

#if (defined(_POSIX_SOURCE) || defined(_POSIX_C_SOURCE) || \
     defined(_XOPEN_SOURCE) || defined(_GNU_SOURCE) || \
     defined(_BSD_SOURCE)) && !defined(__PORTABLE)
/**
 * Variant of `strlen` that only inspects the
 * beginning of s string.
 * 
 * @param   str     The string.
 * @param   maxlen  The number of bytes to inspect, at most.
 * @return          The number of bytes before, the first NUL byte.
 *                  `maxlen` if no NUL byte was found.
 */
size_t strnlen(const char*, size_t)
  __GCC_ONLY(__attribute__((warn_unused_result)));
#endif



/**
 * Override a memory segment with a repeated character.
 * 
 * @param   segment  The beginning of the memory segment.
 * @param   c        The character (8 bits wide.)
 * @param   size     The size of the memory segment.
 * @return           `segment` is returned.
 */
void* memset(void*, int, size_t);

/**
 * Copy a memory segment to another, non-overlapping, segment.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   size     The number of bytes to copy.
 * @return           `whither` is returned.
 */
void* memcpy(void* restrict, const void* restrict, size_t);

#if defined(_GNU_SOURCE) && !defined(__PORTABLE)
/**
 * Copy a memory segment to another, non-overlapping, segment.
 * 
 * This is a GNU extension.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   size     The number of bytes to copy.
 * @return           `whither + size` is returned.
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
 */
void* memmove(void*, const void*, size_t);

#if defined(_SLIBC_SOURCE) && defined(_GNU_SOURCE)
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
 */
void* memccpy(void* restrict, const void* restrict, int, size_t);

#if defined(_SLIBC_SOURCE) && !defined(__PORTABLE)
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
 */
void* memcmove(void*, const void*, int, size_t);
#endif

/**
 * Copy a memory segment to another, non-overlapping, segment,
 * stop when a NUL byte is encountered.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @return           `whither` is returned.
 */
char* strcpy(char* restrict, const char* restrict)
  __GCC_ONLY(__attribute__((returns_nonnull, nonnull)));

/**
 * Copy a memory segment to another, non-overlapping, segment,
 * stop when a NUL byte is encountered.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @return           `whither + strlen(whence)` is returned.
 */
char* stpcpy(char* restrict, const char* restrict)
  __GCC_ONLY(__attribute__((returns_nonnull, nonnull)));

#if defined(_SLIBC_SOURCE) && !defined(__PORTABLE)
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
 */
char* strccpy(char* restrict, const char* restrict, int)
  __GCC_ONLY(__attribute__((nonnull)));

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
 */
char* strstrcpy(char* restrict, const char* restrict, const char* restrict)
  __GCC_ONLY(__attribute__((nonnull(1, 2))));
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
 */
char* strncpy(char* restrict, const char* restrict, size_t)
  __GCC_ONLY(__attribute__((returns_nonnull, nonnull)));

#if defined(_GNU_SOURCE) && !defined(__PORTABLE)
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
 */
char* stpncpy(char* restrict, const char* restrict, size_t)
  __GCC_ONLY(__attribute__((returns_nonnull, nonnull)));

# if defined(_SLIBC_SOURCE)
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
 */
char* strcncpy(char* restrict, const char* restrict, int, size_t)
  __GCC_ONLY(__attribute__((nonnull)));

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
 */
char* strstrncpy(char* restrict, const char* restrict, const char* restrict, size_t)
  __GCC_ONLY(__attribute__((nonnull(1, 2))));
# endif
#endif

#if defined(_SLIBC_SOURCE) && !defined(__PORTABLE)
/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL byte is encountered.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @return           `whither` is returned.
 */
char* strmove(char*, const char*)
  __GCC_ONLY(__attribute__((returns_nonnull, nonnull)));

/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL byte is encountered.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @return           `whither + strlen(whence)` is returned.
 */
char* stpmove(char*, const char*)
  __GCC_ONLY(__attribute__((returns_nonnull, nonnull)));

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
 */
char* strcmove(char*, const char*, int)
  __GCC_ONLY(__attribute__((nonnull)));

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
 */
char* strstrmove(char*, const char*, const char* restrict)
  __GCC_ONLY(__attribute__((nonnull(1, 2))));

/**
 * Copy a memory segment to another, possibly overlapping, segment,
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
 */
char* strnmove(char*, const char*, size_t)
  __GCC_ONLY(__attribute__((returns_nonnull, nonnull)));

# if defined(_GNU_SOURCE)
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
 */
char* stpnmove(char*, const char*, size_t)
  __GCC_ONLY(__attribute__((returns_nonnull, nonnull)));

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
 */
char* strcnmove(char*, const char*, int, size_t)
  __GCC_ONLY(__attribute__((nonnull)));

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
 */
char* strstrnmove(char*, const char*, const char* restrict, size_t)
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
char* strcat(char* restrict, const char* restrict)
  __GCC_ONLY(__attribute__((nonnull)));

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
 */
char* strncat(char* restrict, const char* restrict, size_t)
  __GCC_ONLY(__attribute__((nonnull)));

/* stpncat does not exsits because use of it would be very inefficient. */


/**
 * Duplicate a string.
 * 
 * @param   string  The string to duplicate.
 * @return          The new string. `NULL` is returned on error
 *                  and `errno` is set to indicate the error.
 * 
 * @throws  ENOMEM  The process could not allocate sufficient amount of memory.
 */
char* strdup(const char*)
  __GCC_ONLY(__attribute__((malloc, nonnull, warn_unused_result)));

#if !defined(__PORTABLE)
# if defined(_GNU_SOURCE)
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
 */
char* strndup(const char*, size_t)
  __GCC_ONLY(__attribute__((malloc, nonnull, warn_unused_result)));
# endif

# if defined(_SLIBC_SOURCE)
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
 */
void* memdup(const void*, size_t)
  __GCC_ONLY(__attribute__((malloc, nonnull, warn_unused_result)));
# endif

# if defined (__GNUC__)
#  if defined(_GNU_SOURCE) || defined(_SLIBC_SOURCE)
/**
 * Duplicate a string, using dymanic stack allocation (`alloca`).
 * 
 * This is a GNU-compliant slibc extension.
 * This macro is only available when using GCC.
 * 
 * @param   string:const char*  The string to duplicate.
 * @return  :size_t             The new string. There is no way to
 *                              detect whether the allocation failed.
 */
#   define strdupa(string)				\
  ({							\
    const char* __s = (string);				\
    size_t __n = strlen(__s) + 1;			\
    char* __r = __builtin_alloca(__n * sizeof(char));	\
    memcpy(__r, __s, __n * sizeof(char));		\
  })
#  endif

#  if defined(_GNU_SOURCE)
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
 */
#   define strndupa(string, maxlen)			\
  ({							\
    const char* __s = (string);				\
    size_t __n = strnlen(__s, (maxlen)) + 1;		\
    char* __r = __builtin_alloca(__n * sizeof(char));	\
    memcpy(__r, __s, __n * sizeof(char));		\
  })
#  endif

#  if defined(_SLIBC_SOURCE)
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
 */
#   define memdupa(segment, size)	\
  ({					\
    size_t __n = (size);		\
    void* __r = __builtin_alloca(__n);	\
    memcpy(__r, (segment), __n);	\
  })
#  endif
# endif
#endif



#endif

