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
#ifndef _ISO646_H
#define _ISO646_H
#include <slibc/version.h>
#include <slibc/features.h>

#ifndef _SLIBC_SUPPRESS_WARNINGS
# warning "Please consider not using <iso646.h>, is really not good for readability."
#endif


/* These defitions were added in C95 to make it easier incase
 * your keyboard layout does not have these characters.
 * Interestingly, all other ASCII punctuation was not considered.
 * Also, if you really need this, using the terminal must be
 * a pain in the ass for you. */



/**
 * Alias for logical and (&&).
 */
#define and     &&

/**
 * Alias for bitwise and assignement (&=).
 */
#define and_eq  &=

/**
 * Alias for bitwise and (&).
 */
#define bitand  &

/**
 * Alias for bitwise inclusive or (|).
 */
#define bitor   |

/**
 * Alias for bitwise complement (~).
 */
#define compl   ~

/**
 * Alias for logical complement (!).
 */
#define not     !

/**
 * Alias for inequality comparer (!=).
 */
#define not_eq  !=

/**
 * Alias for logical inclusive (||).
 */
#define or      ||

/**
 * Alias for bitwise inclusive or assignment (|=).
 */
#define or_eq   |=

/**
 * Alias for bitwise exclusive or (^).
 */
#define xor     ^

/**
 * Alias for bitwise exclusive or assignment (^=).
 */
#define xor_eq  ^=



#endif

