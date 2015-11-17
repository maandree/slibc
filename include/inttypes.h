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
#ifndef _STDLIB_H
#define _STDLIB_H
#include <slibc/version.h>
#include <slibc/features.h>


#include <stdint.h>
#include <bits/intconf.h>



#define __NEED_intmax_t
#define __NEED_imaxdiv_t
#define __NEED_wchar_t

#include <bits/types.h>


/**
 * Perform an integer division and return
 * both the quotient and the remainder.
 * 
 * @param   numerator    The numerator.
 * @param   denominator  The denominator, must not be 0 lest
 *                       the process will be killed by SIGFPE.
 * @return               The quotient in `.quot`, and
 *                       the remainder in `.rem`.
 */
imaxdiv_t imaxdiv(intmax_t, intmax_t)
  __GCC_ONLY(__attribute__((__const__)));

/**
 * Return the absolute value of an integer.
 * 
 * Be aware, if the value is `INTMAX_MIN` and
 * `-INTMAX_MAX != -INTMAX_MIN`, the result will
 * overflow, and `INTMAX_MIN` will (probably)
 * be returned.
 * 
 * @param   value  The integer.
 * @return         The absolute value of the integer.
 */
intmax_t (imaxabs)(intmax_t)
  __GCC_ONLY(__attribute__((__const__)));
#define imaxabs(value)  ((intmax_t)value < 0 ? -(intmax_t)value : (intmax_t)value)



/* Printing and scanning code affixes. */

/**
 * Length modifier affix for printing an `int8_t` or an `uint8_t`.
 * For internal use, not libc-portable.
 */
#define __PRI8  ""

/**
 * Length modifier affix for scanning an `int8_t` or an `uint8_t`.
 * For internal use, not libc-portable.
 */
#define __SCN8  "hh"


/**
 * Length modifier affix for printing an `int16_t` or an `uint16_t`.
 * For internal use, not libc-portable.
 */
#define __PRI16  ""

/**
 * Length modifier affix for scanning an `int16_t` or an `uint16_t`.
 * For internal use, not libc-portable.
 */
#define __SCN16  "h"


#if __INT_BIT == 32
/**
 * Length modifier affix for printing an `int32_t` or an `uint32_t`.
 * For internal use, not libc-portable.
 */
# define __PRI32  ""

/**
 * Length modifier affix for scanning an `int32_t` or an `uint32_t`.
 * For internal use, not libc-portable.
 */
# define __SCN32  ""
#else
# define __PRI32  "l"
# define __SCN32  "l"
#endif


#if __LONG_BIT == 64
/**
 * Length modifier affix for printing an `int64_t` or an `uint64_t`.
 * For internal use, not libc-portable.
 */
# define __PRI64  "l"

/**
 * Length modifier affix for scanning an `int64_t` or an `uint64_t`.
 * For internal use, not libc-portable.
 */
# define __SCN64  "l"
#else
# define __PRI64  "ll"
# define __SCN64  "ll"
#endif


/**
 * Length modifier affix for printing an `intmax_t` or an `uintmax_t`.
 * For internal use, not libc-portable.
 */
#define __PRIMAX  "j"

/**
 * Length modifier affix for scanning an `intmax_t` or an `uintmax_t`.
 * For internal use, not libc-portable.
 */
#define __SCNMAX  "j"


#if __PTR_BIT == 8
/**
 * Length modifier affix for printing an `intptr_t`, an `uintptr_t`,
 * a `ptrdiff_t`, an `uptrdiff_t`, an `ssize_t, or a `size_t`.
 * For internal use, not libc-portable.
 */
# define __PRIPTR  __PRI8

/**
 * Length modifier affix for scanning an `intptr_t`, an `uintptr_t`,
 * a `ptrdiff_t`, an `uptrdiff_t`, an `ssize_t, or a `size_t`.
 * For internal use, not libc-portable.
 */
