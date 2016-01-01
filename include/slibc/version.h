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
#ifndef _SLIBC_VERSION_H
#define _SLIBC_VERSION_H


/* Any header file is in the top-level of the header direction,
 * and is provided by slibc, will include this header file.
 * That way you do not need to include an slibc specific header
 * to find out whether you are using slibc. */



/**
 * The major-number in the version of slibc that
 * you are compiling against.
 * 
 * The version is formatted `<major>.<minor>.<micro>.<patch>`,
 * however `.<patch>` is omitted if the patch-number is nought,
 * `.<micro>` is omitted if the both the patch- and micro-number
 * are nought.
 * 
 * @since  Always.
 */
#define __SLIBC_MAJOR__  0

/**
 * The minor-number in the version of slibc that
 * you are compiling against.
 * 
 * @since  Always.
 */
#define __SLIBC_MINOR__  1

/**
 * The micro-number in the version of slibc that
 * you are compiling against.
 * 
 * @since  Always.
 */
#define __SLIBC_MICRO__  0

/**
 * The patch-number in the version of slibc that
 * you are compiling against.
 * 
 * @since  Always.
 */
#define __SLIBC_PATCH__  0



/**
 * This function is used internal for comparing
 * slibc versions.
 * 
 * @param   major  The major-number of the version.
 * @param   minor  The minor-number of the version.
 * @param   micro  The micro-number of the version.
 * @param   patch  The patch-number of the version.
 * @return         A scalar integer describing the version.
 */
#define __SLIBC_CONSTRUCT_VERSION(major, minor, micro, patch)  \
  (((major ## L) << (3 * 7)) |  \
   ((minor ## L) << (2 * 7)) |  \
   ((micro ## L) << (1 * 7)) |  \
   ((patch ## L) << (0 * 7)))


/**
 * The scalar integer describing the version
 * of slibc you are compiling against.
 * 
 * You can check if this header is defined to
 * check whether you are using slibc at all.
 * 
 * @since  Always.
 */
#define __SLIBC__  \
  __SLIBC_CONSTRUCT_VERSION(__SLIBC_MAJOR__, __SLIBC_MINOR__,  \
			    __SLIBC_MICRO__, __SLIBC_PATCH__)


/**
 * Test whether you are compiling against a
 * specific version of slibc, or against any
 * newer version of slibc.
 * 
 * @param  major  The major-number of the least required version of slibc.
 * @param  minor  The minor-number of the least required version of slibc.
 * @param  micro  The micro-number of the least required version of slibc.
 * @param  patch  The patch-number of the least required version of slibc.
 * 
 * @since  Always.
 */
#define __SLIBC_REQ_4__(major, minor, micro, patch)  \
  (__SLIBC__ >= __SLIBC_CONSTRUCT_VERSION(major, minor, micro, patch))

/**
 * Test whether you are compiling against a
 * specific version of slibc, or against any
 * newer version of slibc.
 * 
 * @param  major  The major-number of the least required version of slibc.
 * @param  minor  The minor-number of the least required version of slibc.
 * @param  micro  The micro-number of the least required version of slibc.
 * 
 * @since  Always.
 */
#define __SLIBC_REQ_3__(major, minor, micro)  \
  __SLIBC_REQ_4__(major, minor, micro, patch)

/**
 * Test whether you are compiling against a
 * specific version of slibc, or against any
 * newer version of slibc.
 * 
 * @param  major  The major-number of the least required version of slibc.
 * @param  minor  The minor-number of the least required version of slibc.
 * 
 * @since  Always.
 */
#define __SLIBC_REQ__(major, minor)  \
  __SLIBC_REQ_4__(major, minor, 0, 0)



#endif

