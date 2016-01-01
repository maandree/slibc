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
#include <strings.h>



/**
 * Find the first set bit in an integer.
 * 
 * @etymology  (F)ind (f)irst (s)et bit on `(l)ong int`.
 * 
 * @param   i  The integer.
 * @return     The value of the least significant set bit, zero if none.
 * 
 * @since  Always.
 */
int ffsl(long i)
{
  return __builtin_ffsl(i);
}

