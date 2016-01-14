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
#include <ctype.h>



/**
 * Check whether a character is an alphabetical
 * character or a decimal digit.
 * 
 * @etymology  (Is) character either (al)phabetical or (num)erical [(al)pha(num)erical]?
 * 
 * @param   c  The character.
 * @return     Whether the character is in
 *             ['0', '9'], ['A', 'Z'], or ['a', 'z'].
 * 
 * @since  Always.
 */
int (isalnum)(int c)
{
  return isalnum(c);
}


/**
 * Check whether a character is an alphabetical character.
 * 
 * @etymology  (Is) character (alpha)betical?
 * 
 * @param   c  The character.
 * @return     Whether the character is in
 *             ['A', 'Z'] or ['a', 'z'].
 * 
 * @since  Always.
 */
int (isalpha)(int c)
{
  return isalpha(c);
}


/**
 * Check whether a character is a regular blank space
 * or a horizontal tabulation.
 * 
 * @etymology  (Is) character a (blank) space?
 * 
 * @param   c  The character.
 * @return     Whether the character is a ' ' or a '\t'.
 * 
 * @since  Always.
 */
int (isblank)(int c)
{
  return isblank(c);
}


/**
 * Check whether a character is a non-printable
 * ASCII character.
 * 
 * @etymology  (Is) character a (c)o(ntr)o(l) character?
 * 
 * @param   c  The character.
 * @return     Whether the character is lower than ' '.
 * 
 * @since  Always.
 */
int (iscntrl)(int c)
{
  return iscntrl(c);
}


/**
 * Check whether a character is a decimal digit.
 * 
 * @etymology  (Is) character a (digit)?
 * 
 * @param   c  The character.
 * @return     Whether the character is in ['0', '9'].
 * 
 * @since  Always.
 */
int (isdigit)(int c)
{
  return isdigit(c);
}


/**
 * Check whether a character is has a printable glyph.
 * 
 * @etymology  (Is) character (graph)ical?
 * 
 * @param   c  The character.
 * @return     Whether the character is greater than ' '.
 * 
 * @since  Always.
 */
int (isgraph)(int c)
{
  return isgraph(c);
}


/**
 * Check whether a character is a lowercase
 * alphabetical character.
 * 
 * @etymology  (Is) character a (lower)case character?
 * 
 * @param   c  The character.
 * @return     Whether the character is in ['a', 'z'].
 * 
 * @since  Always.
 */
int (islower)(int c)
{
  return islower(c);
}


/**
 * Check whether a character is has a printable glyph
 * or a blank space.
 * 
 * @etymology  (Is) character (print)able?
 * 
 * @param   c  The character.
 * @return     Whether the character is at least
 *             as great as ' '.
 * 
 * @since  Always.
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
 * @etymology  (Is) character a (punct)uation?
 * 
 * @param   c  The character.
 * @return     Whether the character is a punctuation.
 * 
 * @since  Always.
 */
int (ispunct)(int c)
{
  return ispunct(c);
}


/**
 * Check whether a character is a whitespace character.
 * 
 * @etymology  (Is) character white(space)?
 * 
 * @param   c  The character.
 * @return     Whether the character is a ' ', '\f',
 *             '\n', '\r', '\t', or '\v'.
 * 
 * @since  Always.
 */
int (isspace)(int c)
{
  return isspace(c);
}


/**
 * Check whether a character is an uppercase
 * alphabetical character.
 * 
 * @etymology  (Is) character a (upper)case character?
 * 
 * @param   c  The character.
 * @return     Whether the character is in ['A', 'Z'].
 * 
 * @since  Always.
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
 * @etymology  (Is) character a he(x)adecimal digit?
 * 
 * @param   c  The character.
 * @return     Whether the character is in
 *             ['0', '9'], ['A', 'Z'], or ['a', 'z'].
 * 
 * @since  Always.
 */
int (isxdigit)(int c)
{
  return isxdigit(c);
}



/**
 * Convert a uppercase ASCII character to
 * an lowercase ASCII character.
 * 
 * @etymology  Convert character (to) (lower)case!
 * 
 * @param   c  The character.
 * @return     The character in lowercase.
 *             Guaranteed to be unchanged if the
 *             character already is in lowercase.
 * 
 * @since  Always.
 */
int (tolower)(int c)
{
  return tolower(c);
}


/**
 * Convert a lowercase ASCII character to
 * an uppercase ASCII character.
 * 
 * @etymology  Convert character (to) (upper)case!
 * 
 * @param   c  The character.
 * @return     The character in uppercase.
 *             Guaranteed to be unchanged if the
 *             character already is in lowercase.
 * 
 * @since  Always.
 */
int (toupper)(int c)
{
  return toupper(c);
}



/**
 * Check whether a character is an ASCII character.
 * 
 * @etymology  (Is) character an (ASCII) character?
 * 
 * @param   c  The character
 * @return     Whether the character is an ASCII character.
 * 
 * @since  Always.
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
 * Justification for existence:
 *   The highest bit has historically been used as a
 *   parity bit.
 * 
 * @etymology  Truncate character (to) fit (ASCII) character set!
 * 
 * @param   c  The character.
 * @return     The character with the 8:th bit cleared.
 * 
 * @since  Always.
 */
int (toascii)(int c)
{
  return c & 0x7F;
}


/**
 * This function is identical to `tolower`.
 * It is provided for backwards-compatibility with SVID.
 * 
 * @since  Always.
 */
int _tolower(int c)
{
  return tolower(c);
}


/**
 * This function is identical to `tolower`.
 * It is provided for backwards-compatibility with SVID.
 * 
 * @since  Always.
 */
int _toupper(int c)
{
  return toupper(c);
}



/**
 * Create a variant, with specifiable locale,
 * of one of the functions.
 * 
 * @param  The name of the function without the `_l`-suffix.
 */
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