# define __SCNPTR  __SCN8
#elif __PTR_BIT == 16
# define __PRIPTR  __PRI16
# define __SCNPTR  __SCN16
#elif __PTR_BIT == 32
# define __PRIPTR  __PRI32
# define __SCNPTR  __SCN32
#elif __PTR_BIT == 64
# define __PRIPTR  __PRI64
# define __SCNPTR  __SCN64
#endif



/* Printing codes. */


/**
 * %-code, excluding the %, for printing
 * an int8_t in decimal form.
 */
#define PRId8  __PRI8 "d"

/**
 * %-code, excluding the %, for printing
 * an int16_t in decimal form.
 */
#define PRId16  __PRI16 "d"

/**
 * %-code, excluding the %, for printing
 * an int32_t in decimal form.
 */
#define PRId32  __PRI32 "d"

/**
 * %-code, excluding the %, for printing
 * an int64_t in decimal form.
 */
#define PRId64  __PRI64 "d"


/**
 * %-code, excluding the %, for printing
 * an int_least8_t in decimal form.
 */
#define PRIdLEAST8  PRId8

/**
 * %-code, excluding the %, for printing
 * an int_least16_t in decimal form.
 */
#define PRIdLEAST16  PRId16

/**
 * %-code, excluding the %, for printing
 * an int_least32_t in decimal form.
 */
#define PRIdLEAST32  PRId32

/**
 * %-code, excluding the %, for printing
 * an int_least64_t in decimal form.
 */
#define PRIdLEAST64  PRId64


/**
 * %-code, excluding the %, for printing
 * an int_fast8_t in decimal form.
 */
#define PRIdFAST8  __PRIFAST8 "d"

/**
 * %-code, excluding the %, for printing
 * an int_fast16_t in decimal form.
 */
#define PRIdFAST16  __PRIFAST16 "d"

/**
 * %-code, excluding the %, for printing
 * an int_fast32_t in decimal form.
 */
#define PRIdFAST32  __PRIFAST32 "d"

/**
 * %-code, excluding the %, for printing
 * an int_fast64_t in decimal form.
 */
#define PRIdFAST64  __PRIFAST64 "d"



/**
 * %-code, excluding the %, for printing
 * an int8_t in decimal form.
 */
#define PRIi8  __PRI8 "i"

/**
 * %-code, excluding the %, for printing
 * an int16_t in decimal form.
 */
#define PRIi16  __PRI16 "i"

/**
 * %-code, excluding the %, for printing
 * an int32_t in decimal form.
 */
#define PRIi32  __PRI32 "i"

/**
 * %-code, excluding the %, for printing
 * an int64_t in decimal form.
 */
#define PRIi64  __PRI64 "i"


/**
 * %-code, excluding the %, for printing
 * an int_least8_t in decimal form.
 */
#define PRIiLEAST8  PRIi8

/**
 * %-code, excluding the %, for printing
 * an int_least16_t in decimal form.
 */
#define PRIiLEAST16  PRIi16

/**
 * %-code, excluding the %, for printing
 * an int_least32_t in decimal form.
 */
#define PRIiLEAST32  PRIi32

/**
 * %-code, excluding the %, for printing
 * an int_least64_t in decimal form.
 */
#define PRIiLEAST64  PRIi64


/**
 * %-code, excluding the %, for printing
 * an int_fast8_t in decimal form.
 */
#define PRIiFAST8  __PRIFAST8 "i"

/**
 * %-code, excluding the %, for printing
 * an int_fast16_t in decimal form.
 */
#define PRIiFAST16  __PRIFAST16 "i"

/**
 * %-code, excluding the %, for printing
 * an int_fast32_t in decimal form.
 */
#define PRIiFAST32  __PRIFAST32 "i"

/**
 * %-code, excluding the %, for printing
 * an int_fast64_t in decimal form.
 */
#define PRIiFAST64  __PRIFAST64 "i"



/**
 * %-code, excluding the %, for printing
 * an uint8_t in octal form.
 */
#define PRIo8  __PRI8 "o"

/**
 * %-code, excluding the %, for printing
 * an uint16_t in octal form.
 */
#define PRIo16  __PRI16 "o"

