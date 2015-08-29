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
#ifndef _ERRNO_H
#define _ERRNO_H
#include <slibc/version.h>


#include <slibc/features.h>

/* TODO include error definitions */



/**
 * A modifiable lvalue used to describe an error
 * that has occurred in the thread.
 */
#define errno  (*__errno())


/**
 * Helper definition to `errno` used to
 * assured that the value is thread-dependent
 * and supported on all revisions of C.
 */
volatile int* __errno(void) __GCC_ONLY(__attribute__((__const__))); /* TODO not implemented */



#endif

