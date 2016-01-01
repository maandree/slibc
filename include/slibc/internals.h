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
#ifndef _SLIBC_INTERNALS_H
#define _SLIBC_INTERNALS_H

#include <errno.h>



#define _(msg)  msg


#define OVERFLOW(op, a, b, res, errnum, failrc)	 \
  do						 \
    if (__builtin_##op##_overflow(a, b, res))	 \
      return errno = (errnum), (failrc);	 \
  while (0) 


#define MEM_OVERFLOW(op, a, b, res)  \
  OVERFLOW(op, a, b, res, ENOMEM, NULL)



#endif

