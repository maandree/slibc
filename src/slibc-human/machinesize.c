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
#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>



/**
 * Get prefix-value.
 * 
 * @param   str   Pointer to the string, will be updated to point to the end of the unit.
 * @param   mode  How to parse ambiguous units.
 * @return        The multiple for the value, 0 on error.
 * 
 * @throws  EINVAL  The prefix is unrecognised.
 * @throws  ERANGE  The prefix is too large.
 */
__attribute__((nonnull))
static size_t prefix(char** restrict str, enum machinesize_mode mode)
{
#define P(A, B)  case A: case B: power++
  char* p = *str;
  size_t power = 0;
  size_t base = 0;
  size_t rc = 1;
  
  switch (*p++)
    {
      P('Y', 'y');
      P('Z', 'z');
      P('E', 'e');
      P('P', 'p');
      P('T', 't');
      P('G', 'g');
      P('M', 'm');
      P('k', 'K');
    case 'B': case 'b':
      break;
      default:
	return errno = EINVAL, (size_t)0;
    }
  if (power == 0)
    goto done;
  
  if ((*p == 'i') || (*p == 'I'))
    base = 1024, p++;
  if ((*p == 'B') || (*p == 'b'))
    {
      p++;
      if ((!base) && (mode == (MACHINESIZE_SI | MACHINESIZE_IEC)))
	base = 1000;
    }
  if (!base)
    base = (mode == MACHINESIZE_SI) ? 1000 : 1024;
  
  while (power--)
    OVERFLOW(umull, rc, base, &rc, ERANGE, (size_t)0);
  
 done:
  return *str = p, rc;
#undef P
}


/**
 * Parses a human representation of storage size or file offset.
 * 
 * If no unit is used, bytes are assumed. If you rather it be
 * (for example) kilobytes, you can multiply it if
 * `strpbrk(str, "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM") == NULL`.
 * 
 * @etymology  Convert to (machine)-representation: `(size)_t`.
 * 
 * @param   size   Output parameter for the value, must not be `NULL`.
 * @param   str    The value to parse, must not `NULL`.
 * @param   mode   How to parse ambiguous strings, 0 for default.
 * @param   space  Characters to ignore (thousand-group delimiters).
 *                 Supports UTF-8. `NULL` for default. Default value
 *                 is " '".
 * @param   point  Decimal pointer chracters. Supports UTF-8. `NULL`
 *                 for default. Default value is ",.".
 * @return         Zero on success, -1 on error.
 * 
 * @throws  EINVAL  If `mode` is invalid.
 * @throws  EINVAL  If `str` is not parseable.
 * @throws  ERANGE  If the value is too range to fit in a `size_t`.
 * 
 * @since  Always.
 */
int machinesize(size_t* restrict size, const char* restrict str, enum machinesize_mode mode,
		const char* restrict space, const char* restrict point)
{
  size_t r = 0;
  size_t word;
  long double dword;
  size_t u;
  const char* p;
  const char* q;
  int started = 0;
  int pluses = 0;
  int have_unitless = 0;
  size_t words = 0;
  
  if (space == NULL)  space = " '";
  if (point == NULL)  point = ".,";
  
  if (mode == 0)  mode = MACHINESIZE_SI | MACHINESIZE_IEC;
  if (mode > 3)   goto invalid;
  
  for (p = str; *p;)
    if (strchr(" \t+", *p))
      {
	if ((pluses += (*p++ == '+')) > 1)
	  goto invalid;
      }
    else if ((q = machinefloat(&dword, p, space, point)))
      {
	p = q, words++, pluses = 0, started = 1;
	while (strchr(" \t-", *p))
	  p++;
	if (isalpha(*p) == 0)  u = 1, have_unitless = 1;
	else                   u = prefix(&p, mode);
	if (u == 0)            return -1;
	dword *= (long double)u;
	if (dword > (long double)SIZE_MAX)
	  return errno = ERANGE, -1;
	word = (size_t)dword;
	OVERFLOW(uaddl, word, r, &r, ERANGE, -1);
      }
    else
      return -1;
  
  if ((!started) || (have_unitless && (words > 1)))
    goto invalid;
  return *size = r, 0;
 invalid:
  return errno = EINVAL, -1;
}

