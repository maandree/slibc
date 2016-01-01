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
#include <slibc/internals.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "escapes.h"



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
 * 
 * @since  Always.
 */
char* escape(const char* restrict str, int quote)
{
#define OCTAL(s)   (*w++ = (char)('0' + ((c >> (s)) & 7)))
#define MODNUL(s)  (((unsigned char)((s)[0]) == 0xC0) && ((unsigned char)((s)[1]) == 0x80))
  
  const char* restrict r;
  char* restrict w;
  char* restrict rc;
  size_t extra = 0, len, size;
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
  
  for (r = str; (c = (unsigned char)*r); r++)
    switch (c)
      {
#define X(E, C)  case C:
      LIST_BIJECTIVE_ESCAPES
#undef X
	                      extra += 1;  break;
      case 0x7F:              extra += 3;  break;
      default:
	if      (c == quote)  extra += 1;
	else if (c < ' ')     extra += 3;
	break;
      }
  
  if (!extra++)
    return strdup(str);
  
  len = strlen(str) * sizeof(char);
  MEM_OVERFLOW(uaddl, len, extra * sizeof(char), &size);
  
  w = rc = malloc(size);
  if (rc == NULL)
    return NULL;
  
  for (r = str; (c = (unsigned char)*r); r++)
    switch (c)
      {
#define X(E, C)  case C:  *w++ = '\\', *w++ = E;  break;
      LIST_BIJECTIVE_ESCAPES
#undef X
      case 0x7F:  w = stpcpy(w, "\\177");  break;
      default:
	*w++ = '\\';
	if      (MODNUL(r))   *w++ = '0', r++;
	else if (c == quote)  *w++ = (char)quote;
	else if (c < ' ')     OCTAL(6), OCTAL(3), OCTAL(0);
	else                  w[-1] = (char)c;
	break;
      }
  
  return *w = 0, rc;
}

