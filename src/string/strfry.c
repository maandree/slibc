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
 * Shuffles all bytes in a string.
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
  int r;
  char t;
  if (anagram == NULL)
    return NULL;
  for (i = strlen(anagram); i--;)
    {
      r = rand();
      j = (size_t)((double)r / ((double)RAND_MAX + 1) * (double)i); /* TODO This is not uniformally random. */
      t = anagram[i], anagram[i] = anagram[j], anagram[j] = t;
    }
  return anagram;
}

