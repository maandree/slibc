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
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <inttypes.h>
#include <unistd.h>
#include <string.h>
#include <wchar.h>
/* #include <slibc-scan.h> */


# pragma GCC diagnostic ignored "-Wcast-qual"
# pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"
/* TODO [v]sock[w]scanf (can use MSG_PEEK) */
/* TODO doc: performance issue on [v]d[w]scanf */



/* TODO add <slibc-scan.h> { */
# define generic_scanf_read_func_t  void*
# define generic_wscanf_read_func_t  void*
extern int vgeneric_scanf(void*, void*, size_t, size_t, void*, void*, char*, va_list);
extern int vgeneric_wscanf(void*, void*, size_t, size_t, void*, void*, wchar_t*, va_list);
/* } */


#define V(C)			\
  int r;			\
  va_list args;			\
  va_start(args, format);	\
  r = v##C;			\
  va_end(args);			\
  return r

#define S_CHAR(UNDERLAYING, MAXIMUM, LIMITED, DATA)			\
  return vgeneric_scanf((generic_scanf_read_func_t)UNDERLAYING, NULL,	\
			MAXIMUM, LIMITED, NULL, DATA, format, args)

#define S_WCHAR(UNDERLAYING, MAXIMUM, LIMITED, DATA)			\
  return vgeneric_wscanf((generic_wscanf_read_func_t)UNDERLAYING, NULL,	\
			 MAXIMUM, LIMITED, NULL, DATA, format, args)

#define FLOCK(F)    /* TODO lock stream */
#define FUNLOCK(F)  /* TODO unlock stream */


/* TODO implement underlaying scan functions { */
extern int read_string(void);
extern int read_stream(void);
extern int read_fd(void);
extern int wread_string(void);
extern int wread_stream(void);
extern int wread_fd(void);
/* } */



/**
 * This function is identical to `fscanf` with
 * `stdout` as the first argument.
 * 
 * @param   format  The format of the string.
 * @param   ...     The output parameter for the encoded values.
 * @return          The number successfully converted argument
 *                  (may be less than specified.) `EOF` is returned
 *                  if the end of the input is reached before the
 *                  first argument is successfully converted, or
 *                  on error.
 * 
 * @since  Always.
 */
int scanf(const char* restrict format, ...)
{
  V(scanf(format, args));
}


/**
 * Parse data from from a text stream.
 * 
 * TODO list format rules for fscanf
 * 
 * @param   stream  The input stream.
 * @param   format  The format of the string.
 * @param   ...     The output parameter for the encoded values.
 * @return          The number successfully converted argument
 *                  (may be less than specified.) `EOF` is returned
 *                  if the end of the input is reached before the
 *                  first argument is successfully converted, or
 *                  on error.
 * 
 * @since  Always.
 */
int fscanf(FILE* restrict stream, const char* restrict format, ...)
{
  V(fscanf(stream, format, args));
}


/**
 * This function is identical to `fscanf`,
 * except it reads from a string rather than
 * a file.
 * 
 * @param   input   The formatted string.
 * @param   format  The format of the string.
 * @param   ...     The output parameter for the encoded values.
 * @return          The number successfully converted argument
 *                  (may be less than specified.) `EOF` is returned
 *                  if the end of the input is reached before the
 *                  first argument is successfully converted, or
 *                  on error.
 * 
 * @since  Always.
 */
int sscanf(const char* restrict input, const char* restrict format, ...)
{
  V(sscanf(input, format, args));
}


/**
 * This function is identical to `fscanf`,
 * except it does not lock the stream.
 * 
 * This is a slibc extension.
 * 
 * @param   stream  The input stream.
 * @param   format  The format of the string.
 * @param   ...     The output parameter for the encoded values.
 * @return          The number successfully converted argument
 *                  (may be less than specified.) `EOF` is returned
 *                  if the end of the input is reached before the
 *                  first argument is successfully converted, or
 *                  on error.
 * 
 * @since  Always.
 */
