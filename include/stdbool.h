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
#ifndef __bool_true_false_are_defined
#include <slibc/version.h>
#include <slibc/features.h>

#if !defined(_SLIBC_SUPPRESS_WARNINGS) && !defined(__C99__)
# warning "<stdbool.h> requires that C99 or newer revision is used."
#endif


/* These should be macros, because the user is allowed to undefine them.
 * It is however stated that this is an obsolescent feature that may be
 * removed in the future. */


/**
 * A variant of `int`. Any non-zero data casted to this type
 * is converted to 1 (just like prefixing with `!!`). This
 * assures that overflow during cast does not cause a non-zero
 * value to be converted to zero.
 * 
 * @etymology  (Bool)ean.
 * 
 * @since  Always.
 */
#define bool _Bool

/**
 * A true value.
 * 
 * @since  Always.
 */
#define true 1

/**
 * An untrue value.
 * 
 * @since  Always.
 */
#define false 0

/**
 * This macro can be relied on being defined and set to 1 if
 * <stdbool.h> has defined the type `bool` (as a macro) and
 * the constants (macros) `true` and `false`.
 * 
 * @since  Always.
 */
#define __bool_true_false_are_defined 1



#endif

