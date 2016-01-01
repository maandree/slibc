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
#ifndef _SLIBC_PRINT_H
#define _SLIBC_PRINT_H
#include <slibc/version.h>
#include <slibc/features.h>
#ifndef __PORTABLE



#define __NEED_size_t
#define __NEED_ssize_t
#define __NEED_wchar_t
#define __NEED_intmax_t
#define __NEED_va_list
#include <bits/types.h>



/**
 * Structure used by extensions to `generic_printf`-function
 * to request that additionally arguments be added before the
 * function is called again.
 * 
 * @etymology  (`generic_printf`)-subsystem: (ext)ension (queue).
 * 
 * @since  Always.
 */
struct generic_printf_ext_queue
{
  /**
   * Sizes, in bytes, of the missing arguments.
   * Only 1, 2, 4 and 8 are allowed.
   * 
   * @since  Always.
   */
  char sizes[4];
  
  /**
   * The indices of the missing arguments.
   * 
   * @since  Always.
   */
  size_t indices[4];
  
  /**
   * The amount of missing arguments.
   * `sizes` and `indices` can only hold up to
   * 4 arguments, the function will be later
   * again to retrieve information about the
   * omitted arguments. To avoid a deadlock,
   * add arguments in the order of their index
   * if there are more than 4 missing arguments.
   * 
   * @since  Always.
   */
  size_t count;
};


/**
 * Function-type used by `generic_printf` and `vgeneric_wprintf`
 * to write a string.
 * 
 * @etymology  (`generic_printf`)-subsystem: (write-func)tion, `(t)ypedef`.
 * 
 * @param   text    The text segment to print, it will only contain
 *                  a NUL byte if that NUL byte shall be printed.
 * @param   length  The length of `text`.
 * @param   data    The value passed to `generic_printf` or
 *                  `vgeneric_wprintf` via the parameter `data`.
 * @return          Zero on success, -1 on error. `errno` shall
 *                  be set on error.
 * 
 * @since  Always.
 */
typedef int (* generic_printf_write_func_t)(const char*, size_t, void*);

/**
 * Variant of `generic_printf_write_func_t` used for
 * `generic_wprintf` and `vgeneric_wprintf`.
 * 
 * @etymology  (`generic_wprintf`)-subsystem: (write-func)tion, `(t)ypedef`.
 * 
 * @since  Always.
 */
typedef int (* generic_wprintf_write_func_t)(const wchar_t*, size_t, void*);

/**
 * Function-type used by `generic_printf` and `vgeneric_wprintf`
 * to write a string if a custom formatting code was encountered.
 * 
 * @etymology  (`generic_printf`)-subsystem: (ext)ension(-func)tion, `(t)ypedef`.
 * 
 * @param   code        The %-code, excluding the %.
 * @param   args        Formatting arguments cased to `intmax`.
 * @param   argn        The number of formatting arguments in `args`.
 * @param   silent      Non-zero if the function must not perform a write.
 * @param   data        The value passed to `generic_printf` or
 *                      `vgeneric_wprintf` via the parameter `data`.
 * @param   queue_data  Used to send information to the calling function
 *                      about missing arguments.
 * @return              The number of written characters, -1 on error.
 *                      `errno` shall be set on error. -2 shall be returned
 *                      if argument index equal to or greater than the
 *                      value of `argn`, if `queue_data` must be set.
 * 
 * @throws  EINVAL  If `code` could not be recognised.
 * 
 * @since  Always.
 */
typedef ssize_t (* generic_printf_ext_func_t)(const char*, intmax_t*, size_t, int, void*,
					      struct generic_printf_ext_queue*);

/**
 * Variant of `generic_printf_ext_func_t` used for
 * `generic_wprintf` and `vgeneric_wprintf`.
 * 
 * @etymology  (`generic_wprintf`)-subsystem: (ext)ension(-func)tion, `(t)ypedef`.
 * 
 * @since  Always.
 */
typedef ssize_t (* generic_wprintf_ext_func_t)(const wchar_t*, intmax_t*, size_t, int, void*,
					       struct generic_printf_ext_queue*);


/**
 * An almost fully generic `printf`-function.
 * 
 * @etymology  (Generic) (`wprintf`)-function.
 * 
 * @param   write_function      Function used to write the string. `NULL` if
 *                              it shall not be printed but only measured.
 * @param   extension_function  Function used to extend the functions formatting codes.
 *                              `NULL` if not extensions are to be used.
 * @param   maximum_length      The maximum amount of bytes to write, including the
 *                              NUL byte, ignored if `limited_length` is zero.
 * @param   limited_length      Whether `maximum_length` shall be used.
 * @param   actual_length       Output parameter for the length of the printed string,
 *                              this includes any text that was truncated but not the
 *                              NUL character. Must not be `NULL`.
 * @param   terminate           Whether a NUL character shall be printed at the end.
 * @param   data                Data to pass to `write_function` and
 *                              `extension_function`, it should contain
 *                              the print-sink, and any state data neccessary
 *                              since the functions may be called multiple times.
 * @param   format              The formatting-string, see `fprintf` for details.
 * @param   ...                 The formatting-arguments.
 * @return                      Zero on success, -1 on error. On error, `errno`
 *                              is set to indicate the error.
 * 
 * @throws          Any error thrown by `write_function` or `extension_function`.
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * 
 * @since  Always.
 */
