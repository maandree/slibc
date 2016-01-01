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
#ifndef _ARAP_INET_H
#define _ARAP_INET_H
#include <slibc/version.h>
#include <slibc/features.h>



#define __NEED_uint16_t
#define __NEED_uint32_t
#if defined(__SLIBC_SOURCE)
# define __NEED_uint64_t
#endif

#include <bits/types.h>



/* On some implementations, these functions are defined as macros. */

/**
 * Convert a 16-bit quantity from network byte order
 * little endian) to host byte order.
 * 
 * @etymology  (N)etwork byte order (to) (h)ost byte order, (s)hort.
 * 
 * @param   value  A 16-bit quantity to convert.
 * @return         The value in host byte order.
 * 
 * @since  Always.
 */
uint16_t _ntohs(uint16_t)
  __GCC_ONLY(__attribute__((__const__, __warn_unused_result__)));
#if !defined(__PORTABLE)
# define ntohs  _ntohs
#else
# define ntohs(value)  (_ntohs(value))
#endif

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
uint32_t _ntohl(uint32_t)
  __GCC_ONLY(__attribute__((__const__, __warn_unused_result__)));
#if !defined(__PORTABLE)
# define ntohl  _ntohl
#else
# define ntohl(value)  (_ntohl(value))
#endif

#if defined(__SLIBC_SOURCE)
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
uint64_t _ntohll(uint64_t)
  __GCC_ONLY(__attribute__((__const__, __warn_unused_result__)));
# if !defined(__PORTABLE)
#  define ntohll  _ntohll
# else
#  define ntohll(value)  (_ntohll(value))
# endif
#endif

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
uint16_t _htons(uint16_t)
  __GCC_ONLY(__attribute__((__const__, __warn_unused_result__)));
#if !defined(__PORTABLE)
# define htons  _htons
#else
# define htons(value)  (_htons(value))
#endif

/**
 * Convert a 32-bit quantity from host byte order
 * (little endian) to network byte order.
 * 
 * @etymology  (H)ost byte order (to) (n)etwork byte order, (l)ong.
 * 
 * @param   value  A 32-bit quantity to convert.
 * @return         The value in network byte order.
 * 
 * @since  Always.
 */
uint32_t _htonl(uint32_t)
  __GCC_ONLY(__attribute__((__const__, __warn_unused_result__)));
#if !defined(__PORTABLE)
# define htonl  _htonl
#else
# define htonl(value)  (_htonl(value))
#endif

#if defined(__SLIBC_SOURCE)
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
uint64_t _htonll(uint64_t)
  __GCC_ONLY(__attribute__((__const__, __warn_unused_result__)));
# if !defined(__PORTABLE)
#  define htonll  _htonll
# else
#  define htonll(value)  (_htonll(value))
# endif
#endif


/* TODO We "need" conversion to and from two's complement.
 *      It is important to remember than intN_t cannot be
 *      used for this functions because they require two's
 *      complement.
 *
 *         unsigned to_twos_complement(signed v) {
 *           unsigned r;
 *           if (v >= -0)
 *             return (unsigned)v;
 *           r = (unsigned)-v;
 *           r = ~(r - 1);
 *           return r;
 *         }
 *
 *         signed from_twos_complement(unsigned v) {
 *           signed r;
 *           if ((v >> (X_BIT - 1)) == 0)
 *             return (signed)v;
 *           r = ~r;
 *           if (r == X_MAX)
 *             return errno = ERANGE, 0;
 *           return errno = 0, r + 1;
 *         }
 */



#endif