/**
 * %-code, excluding the %, for printing
 * an uint32_t in octal form.
 */
#define PRIo32  __PRI32 "o"

/**
 * %-code, excluding the %, for printing
 * an uint64_t in octal form.
 */
#define PRIo64  __PRI64 "o"


/**
 * %-code, excluding the %, for printing
 * an uint_least8_t in octal form.
 */
#define PRIoLEAST8  PRIo8

/**
 * %-code, excluding the %, for printing
 * an uint_least16_t in octal form.
 */
#define PRIoLEAST16  PRIo16

/**
 * %-code, excluding the %, for printing
 * an uint_least32_t in octal form.
 */
#define PRIoLEAST32  PRIo32

/**
 * %-code, excluding the %, for printing
 * an uint_least64_t in octal form.
 */
#define PRIoLEAST64  PRIo64


/**
 * %-code, excluding the %, for printing
 * an uint_fast8_t in octal form.
 */
#define PRIoFAST8  __PRIFAST8 "o"

/**
 * %-code, excluding the %, for printing
 * an uint_fast16_t in octal form.
 */
#define PRIoFAST16  __PRIFAST16 "o"

/**
 * %-code, excluding the %, for printing
 * an uint_fast32_t in octal form.
 */
#define PRIoFAST32  __PRIFAST32 "o"

/**
 * %-code, excluding the %, for printing
 * an uint_fast64_t in octal form.
 */
#define PRIoFAST64  __PRIFAST64 "o"



/**
 * %-code, excluding the %, for printing
 * an uint8_t in decimal form.
 */
#define PRIu8  __PRI8 "u"

/**
 * %-code, excluding the %, for printing
 * an uint16_t in decimal form.
 */
#define PRIu16  __PRI16 "u"

/**
 * %-code, excluding the %, for printing
 * an uint32_t in decimal form.
 */
#define PRIu32  __PRI32 "u"

/**
 * %-code, excluding the %, for printing
 * an uint64_t in decimal form.
 */
#define PRIu64  __PRI64 "u"


/**
 * %-code, excluding the %, for printing
 * an uint_least8_t in decimal form.
 */
#define PRIuLEAST8  PRIu8

/**
 * %-code, excluding the %, for printing
 * an uint_least16_t in decimal form.
 */
#define PRIuLEAST16  PRIu16

/**
 * %-code, excluding the %, for printing
 * an uint_least32_t in decimal form.
 */
#define PRIuLEAST32  PRIu32

/**
 * %-code, excluding the %, for printing
 * an uint_least64_t in decimal form.
 */
#define PRIuLEAST64  PRIu64


/**
 * %-code, excluding the %, for printing
 * an uint_fast8_t in decimal form.
 */
#define PRIuFAST8  __PRIFAST8 "u"

/**
 * %-code, excluding the %, for printing
 * an uint_fast16_t in decimal form.
 */
#define PRIuFAST16  __PRIFAST16 "u"

/**
 * %-code, excluding the %, for printing
 * an uint_fast32_t in decimal form.
 */
#define PRIuFAST32  __PRIFAST32 "u"

/**
 * %-code, excluding the %, for printing
 * an uint_fast64_t in decimal form.
 */
#define PRIuFAST64  __PRIFAST64 "u"



/**
 * %-code, excluding the %, for printing an
 * uint8_t in lowercase hexadecimal form.
 */
#define PRIx8  __PRI8 "x"

/**
 * %-code, excluding the %, for printing an
 * uint16_t in lowercase hexadecimal form.
 */
#define PRIx16  __PRI16 "x"

/**
 * %-code, excluding the %, for printing an
 * uint32_t in lowercase hexadecimal form.
 */
#define PRIx32  __PRI32 "x"

/**
 * %-code, excluding the %, for printing an
 * uint64_t in lowercase hexadecimal form.
 */
#define PRIx64  __PRI64 "x"


/**
 * %-code, excluding the %, for printing an
 * uint_least8_t in lowercase hexadecimal form.
 */