int generic_printf(generic_printf_write_func_t, generic_printf_ext_func_t,
		   size_t, int, size_t* restrict, int, void*, const char*, ...)
  __GCC_ONLY(__attribute__((__nonnull__(5, 8), __format__(__slibc_printf__, 8, 9), __warn_unused_result__)));

/**
 * Variant of `generic_printf` that uses `va_list`
 * instead of variadic arguments.
 * 
 * @etymology  (V)ariadic version of (`generic_printf`).
 * 
 * @param   write_function      Function used to write the string. `NULL` if
 *                              it shall not be printed but only measured.
 * @param   extension_function  Function used to extend the functions formatting codes.
 *                              `NULL` if not extensions are to be used.
 * @param   maximum_length      The maximum amount of bytes to write, including the
 *                              NUL byte, ignored if `limited_length` is zero.
 * @param   limited_length      Whether `maximum_length` shall be used.
 * @param   actual_length       Output parameter for the length of the printed string,
 *                              this includes any text that was truncated but not the
 *                              NUL character. Must not be `NULL`.
 * @param   terminate           Whether a NUL character shall be printed at the end.
 * @param   data                Data to pass to `write_function` and
 *                              `extension_function`, it should contain
 *                              the print-sink, and any state data neccessary
 *                              since the functions may be called multiple times.
 * @param   format              The formatting-string, see `fprintf` for details.
 * @param   args                The formatting-arguments.
 * @return                      Zero on success, -1 on error. On error, `errno`
 *                              is set to indicate the error.
 * 
 * @throws          Any error thrown by `write_function` or `extension_function`.
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * 
 * @since  Always.
 */
int vgeneric_printf(generic_printf_write_func_t, generic_printf_ext_func_t,
		    size_t, int, size_t* restrict, int, void*, const char*, va_list)
  __GCC_ONLY(__attribute__((__nonnull__(5, 8), __warn_unused_result__)));

/**
 * Variant of `generic_printf` uses `wchar_t` instead of `char`;
 * 
 * @etymology  (Generic) (`printf`)-function.
 * 
 * @param   write_function      Function used to write the string. `NULL` if
 *                              it shall not be printed but only measured.
 * @param   extension_function  Function used to extend the functions formatting codes.
 *                              `NULL` if not extensions are to be used.
 * @param   maximum_length      The maximum amount of wide characters to write,
 *                              including the NUL wide character, ignored if
 *                              `limited_length` is zero.
 * @param   limited_length      Whether `maximum_length` shall be used.
 * @param   actual_length       Output parameter for the length of the printed string,
 *                              this includes any text that was truncated but not the
 *                              NUL character. Must not be `NULL`.
 * @param   terminate           Whether a NUL character shall be printed at the end.
 * @param   data                Data to pass to `write_function` and
 *                              `extension_function`, it should contain
 *                              the print-sink, and any state data neccessary
 *                              since the functions may be called multiple times.
 * @param   format              The formatting-string, see `fprintf` for details.
 * @param   ...                 The formatting-arguments.
 * @return                      Zero on success, -1 on error. On error, `errno`
 *                              is set to indicate the error.
 * 
 * @throws          Any error thrown by `write_function` or `extension_function`.
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * 
 * @since  Always.
 */
int generic_wprintf(generic_wprintf_write_func_t, generic_wprintf_ext_func_t,
		    size_t, int, size_t* restrict, int, void*, const wchar_t*, ...)
  __GCC_ONLY(__attribute__((__nonnull__(5, 8), __warn_unused_result__)));

/**
 * Variant of `generic_wprintf` that uses `va_list`
 * instead of variadic arguments.
 * 
 * @etymology  (V)ariadic version of (`generic_wprintf`).
 * 
 * @param   write_function      Function used to write the string. `NULL` if
 *                              it shall not be printed but only measured.
 * @param   extension_function  Function used to extend the functions formatting codes.
 *                              `NULL` if not extensions are to be used.
 * @param   maximum_length      The maximum amount of wide characters to write,
 *                              including the NUL wide character, ignored if
 *                              `limited_length` is zero.
 * @param   limited_length      Whether `maximum_length` shall be used.
 * @param   actual_length       Output parameter for the length of the printed string,
 *                              this includes any text that was truncated but not the
 *                              NUL character. Must not be `NULL`.
 * @param   terminate           Whether a NUL character shall be printed at the end.
 * @param   data                Data to pass to `write_function` and
 *                              `extension_function`, it should contain
 *                              the print-sink, and any state data neccessary
 *                              since the functions may be called multiple times.
 * @param   format              The formatting-string, see `fprintf` for details.
 * @param   ...                 The formatting-arguments.
 * @return                      Zero on success, -1 on error. On error, `errno`
 *                              is set to indicate the error.
 * 
 * @throws          Any error thrown by `write_function` or `extension_function`.
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * 
 * @since  Always.
 */
int vgeneric_wprintf(generic_wprintf_write_func_t, generic_wprintf_ext_func_t,
		     size_t, int, size_t* restrict, int, void*, const wchar_t*, va_list)
  __GCC_ONLY(__attribute__((__nonnull__(5, 8), __warn_unused_result__)));



#endif
#endif

