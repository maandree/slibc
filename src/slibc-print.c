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
#include <slibc-print.h>
#include <stdarg.h>



/**
 * An almost fully generic `printf`-function.
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
int generic_printf(generic_printf_write_func_t write_function, generic_printf_ext_func_t extension_function,
		   size_t maximum_length, int limited_length, size_t* restrict actual_length, int terminate,
		   void* data, const char* format, ...)
{
  int r;
  va_list args;
  va_start(args, format);
  r = vgeneric_printf(write_function, extension_function, maximum_length,
		      limited_length, actual_length, terminate, data, format, args);
  va_end(args);
  return r;
}


/**
 * Variant of `generic_printf` that uses `va_list`
 * instead of variadic arguments.
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
int vgeneric_printf(generic_printf_write_func_t write_function, generic_printf_ext_func_t extension_function,
		    size_t maximum_length, int limited_length, size_t* restrict actual_length, int terminate,
		    void* data, const char* format, va_list args)
{
  /* TODO vgeneric_printf */
  return 0;
  (void) write_function;
  (void) extension_function;
  (void) maximum_length;
  (void) limited_length;
  (void) actual_length;
  (void) terminate;
  (void) data;
  (void) format;
  (void) args;
}


/**
 * Variant of `generic_printf` uses `wchar_t` instead of `char`;
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
int generic_wprintf(generic_wprintf_write_func_t write_function, generic_wprintf_ext_func_t extension_function,
		    size_t maximum_length, int limited_length, size_t* restrict actual_length, int terminate,
		    void* data, const wchar_t* format, ...)
{
  int r;
  va_list args;
  va_start(args, format);
  r = vgeneric_wprintf(write_function, extension_function, maximum_length,
		       limited_length, actual_length, terminate, data, format, args);
  va_end(args);
  return r;
}


/**
 * Variant of `generic_wprintf` that uses `va_list`
 * instead of variadic arguments.
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
int vgeneric_wprintf(generic_wprintf_write_func_t write_function, generic_wprintf_ext_func_t extension_function,
		     size_t maximum_length, int limited_length, size_t* restrict actual_length, int terminate,
		     void* data, const wchar_t* format, va_list args)
{
  /* TODO vgeneric_wprintf */
  return 0;
  (void) write_function;
  (void) extension_function;
  (void) maximum_length;
  (void) limited_length;
  (void) actual_length;
  (void) terminate;
  (void) data;
  (void) format;
  (void) args;
}

