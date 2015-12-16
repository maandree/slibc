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
 * Convert a 64-bit quantity from network byte order
 * (little endian) to host byte order.
 * 
 * This is a slibc extension.
 * 
 * @etymology  (N)etwork byte order (to) (h)ost byte order, (l)ong (l)ong.
 * 
 * @param   value  A 64-bit quantity to convert.
 * @return         The value in host byte order.
 * 
 * @since  Always.
 */
uint64_t _ntohll(uint64_t value)
{
  unsigned char* v = (unsigned char*)&value;
  uint64_t rc = 0;
  rc |= (uint64_t)(v[0]) << 56;
  rc |= (uint64_t)(v[1]) << 48;
  rc |= (uint64_t)(v[2]) << 40;
  rc |= (uint64_t)(v[3]) << 32;
  rc |= (uint64_t)(v[4]) << 24;
  rc |= (uint64_t)(v[5]) << 16;
  rc |= (uint64_t)(v[6]) <<  8;
  rc |= (uint64_t)(v[7]) <<  0;
  return rc;
}