int fscanf_unlocked(FILE* restrict stream, const char* restrict format, ...)
{
  V(fscanf_unlocked(stream, format, args));
}


/**
 * This function is identical to `scanf`,
 * except it will stop parsing the string
 * after a selected number of bytes, or
 * at the end of the string.
 * 
 * This is a slibc extension.
 * 
 * @param   input   The formatted string.
 * @param   length  The maximum number of bytes to read.
 * @param   format  The format of the string.
 * @param   ...     The output parameter for the encoded values.
 * @return          The number successfully converted argument
 *                  (may be less than specified.) `EOF` is returned
 *                  if the end of the input is reached before the
 *                  first argument is successfully converted, or
 *                  on error.
 * 
 * @since  Always.
 */
int snscanf(const char* restrict input, size_t length, const char* restrict format, ...)
{
  V(snscanf(input, length, format, args));
}


/**
 * This function is identical to `fscanf`,
 * except it is limited to file descriptor-backed
 * streams, and uses the file descriptor as the
 * first argument rather than the stream.
 * 
 * This is a slibc extension.
 * 
 * @param   fd      The file descriptor.
 * @param   format  The format of the string.
 * @param   ...     The output parameter for the encoded values.
 * @return          The number successfully converted argument
 *                  (may be less than specified.) `EOF` is returned
 *                  if the end of the input is reached before the
 *                  first argument is successfully converted, or
 *                  on error.
 * 
 * @since  Always.
 */
int dscanf(int fd, const char* restrict format, ...)
{
  V(dscanf(fd, format, args));
}


/**
 * This function is identical to `scanf`,
 * except it uses `va_list` instead of variadic arguments.
 * 
 * @param   format  The format of the string.
 * @param   args    The output parameter for the encoded values.
 * @return          The number successfully converted argument
 *                  (may be less than specified.) `EOF` is returned
 *                  if the end of the input is reached before the
 *                  first argument is successfully converted, or
 *                  on error.
 * 
 * @since  Always.
 */
int vscanf(const char* restrict format, va_list args)
{
  return vfscanf(stdout, format, args);
}


/**
 * This function is identical to `fscanf`,
 * except it uses `va_list` instead of variadic arguments.
 * 
 * @param   stream  The input stream.
 * @param   format  The format of the string.
 * @param   args    The output parameter for the encoded values.
 * @return          The number successfully converted argument
 *                  (may be less than specified.) `EOF` is returned
 *                  if the end of the input is reached before the
 *                  first argument is successfully converted, or
 *                  on error.
 * 
 * @since  Always.
 */
int vfscanf(FILE* restrict stream, const char* restrict format, va_list args)
{
  int r, saved_errno;
  FLOCK(stream);
  r = vfscanf_unlocked(stream, format, args);
  saved_errno = errno;
  FUNLOCK(stream);
  return errno = saved_errno, r;
}


/**
 * This function is identical to `sscanf`,
 * except it uses `va_list` instead of variadic arguments.
 * 
 * @param   input   The formatted string.
 * @param   format  The format of the string.
 * @param   args    The output parameter for the encoded values.
 * @return          The number successfully converted argument
 *                  (may be less than specified.) `EOF` is returned
 *                  if the end of the input is reached before the
 *                  first argument is successfully converted, or
 *                  on error.
 * 
 * @since  Always.
 */
int vsscanf(const char* restrict input, const char* restrict format, va_list args)
{
  S_CHAR(read_string, 0, 0, (char*)input);
}


/**
 * This function is identical to `fscanf_unlocked`,
 * except it uses `va_list` instead of variadic arguments.
 * 
 * This is a slibc extension.
 * 
 * @param   stream  The input stream.
 * @param   format  The format of the string.
 * @param   args    The output parameter for the encoded values.
 * @return          The number successfully converted argument
 *                  (may be less than specified.) `EOF` is returned
 *                  if the end of the input is reached before the
 *                  first argument is successfully converted, or
 *                  on error.
 * 
 * @since  Always.
 */