#define PRIxLEAST8  PRIx8

/**
 * %-code, excluding the %, for printing an
 * uint_least16_t in lowercase hexadecimal form.
 */
#define PRIxLEAST16  PRIx16

/**
 * %-code, excluding the %, for printing an
 * uint_least32_t in lowercase hexadecimal form.
 */
#define PRIxLEAST32  PRIx32

/**
 * %-code, excluding the %, for printing an
 * uint_least64_t in lowercase hexadecimal form.
 */
#define PRIxLEAST64  PRIx64


/**
 * %-code, excluding the %, for printing an
 * uint_fast8_t in lowercase hexadecimal form.
 */
#define PRIxFAST8  __PRIFAST8 "x"

/**
 * %-code, excluding the %, for printing an
 * uint_fast16_t in lowercase hexadecimal form.
 */
#define PRIxFAST16  __PRIFAST16 "x"

/**
 * %-code, excluding the %, for printing an
 * uint_fast32_t in lowercase hexadecimal form.
 */
#define PRIxFAST32  __PRIFAST32 "x"

/**
 * %-code, excluding the %, for printing an
 * uint_fast64_t in lowercase hexadecimal form.
 */
#define PRIxFAST64  __PRIFAST64 "x"



/**
 * %-code, excluding the %, for printing an
 * uint8_t in uppercase hexadecimal form.
 */
#define PRIX8  __PRI8 "X"

/**
 * %-code, excluding the %, for printing an
 * uint16_t in uppercase hexadecimal form.
 */
#define PRIX16  __PRI16 "X"

/**
 * %-code, excluding the %, for printing an
 * uint32_t in uppercase hexadecimal form.
 */
#define PRIX32  __PRI32 "X"

/**
 * %-code, excluding the %, for printing an
 * uint64_t in uppercase hexadecimal form.
 */
#define PRIX64  __PRI64 "X"


/**
 * %-code, excluding the %, for printing an
 * uint_least8_t in uppercase hexadecimal form.
 */
#define PRIXLEAST8  PRIX8

/**
 * %-code, excluding the %, for printing an
 * uint_least16_t in uppercase hexadecimal form.
 */
#define PRIXLEAST16  PRIX16

/**
 * %-code, excluding the %, for printing an
 * uint_least32_t in uppercase hexadecimal form.
 */
#define PRIXLEAST32  PRIX32

/**
 * %-code, excluding the %, for printing an
 * uint_least64_t in uppercase hexadecimal form.
 */
#define PRIXLEAST64  PRIX64


/**
 * %-code, excluding the %, for printing an
 * uint_fast8_t in uppercase hexadecimal form.
 */
#define PRIXFAST8  __PRIFAST8 "X"

/**
 * %-code, excluding the %, for printing an
 * uint_fast16_t in uppercase hexadecimal form.
 */
#define PRIXFAST16  __PRIFAST16 "X"

/**
 * %-code, excluding the %, for printing an
 * uint_fast32_t in uppercase hexadecimal form.
 */
#define PRIXFAST32  __PRIFAST32 "X"

/**
 * %-code, excluding the %, for printing an
 * uint_fast64_t in uppercase hexadecimal form.
 */
#define PRIXFAST64  __PRIFAST64 "X"



/**
 * %-code, excluding the %, for printing an
 * intmax_t in decimal form.
 */
#define PRIdMAX __PRIMAX "d"

/**
 * %-code, excluding the %, for printing an
 * intmax_t in decimal form.
 */
#define PRIiMAX __PRIMAX "i"

/**
 * %-code, excluding the %, for printing an
 * uintmax_t in octal form.
 */
#define PRIoMAX __PRIMAX "o"

/**
 * %-code, excluding the %, for printing an
 * uintmax_t in decimal form.
 */
#define PRIuMAX __PRIMAX "u"

/**
 * %-code, excluding the %, for printing an
 * uintmax_t in lowercase hexadecimal form.
 */
#define PRIxMAX __PRIMAX "x"

/**
 * %-code, excluding the %, for printing an
 * uintmax_t in uppercase hexadecimal form.
 */
