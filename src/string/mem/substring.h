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
/* This file is intended to be included inside a
 * [w]mem[r][case]mem function. `haystack` and
 * `needle` shall be defined the same pointer type,
 * but not as `void*`. `haystack_length` and
 * `needle_length` shall be defined in the `size_t`
 * type. CASE shall be defined iff case insensitive
 * search shall be used. RIGHT shall be defined iff
 * the last occurrence shall be find. WIDE shall be
 * defined iff wide characters are used. It is assumed
 * that `needle_length` <= `haystack_length` */


/* The Knuth–Morris–Pratt algorithm. */


/**
 * Test whether to characters are equal.
 * Case-sensitivity depends on `CASE` being defined.
 * 
 * @param   a  One of the characters.
 * @param   b  The other character.
 * @return     1 if `a` and `b` or equal, 0 otherwise.
 *             The comparison is case-insensitive if
 *             `CASE` is defined.
 */
#if !defined(CASE)
# define CHREQ(a, b)  (a == b)
#elif !defined(WIDE)
# define CHREQ(a, b)  ((islower(a) ? tolower(a) : (a)) == tolower(b))
#else
# define CHREQ(a, b)  ((iswlower(a) ? towlower(a) : (a)) == towlower(b))
#endif


/* TODO add support for RIGHT */
/* TODO add [w]mem[r]{lower,upper}mem */


/* The implementation of the algorithm, read
 * elsewhere for documentation/explanation. */
{
  ssize_t* next_map = alloca((needle_length + 1) * sizeof(ssize_t));
  ssize_t hay, ned, skp;
  
  ned = 0, skp = next_map[0] = -1;
  while (ned < (ssize_t)needle_length)
    {
      while ((skp > -1) && !CHREQ(needle[ned], needle[skp]))
	skp = next_map[skp];
      ned++, skp++;
      next_map[ned] = CHREQ(needle[ned], needle[skp]) ? next_map[skp] : skp;
    }
  
  hay = ned = 0;
  while (hay < (ssize_t)haystack_length)
    {
      while ((ned > -1) && !CHREQ(haystack[hay], needle[ned]))
	ned = next_map[ned];
      hay++, ned++;
      if (ned >= (ssize_t)needle_length)
	return needle + (hay - ned);
    }
  
  return NULL;
}


#undef CHREQ