int vfscanf_unlocked(FILE* restrict stream, const char* restrict format, va_list args)
{
  S_CHAR(read_stream, 0, 0, stream);
}


/**
 * This function is identical to `snscanf`,
 * except it uses `va_list` instead of variadic arguments.
 * 
 * This is a slibc extension.
 * 
 * @param   input   The formatted string.
 * @param   length  The maximum number of bytes to read.
 * @param   format  The format of the string.
 * @param   args    The output parameter for the encoded values.
 * @return          The number successfully converted argument
 *                  (may be less than specified.) `EOF` is returned
 *                  if the end of the input is reached before the
 *                  first argument is successfully converted, or
 *                  on error.
 * 
 * @since  Always.
 */
int vsnscanf(const char* restrict input, size_t length, const char* restrict format, va_list args)
{
  S_CHAR(read_string, length, 1, (char*)input);
}


/**
 * This function is identical to `sscanf`,
 * except it uses `va_list` instead of variadic arguments.
 * 
 * This is a slibc extension.
 * 
 * @param   fd      The file descriptor.
 * @param   format  The format of the string.
 * @param   args    The output parameter for the encoded values.
 * @return          The number successfully converted argument
 *                  (may be less than specified.) `EOF` is returned
 *                  if the end of the input is reached before the
 *                  first argument is successfully converted, or
 *                  on error.
 * 
 * @since  Always.
 */
int vdscanf(int fd, const char* restrict format, va_list args)
{
  S_CHAR(read_fd, 0, 0, &fd);
}


/**
 * This function is identical to `scanf`,
 * except it uses `wchar_t` instead of `char`.
 * 
 * @param   format  The format of the string.
 * @param   ...     The output parameter for the encoded values.
 * @return          The number successfully converted argument
 *                  (may be less than specified.) `EOF` is returned
 *                  if the end of the input is reached before the
 *                  first argument is successfully converted, or
 *                  on error.
 * 
 * @since  Always.
 */
int wscanf(const wchar_t* restrict format, ...)
{
  V(wscanf(format, args));
}


/**
 * This function is identical to `fscanf`,
 * except it uses `wchar_t` instead of `char`.
 * 
 * @param   stream  The input stream.
 * @param   format  The format of the string.
 * @param   ...     The output parameter for the encoded values.
 * @return          The number successfully converted argument
 *                  (may be less than specified.) `EOF` is returned
 *                  if the end of the input is reached before the
 *                  first argument is successfully converted, or
 *                  on error.
 * 
 * @since  Always.
 */
int fwscanf(FILE* restrict stream, const wchar_t* restrict format, ...)
{
  V(fwscanf(stream, format, args));
}


/**
 * This function is identical to `sscanf`,
 * except it uses `wchar_t` instead of `char`.
 * 
 * @param   input   The formatted string.
 * @param   format  The format of the string.
 * @param   ...     The output parameter for the encoded values.
 * @return          The number successfully converted argument
 *                  (may be less than specified.) `EOF` is returned
 *                  if the end of the input is reached before the
 *                  first argument is successfully converted, or
 *                  on error.
 * 
 * @since  Always.
 */
int swscanf(const wchar_t* restrict input, const wchar_t* restrict format, ...)
{
  V(swscanf(input, format, args));
}


/**
 * This function is identical to `fscanf_unlocked`,
 * except it uses `wchar_t` instead of `char`.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   stream  The input stream.
 * @param   format  The format of the string.
 * @param   ...     The output parameter for the encoded values.
 * @return          The number successfully converted argument
 *                  (may be less than specified.) `EOF` is returned
 *                  if the end of the input is reached before the
 *                  first argument is successfully converted, or
 *                  on error.
 * 
 * @since  Always.
 */
int fwscanf_unlocked(FILE* restrict stream, const wchar_t* restrict format, ...)
{
  V(fwscanf_unlocked(stream, format, args));
}


