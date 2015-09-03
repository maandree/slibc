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
#include <ctype.h>



/**
 * Check whether a character is an alphabetical
 * character or a decimal digit.
 * 
 * @param   c  The character.
 * @return     Whether the character is in
 *             ['0', '9'], ['A', 'Z'], or ['a', 'z'].
 */
int (isalnum)(int c)
{
  return isalnum(c);
}


/**
 * Check whether a character is an alphabetical character.
 * 
 * @param   c  The character.
 * @return     Whether the character is in
 *             ['A', 'Z'] or ['a', 'z'].
 */
int (isalpha)(int c)
{
  return isalpha(c);
}


/**
 * Check whether a character is a regular blank space
 * or a horizontal tabulation.
 * 
 * @param   c  The character.
 * @return     Whether the character is a ' ' or a '\t'.
 */
int (isblank)(int c)
{
  return isblank(c);
}


/**
 * Check whether a character is a non-printable
 * ASCII character.
 * 
 * @param   c  The character.
 * @return     Whether the character is lower than ' '.
 */
int (iscntrl)(int c)
{
  return iscntrl(c);
}


/**
 * Check whether a character is a decimal digit.
 * 
 * @param   c  The character.
 * @return     Whether the character is in ['0', '9'].
 */
int (isdigit)(int c)
{
  return isdigit(c);
}


/**
 * Check whether a character is has a printable glyph.
 * 
 * @param   c  The character.
 * @return     Whether the character is greater than ' '.
 */
int (isgraph)(int c)
{
  return isgraph(c);
}


/**
 * Check whether a character is a lowercase
 * alphabetical character.
 * 
 * @param   c  The character.
 * @return     Whether the character is in ['a', 'z'].
 */
int (islower)(int c)
{
  return islower(c);
}


/**
 * Check whether a character is has a printable glyph
 * or a blank space.
 * 
 * @param   c  The character.
 * @return     Whether the character is at least
 *             as great as ' '.
 */
int (isprint)(int c)
{
  return isprint(c);
}


/**
 * Check whether a character is has a punctuation,
 * that is, a printable character but a blank space,
 * numerical or alphabetical.
 * 
 * @param   c  The character.
 * @return     Whether the character is a punctuation.
 */
int (ispunct)(int c)
{
  return ispunct(c);
}


/**
 * Check whether a character is a whitespace character.
 * 
 * @param   c  The character.
 * @return     Whether the character is a ' ', '\f',
 *             '\n', '\r', '\t', or '\v'.
 */
int (isspace)(int c)
{
  return isspace(c);
}


/**
 * Check whether a character is an uppercase
 * alphabetical character.
 * 
 * @param   c  The character.
 * @return     Whether the character is in ['A', 'Z'].
 */
int (isupper)(int c)
{
  return isupper(c);
}


/**
 * Check whether a character is an ASCII
 * hexadecimal digit. Both uppercase and
 * lowercase is supported.
 * 
 * @param   c  The character.
 * @return     Whether the character is in
 *             ['0', '9'], ['A', 'Z'], or ['a', 'z'].
 */
int (isxdigit)(int c)
{
  return isxdigit(c);
}



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
int (tolower)(int c)
{
  return tolower(c);
}


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
int (toupper)(int c)
{
  return toupper(c);
}



/**
 * Check whether a character is an ASCII character.
 * 
 * @param   c  The character
 * @return     Whether the character is an ASCII character.
 */
int (isascii)(int c)
{
  return isascii(c);
}


/**
 * Remove the 8:th bit from a character.
 * 
 * Note that this does not make a proper character set
 * convertion and the result is virtually arbitrary.
 * 
 * @param   c  The character.
 * @return     The character with the 8:th bit cleared.
 */
int (toascii)(int c)
{
  return c & 0x7F;
}


/**
 * This function is identical to `tolower`.
 * It is provided for backwards-compatibility with SVID.
 */
int _tolower(int c)
{
  return tolower(c);
}


/**
 * This function is identical to `tolower`.
 * It is provided for backwards-compatibility with SVID.
 */
int _toupper(int c)
{
  return toupper(c);
}



#define CTYPE_LOCALE(F)			\
  int F##_l(int c, locale_t locale)	\
  {					\
    return F(c);			\
    (void) locale;			\
  }

CTYPE_LOCALE(isalnum)
CTYPE_LOCALE(isalpha)
CTYPE_LOCALE(isblank)
CTYPE_LOCALE(iscntrl)
CTYPE_LOCALE(isdigit)
CTYPE_LOCALE(isgraph)
CTYPE_LOCALE(islower)
CTYPE_LOCALE(isprint)
CTYPE_LOCALE(ispunct)
CTYPE_LOCALE(isspace)
CTYPE_LOCALE(isupper)
CTYPE_LOCALE(isxdigit)
CTYPE_LOCALE(isascii)
CTYPE_LOCALE(toascii)
CTYPE_LOCALE(tolower)
CTYPE_LOCALE(toupper)

