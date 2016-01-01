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
/* That's right. No inclusion-guard; we want multiple
 * headers to be able to define types by including this
 * header without the need of keeping in mind which
 * order headers are included. */
#include <slibc/features.h>


#include <bits/intconf.h>
/* TODO [u]int(|_least|_fast)$N_t are compiler-dependent and may even
 *      be compiler-flag-dependent. Some CPP-magic is required to
 *      figure their exact underlaying intrinsic type and existence. */


/* Ensure that dependencies for type are defined. */
#if defined(__NEED_imaxdiv_t) && !defined(__NEED_intmax_t)
# define __NEED_intmax_t
#endif



/**
 * Returns the maximum value of an unsigned integer type,
 * in that type.
 */
#ifndef __MAX_OF
# define  __MAX_OF(type)  \
  (((type)1) << sizeof(type))
#endif

/**
 * An integer type for pointers, but not wider than `long int`.
 */
#ifndef __LIMITED_PTR_INT
# if __PTR_BIT == __CHAR_BIT
#  define __LIMITED_PTR_INT  char
# elif __PTR_BIT == __SHORT_BIT
#  define __LIMITED_PTR_INT  short int
# elif __PTR_BIT == __INT_BIT
#  define __LIMITED_PTR_INT  int
# else
#  define __LIMITED_PTR_INT  long int
# endif
#endif


/**
 * Signed integer type of the result of subtracting two pointers.
 * May not be greater than the width of type `long int`.
 * 
 * @since  Always.
 */
#if defined(__NEED_ptrdiff_t) && !defined(__DEFINED_ptrdiff_t)
# define __DEFINED_ptrdiff_t
typedef signed __LIMITED_PTR_INT ptrdiff_t;
#endif


/**
 * Unsigned version of `ptrdiff_t`
 * 
 * @since  Always.
 */
#if defined(__NEED_uptrdiff_t) && !defined(__DEFINED_uptrdiff_t)
# define __DEFINED_uptrdiff_t
typedef unsigned __LIMITED_PTR_INT uptrdiff_t;
#endif


#ifndef __PORTABLE
/**
 * Integer type which can represent any character.
 * May not be greater than the with of type long.
 * 
 * Unicode originally had an, inclusive upper limit
 * of U+FFFF. UTF-8 however had 31-bits (U+7FFFFFFF).
 * Unicode is now limited to 0x10FFFF.
 * 
 * 32 bits should be sufficient (long is at least 32
 * bits), but why limit further than POSIX does.
 * 
 * `wchar_t` is not safe for data serialisation/marshalling;
 * it is implementation specific and may depend on the
 * libc implementation, the version of the libc implementation,
 * and the microarchitecture.
 * 
 * @since  Always.
 */
# if defined(__NEED_wchar_t) && !defined(__DEFINED_wchar_t)
#  define __DEFINED_wchar_t
#  if __WCHAR_BIT == 8
typedef __WCHAR_SIGNNESS __INT8 wchar_t
#  elif __WCHAR_BIT == 16
typedef __WCHAR_SIGNNESS __INT16 wchar_t
#  elif __WCHAR_BIT == 32
typedef __WCHAR_SIGNNESS __INT32 wchar_t
#  elif __WCHAR_BIT == 64
typedef __WCHAR_SIGNNESS __INT64 wchar_t
#  endif
  __warning("'wchar_t' is not guaranteed to be defined as expected, use 'int32_t'.");
# endif
# ifndef __WCHAR_MAX
#  if __WCHAR_BIT == 8
#   define __WCHAR_MAX  INT8_MAX
#  elif __WCHAR_BIT == 16
#   define __WCHAR_MAX  INT16_MAX
#  elif __WCHAR_BIT == 32
#   define __WCHAR_MAX  INT32_MAX
#  elif __WCHAR_BIT == 64
#   define __WCHAR_MAX  INT64_MAX
#  endif
# endif


/**
 * Variant of `wchar_t` that can hold the value of `WEOF`.
 * 
 * `wint_t` is not safe for data serialisation/marshalling;
 * it is implementation specific and may depend on the
 * libc implementation, the version of the libc implementation,
 * and the microarchitecture.
 * 
 * @since  Always.
 */