/**
 * This function is identical to `snscanf`,
 * except it uses `wchar_t` instead of `char`.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   input   The formatted string.
 * @param   length  The maximum number of characters to read.
 * @param   format  The format of the string.
 * @param   ...     The output parameter for the encoded values.
 * @return          The number successfully converted argument
 *                  (may be less than specified.) `EOF` is returned
 *                  if the end of the input is reached before the
 *                  first argument is successfully converted, or
 *                  on error.
 * 
 * @since  Always.
 */
int snwscanf(const wchar_t* restrict input, size_t length, const wchar_t* restrict format, ...)
{
  V(snwscanf(input, length, format, args));
}


/**
 * This function is identical to `dscanf`,
 * except it uses `wchar_t` instead of `char`.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   fd      The file descriptor.
 * @param   format  The format of the string.
 * @param   ...     The output parameter for the encoded values.
 * @return          The number successfully converted argument
 *                  (may be less than specified.) `EOF` is returned
 *                  if the end of the input is reached before the
 *                  first argument is successfully converted, or
 *                  on error.
 * 
 * @since  Always.
 */
int dwscanf(int fd, const wchar_t* restrict format, ...)
{
  V(dwscanf(fd, format, args));
}


/**
 * This function is identical to `wscanf`,
 * except it uses `va_list` instead of variadic arguments.
 * 
 * @param   format  The format of the string.
 * @param   args    The output parameter for the encoded values.
 * @return          The number successfully converted argument
 *                  (may be less than specified.) `EOF` is returned
 *                  if the end of the input is reached before the
 *                  first argument is successfully converted, or
 *                  on error.
 * 
 * @since  Always.
 */
int vwscanf(const wchar_t* restrict format, va_list args)
{
  return vfwscanf(stdout, format, args);
}


/**
 * This function is identical to `fwscanf`,
 * except it uses `va_list` instead of variadic arguments.
 * 
 * @param   stream  The input stream.
 * @param   format  The format of the string.
 * @param   args    The output parameter for the encoded values.
 * @return          The number successfully converted argument
 *                  (may be less than specified.) `EOF` is returned
 *                  if the end of the input is reached before the
 *                  first argument is successfully converted, or
 *                  on error.
 * 
 * @since  Always.
 */
int vfwscanf(FILE* restrict stream, const wchar_t* restrict format, va_list args)
{
  int r, saved_errno;
  FLOCK(stream);
  r = vfwscanf_unlocked(stream, format, args);
  saved_errno = errno;
  FUNLOCK(stream);
  return errno = saved_errno, r;
}


/**
 * This function is identical to `swscanf`,
 * except it uses `va_list` instead of variadic arguments.
 * 
 * @param   input   The formatted string.
 * @param   format  The format of the string.
 * @param   args    The output parameter for the encoded values.
 * @return          The number successfully converted argument
 *                  (may be less than specified.) `EOF` is returned
 *                  if the end of the input is reached before the
 *                  first argument is successfully converted, or
 *                  on error.
 * 
 * @since  Always.
 */
int vswscanf(const wchar_t* restrict input, const wchar_t* restrict format, va_list args)
{
  S_WCHAR(wread_string, 0, 0, (wchar_t*)input);
}


/**
 * This function is identical to `fwscanf_unlocked`,
 * except it uses `va_list` instead of variadic arguments.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   stream  The input stream.
 * @param   format  The format of the string.
 * @param   args    The output parameter for the encoded values.
 * @return          The number successfully converted argument
 *                  (may be less than specified.) `EOF` is returned
 *                  if the end of the input is reached before the
 *                  first argument is successfully converted, or
 *                  on error.
 * 
 * @since  Always.
 */
int vfwscanf_unlocked(FILE* restrict stream, const wchar_t* restrict format, va_list args)
{
  S_WCHAR(wread_stream, 0, 0, stream);
}


