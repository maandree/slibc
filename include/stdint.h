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
#ifndef _STDINT_H
#define _STDINT_H
#include <slibc/version.h>
#include <slibc/features.h>



#if defined(__C99__)
# define __NEED_intN_t
# define __NEED_uintN_t
# define __NEED_int_leastN_t
# define __NEED_uint_leastN_t
# define __NEED_int_fastN_t
# define __NEED_uint_fastN_t
# define __NEED_intptr_t
# define __NEED_uintptr_t
# define __NEED_intmax_t
# define __NEED_uintmax_t
#endif
#include <bits/types.h>



#if defined(__C99__)
/**
 * Macro that ensure that a signed numeral literal
 * of at most 8 encoding bits does not overflow.
 * 
 * @since  Always.
 */
# define  INT8_C(value)   value

/**
 * Macro that ensure that an unsigned numeral literal
 * of at most 8 encoding bits does not overflow.
 * 
 * @since  Always.
 */
# define  UINT8_C(value)  value


/**
 * Macro that ensure that a signed numeral literal
 * of at most 16 encoding bits does not overflow.
 * 
 * @since  Always.
 */
# define  INT16_C(value)   value

/**
 * Macro that ensure that an unsigned numeral literal
 * of at most 16 encoding bits does not overflow.
 * 
 * @since  Always.
 */
# define  UINT16_C(value)  value ## U


/**
 * Macro that ensure that a signed numeral literal
 * of at most 32 encoding bits does not overflow.
 * 
 * @since  Always.
 */
# if __INT_BIT == 16
#  define  INT32_C(value)   value ## L
# else
#  define  INT32_C(value)   value
# endif

/**
 * Macro that ensure that an unsigned numeral literal
 * of at most 32 encoding bits does not overflow.
 * 
 * @since  Always.
 */
# if __INT_BIT == 16
#  define  UINT32_C(value)  value ## UL
# else
#  define  UINT32_C(value)  value ## U
# endif


/**
 * Macro that ensure that a signed numeral literal
 * of at most 64 encoding bits does not overflow.
 * 
 * @since  Always.
 */
# if __LONG_BIT == 32
#  define  INT64_C(value)   value ## LL
# else
#  define  INT64_C(value)   value ## L
# endif

/**
 * Macro that ensure that an unsigned numeral literal
 * of at most 64 encoding bits does not overflow.
 * 
 * @since  Always.
 */
# if __LONG_BIT == 32
#  define  UINT64_C(value)  value ## ULL
# else
#  define  UINT64_C(value)  value ## UL
# endif


/**
 * Macro that ensure that any signed numeral literal
 * does not overflow, unless there is no scalar integer
 * type that can hold it.
 * 
 * @since  Always.
 */
# if __LONG_BIT == __LONG_LONG_BIT
#  define  INTMAX_C(value)   value ## L
# else
#  define  INTMAX_C(value)   value ## LL
# endif

/**
 * Macro that ensure that any unsigned numeral literal
 * does not overflow, unless there is no scalar integer
 * type that can hold it.
 * 
 * @since  Always.
 */
# if __LONG_BIT == __LONG_LONG_BIT
#  define  UINTMAX_C(value)   value ## UL
# else
#  define  UINTMAX_C(value)   value ## ULL
# endif



/**
 * Maximum value of `uint8_t`.
 * 
 * @since  Always.
 */
# define UINT8_MAX  (UINT8_C(0xFF))

/**
 * Maximum value of `int8_t`.
 * 
 * @since  Always.
 */
# define INT8_MAX  (INT8_C(0x7F))

/**
 * Minimum value of `int8_t`.
 * 
 * @since  Always.
 */
# define INT8_MIN  (-(INT8_MAX) - 1)


/**
 * Maximum value of `uint16_t`.
 * 
 * @since  Always.
 */
# define UINT16_MAX  (UINT16_C(0xFFFF))

/**
 * Maximum value of `int16_t`.
 * 
 * @since  Always.
 */
# define INT16_MAX  (INT16_C(0x7FFF))

/**
 * Minimum value of `int16_t`.
 * 
 * @since  Always.
 */
# define INT16_MIN  (-(INT16_MAX) - 1)


/**
 * Maximum value of `uint32_t`.
 * 
 * @since  Always.
 */
