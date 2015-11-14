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
#ifndef _SLIBC_HUMAN_H
#define _SLIBC_HUMAN_H
#include <slibc/version.h>
#include <slibc/features.h>
#ifndef __PORTABLE



#define __NEED_mode_t
#ifdef __C99__
# define __NEED_intmax_t
# define __NEED_uintmax_t
#endif

#include <bits/types.h>



/**
 * Ways to handled unrecognised escapes,
 * and other configurations.
 */
enum unescape_mode
  {
    /**
     * For any unrecognised character '#',
     * '\#' results in an EINVAL-error.
     * 
     * Cannot be used together with
     * `UNESCAPE_VERBATIM` or `UNESCAPE_IGNORE`.
     */
    UNESCAPE_EINVAL = 1,
    
    /**
     * For any unrecognised character '#',
     * '\#' results in '#'.
     * 
     * Cannot be used together with
     * `UNESCAPE_EINVAL` or `UNESCAPE_IGNORE`.
     */
    UNESCAPE_VERBATIM = 2,
    
    /**
     * For any unrecognised character '#',
     * '\#' results in '\#'.
     * 
     * Cannot be used together with
     * `UNESCAPE_EINVAL` or `UNESCAPE_VERBATIM`.
     */
    UNESCAPE_IGNORE = 4,
    
    
    /**
     * '\&' resolves to the byte 255 (0xFF).
     * 
     * If not used, '\&' is handled as an
     * unsupported escape.
     */
    UNESCAPE_AMPERSAND = 8,
    
    /**
     * '\0' resolves to the byte sequence
     * 192 128 (0xC0 0x80).
     * 
     * If not used, '\0' resolves to a
     * 0 byte (termination).
     */
    UNESCAPE_MOD_UTF8 = 16,
  };


enum humansize_mode
  {
    /**
     * 'k' is 1000.
     * 
     * Cannot be combined with `HUMANSIZE_IEC`
     * or `HUMANSIZE_IEC_EXPLICIT`.
     */
    HUMANSIZE_SI = 1,
    
    /**
     * 'K' is 1024.
     * 
     * Cannot be combined with `HUMANSIZE_SI`
     * or `HUMANSIZE_IEC_EXPLICIT`.
     */
    HUMANSIZE_IEC = 2,
    
    /**
     * 'Ki' is 1024.
     * 
     * Cannot be combined with `HUMANSIZE_SI`
     * or `HUMANSIZE_IEC`.
     */
    HUMANSIZE_IEC_EXPLICIT = 4,
    
    
    /**
     * 'B' is only included if there is no prefix.
     */
    HUMANSIZE_PREFIX_ONLY = 8,
    
    
    /**
     * Print size exactly if `detail` is 0,
     * otherwise use the highest `detail` prefixes.
     * 
     * For example `detail == 0` may yeild '3TB 2MB 1KB',
     * and `detail == 3` may yeild '3TB 2MB' for the same size.
     */
    HUMANSIZE_EXACT = 16,
    
    /**
     * Similar to `HUMANSIZE_EXACT` with `detail == 1`,
     * but the value will include `detail` digits.
     * `detail` < 0 is allowed, 
     */
    HUMANSIZE_ROUND = 32,
  }


enum machinesize_mode
  {
    /**
     * 'k' and 'K' is 1000.
     * 
     * If `MACHINESIZE_IEC` is also used,
     * 1000-base is used if 'B' is explicitly
     * included, otherwise 1024-base is used.
     */
    MACHINESIZE_SI = 1,
    
    /**
     * 'k' and 'K' is 1024.
     * 
     * If `MACHINESIZE_SI` is also used,
     * 1000-base is used if 'B' is explicitly
     * included, otherwise 1024-base is used.
     */
    MACHINESIZE_IEC = 2,
  }



char* humanmode(char* restrict buffer, mode_t mode);

mode_t machinemode(const char* restrict str, mode_t mode, mode_t mask);


char* humansize(char* restrict buffer, size_t size, enum humansize_mode mode, int detail);

int machinesize(size_t* restrict size, const char* restrict string, enum machinesize_mode mode);


#ifdef __C99__
int humandur(intmax_t sec, long int nsec, const char* restrict comma, const char* restrict format);

int machinedur(intmax_t* restrict sec, long int* nsec, const char* restrict str,
	       const char* restrict space, const char* restrict comma);


char* machineint(intmax_t* restrict r, const char* restrict str);
# ifdef __CONST_CORRECT
#  define machineint(...)  (__const_correct_2p(machineint, __VA_ARGS__))
# endif

char* machineuint(uintmax_t* restrict r, const char* restrict str);
# ifdef __CONST_CORRECT
#  define machineuint(...)  (__const_correct_2p(machineuint, __VA_ARGS__))
# endif
#endif

int machinefloat(long double* restrict r, const char* restrict str,
		 const char* restrict space, const char* restrict comma);
#ifdef __CONST_CORRECT
# define machinefloat(...)  (__const_correct_2(machinefloat, __VA_ARGS__))
#endif


/**
 * Parse an escaped string.
 * 
 * Supported escapes:
 *   \' \" \$ \& \? \\ \/ \### \a \b \e \f \n
 *   \r \t \s \u#### \u{#…} \U######## \v \x##
 *   \^@…\^_
 *   \NUL \SOH \STX \ETX \EOT \ENQ \ACK \BEL \BS \HT
 *   \LF \VT \FF \CR \SO \SI \DLE \DC1 \DC2 \DC3 \DC4
 *   \NAK \SYN \ETB \CAN \EM \SUB \ESC \FS \GS \RS
 *   \US \SP \DEL
 * 
 * Unsupported escapes:
 *   \N{character name}
 * 
 * @param   str   The escaped string, may be edited, may be `NULL`.
 *                Must not be reused on error.
 * @param   mode  How unrecognised escapes should be handled,
 *                and other configurations, 0 for default.
 * @return        The new end of `str` is returned. `NULL` is returned
 *                on error or if `str` is `NULL`.
 * 
 * @throws  0       `str` is `NULL`.
 * @throws  EINVAL  If `mode` is invalid.
 * @throws  EINVAL  If `str` is invalid and `mode & UNESCAPE_EINVAL`.
 */
char* unescape(char*, enum unescape_mode);

/**
 * Escapes a string.
 * 
 * @param   str    The unescaped string, may be `NULL`.
 * @param   quote  The queue character, must be either ', "
 *                 or a NUL-character (for no surrounding quotes).
 *                 Note, these quotes are not added to output.
 * @return         Escaped variant of the string, `NULL`.
 *                 You are responsible for deallocating the
 *                 returned pointer.
 * 
 * @throws  0       `str` is `NULL`.
 * @throws  EINVAL  If `quote` is invalid.
 * @throws  ENOMEM  The process cannot allocate more memory.
 */
char* escape(const char* restrict)
  __GCC_ONLY(__attribute__((__malloc__, __warn_unused_result__)));



#endif
#endif

