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
 * Convert a 32-bit quantity from network byte order
 * (little endian) to host byte order.
 * 
 * @etymology  (N)etwork byte order (to) (h)ost byte order, (l)ong.
 * 
 * @param   value  A 32-bit quantity to convert.
 * @return         The value in host byte order.
 * 
 * @since  Always.
 */
uint32_t _ntohl(uint32_t value)
{
#if __INT32_BYTEORDER == 0x01020304L
  return value;
#elif __INT32_BYTEORDER == 0x04030201L
  return (value >> 24) | ((value & 0xFF0000) >> 8) | ((value & 0x00FF00) << 8) | (value << 24);
#elif __INT32_BYTEORDER == 0x02010403L
  return (value & 0xFF00FF00) >> 8) | ((value & 0x00FF00FF) << 8);
#else
  unsigned char* v = (unsigned char*)&value;
  uint32_t rc = 0;
  rc |= (uint32_t)(v[0]) << 24;
  rc |= (uint32_t)(v[1]) << 16;
  rc |= (uint32_t)(v[2]) <<  8;
  rc |= (uint32_t)(v[3]) <<  0;
  return rc;
#endif
}

