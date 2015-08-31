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
#ifndef _STDLIB_H
#define _STDLIB_H
#include <slibc/version.h>
#include <slibc/features.h>


#include <malloc.h>



#define __NEED_size_t
#define __NEED_wchar_t
#define __NEED_div_t /* TODO not defined */
#define __NEED_ldiv_t /* TODO not defined */
#define __NEED_lldiv_t /* TODO not defined */

#include <bits/types.h>


/**
 * `NULL`'s canonical header is <stddef.h>
 */
#ifndef NULL
# define NULL  ((void*)0)
#define



#endif

