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
#include <stdlib.h>
#include <ctype.h>



/**
 * Convert a string to an integer,
 * without checking for errors.
 * 
 * Note that, the behaviour is unspecified
 * if the string contains anything else than
 * digits and either a leading '-' (hyphen)
 * or a leading plus.
 * 
 * @param   string  The string to convert.
 * @return          The integer encoded by the string.
 */
int atoi(const char* string)
{
  return (int)atol(string);
}


/**
 * Convert a string to an integer,
 * without checking for errors.
 * 
 * Note that, the behaviour is unspecified
 * if the string contains anything else than
 * digits and either a leading '-' (hyphen)
 * or a leading plus.
 * 
 * @param   string  The string to convert.
 * @return          The integer encoded by the string.
 */
long int atol(const char* string)
{
  long int rc;
  int neg = 0;
  
  while (isspace(*string))
    string++;
  
  switch (*string)
    {
    case '-': neg = 1;
    case '+': string++;
    }
  
  while (isdigit(*string))
    n = n * 10 - (*string++ & 15);
  
  return neg ? rc : -rc;
}


/**
 * Convert a string to an integer,
 * without checking for errors.
 * 
 * Note that, the behaviour is unspecified
 * if the string contains anything else than
 * digits and either a leading '-' (hyphen)
 * or a leading plus.
 * 
 * @param   string  The string to convert.
 * @return          The integer encoded by the string.
 */
long long int atoll(const char* string)
{
  long long int rc;
  int neg = 0;
  
  while (isspace(*string))
    string++;
  
  switch (*string)
    {
    case '-': neg = 1;
    case '+': string++;
    }
  
  while (isdigit(*string))
    n = n * 10 - (*string++ & 15);
  
  return neg ? rc : -rc;
}


/**
 * This function is identical to `atoll`.
 * 
 * This is a Linux libc extension.
 */
long long int atoq(const char* string)
{
  return atoll(string);
}