# if defined(__NEED_wint_t) && !defined(__DEFINED_wint_t)
#  define __DEFINED_wint_t
typedef wchar_t wint_t
  __warning("'wint_t' is not guaranteed to be defined as expected, use 'int32_t'.");
# endif
#endif


/**
 * Unsigned integer type of the result of the
 * `sizeof` operator. May not be greater than the
 * width of type `long int`.
 * 
 * @since  Always.
 */
#if defined(__NEED_size_t) && !defined(__DEFINED_size_t)
# define __DEFINED_size_t
typedef unsigned __LIMITED_PTR_INT size_t;
#endif


/**
 * Signed version of `size_t`
 * 
 * @since  Always.
 */
#if defined(__NEED_ssize_t) && !defined(__DEFINED_ssize_t)
# define __DEFINED_ssize_t
typedef signed __LIMITED_PTR_INT ssize_t;
#endif


/**
 * A type, of unspecified construct, whose alignment requirement
 * is at least as strict as that of every scalar type.
 * 
 * @since  Always.
 */
#if defined(__NEED_max_align_t) && !defined(__DEFINED_max_align_t)
# define __DEFINED_max_align_t
typedef struct
{
  long long int __lli __attribute__((__aligned__(__alignof__(long long int))));
  long double   __ld  __attribute__((__aligned__(__alignof__(long double))));
} max_align_t;
#endif


/**
 * Signed exact-width integer types.
 * 
 * These types are guaranteed to use two's complement.
 * 
 * @since  Always.
 */
#if defined(__NEED_intN_t) && !defined(__DEFINED_intN_t)
# define __DEFINED_intN_t
typedef signed __INT8 int8_t;
typedef signed __INT16 int16_t;
typedef signed __INT32 int32_t;
typedef signed __INT64 int64_t;
#endif


/**
 * Unsigned exact-width integer types.
 * 
 * @since  Always.
 */
#if defined(__NEED_uintN_t) && !defined(__DEFINED_uintN_t)
# define __DEFINED_uintN_t
typedef unsigned __INT8 uint8_t;
typedef unsigned __INT16 uint16_t;
typedef unsigned __INT32 uint32_t;
typedef unsigned __INT64 uint64_t;
#endif


/**
 * Signed integer types with guaranteed minimum length
 * with otherwise minimal length.
 * 
 * `int_least8_t`, `int_least16_t`, `int_least32_t`, and
 * `int_least64_t` are guaranteed to be defined.
 * 
 * @since  Always.
 */
#if defined(__NEED_int_leastN_t) && !defined(__DEFINED_int_leastN_t)
# define __DEFINED_int_leastN_t
typedef signed __INT8 int_least8_t;
typedef signed __INT16 int_least16_t;
typedef signed __INT32 int_least32_t;
typedef signed __INT64 int_least64_t;
#endif


/**
 * Unsigned integer types with guaranteed minimum length
 * with otherwise minimal length.
 * 
 * `uint_least8_t`, `uint_least16_t`, `uint_least32_t`, and
 * `uint_least64_t` are guaranteed to be defined.
 * 
 * @since  Always.
 */
#if defined(__NEED_uint_leastN_t) && !defined(__DEFINED_uint_leastN_t)
# define __DEFINED_uint_leastN_t
typedef unsigned __INT8 uint_least8_t;
typedef unsigned __INT16 uint_least16_t;
typedef unsigned __INT32 uint_least32_t;
typedef unsigned __INT64 uint_least64_t;
#endif


/**
 * Signed integer types with guaranteed minimum length
 * and are thought to be the fastest to in most use-cases.
 * 
 * `int_fast8_t`, `int_fast16_t`, `int_fast32_t`, and
 * `int_fast64_t` are guaranteed to be defined.
 * It is howevr strongly discouraged to uses this types
 * in serialised/marshalled data, as they may depend
 * on the C library the program is compiled against
 * and the version of that library.
 * 
 * @since  Always.
 */