#define PRIXMAX __PRIMAX "X"



/**
 * %-code, excluding the %, for printing
 * an intptr_t, ptrdiff_t, or ssize_t
 * in decimal form.
 */
#define PRIdPTR __PRIPTR "d"

/**
 * %-code, excluding the %, for printing
 * an intptr_t, ptrdiff_t, or ssize_t
 * in decimal form.
 */
#define PRIiPTR __PRIPTR "i"

/**
 * %-code, excluding the %, for printing
 * an uintptr_t, uptrdiff_t, or size_t
 * in octal form.
 */
#define PRIoPTR __PRIPTR "o"

/**
 * %-code, excluding the %, for printing
 * an uintptr_t, uptrdiff_t, or size_t
 * in decimal form.
 */
#define PRIuPTR __PRIPTR "u"

/**
 * %-code, excluding the %, for printing
 * an uintptr_t, uptrdiff_t, or size_t
 * in lowercase hexadecimal form.
 */
#define PRIxPTR __PRIPTR "x"

/**
 * %-code, excluding the %, for printing
 * an uintptr_t, uptrdiff_t, or size_t
 * in uppercase hexadecimal form.
 */
#define PRIXPTR __PRIPTR "X"



/* Scanning codes. */


/**
 * %-code, excluding the %, for scanning
 * an int8_t from decimal form.
 */
#define SCNd8  __SCN8 "d"

/**
 * %-code, excluding the %, for scanning
 * an int16_t from decimal form.
 */
#define SCNd16  __SCN16 "d"

/**
 * %-code, excluding the %, for scanning
 * an int32_t from decimal form.
 */
#define SCNd32  __SCN32 "d"

/**
 * %-code, excluding the %, for scanning
 * an int64_t from decimal form.
 */
#define SCNd64  __SCN64 "d"


/**
 * %-code, excluding the %, for scanning
 * an int_least8_t from decimal form.
 */
#define SCNdLEAST8  SCNd8

/**
 * %-code, excluding the %, for scanning
 * an int_least16_t from decimal form.
 */
#define SCNdLEAST16  SCNd16

/**
 * %-code, excluding the %, for scanning
 * an int_least32_t from decimal form.
 */
#define SCNdLEAST32  SCNd32

/**
 * %-code, excluding the %, for scanning
 * an int_least64_t from decimal form.
 */
#define SCNdLEAST64  SCNd64


/**
 * %-code, excluding the %, for scanning
 * an int_fast8_t from decimal form.
 */
#define SCNdFAST8  __SCNFAST8 "d"

/**
 * %-code, excluding the %, for scanning
 * an int_fast16_t from decimal form.
 */
#define SCNdFAST16  __SCNFAST16 "d"

/**
 * %-code, excluding the %, for scanning
 * an int_fast32_t from decimal form.
 */
#define SCNdFAST32  __SCNFAST32 "d"

/**
 * %-code, excluding the %, for scanning
 * an int_fast64_t from decimal form.
 */
#define SCNdFAST64  __SCNFAST64 "d"



/**
 * %-code, excluding the %, for scanning
 * an int8_t from decimal form.
 */
#define SCNi8  __SCN8 "i"

/**
 * %-code, excluding the %, for scanning
 * an int16_t from decimal form.
 */
#define SCNi16  __SCN16 "i"

/**
 * %-code, excluding the %, for scanning
 * an int32_t from decimal form.
 */
#define SCNi32  __SCN32 "i"

/**
 * %-code, excluding the %, for scanning
 * an int64_t from decimal form.
 */
#define SCNi64  __SCN64 "i"


/**
 * %-code, excluding the %, for scanning
 * an int_least8_t from decimal form.
 */
#define SCNiLEAST8  SCNi8

/**
 * %-code, excluding the %, for scanning
 * an int_least16_t from decimal form.
 */
#define SCNiLEAST16  SCNi16

/**
 * %-code, excluding the %, for scanning
 * an int_least32_t from decimal form.
 */
