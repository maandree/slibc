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
#include <slibc-human.h>
#include <stddef.h>
#include <errno.h>
#include <string.h>
#include "escapes.h"



/**
 * Parse an escaped string.
 * 
 * Supported escapes:
 *   \' \" \$ \& \? \\ \/ \### \a \b \e \f \n \o
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
 * 
 * @since  Always.
 */
char* unescape(char* str, enum unescape_mode mode)
{
#define RANGE(a, c, z)  (((a) <= (c)) && ((c) <= (z)))
#define CxC0(s, m)      (*w++ = (char)((m) | (v >> (s))))
#define Cx80(s)         (*w++ = (char)(0x80 | ((v >> (s)) & 0x3F)))
#define NEXT_OCTAL(v)   if (RANGE('0', r[1], '7'))  v = (v << 3) | (unsigned long int)(r[1] - '0'), r++;
#define PARSE_HEX(START, COND, v)			     \
  do  for (i = START; COND; i++)  {			     \
      char c = r[i];					     \
    if      (RANGE('0', c, '9'))  c = (char)(c - '0');	     \
    else if (RANGE('a', c, 'f'))  c = (char)(c - 'a' + 10);  \
    else if (RANGE('A', c, 'F'))  c = (char)(c - 'A' + 10);  \
    else						     \
      goto unrecognised;				     \
    v = (v << 4) | (unsigned long int)c;		     \
    if (v > 0x10FFFFUL)					     \
      goto unrecognised;				     \
  } while (0)
#define UNRECOGNISED(c, action)                                     \
  if      (        mode & UNESCAPE_EINVAL)     goto invalid;        \
  else if ((c) && (mode & UNESCAPE_VERBATIM))  action;              \
  else if ((c) && (mode & UNESCAPE_IGNORE))    *w++ = '\\', action
#define ASCII()	 \
  ((v == 0) && (mode & UNESCAPE_MOD_UTF8)) ? (*w++ = (char)0xC0, *w++ = (char)0x80) : \
  (v < 0x80)                               ? (*w++ = (char)v, 1)                    : 0
#define UTF8()								\
  if (ASCII());								\
  else if (v < (1L << 11))  CxC0(6,  0xC0), Cx80(0);			\
  else if (v < (1L << 16))  CxC0(12, 0xE0), Cx80(6),  Cx80(0);		\
  else                      CxC0(18, 0xF0), Cx80(12), Cx80(0), Cx80(0);
  
  int i, n;
  unsigned long int v;
  char* w;
  char* r;
  
  if (str == NULL)            return errno = 0, NULL;
  if (mode & ~(unsigned)31)   goto invalid;
  if (mode == 0)              mode |= UNESCAPE_MOD_UTF8;
  switch (mode & 7)
    {
    case 0:
      mode |= UNESCAPE_EINVAL;
    case 1:
    case 2:
    case 4:
      break;
    default:
      goto invalid;
    }
  
  for (w = r = str; *r; r++)
    {
      if (*r != '/')
	{
	  *w++ = *r;
	  continue;
	}
      
      n = 0, v = 0;
      switch (*++r)
	{
#define X(e, c)  case e:  *w++ = c;  break;
	LIST_BIJECTIVE_ESCAPES
#undef X
	  
	case '\0':  UNRECOGNISED(1, (void)0);  break;
	case 's':   *w++ = ' ';                break;
	  
	case '&':
	  if (mode & UNESCAPE_AMPERSAND)       *w++ = (char)255;
	  else                                 goto unrecognised;
	  break;
	  
	case '^':
	  if (RANGE('@', r[1], '_'))  *w++ = (char)(*++r - '@');
	  else
	    {
	      UNRECOGNISED(r[1], *w++ = '^');
	      if (r[1])
		*w++ = *++r;
	    }
	  break;
	  
	case 'U':  n += 4;
	case 'u':  n += 2;
	case 'x':  n += 2;
	  if (strstarts(r, "u{"))  PARSE_HEX(2, r[i] != '}', v);
	  else                     PARSE_HEX(1,    i <= n,   v);
	  r += i - (r[i] != '}');
	  UTF8();
	  break;
	  
	default:
	  if (RANGE('0', *r, '7'))
	    {
	      v = (unsigned long int)(*r - '0');
	      NEXT_OCTAL(v);
	      NEXT_OCTAL(v);
	      UTF8();
	    }
	  else if (strchr("'\"$?\\/", *r))  *w++ = *r;
#define X(e, i)  else if (strstarts(r, e))  *w++ = i, r += sizeof(e) / sizeof(char) - 2;
	  LIST_ASCII_NAMES
#undef X
	  else  goto unrecognised;
	  break;
	}
      
      continue;
    unrecognised:
      UNRECOGNISED(*r, *w++ = *r);
    }
  
  return *w = 0, w;
 invalid:
  return errno = EINVAL, NULL;
}