# define UINT32_MAX  (UINT32_C(0xFFFFFFFF))

/**
 * Maximum value of `int32_t`.
 * 
 * @since  Always.
 */
# define INT32_MAX  (INT32_C(0x7FFFFFFF))

/**
 * Minimum value of `int32_t`.
 * 
 * @since  Always.
 */
# define INT32_MIN  (-(INT32_MAX) - 1)


/**
 * Maximum value of `uint64_t`.
 * 
 * @since  Always.
 */
# define UINT64_MAX  (UINT64_C(0xFFFFFFFFFFFFFFFF))

/**
 * Maximum value of `int64_t`.
 * 
 * @since  Always.
 */
# define INT64_MAX  (INT64_C(0x7FFFFFFFFFFFFFFF))

/**
 * Minimum value of `int64_t`.
 * 
 * @since  Always.
 */
# define INT64_MIN  (-(INT64_MAX) - 1)


/**
 * Maximum value of `uint_least8_t`.
 * 
 * @since  Always.
 */
# define UINT_LEAST8_MAX  UINT8_MAX

/**
 * Maximum value of `int_least8_t`.
 * 
 * @since  Always.
 */
# define INT_LEAST8_MAX  INT8_MAX

/**
 * Minimum value of `int_least8_t`.
 * 
 * @since  Always.
 */
# define INT_LEAST8_MIN  (__MAX_TO_MIN(INT_LEAST8_MAX))


/**
 * Maximum value of `uint_least16_t`.
 * 
 * @since  Always.
 */
# define UINT_LEAST16_MAX  UINT16_MAX

/**
 * Maximum value of `int_least16_t`.
 * 
 * @since  Always.
 */
# define INT_LEAST16_MAX  INT16_MAX

/**
 * Minimum value of `int_least16_t`.
 * 
 * @since  Always.
 */
# define INT_LEAST16_MIN  (__MAX_TO_MIN(INT_LEAST16_MAX))


/**
 * Maximum value of `uint_least32_t`.
 * 
 * @since  Always.
 */
# define UINT_LEAST32_MAX  UINT32_MAX

/**
 * Maximum value of `int_least32_t`.
 * 
 * @since  Always.
 */
# define INT_LEAST32_MAX  INT32_MAX

/**
 * Minimum value of `int_least32_t`.
 * 
 * @since  Always.
 */
# define INT_LEAST32_MIN  (__MAX_TO_MIN(INT_LEAST32_MAX))


/**
 * Maximum value of `uint_least64_t`.
 * 
 * @since  Always.
 */
# define UINT_LEAST64_MAX  UINT64_MAX

/**
 * Maximum value of `int_least64_t`.
 * 
 * @since  Always.
 */
# define INT_LEAST64_MAX  INT64_MAX

/**
 * Minimum value of `int_least64_t`.
 * 
 * @since  Always.
 */
# define INT_LEAST64_MIN  (__MAX_TO_MIN(INT_LEAST64_MAX))


/**
 * Maximum value of `uint_fast8_t`.
 * 
 * @since  Always.
 */
# define UINT_FAST8_MAX  __UINT_FAST8_MAX

/**
 * Maximum value of `int_fast8_t`.
 * 
 * @since  Always.
 */
# define INT_FAST8_MAX  __INT_FAST8_MAX

/**
 * Minimum value of `int_fast8_t`.
 * 
 * @since  Always.
 */
# define INT_FAST8_MIN  (__MAX_TO_MIN(INT_FAST8_MAX))


/**
 * Maximum value of `uint_fast16_t`.
 * 
 * @since  Always.
 */
# define UINT_FAST16_MAX  __UINT_FAST16_MAX

/**
 * Maximum value of `int_fast16_t`.
 * 
 * @since  Always.
 */
# define INT_FAST16_MAX  __INT_FAST16_MAX

/**
 * Minimum value of `int_fast16_t`.
 * 
 * @since  Always.
 */
# define INT_FAST16_MIN  (__MAX_TO_MIN(INT_FAST16_MAX))


/**
 * Maximum value of `uint_fast32_t`.
 * 
 * @since  Always.
 */
# define UINT_FAST32_MAX  __UINT_FAST32_MAX

