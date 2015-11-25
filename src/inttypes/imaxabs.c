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
#include <inttypes.h>



/**
 * Return the absolute value of an integer.
 * 
 * Be aware, if the value is `INTMAX_MIN` and
 * `-INTMAX_MAX != -INTMAX_MIN`, the result will
 * overflow, and `INTMAX_MIN` will (probably)
 * be returned.
 * 
 * @etymology  `(i)nt(max)_t`-function: (abs)olute value.
 * 
 * @param   value  The integer.
 * @return         The absolute value of the integer.
 * 
 * @since  Always.
 */
intmax_t (imaxabs)(intmax_t value)
{
  return value < 0 ? -value : value;
}

