/**
 * slibc — Yet another C library
 * Copyright © 2015, 2016  Mattias Andrée (m@maandree.se)
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


# pragma GCC diagnostic ignored "-Waggregate-return"



/**
 * Perform an integer division and return
 * both the quotient and the remainder.
 * 
 * @etymology  `(i)nt(max)_t`-function: (div)ide.
 * 
 * @param   numerator    The numerator.
 * @param   denominator  The denominator, must not be 0 lest
 *                       the process will be killed by SIGFPE.
 * @return               The quotient in `.quot`, and
 *                       the remainder in `.rem`.
 * 
 * @since  Always.
 */
imaxdiv_t imaxdiv(intmax_t numerator, intmax_t denominator)
{
  return (imaxdiv_t){ numerator / denominator, numerator % denominator };
}