#define SCNiLEAST32  SCNi32

/**
 * %-code, excluding the %, for scanning
 * an int_least64_t from decimal form.
 */
#define SCNiLEAST64  SCNi64


/**
 * %-code, excluding the %, for scanning
 * an int_fast8_t from decimal form.
 */
#define SCNiFAST8  __SCNFAST8 "i"

/**
 * %-code, excluding the %, for scanning
 * an int_fast16_t from decimal form.
 */
#define SCNiFAST16  __SCNFAST16 "i"

/**
 * %-code, excluding the %, for scanning
 * an int_fast32_t from decimal form.
 */
#define SCNiFAST32  __SCNFAST32 "i"

/**
 * %-code, excluding the %, for scanning
 * an int_fast64_t from decimal form.
 */
#define SCNiFAST64  __SCNFAST64 "i"



/**
 * %-code, excluding the %, for scanning
 * an uint8_t from octal form.
 */
#define SCNo8  __SCN8 "o"

/**
 * %-code, excluding the %, for scanning
 * an uint16_t from octal form.
 */
#define SCNo16  __SCN16 "o"

/**
 * %-code, excluding the %, for scanning
 * an uint32_t from octal form.
 */
#define SCNo32  __SCN32 "o"

/**
 * %-code, excluding the %, for scanning
 * an uint64_t from octal form.
 */
#define SCNo64  __SCN64 "o"


/**
 * %-code, excluding the %, for scanning
 * an uint_least8_t from octal form.
 */
#define SCNoLEAST8  SCNo8

/**
 * %-code, excluding the %, for scanning
 * an uint_least16_t from octal form.
 */
#define SCNoLEAST16  SCNo16

/**
 * %-code, excluding the %, for scanning
 * an uint_least32_t from octal form.
 */
#define SCNoLEAST32  SCNo32

/**
 * %-code, excluding the %, for scanning
 * an uint_least64_t from octal form.
 */
#define SCNoLEAST64  SCNo64


/**
 * %-code, excluding the %, for scanning
 * an uint_fast8_t from octal form.
 */
#define SCNoFAST8  __SCNFAST8 "o"

/**
 * %-code, excluding the %, for scanning
 * an uint_fast16_t from octal form.
 */
#define SCNoFAST16  __SCNFAST16 "o"

/**
 * %-code, excluding the %, for scanning
 * an uint_fast32_t from octal form.
 */
#define SCNoFAST32  __SCNFAST32 "o"

/**
 * %-code, excluding the %, for scanning
 * an uint_fast64_t from octal form.
 */
#define SCNoFAST64  __SCNFAST64 "o"



/**
 * %-code, excluding the %, for scanning
 * an uint8_t from decimal form.
 */
#define SCNu8  __SCN8 "u"

/**
 * %-code, excluding the %, for scanning
 * an uint16_t from decimal form.
 */
#define SCNu16  __SCN16 "u"

/**
 * %-code, excluding the %, for scanning
 * an uint32_t from decimal form.
 */
#define SCNu32  __SCN32 "u"

/**
 * %-code, excluding the %, for scanning
 * an uint64_t from decimal form.
 */
#define SCNu64  __SCN64 "u"


/**
 * %-code, excluding the %, for scanning
 * an uint_least8_t from decimal form.
 */
#define SCNuLEAST8  SCNu8

/**
 * %-code, excluding the %, for scanning
 * an uint_least16_t from decimal form.
 */
#define SCNuLEAST16  SCNu16

/**
 * %-code, excluding the %, for scanning
 * an uint_least32_t from decimal form.
 */
#define SCNuLEAST32  SCNu32

/**
 * %-code, excluding the %, for scanning
 * an uint_least64_t from decimal form.
 */
#define SCNuLEAST64  SCNu64


/**
 * %-code, excluding the %, for scanning
 * an uint_fast8_t from decimal form.
 */
#define SCNuFAST8  __SCNFAST8 "u"

/**
 * %-code, excluding the %, for scanning
 * an uint_fast16_t from decimal form.
 */
