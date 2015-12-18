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
#include <arpa/inet.h>


/**
 * Convert a 64-bit quantity from host byte order
 * (little endian) to network byte order.
 * 
 * This is a slibc extension.
 * 
 * @etymology  (H)ost byte order (to) (n)etwork byte order, (l)ong (l)ong.
 * 
 * @param   value  A 64-bit quantity to convert.
 * @return         The value in network byte order.
 * 
 * @since  Always.
 */
uint64_t _htonll(uint64_t value)
{
  char rc[8];
  rc[0] = (value >> 56) & 255;
  rc[1] = (value >> 48) & 255;
  rc[2] = (value >> 40) & 255;
  rc[3] = (value >> 32) & 255;
  rc[4] = (value >> 24) & 255;
  rc[5] = (value >> 16) & 255;
  rc[6] = (value >>  8) & 255;
  rc[7] = (value >>  0) & 255;
  return *(uint64_t*)rc;
}

