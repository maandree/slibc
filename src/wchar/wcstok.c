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
#include <wchar.h>



/**
 * Tokenise a string.
 * 
 * @param   string      The string to tokenise on the first,
 *                      `NULL` on subsequent calls.
 *                      All characters found in `delimiters` will
 *                      be overriden with NUL characters.
 * @param   delimiters  Delimiting characters.
 * @param   state       Pointer to a `char*` that the function
 *                      can use to keep track of its state.
 *                      It is reasonable to make it point to `NULL`
 *                      on the first call.
 * @return              The next non-empty string that does not
 *                      contain a byte from `delimiters`. The
 *                      returned string will be as long as possible.
 *                      `NULL` is returned the search as reached
 *                      the end of the string, and there therefore
 *                      are no more tokens.
 * 
 * @since  Always.
 */
wchar_t* wcstok(wchar_t* restrict string, const wchar_t* restrict delimiters,
		wchar_t** restrict state)
{
  wchar_t* r;
  if (string == NULL)
    *state = string;
  for (;;)
    {
      r = wcssep(state, delimiters);
      if (r == NULL)
	return NULL;
      if (*r)
	return r;
    }
}

