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
#include <stdlib.h>
#include <string.h>
#include <errno.h>



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
char* escape(const char* restrict str, char quote)
{
  const char* restrict r;
  char* restrict w;
  char* restrict rc;
  size_t extra = 1, len, size;
  unsigned char c;
  
  if (str == NULL)
    return errno = 0, NULL;
  
  switch (quote)
    {
    case '\'':
    case '\"':
    case '\0':
      break;
    default:
      return errno = EINVAL, NULL;
    }
  
  for (r = str; *r; r++)
    switch (*r)
      {
      case '\a':
      case '\b':
      case '\e':
      case '\f':
      case '\n':
      case '\r':
      case '\t':
      case '\v':
      case '\\':
	extra += 1;
	break;
      case 0x7F:
	extra += 3;
	break;
      default:
	if (*r == quote)
	  extra += 1;
	else if (*r < ' ')
	  extra += 3;
	break;
      }
  
  if (extra == 1)
    return strdup(str);
  
  len = strlen(str);
  if (__builtin_uaddl_overflow(len, extra, &size))
    return errno = ENOMEM, NULL;
  
  w = rc = malloc(size * sizeof(char));
  if (w == NULL)
    return NULL;
  
  for (r = str; (c = *r); r++)
    switch (c)
      {
      case '\a':  *w++ = '\\', *w++ = 'a';   break;
      case '\b':  *w++ = '\\', *w++ = 'b';   break;
      case 033:   *w++ = '\\', *w++ = 'e';   break;
      case '\f':  *w++ = '\\', *w++ = 'f';   break;
      case '\n':  *w++ = '\\', *w++ = 'n';   break;
      case '\r':  *w++ = '\\', *w++ = 'r';   break;
      case '\t':  *w++ = '\\', *w++ = 't';   break;
      case '\v':  *w++ = '\\', *w++ = 'v';   break;
      case '\\':  *w++ = '\\', *w++ = '\\';  break;
      case 0x7F:  *w++ = '\\', *w++ = '1', *w++ = '7', *w++ = '7';  break;
      default:
	if (c == quote)
	  *w++ = '\\', *w++ = quote;
	else if (c < ' ')
	  *w++ = '\\',
	    *w++ = '0' + (c >> 6),
	    *w++ = '0' + ((c >> 3) & 7),
	    *w++ = '0' + (c & 7);
	else
	  *w++ = c;
	break;
      }
  
  return *w = 0, rc;
}