/**
 * Maximum value of `int_fast32_t`.
 * 
 * @since  Always.
 */
# define INT_FAST32_MAX  __INT_FAST32_MAX

/**
 * Minimum value of `int_fast32_t`.
 * 
 * @since  Always.
 */
# define INT_FAST32_MIN  (__MAX_TO_MIN(INT_FAST32_MAX))


/**
 * Maximum value of `uint_fast64_t`.
 * 
 * @since  Always.
 */
# define UINT_FAST64_MAX  __UINT_FAST64_MAX

/**
 * Maximum value of `int_fast64_t`.
 * 
 * @since  Always.
 */
# define INT_FAST64_MAX  __INT_FAST64_MAX

/**
 * Minimum value of `int_fast64_t`.
 * 
 * @since  Always.
 */
# define INT_FAST64_MIN  (__MAX_TO_MIN(INT_FAST64_MAX))


/**
 * Maximum value of `uintmax_t`.
 * 
 * @since  Always.
 */
# define UINTMAX_MAX  __UINTMAX_MAX

/**
 * Maximum value of `intmax_t`.
 * 
 * @since  Always.
 */
# define INTMAX_MAX  __INTMAX_MAX

/**
 * Minimum value of `intmax_t`.
 * 
 * @since  Always.
 */
# define INTMAX_MIN  (__MAX_TO_MIN(INTMAX_MIN))


/**
 * Maximum value of `uintptr_t`.
 * 
 * @since  Always.
 */
# if __PTR_BIT == 8
#  define UINTPTR_MAX  UINT8_MAX
# elif __PTR_BIT == 16
#  define UINTPTR_MAX  UINT16_MAX
# elif __PTR_BIT == 32
#  define UINTPTR_MAX  UINT32_MAX
# else
#  define UINTPTR_MAX  UINT64_MAX
# endif

/**
 * Maximum value of `intptr_t`.
 * 
 * @since  Always.
 */
# if __PTR_BIT == 8
#  define INTPTR_MAX  INT8_MAX
# elif __PTR_BIT == 16
#  define INTPTR_MAX  INT16_MAX
# elif __PTR_BIT == 32
#  define INTPTR_MAX  INT32_MAX
# else
#  define INTPTR_MAX  INT64_MAX
# endif

/**
 * Minimum value of `intptr_t`.
 * 
 * @since  Always.
 */
# define INTPTR_MIN  (__MAX_TO_MIN(INTPTR_MAX))
#endif


/**
 * Maximum value of `size_t`.
 * 
 * @since  Always.
 */
#define SIZE_MAX  UINTPTR_MAX

/**
 * Maximum value of `ssize_t`.
 * 
 * @since  Always.
 */
#define SSIZE_MAX  INTPTR_MAX

/**
 * Minimum value of `ssize_t`.
 * 
 * @since  Always.
 */
#define SSIZE_MIN  INTPTR_MIN


#ifndef __PORTABLE
/**
 * Maximum value of `wchar_t`.
 * 
 * @since  Always.
 */
# define WCHAR_MAX  __WCHAR_MAX

/**
 * Minimum value of `wchar_t`.
 * 
 * @since  Always.
 */
# define WCHAR_MIN  (__MAX_TO_MIN(WCHAR_MAX))


/**
 * Maximum value of `wint_t`.
 * 
 * @since  Always.
 */
# define WINT_MAX  WCHAR_MAX

/**
 * Minimum value of `wint_t`.
 * 
 * @since  Always.
 */
# define WINT_MIN  WCHAR_MIN
#endif


/**
 * Maximum value of `sig_atomic_t`.
 * 
 * @since  Always.
 */
#if __SIG_ATOMIC_BIT == 8
# define SIG_ATOMIC_MAX  INT8_MAX
#elif __SIG_ATOMIC_BIT == 16
# define SIG_ATOMIC_MAX  INT16_MAX
#elif __SIG_ATOMIC_BIT == 32
# define SIG_ATOMIC_MAX  INT32_MAX
#else
# define SIG_ATOMIC_MAX  INT64_MAX
#endif

/**
 * Minimum value of `sig_atomic_t`.
 * 
 * @since  Always.
 */
#define SIG_ATOMIC_MIN  (__MAX_TO_MIN(__SIG_ATOMIC_MAX))



#endif

