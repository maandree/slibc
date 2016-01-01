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
#include <arpa/inet.h>
#include <bits/intconf.h>



/**
 * Convert a 16-bit quantity from host byte order
 * little endian) to network byte order.
 * 
 * @etymology  (H)ost byte order (to) (n)etwork byte order, (s)hort.
 * 
 * @param   value  A 16-bit quantity to convert.
 * @return         The value in network byte order.
 * 
 * @since  Always.
 */
uint16_t _htons(uint16_t value)
{
#if __INT16_BYTEORDER == 0x0102
  return value;
#else
  return (value >> 8) | (value << 8);
#endif
}

