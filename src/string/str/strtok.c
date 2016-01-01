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



/**
 * Tokenise a string.
 * 
 * @param   string      The string to tokenise on the first,
 *                      `NULL` on subsequent calls.
 *                      All bytes found in `delimiters` will
 *                      be overriden with NUL bytes.
 * @param   delimiters  Delimiting bytes (not characters).
 * @return              The next non-empty string that does not
 *                      contain a byte from `delimiters`. The
 *                      returned string will be as long as possible.
 *                      `NULL` is returned the search as reached
 *                      the end of the string, and there therefore
 *                      are no more tokens.
 * 
 * @since  Always.
 */
char* strtok(char* restrict string, const char* restrict delimiters)
{
  static char* state = NULL;
  if (string == NULL)
    state = NULL;
  return strtok_r(string, delimiters, &state);
}

