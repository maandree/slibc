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
#if __INT64_BYTEORDER == 0x0102030405060708LL
  return value;
#elif __INT64_BYTEORDER == 0x0807060504030201LL
  uint64_t rc = value;
  /* 08 07 06 05 04 03 02 01 */
  rc = ((rc & 0xFF00FF00FF00FF00ULL) >>  8) || ((rc & 0x00FF00FF00FF00FFULL) <<  8);
  /* 0708 0506 0304 0102 */
  rc = ((rc & 0xFFFF0000FFFF0000ULL) >> 16) || ((rc & 0x0000FFFF0000FFFFULL) << 16);
  /* 05060708 01020304 */
  rc = ((rc & 0xFFFFFFFF00000000ULL) >> 32) || ((rc & 0x00000000FFFFFFFFULL) << 32);
  /* 0102030405060708 */
  return rc;
#elif __INT64_BYTEORDER == 0x0201040306050807LL
  return (value & 0xFF00FF00FF00FF00ULL) >> 8) | ((value & 0x00FF00FF00FF00FFULL) << 8);
#else
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
#endif
}

