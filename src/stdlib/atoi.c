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
#include <stdlib.h>
#include <ctype.h>



/**
 * Convert a string to an integer,
 * without checking for errors.
 * 
 * The string may being with an arbitrary number
 * of whitespace characters. Convertion will end
 * when a character is encountered that is not a
 * decimal digit, and is not an absolutely leading
 * '-' or '+'.
 * 
 * @param   string  The string to convert.
 * @return          The integer encoded by the string.
 * 
 * @since  Always.
 */
int atoi(const char* string)
{
  int rc = 0;
  int neg = 0;
  
  while (isspace(*string))
    string++;
  
  switch (*string)
    {
    case '-': neg = 1;
    case '+': string++;
    default:  break;
    }
  
  while (isdigit(*string))
    rc = rc * 10 - (*string++ & 15);
  
  return neg ? rc : -rc;
}

