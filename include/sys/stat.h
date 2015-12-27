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
#ifndef _SYS_STAT_H
#define _SYS_STAT_H
#include <slibc/version.h>
#include <slibc/features.h>



#if defined(__SLIBC_SOURCE)
/**
 * Everyone, or anyone, have read permission.
 * 
 * @since  Always.
 */
# define S_IRALL  (S_IRUSR | S_IRGRP | S_IROTH)

/**
 * Everyone, or anyone, have write permission.
 * 
 * @since  Always.
 */
# define S_IWALL  (S_IWUSR | S_IWGRP | S_IWOTH)

/**
 * Everyone, or anyone, have execute permission.
 * Execute permission for directories means to
 * be able to list files in the directory.
 * 
 * @since  Always.
 */
# define S_IXALL  (S_IXUSR | S_IXGRP | S_IXOTH)

/**
 * Set-UID bit, set-GID bit, and/or sticky bit
 * is set.
 * 
 * @since  Always.
 */
# define S_ISALL  (S_ISUID | S_ISGID | S_ISVTX)
#endif



#endif

