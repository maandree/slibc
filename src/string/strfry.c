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
#include <string.h>
#include <stdlib.h>


/* Durstenfeld's algorithm. */


/**
 * The number of bits to retain from `rand` output.
 */
#define BITS  8


/**
 * Generate a `size_t` uniformly random.
 * 
 * @param   max  The largest number to generate, inclusive.
 * @return       A random number between 0 and `max`, inclusively.
 */
static size_t
uniform_random_zu(size_t max)
{
  size_t n, r = 0, mask = max, s = 1;
  double b;
  while (((mask + 1) & ~mask) != mask + 1)
    mask |= mask >> s++;
  do
    for (n = max; n; n >>= BITS)
      {
	b = rand();
	b /= (double)RAND_MAX + 1;
	r = (r << BITS) | (int)(b * (1 << BITS));
      }
  while (r &= mask, r > max);
  return r;
}

/**
 * Shuffles all bytes in a string.
 * 
 * You should have called `srand` before
 * calling this function.
 * 
 * This is a GNU joke extension.
 * 
 * @param   anagram  An anagram of the output, will be modified.
 * @retrun           The string, which will `== anagram`.
 * 
 * @since  Always.
 */
char* strfry(char* anagram)
{
  size_t i, j;
  char t;
  if (anagram == NULL)
    return NULL;
  for (i = strlen(anagram); i--;)
    {
      j = uniform_random_zu(i);
      t = anagram[i], anagram[i] = anagram[j], anagram[j] = t;
    }
  return anagram;
}

