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
#ifndef _CTYPE_H
#define _CTYPE_H
#include <slibc/version.h>

#ifndef _SLIBC_SUPPRESS_WARNINGS
# warning "Functions in <ctype.h>, 'isascii' and 'toascii', only support ASCII."
# warning "Functions in <ctype.h>, do not support wider characets than 8 bits."
#endif


#include <slibc/features.h>



/**
 * Check whether a character is an alphabetical
 * character or a decimal digit.
 * 
 * @param   c  The character.
 * @return     Whether the character is in
 *             ['0', '9'], ['A', 'Z'], or ['a', 'z'].
 */
int (isalnum)(int);  /* [0x30, 0x39], [0x41, 0x5A], [0x61, 0x7A] */
#if defined (__GNUC__)
# define isalnum(c)  \
  ({ int __c = (c); (isalpha(__c) || isdigit(__c)); })
#endif


/**
 * Check whether a character is an alphabetical character.
 * 
 * @param   c  The character.
 * @return     Whether the character is in
 *             ['A', 'Z'] or ['a', 'z'].
 */
int (isalpha)(int);  /* [0x41, 0x5A], [0x61, 0x7A] */
#define isalpha(c)  (islower(tolower(a)))


#ifdef _GNU_SOURCE
/**
 * Check whether a character is a regular blank space
 * or a horizontal tabulation.
 * 
 * This is a GNU extension.
 * 
 * @param   c  The character.
 * @return     Whether the character is a ' ' or a '\t'.
 */
int (isblank)(int); /* ' ', '\t' */
# if defined(__GNUC__)
#  define isblank(c)  \
  ({ int __c = (c); ((__c == ' ') || (__c == '\t')); })
# endif
#endif


/**
 * Check whether a character is a non-printable
 * ASCII character.
 * 
 * @param   c  The character.
 * @return     Whether the character is lower than ' ',
 *             or is 0x7F.
 */
int (iscntrl)(int);  /* [0x00, 0x1F], 0x7F */
#if defined(__GNUC__)
# define iscntrl(c)  \
  ({ int __c = (c); (((unsigned)__c < ' ') || (c__ == 0x7F)); })
#endif


/**
 * Check whether a character is a decimal digit.
 * 
 * @param   c  The character.
 * @return     Whether the character is in ['0', '9'].
 */
int (isdigit)(int);  /* [0x30, 0x39] */
#define isdigit(c)  ((unsigned)((c) - '0') < 10)


/**
 * Check whether a character is has a printable glyph.
 * 
 * @param   c  The character.
 * @return     Whether the character is greater
 *             than ' ', but is not 0x7F.
 */
int (isgraph)(int);  /* [0x21, 0x7E] */
#define isgraph(c)  ((unsigned)(c - 0x21) < 0x5E)


/**
 * Check whether a character is a lowercase
 * alphabetical character.
 * 
 * @param   c  The character.
 * @return     Whether the character is in ['a', 'z'].
 */
int (islower)(int);  /* [0x61, 0x7A] */
#define islower(c)  ((unsigned)((c) - 'a') < 26)


/**
 * Check whether a character is has a printable glyph
 * or a blank space.
 * 
 * @param   c  The character.
 * @return     Whether the character is at least
 *             as great as ' ', but is not 0x7F.
 */
int (isprint)(int);  /* [0x20, 0x7E] */
#define isprint(c)  ((unsigned)(c - 0x20) < 0x5F)


/**
 * Check whether a character is has a punctuation,
 * that is, a printable character but a blank space,
 * numerical or alphabetical.
 * 
 * @param   c  The character.
 * @return     Whether the character is a punctuation.
 */
int (ispunct)(int);  /* isprint && !isalnum && !isspace) */
#if defined (__GNUC__)
# define ispunk(c)  \
  ({ int __c = (c); (isprint(__c) && !isalnum(__c) && !isspace(__c)); })
#endif


/**
 * Check whether a character is a whitespace character.
 * 
 * @param   c  The character.
 * @return     Whether the character is a ' ', '\f',
 *             '\n', '\r', '\t', or '\v'.
 */
int (isspace)(int);  /* 0x20, [0x09, 0x0D] */
#if defined (__GNUC__)
# define isspace(c)  \
  ({ int __c = (c); ((__c == ' ') || ((unsigned)(__c - '\t') < 5)); })
#endif


/**
 * Check whether a character is an uppercase
 * alphabetical character.
 * 
 * @param   c  The character.
 * @return     Whether the character is in ['A', 'Z'].
 */
int (isupper)(int);  /* [0x41, 0x5A] */
#define isupper(c)  ((unsigned)((c) - 'A') < 26)


/**
 * Check whether a character is an ASCII
 * hexadecimal digit. Both uppercase and
 * lowercase is supported.
 * 
 * @param   c  The character.
 * @return     Whether the character is in
 *             ['0', '9'], ['A', 'Z'], or ['a', 'z'].
 */
int (isxdigit)(int);  /* [0x30, 0x39], [0x41, 0x46], [0x61, 0x66] */
#if defined (__GNUC__)
# define isxdigit(c)  \
  ({ int __c = (c); (isdigit(__c) && (tolower(__c) - 'a' < 6)); })
#endif



/**
 * Convert a uppercase ASCII character to
 * an lowercase ASCII character.
 * 
 * The function's behaviour is unspecifed
 * of the character is not alphabetical.
 * You should consider running
 * `(isupper(c) ? tolower(c) : c)` instead.
 * 
 * @param   c  The character.
 * @return     The character in lowercase.
 *             Guaranteed to be unchanged if the
 *             character already is in lowercase.
 */
int (tolower)(int);  /* [0x41, 0x5A] -> [0x61, 0x7A] */
#define tolower(c)  ((c) | 0x20)

/**
 * Convert a lowercase ASCII character to
 * an uppercase ASCII character.
 * 
 * The function's behaviour is unspecifed
 * of the character is not alphabetical.
 * You should consider running
 * `(isupper(c) ? tolower(c) : c)` instead.
 * 
 * @param   c  The character.
 * @return     The character in uppercase.
 *             Guaranteed to be unchanged if the
 *             character already is in lowercase.
 */
int (toupper)(int);  /* [0x61, 0x7A] -> [0x41, 0x5A] */
#define toupper(c)  ((c) & ~0x20)



/**
 * Check whether a character is an ASCII character.
 * 
 * @param   c  The character
 * @return  -  Whether the character is an ASCII character.
 */
int (isascii)(int);  /* [0x00, 0x7E] */
#define isascii(c)  ((unsigned)(c) < 0x7F)

/**
 * Remove the 8:th bit from a character.
 * 
 * Note that this does not make a proper character set
 * convertion and the result is virtually arbitrary.
 * 
 * @param  c  The character.
 * @param  c  The character with the 8:th bit cleared.
 */
int (toascii)(int)
  __warning("Using 'toascii' is, generally, unwise.");
#if defined(_SLIBC_SUPPRESS_WARNINGS)
# define toascii(c)  ((c) & 0x7F)
#endif

/**
 * This function is identical to `tolower`.
 * It is provided for backwards-compatibility with SVID.
 */
int _tolower(int)
  __deprecated("Use 'tolower' instead.");

/**
 * This function is identical to `tolower`.
 * It is provided for backwards-compatibility with SVID.
 */
int _toupper(int)
  __deprecated("Use 'toupper' instead.");



/* TODO _l variants */



#endif