#if defined(__NEED_int_fastN_t) && !defined(__DEFINED_int_fastN_t)
# define __DEFINED_int_fastN_t
typedef signed __INT_FAST8 int_fast8_t;
typedef signed __INT_FAST16 int_fast16_t;
typedef signed __INT_FAST32 int_fast32_t;
typedef signed __INT_FAST64 int_fast64_t;
#endif


/**
 * Ubsigned integer types with guaranteed minimum length
 * and are thought to be the fastest to in most use-cases.
 * 
 * `uint_fast8_t`, `uint_fast16_t`, `uint_fast32_t`, and
 * `uint_fast64_t` are guaranteed to be defined.
 * It is howevr strongly discouraged to uses this types
 * in serialised/marshalled data, as they may depend
 * on the C library the program is compiled against
 * and the version of that library.
 * 
 * @since  Always.
 */
#if defined(__NEED_uint_fastN_t) && !defined(__DEFINED_uint_fastN_t)
# define __DEFINED_uint_fastN_t
typedef unsigned __INT_FAST8 uint_fast8_t;
typedef unsigned __INT_FAST16 uint_fast16_t;
typedef unsigned __INT_FAST32 uint_fast32_t;
typedef unsigned __INT_FAST64 uint_fast64_t;
#endif


/**
 * The widest signed integer type available.
 * 
 * @since  Always.
 */
#if defined(__NEED_intmax_t) && !defined(__DEFINED_intmax_t)
# define __DEFINED_intmax_t
typedef signed __INT64 intmax_t;
#endif
#ifndef __INTMAX_MAX
# define __INTMAX_MAX  INT64_MAX
#endif


/**
 * The widest unsigned integer type available.
 * 
 * @since  Always.
 */
#if defined(__NEED_uintmax_t) && !defined(__DEFINED_uintmax_t)
# define __DEFINED_uintmax_t
typedef unsigned __INT64 uintmax_t;
#endif
#ifndef __UINTMAX_MAX
# define __UINTMAX_MAX  UINT64_MAX
#endif


/**
 * A integer type over which operations are atomic.
 * It may be defined as volatile, slibc does not do
 * this however because it is good practice to do
 * so explcitily when using the `sig_atomic_t` type.
 * 
 * @since  Always.
 */
#if defined(__NEED_sig_atomic_t) && !defined(__DEFINED_sig_atomic_t)
# define __DEFINED_sig_atomic_t
typedef int sig_atomic_t;
#endif
#ifndef __SIG_ATOMIC_BIT
# define __SIG_ATOMIC_BIT  __INT_BIT
#endif


/**
 * A structure than holds both the quotient and
 * the remainer in an integer division, of
 * `int` type.
 * 
 * @since  Always.
 */
#if defined(__NEED_div_t) && !defined(__DEFINED_div_t)
# define __DEFINED_div_t
typedef struct {
  /**
   * Quotient.
   */
  int quot;
  
  /**
   * Remainder.
   */
  int rem;
  
} div_t;
#endif


/**
 * A structure than holds both the quotient and
 * the remainer in an integer division, of
 * `long int` type.
 * 
 * @since  Always.
 */
#if defined(__NEED_ldiv_t) && !defined(__DEFINED_ldiv_t)
# define __DEFINED_ldiv_t
typedef struct {
  /**
   * Quotient.
   */
  long int quot;
  
  /**
   * Remainder.
   */
  long int rem;
  
} ldiv_t;
#endif


/**
 * A structure than holds both the quotient and
 * the remainer in an integer division, of
 * `long long int` type.
 * 
 * @since  Always.
 */
#if defined(__NEED_lldiv_t) && !defined(__DEFINED_lldiv_t)
# define __DEFINED_lldiv_t
typedef struct {
  /**
   * Quotient.
   */
  long long int quot;
  
  /**
   * Remainder.
   */
  long long int rem;
  
} lldiv_t;
#endif


/**
 * A structure than holds both the quotient and
 * the remainer in an integer division, of
 * `intmax_t` type.
 * 
 * @since  Always.
 */
#if defined(__NEED_imaxdiv_t) && !defined(__DEFINED_imaxdiv_t)
# define __DEFINED_imaxdiv_t
typedef struct {
  /**
   * Quotient.
   */
  intmax_t quot;
  
  /**
   * Remainder.
   */
  intmax_t rem;
  
} imaxdiv_t;
#endif


