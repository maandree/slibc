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
#ifndef _SYS_STAT_H
#define _SYS_STAT_H
#include <slibc/version.h>
#include <slibc/features.h>



/**
 * Users that are not the owner and are int the
 * group (“others”) have read permission.
 * 
 * @since  Always.
 */
#define S_IROTH  4

/**
 * Users that are not the owner and are int the
 * group (“others”) have write permission.
 * 
 * @since  Always.
 */
#define S_IWOTH  2

/**
 * Users that are not the owner and are int the
 * group (“others”) have execute permission.
 * Execute permission for directories means to
 * be able to list files in the directory.
 * 
 * @since  Always.
 */
#define S_IXOTH  1

/**
 * Users that are not the owner and are int the
 * group (“others”) have all/some permissions.
 * 
 * This macro is defined to be equivalent to
 * `(S_IROTH | S_IWOTH | S_IXOTH)`.
 * 
 * @since  Always.
 */
#define S_IRWXO  (S_IROTH | S_IWOTH | S_IXOTH)


/**
 * Users that are in the group but is not the
 * owner have read permission.
 * 
 * @since  Always.
 */
#define S_IRGRP  (S_IROTH << 3)

/**
 * Users that are in the group but is not the
 * owner have write permission.
 * 
 * @since  Always.
 */
#define S_IWGRP  (S_IWOTH << 3)

/**
 * Users that are in the group but is not the
 * owner have execute permission.
 * Execute permission for directories means to
 * be able to list files in the directory.
 * 
 * @since  Always.
 */
#define S_IXGRP  (S_IXOTH << 3)

/**
 * Users that are in the group but is not the
 * owner have all/some permissions.
 * 
 * This macro is defined to be equivalent to
 * `(S_IRGRP | S_IWGRP | S_IXGRP)`.
 * 
 * @since  Always.
 */
#define S_IRWXG  (S_IRGRP | S_IWGRP | S_IXGRP)


/**
 * The owner (“user”) has read permission.
 * 
 * @since  Always.
 */
#define S_IRUSR  (S_IROTH << 6)

/**
 * The owner (“user”) has write permission.
 * 
 * @since  Always.
 */
#define S_IWUSR  (S_IWOTH << 6)

/**
 * The owner (“user”) has execute permission.
 * Execute permission for directories means to
 * be able to list files in the directory.
 * 
 * @since  Always.
 */
#define S_IXUSR  (S_IXOTH << 6)

/**
 * The owner (“user”) has all/some permissions.
 * 
 * This macro is defined to be equivalent to
 * `(S_IRUSR | S_IWUSR | S_IXUSR)`.
 * 
 * @since  Always.
 */
#define S_IRWXU  (S_IRUSR | S_IWUSR | S_IXUSR)


/**
 * Set user ID upon execution (setuid; set-user-ID)
 * is set.
 * 
 * For executable files, when a user runs the
 * program (must have sufficient privileges to
 * do so, here is however documentation that is
 * is not required, so perhaps it is not required
 * on all systems, but it is required on Linux)
 * her effective user ID is switched to that of
 * the owner of the file. Most systems disregard
 * this flag for interpreted files, and can be
 * made ineffective with mount options.
 * 
 * For directories, on some systems, when a new
 * file or subdirectory is created, it inherit
 * the user ID (owner) of the directory in which
 * it is created.
 * 
 * @since  Always.
 */
#define S_ISUID  (4 << 9)

/**
 * Set group ID upon execution (setgid; set-group-ID)
 * is set.
 * 
 * For executable files, when a user runs the
 * program (must have sufficient privileges to
 * do so, here is however documentation that is
 * is not required, so perhaps it is not required
 * on all systems, but it is required on Linux)
 * her effective group ID is switched to that of
 * the group of the file. Most systems disregard
 * this flag for interpreted files, and can be
 * made ineffective with mount options.
 * 
 * For directories, on some systems, when a new
 * file or subdirectory is created, it inherit
 * the group ID of the directory in which it is
 * created.
 * 
 * On Linux, if set-group-ID is set, but members
 * of the group do not have execute permission
 * (`S_IXGRP` is cleared), the file locks on the
 * file are mandatory.
 * 
 * @since  Always.
 */
#define S_ISGID  (2 << 9)

/**
 * Sticky bit (as it is called for regular files) or
 * restricted deletion flag (as it is called for
 * directories) is set.
 * 
 * If set, for directories, unprivileged users
 * cannot remove or rename a file in the directory.
 * They have to own the file or the directory.
 * Directories that anyone can write to, such as
 * '/tmp' and '/var/tmp' usually has this set.
 * 
 * If set, for regular files, it saves the
 * text image of a the program to the swap device,
 * so it will load more quickly when run. This
 * is only present on some older Unix systems.
 * 
 * @since  Always.
 */
#define S_ISVTX  (1 << 9)



#if defined(__SLIBC_SOURCE)
/**
 * Everyone, or anyone, have read permission.
 * 
 * This macro is defined to be equivalent to
 * `(S_IRUSR | S_IRGRP | S_IROTH)`.
 * 
 * This is a slibc extension.
 * 
 * @since  Always.
 */
# define S_IRALL  (S_IRUSR | S_IRGRP | S_IROTH)

/**
 * Everyone, or anyone, have write permission.
 * 
 * This macro is defined to be equivalent to
 * `(S_IWUSR | S_IWGRP | S_IWOTH)`.
 * 
 * This is a slibc extension.
 * 
 * @since  Always.
 */
# define S_IWALL  (S_IWUSR | S_IWGRP | S_IWOTH)

/**
 * Everyone, or anyone, have execute permission.
 * Execute permission for directories means to
 * be able to list files in the directory.
 * 
 * This macro is defined to be equivalent to
 * `(S_IXUSR | S_IXGRP | S_IXOTH)`.
 * 
 * This is a slibc extension.
 * 
 * @since  Always.
 */
# define S_IXALL  (S_IXUSR | S_IXGRP | S_IXOTH)

/**
 * Set-user-ID bit, set-group-ID bit, and/or sticky bit
 * is set.
 * 
 * This macro is defined to be equivalent to
 * `(S_ISUID | S_ISGID | S_ISVTX)`.
 * 
 * This is a slibc extension.
 * 
 * @since  Always.
 */
# define S_ISALL  (S_ISUID | S_ISGID | S_ISVTX)
#endif



#endif