/**
 * This function is identical to `snwscanf`,
 * except it uses `va_list` instead of variadic arguments.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   input   The formatted string.
 * @param   length  The maximum number of characters to read.
 * @param   format  The format of the string.
 * @param   args    The output parameter for the encoded values.
 * @return          The number successfully converted argument
 *                  (may be less than specified.) `EOF` is returned
 *                  if the end of the input is reached before the
 *                  first argument is successfully converted, or
 *                  on error.
 * 
 * @since  Always.
 */
int vsnwscanf(const wchar_t* restrict input, size_t length, const wchar_t* restrict format, va_list args)
{
  S_WCHAR(wread_string, length, 1, (wchar_t*)input);
}


/**
 * This function is identical to `swscanf`,
 * except it uses `va_list` instead of variadic arguments.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   fd      The file descriptor.
 * @param   format  The format of the string.
 * @param   args    The output parameter for the encoded values.
 * @return          The number successfully converted argument
 *                  (may be less than specified.) `EOF` is returned
 *                  if the end of the input is reached before the
 *                  first argument is successfully converted, or
 *                  on error.
 * 
 * @since  Always.
 */
int vdwscanf(int fd, const wchar_t* restrict format, va_list args)
{
  S_WCHAR(wread_fd, 0, 0, &fd);
}



/**
 * This function is identical to `scanf`.
 * 
 * @since  Always.
 */
int __isoc99_scanf(const char* restrict format, ...)
{
  V(scanf(format, args));
}

/**
 * This function is identical to `fscanf`.
 * 
 * @since  Always.
 */
int __isoc99_fscanf(FILE* restrict stream, const char* restrict format, ...)
{
  V(fscanf(stream, format, args));
}

/**
 * This function is identical to `sscanf`.
 * 
 * @since  Always.
 */
int __isoc99_sscanf(const char* restrict input, const char* restrict format, ...)
{
  V(sscanf(input, format, args));
}

/**
 * This function is identical to `vscanf`.
 * 
 * @since  Always.
 */
int __isoc99_vscanf(const char* restrict format, va_list args)
{
  return vscanf(format, args);
}

/**
 * This function is identical to `vfscanf`.
 * 
 * @since  Always.
 */
int __isoc99_vfscanf(FILE* restrict stream, const char* restrict format, va_list args)
{
  return vfscanf(stream, format, args);
}

/**
 * This function is identical to `vsscanf`.
 * 
 * @since  Always.
 */
int __isoc99_vsscanf(const char* restrict input, const char* restrict format, va_list args)
{
  return vsscanf(input, format, args);
}

/**
 * This function is identical to `wscanf`.
 * 
 * @since  Always.
 */
int __isoc99_wscanf(const wchar_t* restrict format, ...)
{
  V(wscanf(format, args));
}

/**
 * This function is identical to `fwscanf`.
 * 
 * @since  Always.
 */
int __isoc99_fwscanf(FILE* restrict stream, const wchar_t* restrict format, ...)
{
  V(fwscanf(stream, format, args));
}

/**
 * This function is identical to `swscanf`.
 * 
 * @since  Always.
 */
int __isoc99_swscanf(const wchar_t* restrict input, const wchar_t* restrict format, ...)
{
  V(swscanf(input, format, args));
}

/**
 * This function is identical to `vwscanf`.
 * 
 * @since  Always.
 */
int __isoc99_vwscanf(const wchar_t* restrict format, va_list args)
{
  return vwscanf(format, args);
}

/**
 * This function is identical to `vfwscanf`.
 * 
 * @since  Always.
 */
int __isoc99_vfwscanf(FILE* restrict stream, const wchar_t* restrict format, va_list args)
{
  return vfwscanf(stream, format, args);
}

/**
 * This function is identical to `vswscanf`.
 * 
 * @since  Always.
 */
int __isoc99_vswscanf(const wchar_t* restrict input, const wchar_t* restrict format, va_list args)
{
  return vswscanf(input, format, args);
}