/**
 * Locale datatype.
 * 
 * @since  Always.
 */
#if defined(__NEED_locale_t) && !defined(__DEFINED_locale_t)
# define __DEFINED_locale_t
typedef int locale_t; /* TODO not implemented */
#endif
#ifndef __INTMAX_MAX
# define __INTMAX_MAX  INT64_MAX
#endif


/**
 * State of variadic argument-reading.
 * 
 * @since  Always.
 */
#define __ONLY_va_list
# include <stdarg.h>
#undef __ONLY_va_list


/**
 * Datatype for file permissions and file type.
 * 
 * @since  Always.
 */
#if defined(__NEED_mode_t) && !defined(__DEFINED_mode_t)
# define __DEFINED_mode_t
typedef unsigned int mode_t;
#endif


/**
 * Datatype for process identifiers.
 * 
 * @since  Always.
 */
#if defined(__NEED_pid_t) && !defined(__DEFINED_pid_t)
# define __DEFINED_pid_t
typedef signed int pid_t;
#endif


/**
 * Datatype for user identifiers.
 * 
 * @since  Always.
 */
#if defined(__NEED_uid_t) && !defined(__DEFINED_uid_t)
# define __DEFINED_uid_t
typedef unsigned int uid_t;
#endif


/**
 * Datatype for group identifiers.
 * 
 * @since  Always.
 */
#if defined(__NEED_gid_t) && !defined(__DEFINED_gid_t)
# define __DEFINED_gid_t
typedef unsigned int gid_t;
#endif


/**
 * Datatype for microseconds.
 * (The name should be 'µseconds', but we are limited
 * to ASCII and 'u' looks similar to 'µ'.)
 * 
 * @since  Always.
 */
#if defined(__NEED_useconds_t) && !defined(__DEFINED_useconds_t)
# define __DEFINED_useconds_t
typedef signed long useconds_t;
#endif


/**
 * Datatype for file offsets.
 * 
 * @since  Always.
 */
#if defined(__NEED_off_t) && !defined(__DEFINED_off_t)
# define __DEFINED_off_t
typedef signed __INT64 off_t;
#endif


/**
 * Datatype for inode identifiers, the number identifying
 * a file on a filesystem.
 * ('inode' is probably a contraction of 'index node'.)
 * 
 * @since  Always.
 */
#if defined(__NEED_ino_t) && !defined(__DEFINED_ino_t)
# define __DEFINED_ino_t
typedef unsigned __INT64 ino_t;
#endif


/**
 * Datatype for device identifiers.
 * 
 * @since  Always.
 */
#if defined(__NEED_dev_t) && !defined(__DEFINED_dev_t)
# define __DEFINED_dev_t
typedef unsigned __INT64 dev_t;
#endif


/**
 * Datatype for filesystem block counts.
 * 
 * @since  Always.
 */
#if defined(__NEED_fsblkcnt_t) && !defined(__DEFINED_fsblkcnt_t)
# define __DEFINED_fsblkcnt_t
typedef unsigned __INT64 fsblkcnt_t;
#endif


/**
 * Datatype for filesystem file counts.
 * 
 * @since  Always.
 */
#if defined(__NEED_fsfilcnt_t) && !defined(__DEFINED_fsfilcnt_t)
# define __DEFINED_fsfilcnt_t
typedef unsigned __INT64 fsfilcnt_t;
#endif


/**
 * Datatype for block sizes.
 * 
 * @since  Always.
 */
#if defined(__NEED_blksize_t) && !defined(__DEFINED_blksize_t)
# define __DEFINED_blksize_t
typedef signed __LIMITED_PTR_INT blksize_t;
#endif


/**
 * Datatype for block counts.
 * 
 * @since  Always.
 */
#if defined(__NEED_blkcnt_t) && !defined(__DEFINED_blkcnt_t)
# define __DEFINED_blkcnt_t
typedef signed __INT64 blkcnt_t;
#endif


/* pid_t and suseconds_t may not exceed long int */

