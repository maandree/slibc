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



/**
 * Return the absolute value of an integer.
 * 
 * Be aware, if the value is `LLONG_MIN` and
 * `-LLONG_MAX != -LLONG_MIN`, the result will
 * overflow, and `LLONG_MIN` will (probably)
 * be returned.
 * 
 * @param   value  The integer.
 * @return         The absolute value of the integer.
 * 
 * @since  Always.
 */
long long int (llabs)(long long int value)
{
  return value < 0 ? -value : value;
}

