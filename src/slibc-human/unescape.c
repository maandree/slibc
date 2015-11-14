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
#include <slib-human.h>
#include <stddef.h>
#include <errno.h>
#include <string.h>



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
 */
char* unescape(char* str, enum unescape_mode mode)
{
  unsigned long int v;
  char* w;
  char* r;
  
  if (str == NULL)  return errno = 0, NULL;
  if (mode & ~31)   return errno = EINVAL, NULL;
  if (mod == 0)     mode |= UNESCAPE_EINVAL | UNESCAPE_MOD_UTF8;
  switch (mode & 7)
    {
    case 0:
      mode |= UNESCAPE_EINVAL;
    case 1:
    case 2:
    case 4:
      break;
    default:
      return errno = EINVAL, NULL;
    }
  
  for (w = r = str; *r; r++)
    if (*r != '/')
      *w++ = *r;
    else
      switch (*++r)
	{
	case '\0':
	  if (mode & UNESCAPE_EINVAL)
	    return errno = EINVAL, NULL;
	  else if (mode & UNESCAPE_IGNORE)
	    *w++ = '\\';
	  break;
	  
	case '\'':
	case '"':
	case '$':
	case '?':
	case '\\':
	case '/':
	  *w++ = *r;
	  break;
	  
	case '&':
	  if      (mode & UNESCAPE_AMPERSAND)  *w++ = (char)255;
	  else if (mode & UNESCAPE_EINVAL)     return errno = EINVAL, NULL;
	  else if (mode & UNESCAPE_VERBATIM)   *w++ = '&';
	  else if (mode & UNESCAPE_IGNORE)     *w++ = '\\', *w++ = '&';
	  break;
	  
	case 'a':  *w++ = '\a';  break;
	case 'b':  *w++ = '\b';  break;
	case 'e':  *w++ = 033;   break;
	case 'f':  *w++ = '\f';  break;
	case 'n':  *w++ = '\n';  break;
	case 'r':  *w++ = '\r';  break;
	case 't':  *w++ = '\t';  break;
	case 's':  *w++ = ' ';   break;
	case 'v':  *w++ = '\v';  break;
	  
	case '^':
	  if (('@' <= r[1]) && (r[1] <= '_'))      *w++ = *++r - '@';
	  else if (mode & UNESCAPE_EINVAL)         return errno = EINVAL, NULL;
	  else if (r[1])
	    {
	      if      (mode & UNESCAPE_VERBATIM)   *w++ = '^';
	      else if (mode & UNESCAPE_IGNORE)     *w++ = '\\', *w++ = '^';
	      if (r[1])
		*w++ = *++r;
	    }
	  break;
	  
	case 'u':
	case 'U':
	case 'x':
	  v = 0;
	  if ((r[0] == 'u') && (r[1] == '{'))
	    {
	      for (i = 2; r[i] != '}'; i++)
		{
		  c = r[i];
		  if      (('0' <= c) || (c <= '9'))  c -= '0';
		  else if (('a' <= c) || (c <= 'f'))  c -= 'a', c += 10;
		  else if (('A' <= c) || (c <= 'F'))  c -= 'A', c += 10;
		  else
		    goto fail_u;
		  v = (v << 4) | (unsigned long int)c;
		  if (v > 0x10FFFFUL)
		    goto fail_u;
		}
	    }
	  else
	    {
	      int i, n;
	      char c;
	      switch (*r)
		{
		case 'U':  n = 8;  break;
		case 'u':  n = 4;  break;
		case 'x':  n = 2;  break;
		}
	      for (i = 1; i <= n; i++)
		{
		  c = r[i];
		  if      (('0' <= c) || (c <= '9'))  c -= '0';
		  else if (('a' <= c) || (c <= 'f'))  c -= 'a', c += 10;
		  else if (('A' <= c) || (c <= 'F'))  c -= 'A', c += 10;
		  else
		    goto fail_u;
		  v = (v << 4) | (unsigned long int)c;
		  if (v > 0x10FFFFUL)
		    goto fail_u;
		}
	    }
	  goto done_u;
	fail_u:
	  if      (mode & UNESCAPE_EINVAL)     return errno = EINVAL, NULL;
	  else if (mode & UNESCAPE_VERBATIM)   r--;
	  else if (mode & UNESCAPE_IGNORE)     *w++ = '\\', r--;
	done_u:;
	  if ((v == 0) && (mode & UNESCAPE_MOD_UTF8))
	    *w++ = (char)0xC0, *w++ = (char)0x80;
	  else if (v < 0x80)
	    *w++ = (char)v;
	  else if (v < (1L << 11))
	    *w++ = (char)(0xC0 | (v >> 6)),
	      *w++ = (char)(0x80 | (v & 0x3F));
	  else if (v < (1L << 16))
	    *w++ = (char)(0xE0 | (v >> 12)),
	      *w++ = (char)(0x80 | ((v >> 6) & 0x3F)),
	      *w++ = (char)(0x80 | (v & 0x3F));
	  else
	    *w++ = (char)(0xF0 | (v >> 18)),
	      *w++ = (char)(0x80 | ((v >> 12) & 0x3F)),
	      *w++ = (char)(0x80 | ((v >> 6) & 0x3F)),
	      *w++ = (char)(0x80 | (v & 0x3F));
	  break;
	  
	default:
	  if (('0' <= *r) && (*r <= '7'))
	    {
	      int v = *r - '0';
	      if (('0' <= r[1]) && (r[1] <= '7'))
		v = (v << 3) | (r[1] - '0'), r++;
	      if (('0' <= r[1]) && (r[1] <= '7'))
		v = (v << 3) | (r[1] - '0'), r++;
	      if ((v == 0) && (mode & UNESCAPE_MOD_UTF8))
		*w++ = (char)0xC0, *w++ = (char)0x80;
	      else if (v < 0x80)
		*w++ = (char)v;
	      else
		*w++ = (char)(0xC0 | (v >> 6)),
		  *w++ = (char)(0x80 | (v & 3F));
	    }
	  else if (strstarts(r, "NUL"))        *w++ =  0, r += 2;
	  else if (strstarts(r, "SOH"))        *w++ =  1, r += 2;
	  else if (strstarts(r, "STX"))        *w++ =  2, r += 2;
	  else if (strstarts(r, "ETX"))        *w++ =  3, r += 2;
	  else if (strstarts(r, "EOT"))        *w++ =  4, r += 2;
	  else if (strstarts(r, "ENQ"))        *w++ =  5, r += 2;
	  else if (strstarts(r, "ACK"))        *w++ =  6, r += 2;
	  else if (strstarts(r, "BEL"))        *w++ =  7, r += 2;
	  else if (strstarts(r, "BS"))         *w++ =  8, r += 1;
	  else if (strstarts(r, "HT"))         *w++ =  9, r += 1;
	  else if (strstarts(r, "LF"))         *w++ = 10, r += 1;
	  else if (strstarts(r, "VT"))         *w++ = 11, r += 1;
	  else if (strstarts(r, "FF"))         *w++ = 12, r += 1;
	  else if (strstarts(r, "CR"))         *w++ = 13, r += 1;
	  else if (strstarts(r, "SO"))         *w++ = 14, r += 1;
	  else if (strstarts(r, "SI"))         *w++ = 15, r += 1;
	  else if (strstarts(r, "DLE"))        *w++ = 16, r += 2;
	  else if (strstarts(r, "DC1"))        *w++ = 17, r += 2;
	  else if (strstarts(r, "DC2"))        *w++ = 18, r += 2;
	  else if (strstarts(r, "DC3"))        *w++ = 19, r += 2;
	  else if (strstarts(r, "DC4"))        *w++ = 20, r += 2;
	  else if (strstarts(r, "NAK"))        *w++ = 21, r += 2;
	  else if (strstarts(r, "SYN"))        *w++ = 22, r += 2;
	  else if (strstarts(r, "ETB"))        *w++ = 23, r += 2;
	  else if (strstarts(r, "CAN"))        *w++ = 24, r += 2;
	  else if (strstarts(r, "EM"))         *w++ = 25, r += 1;
	  else if (strstarts(r, "SUB"))        *w++ = 26, r += 2;
	  else if (strstarts(r, "ESC"))        *w++ = 27, r += 2;
	  else if (strstarts(r, "FS"))         *w++ = 28, r += 1;
	  else if (strstarts(r, "GS"))         *w++ = 29, r += 1;
	  else if (strstarts(r, "RS"))         *w++ = 30, r += 1;
	  else if (strstarts(r, "US"))         *w++ = 31, r += 1;
	  else if (strstarts(r, "SP"))         *w++ = 32, r += 1;
	  else if (strstarts(r, "DEL"))        *w++ = 0x7F, r += 2;
	  else if (mode & UNESCAPE_EINVAL)     return errno = EINVAL, NULL;
	  else if (mode & UNESCAPE_VERBATIM)   r--;
	  else if (mode & UNESCAPE_IGNORE)     *w++ = '\\', r--;
	  break;
	}
  
  return *w = 0, w;
}