#define SCNuFAST16  __SCNFAST16 "u"

/**
 * %-code, excluding the %, for scanning
 * an uint_fast32_t from decimal form.
 */
#define SCNuFAST32  __SCNFAST32 "u"

/**
 * %-code, excluding the %, for scanning
 * an uint_fast64_t from decimal form.
 */
#define SCNuFAST64  __SCNFAST64 "u"



/**
 * %-code, excluding the %, for scanning an
 * uint8_t from hexadecimal form.
 */
#define SCNx8  __SCN8 "x"

/**
 * %-code, excluding the %, for scanning an
 * uint16_t from hexadecimal form.
 */
#define SCNx16  __SCN16 "x"

/**
 * %-code, excluding the %, for scanning an
 * uint32_t from hexadecimal form.
 */
#define SCNx32  __SCN32 "x"

/**
 * %-code, excluding the %, for scanning an
 * uint64_t from hexadecimal form.
 */
#define SCNx64  __SCN64 "x"


/**
 * %-code, excluding the %, for scanning an
 * uint_least8_t from hexadecimal form.
 */
#define SCNxLEAST8  SCNx8

/**
 * %-code, excluding the %, for scanning an
 * uint_least16_t from hexadecimal form.
 */
#define SCNxLEAST16  SCNx16

/**
 * %-code, excluding the %, for scanning an
 * uint_least32_t from hexadecimal form.
 */
#define SCNxLEAST32  SCNx32

/**
 * %-code, excluding the %, for scanning an
 * uint_least64_t from hexadecimal form.
 */
#define SCNxLEAST64  SCNx64


/**
 * %-code, excluding the %, for scanning an
 * uint_fast8_t from hexadecimal form.
 */
#define SCNxFAST8  __SCNFAST8 "x"

/**
 * %-code, excluding the %, for scanning an
 * uint_fast16_t from hexadecimal form.
 */
#define SCNxFAST16  __SCNFAST16 "x"

/**
 * %-code, excluding the %, for scanning an
 * uint_fast32_t from hexadecimal form.
 */
#define SCNxFAST32  __SCNFAST32 "x"

/**
 * %-code, excluding the %, for scanning an
 * uint_fast64_t from hexadecimal form.
 */
#define SCNxFAST64  __SCNFAST64 "x"



/**
 * %-code, excluding the %, for scanning an
 * intmax_t from decimal form.
 */
#define SCNdMAX __SCNMAX "d"

/**
 * %-code, excluding the %, for scanning an
 * intmax_t from decimal form.
 */
#define SCNiMAX __SCNMAX "i"

/**
 * %-code, excluding the %, for scanning an
 * uintmax_t from octal form.
 */
#define SCNoMAX __SCNMAX "o"

/**
 * %-code, excluding the %, for scanning an
 * uintmax_t from decimal form.
 */
#define SCNuMAX __SCNMAX "u"

/**
 * %-code, excluding the %, for scanning an
 * uintmax_t from hexadecimal form.
 */
#define SCNxMAX __SCNMAX "x"



/**
 * %-code, excluding the %, for scanning
 * an intptr_t, ptrdiff_t, or ssize_t
 * from decimal form.
 */
#define SCNdPTR __SCNPTR "d"

/**
 * %-code, excluding the %, for scanning
 * an intptr_t, ptrdiff_t, or ssize_t
 * from decimal form.
 */
#define SCNiPTR __SCNPTR "i"

/**
 * %-code, excluding the %, for scanning
 * an uintptr_t, uptrdiff_t, or size_t
 * from octal form.
 */
#define SCNoPTR __SCNPTR "o"

/**
 * %-code, excluding the %, for scanning
 * an uintptr_t, uptrdiff_t, or size_t
 * from decimal form.
 */
#define SCNuPTR __SCNPTR "u"

/**
 * %-code, excluding the %, for scanning
 * an uintptr_t, uptrdiff_t, or size_t
 * from hexadecimal form.
 */
#define SCNxPTR __SCNPTR "x"


#endif

