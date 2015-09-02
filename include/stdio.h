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
#ifndef _STDIO_H
#define _STDIO_H
#include <slibc/version.h>
#include <slibc/features.h>



#define __NEED_fpos_t /* TODO not implemented */
#define __NEED_off_t
#define __NEED_size_t
#define __NEED_ssize_t
#define __NEED_va_list
#if __STDC_VERSION__ >= 201112L
# define __NEED_max_align_t
#endif

#include <bits/types.h>



/* TODO implement I/O */
int fflush(void*);
#define stdin NULL
#define stdout NULL
#define stderr NULL
int printf(const char*, ...);
int fprintf(void*, const char*, ...);
int dprintf(int, const char*, ...);
int sprintf(char*, const char*, ...);
int snprintf(char*, size_t, const char*, ...);
#if (defined(_GNU_SOURCE) || defined(_SLIBC_SOURCE)) && !defined(__PORTABLE)
int asprintf(char**, const char*, ...);
#endif
int vprintf(const char*, va_list);
int vfprintf(void*, const char*, va_list);
int vdprintf(int, const char*, va_list);
int vsprintf(char*, const char*, va_list);
int vsnprintf(char*, size_t, const char*, va_list);
#if (defined(_GNU_SOURCE) || defined(_SLIBC_SOURCE)) && !defined(__PORTABLE)
int vasprintf(char**, const char*, va_list);
#endif



#endif

