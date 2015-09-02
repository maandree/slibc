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
/* That's right. No inclusion-guard; we want multiple
 * headers to be able to define types by including this
 * header without the need of keeping in mind which
 * order headers are included. */
#include <slibc/features.h>


#include <bits/intconf.h>


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
 * Signed integer type of the result of subtracting two pointers.
 * May not be greater than the with of type long.
 */
#if defined(__NEED_ptrdiff_t) && !defined(__DEFINED_ptrdiff_t)
# define __DEFINED_ptrdiff_t
typedef signed long int ptrdiff_t;
#endif


/**
 * Unsigned version of `ptrdiff_t`
 */
#if defined(__NEED_uptrdiff_t) && !defined(__DEFINED_uptrdiff_t)
# define __DEFINED_uptrdiff_t
typedef unsigned long int uptrdiff_t;
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
 */
# if defined(__NEED_wchar_t) && !defined(__DEFINED_wchar_t)
#  define __DEFINED_wchar_t
typedef long int wchar_t
  __warning("'wchar_t' is not guaranteed to be defined as expected, use 'int32_t'.");
# endif
# ifndef __WCHAR_MAX
#  define  __WCHAR_MAX  INTPTR_MAX
# endif


/**
 * Variant of `wchar_t` that can hold the value of `WEOF`.
 * 
 * `wint_t` is not safe for data serialisation/marshalling;
 * it is implementation specific and may depend on the
 * libc implementation, the version of the libc implementation,
 * and the microarchitecture.
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
 * with of type long.
 */
#if defined(__NEED_size_t) && !defined(__DEFINED_size_t)
# define __DEFINED_size_t
typedef unsigned long int size_t;
#endif


/**
 * Signed version of `size_t`
 */
#if defined(__NEED_ssize_t) && !defined(__DEFINED_ssize_t)
# define __DEFINED_ssize_t
typedef signed long int ssize_t;
#endif


/**
 * A type, of unspecified construct, whose alignment requirement
 * is at least as strict as that of every scalar type.
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

