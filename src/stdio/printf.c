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
#include <slibc-print.h>
#include <inttypes.h>
#include <unistd.h>
#include <slibc-alloc.h>
#include <string.h>
#include <wchar.h>


#define INT_MAX  0x7FFFFFFF  /* TODO temporary */

#define V(C)			\
  int r;			\
  va_list args;			\
  va_start(args, format);	\
  r = v##C;			\
  va_end(args);			\
  return r

#define P_CHAR(UNDERLAYING, MAXIMUM, LIMITED, TERMINATE, DATA)				\
  size_t length;									\
  int r = vgeneric_printf((generic_printf_write_func_t)UNDERLAYING, NULL,		\
                          MAXIMUM, LIMITED, &length, TERMINATE, DATA, format, args);	\
  return r < 0 ? -1 : length < INT_MAX ? (int)length : INT_MAX

#define P_WCHAR(UNDERLAYING, MAXIMUM, LIMITED, TERMINATE, DATA)				\
  size_t length;									\
  int r = vgeneric_wprintf((generic_wprintf_write_func_t)UNDERLAYING, NULL,		\
                           MAXIMUM, LIMITED, &length, TERMINATE, DATA, format, args);	\
  return r < 0 ? -1 : length < INT_MAX ? (int)length : INT_MAX

#define FLOCK(F)    /* TODO lock stream */
#define FUNLOCK(F)  /* TODO unlock stream */



/**
 * Buffer information.
 */
struct buffer
{
  /**
   * The buffer.
   */
  union
  {
    /**
     * Byte-oriented buffer.
     */
    char* str;
    
    /**
     * Wide character-oriented buffer.
     */
    wchar_t* wcs;
    
  } buf;
  
  /**
   * Pointer to the size of the buffer, in number of elements.
   */
  size_t* size;
  
  /**
   * The write offset.
   */
  size_t off;
  
  /**
   * Whether `EXTALLOC_CLEAR`, `secure_realloc`,
   * or `secure_free` shall be used.
   */
  int secure;
  
  /**
   * Whether `.buf` shall be freed on error.
   */
  int free_on_error;
  
};


/**
 * Write a string segment to a buffer.
 * 
 * @param   text    The text to write, not NUL terminated.
 * @param   length  The length of `text`.
 * @param   buffer  Pointer to the output buffer, will be
 *                  updated to point to the end of the write.
 * @return          Zero on success, -1 on error.
 *                  This function is always successful.
 */
static int write_string(const char* text, size_t length, char* restrict* buffer)
{
  memcpy(*buffer, text, length);
  (*buffer) += length;
  return 0;
}


/**
 * Write a string segment to a buffer.
 * 
 * @param   text    The text to write, not NUL terminated.
 * @param   length  The length of `text`.
 * @param   buffer  Pointer to the output buffer, will be
 *                  updated to point to the end of the write.
 * @return          Zero on success, -1 on error.
 *                  This function is always successful.
 */
static int wwrite_string(const wchar_t* text, size_t length, wchar_t* restrict* buffer)
{
  wmemcpy(*buffer, text, length);
  (*buffer) += length;
  return 0;
}


/**
 * Write a string segment to a file.
 * 
 * @param   text    The text to write, not NUL terminated.
 * @param   length  The length of `text`.
 * @param   fdp     Pointer to the file descriptor of the file.
 * @return          Zero on success, -1 on error.
 * 
 * @throws  Any error specified for `write`.
 */
static int write_fd(const char* text, size_t length, int* fdp)
{
  /* TODO write_fd  */
  /*
  ssize_t wrote;
  size_t ptr = 0;
  while (ptr < length)
    {
      wrote = write(*fdp, text + ptr, length - ptr);
      if (wrote < 0)
	return -1;
      ptr += (size_t)wrote;
    }
  return 0;
  */
  return 0;
  (void) text, (void) length, (void) fdp;
}


/**
 * Write a string segment to a file.
 * 
 * @param   text    The text to write, not NUL terminated.
 * @param   length  The length of `text`.
 * @param   fdp     Pointer to the file descriptor of the file.
 * @return          Zero on success, -1 on error.
 * 
 * @throws  Any error specified for `write`.
 */
static int wwrite_fd(const wchar_t* text, size_t length, int* fdp)
{
  /* TODO wwrite_fd  */
  return 0;
  (void) text, (void) length, (void) fdp;
}


/**
 * Write a string segment to a socket with `send`.
 * 
 * @param   text    The text to write, not NUL terminated.
 * @param   length  The length of `text`.
 * @param   input   Element 0: pointer to the file descriptor of the file.
 *                  Element 1: flags for `send`.
 * @return          Zero on success, -1 on error.
 * 
 * @throws  Any error specified for `write`.
 */
static int send_fd(const char* text, size_t length, int* input)
{
  int fd = input[0], flags = input[1];
  /* TODO send_fd  */
  return 0;
  (void) text, (void) length, (void) fd, (void) flags;
}


/**
 * Write a string segment to a socket with `send`.
 * 
 * @param   text    The text to write, not NUL terminated.
 * @param   length  The length of `text`.
 * @param   input   Element 0: pointer to the file descriptor of the file.
 *                  Element 1: flags for `send`.
 * @return          Zero on success, -1 on error.
 * 
 * @throws  Any error specified for `write`.
 */
static int wsend_fd(const wchar_t* text, size_t length, int* input)
{
  int fd = input[0], flags = input[1];
  /* TODO wsend_fd  */
  return 0;
  (void) text, (void) length, (void) fd, (void) flags;
}


/**
 * Write a string segment to a stream.
 * 
 * @param   text    The text to write, not NUL terminated.
 * @param   length  The length of `text`.
 * @param   stream  The output stream.
 * @return          Zero on success, -1 on error.
 * 
 * @throws  Any error specified for `fwrite_unlocked`.
 */
static int write_stream(const char* text, size_t length, FILE* stream)
{
  /* TODO write_stream */
  /*
  size_t wrote = fwrite_unlocked(text, 1, length, stream);
  return wrote == length ? 0 : -1;
  */
  return 0;
  (void) text, (void) length, (void) stream;
}


/**
 * Write a string segment to a stream.
 * 
 * @param   text    The text to write, not NUL terminated.
 * @param   length  The length of `text`.
 * @param   stream  The output stream.
 * @return          Zero on success, -1 on error.
 * 
 * @throws  ENOMEM  The process cannot allocation the
 *                  sufficient amount of memory.
 * 
 * @throws  Any error specified for `fwrite_unlocked`.
 */
static int wwrite_stream(const wchar_t* text, size_t length, FILE* stream)
{
  /* TODO wwrite_stream */
  return 0;
  (void) text, (void) length, (void) stream;
}


/**
 * Write a string segment to a buffer and reallocate it necessary.
 * 
 * @param   text    The text to write, not NUL terminated.
 * @param   length  The length of `text`.
 * @param   buffer  Information about the buffer.
 * @return          Zero on success, -1 on error.
 * 
 * @throws  ENOMEM  The process cannot allocation the
 *                  sufficient amount of memory.
 */
static int write_buffer(const char* text, size_t length, struct buffer* buffer)
{
  enum extalloc_mode flags = EXTALLOC_MALLOC | (buffer->secure ? EXTALLOC_CLEAR : 0);
  char* new;
  
  if (buffer->off + length > *(buffer->size))
    {
      if (buffer->off || !*(buffer->size))
	new = (buffer->secure ? secure_realloc : fast_realloc)
	  (buffer->buf.str, *(buffer->size) * sizeof(char));
      else
	new = extalloc(buffer->buf.str, *(buffer->size) * sizeof(char), flags);
      
      if (new == NULL)
	{
	  if (buffer->free_on_error)
	    (buffer->secure ? secure_free : fast_free)(buffer->buf.str),
	      buffer->buf.str = NULL;
	  return -1;
	}
      *(buffer->size) = buffer->off + length;
      buffer->buf.str = new;
    }
  memcpy(buffer->buf.str, text, length);
  buffer->off += length;
  return 0;
}


/**
 * Write a string segment to a buffer and reallocate it necessary.
 * 
 * @param   text    The text to write, not NUL terminated.
 * @param   length  The length of `text`.
 * @param   buffer  Information about the buffer.
 * @return          Zero on success, -1 on error.
 */
static int wwrite_buffer(const wchar_t* text, size_t length, struct buffer* buffer)
{
  enum extalloc_mode flags = EXTALLOC_MALLOC | (buffer->secure ? EXTALLOC_CLEAR : 0);
  wchar_t* new;
  
  if (buffer->off + length > *(buffer->size))
    {
      if (buffer->off || !*(buffer->size))
	new = (buffer->secure ? secure_realloc : fast_realloc)
	  (buffer->buf.wcs, *(buffer->size) * sizeof(wchar_t));
      else
	new = extalloc(buffer->buf.wcs, *(buffer->size) * sizeof(wchar_t), flags);
      
      if (new == NULL)
	{
	  if (buffer->free_on_error)
	    (buffer->secure ? secure_free : fast_free)(buffer->buf.wcs),
	      buffer->buf.wcs = NULL;
	  return -1;
	}
      *(buffer->size) = buffer->off + length;
      buffer->buf.wcs = new;
    }
  wmemcpy(buffer->buf.wcs, text, length);
  buffer->off += length;
  return 0;
}



/**
 * This function is identical to `fprintf` with
 * `stdout` as the first argument.
 * 
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written bytes.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` bytes are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws          Any error specified for `fwrite`.
 * 
 * @since  Always.
 */
int printf(const char* restrict format, ...)
{
  V(printf(format, args));
}


/**
 * Print a formatted string to a stream.
 * 
 * TODO list format rules for fprintf
 * 
 * @param   stream  The output stream.
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written bytes.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` bytes are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws          Any error specified for `fwrite`.
 * 
 * @since  Always.
 */
int fprintf(FILE* restrict stream, const char* restrict format, ...)
{
  V(fprintf(stream, format, args));
}


/**
 * This function is identical to `fprintf`,
 * except it does not lock the stream.
 * 
 * This is a slibc extension.
 * 
 * @param   stream  The output stream.
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written bytes.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` bytes are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws          Any error specified for `fwrite_unlocked`.
 * 
 * @since  Always.
 */
int fprintf_unlocked(FILE* restrict stream, const char* restrict format, ...)
{
  V(fprintf_unlocked(stream, format, args));
}


/**
 * This function is identical to `fprintf`,
 * except it is limited to file descriptor-backed
 * streams, and uses the file descriptor as the
 * first argument rather than the stream.
 * 
 * @param   fd      The file descriptor.
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written bytes.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` bytes are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws           Any error specified for `write`.
 * 
 * @since  Always.
 */
int dprintf(int fd, const char* restrict format, ...)
{
  V(dprintf(fd, format, args));
}


/**
 * This function is identical to `dprintf`,
 * except it uses `send` instead of `write`
 * and supports transmissions flags.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   fd      The file descriptor.
 * @param   flags   Flags to pass to `send`, see `send`
 *                  for more information.
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written bytes.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` bytes are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws           Any error specified for `write`.
 * 
 * @since  Always.
 */
int sockprintf(int fd, int flags, const char* restrict format, ...)
{
  V(sockprintf(fd, flags, format, args));
}


/**
 * This function is identical to `fprintf`,
 * it prints to a buffer rather than a stream.
 * 
 * This is identical to `snprintf` with
 * `SIZE_MAX` as the second argument.
 * 
 * `sprintf` is(!) safe to use. As long as you allocate
 * the a large enough buffer. One way to do this is
 * by measuring the length of the result first.
 * 
 *     ssize_t n;
 *     char* buffer = NULL;
 *     snprintf(NULL, 0, "%zu%zn", your_value, &n);
 *     buffer = malloc((size_t)n * sizeof(char));
 *     if (buffer == NULL) goto fail;
 *     sprintf(buffer, "%zu", your_value);
 * 
 * If you don't care about portability, you can use
 * `asprintf`, `asprintfa` or `bprintf`. However, you
 * often do not need to measure the result with `snprintf`.
 * A maximum possible length can often be determined
 * at compile-time or only using `strlen'.
 * 
 *     char buffer[3 * sizeof(ssize_t) + 2]; // A very poor, but still safe,
 *                                           // approximation to log₁₀.
 *     spritnf(buffer, "%zi", your_signed_value);
 * 
 * These techniques guarantees that all of the string is
 * written, and is therefore preferable over replacing
 * `sprintf` with `snprintf`. Because of this, slibc
 * does not consider `sprintf` unsafe like some of the
 * more hokey C standard library implementations. This
 * is C damn it!
 * 
 *   “Almost anything can be unsafe if you don't use it properly.”
 * 
 * @param   buffer  The output buffer.
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written bytes, excluding
 *                  the NUL byte. On error, a negative value
 *                  (namely -1 in this implementation) is
 *                  returned. It is unspecified what shall
 *                  happen if more than `INT_MAX` non-NUL
 *                  bytes are written; in slibc, `INT_MAX`
 *                  is returned if more is written, you can
 *                  use "%zn" to find the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * 
 * @since  Always.
 */
int sprintf(char* restrict buffer, const char* restrict format, ...)
{
  V(sprintf(buffer, format, args));
}


/**
 * This function is identical to `sprintf`,
 * expect it truncates the output.
 * 
 * @param   buffer  The output buffer.
 * @param   size    The allocation size of `buffer`.
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written bytes, excluding
 *                  the NUL byte, that would have been written
 *                  if `size` was ignored. On error, a negative
 *                  value (namely -1 in this implementation) is
 *                  returned. It is unspecified what shall
 *                  happen if more than `INT_MAX` non-NUL
 *                  bytes would have been written; in slibc,
 *                  `INT_MAX` is returned if more would have
 *                  been written, you can use "%zn" to find the
 *                  actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * 
 * @since  Always.
 */
int snprintf(char* restrict buffer, size_t size, const char* restrict format, ...)
{
  V(snprintf(buffer, size, format, args));
}


/**
 * This function is identical to `sprintf`,
 * except it allocates a sufficiently large
 * buffer.
 * 
 * This is a GNU extension.
 * 
 * @param   buffer  Output parameter for the output buffer.
 *                  On error the content of this pointer is undefined.
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written bytes, excluding
 *                  the NUL byte. On error, a negative value
 *                  (namely -1 in this implementation) is
 *                  returned. It is unspecified what shall
 *                  happen if more than `INT_MAX` non-NUL
 *                  bytes are written; in slibc, `INT_MAX`
 *                  is returned if more is written, you can
 *                  use "%zn" to find the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws  ENOMEM  The process cannot allocation the
 *                  sufficient amount of memory.
 * 
 * @since  Always.
 */
int asprintf(char** restrict buffer, const char* restrict format, ...)
{
  V(asprintf(buffer, format, args));
}


/**
 * This function is identical to `asprintf`,
 * except it can reuse allocated buffers.
 * 
 * This is a slibc extension.
 * 
 * @param   buffer  Reference parameter for the output buffer.
 *                  It should point to the buffer than shall
 *                  be used, or point to `NULL` if a new buffer
 *                  shall be allocated. It will be updated with
 *                  a new buffer if it points to `NULL`, or the
 *                  new pointer if `buffer` needed to be reallocated.
 *                  On error, this pointer will only have been
 *                  updated if the buffer was reallocated during
 *                  the call; if it pointed to `NULL`, it will
 *                  still point to `NULL`.
 * @param   size    Reference parameter for the buffer size.
 *                  It shall point to a variable whose value is
 *                  the allocation size of `*buffer`, or point to
 *                  a variable whose value is zero if `*buffer`
 *                  is `NULL`.
 * @param   offset  The offset in the buffer where the function
 *                  shall start the printing.
 * @param   secure  Non-zero if the function must override the
 *                  buffer with zero before freeing it if it
 *                  creates a new allocation.
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written bytes, excluding
 *                  the NUL byte. On error, a negative value
 *                  (namely -1 in this implementation) is
 *                  returned. It is unspecified what shall
 *                  happen if more than `INT_MAX` non-NUL
 *                  bytes are written; in slibc, `INT_MAX`
 *                  is returned if more is written, you can
 *                  use "%zn" to find the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws  ENOMEM  The process cannot allocation the
 *                  sufficient amount of memory.
 * 
 * @since  Always.
 */
int bprintf(char** restrict buffer, size_t* restrict size, size_t offset,
	    int secure, const char* restrict format, ...)
{
  V(bprintf(buffer, size, offset, secure, format, args));
}


/**
 * This function is identical to `printf`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written bytes.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` bytes are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws          Any error specified for `fwrite`.
 * 
 * @since  Always.
 */
int vprintf(const char* restrict format, va_list args)
{
  return vfprintf(stdout, format, args);
}


/**
 * This function is identical to `fprintf`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * @param   stream  The output stream.
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written bytes.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` bytes are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws          Any error specified for `fwrite`.
 * 
 * @since  Always.
 */
int vfprintf(FILE* restrict stream, const char* restrict format, va_list args)
{
  int r, saved_errno;
  FLOCK(stream);
  r = vfprintf_unlocked(stream, format, args);
  saved_errno = errno;
  FUNLOCK(stream);
  return errno = saved_errno, r;
}


/**
 * This function is identical to `fprintf_unlocked`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * This is a slibc extension.
 * 
 * @param   stream  The output stream.
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written bytes.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` bytes are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws          Any error specified for `fwrite_unlocked`.
 * 
 * @since  Always.
 */
int vfprintf_unlocked(FILE* restrict stream, const char* restrict format, va_list args)
{
  P_CHAR(write_stream, 0, 0, 0, stream);
}


/**
 * This function is identical to `dprintf`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * @param   fd      The file descriptor.
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written bytes.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` bytes are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws          Any error specified for `write`.
 * 
 * @since  Always.
 */
int vdprintf(int fd, const char* restrict format, va_list args)
{
  P_CHAR(write_fd, 0, 0, 0, &fd);
}


/**
 * This function is identical to `sockprintf`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   fd      The file descriptor.
 * @param   flags   Flags to pass to `send`, see `send`
 *                  for more information.
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written bytes.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` bytes are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws           Any error specified for `write`.
 * 
 * @since  Always.
 */
int vsockprintf(int fd, int flags, const char* restrict format, va_list args)
{
  int input[] = {fd, flags};
  P_CHAR(send_fd, 0, 0, 0, input);
}


/**
 * This function is identical to `sprintf`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * @param   buffer  The output buffer.
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written bytes, excluding
 *                  the NUL byte. On error, a negative value
 *                  (namely -1 in this implementation) is
 *                  returned. It is unspecified what shall
 *                  happen if more than `INT_MAX` non-NUL
 *                  bytes are written; in slibc, `INT_MAX`
 *                  is returned if more is written, you can
 *                  use "%zn" to find the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * 
 * @since  Always.
 */
int vsprintf(char* restrict buffer, const char* restrict format, va_list args)
{
  char* buf = buffer;
  P_CHAR(write_string, 0, 0, 1, &buf);
}


/**
 * This function is identical to `snprintf`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * @param   buffer  The output buffer.
 * @param   size    The allocation size of `buffer`.
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written bytes, excluding
 *                  the NUL byte, that would have been written
 *                  if `size` was ignored. On error, a negative
 *                  value (namely -1 in this implementation) is
 *                  returned. It is unspecified what shall
 *                  happen if more than `INT_MAX` non-NUL
 *                  bytes would have been written; in slibc,
 *                  `INT_MAX` is returned if more would have
 *                  been written, you can use "%zn" to find the
 *                  actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * 
 * @since  Always.
 */
int vsnprintf(char* restrict buffer, size_t size, const char* restrict format, va_list args)
{
  char* buf = buffer;
  P_CHAR(write_string, size, 1, 1, &buf);
}


/**
 * This function is identical to `asprintf`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * This is a GNU extension.
 * 
 * @param   buffer  Output parameter for the output buffer.
 *                  On error the content of this pointer is undefined.
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written bytes, excluding
 *                  the NUL byte. On error, a negative value
 *                  (namely -1 in this implementation) is
 *                  returned. It is unspecified what shall
 *                  happen if more than `INT_MAX` non-NUL
 *                  bytes are written; in slibc, `INT_MAX`
 *                  is returned if more is written, you can
 *                  use "%zn" to find the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws  ENOMEM  The process cannot allocation the
 *                  sufficient amount of memory.
 * 
 * @since  Always.
 */
int vasprintf(char** restrict buffer, const char* restrict format, va_list args)
{
  char* buf = NULL;
  size_t _size = 0;
  int r = vbprintf(&buf, &_size, 0, 0, format, args);
  return r ? r : (*buffer = buf, 0);
}


/**
 * This function is identical to `bprintf`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * This is a slibc extension.
 * 
 * @param   buffer  Reference parameter for the output buffer.
 *                  It should point to the buffer than shall
 *                  be used, or point to `NULL` if a new buffer
 *                  shall be allocated. It will be updated with
 *                  a new buffer if it points to `NULL`, or the
 *                  new pointer if `buffer` needed to be reallocated.
 *                  On error, this pointer will only have been
 *                  updated if the buffer was reallocated during
 *                  the call; if it pointed to `NULL`, it will
 *                  still point to `NULL`.
 * @param   size    Reference parameter for the buffer size.
 *                  It shall point to a variable whose value is
 *                  the allocation size of `*buffer`, or point to
 *                  a variable whose value is zero if `*buffer`
 *                  is `NULL`.
 * @param   offset  The offset in the buffer where the function
 *                  shall start the printing.
 * @param   secure  Non-zero if the function must override the
 *                  buffer with zero before freeing it if it
 *                  creates a new allocation.
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written bytes, excluding
 *                  the NUL byte. On error, a negative value
 *                  (namely -1 in this implementation) is
 *                  returned. It is unspecified what shall
 *                  happen if more than `INT_MAX` non-NUL
 *                  bytes are written; in slibc, `INT_MAX`
 *                  is returned if more is written, you can
 *                  use "%zn" to find the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws  ENOMEM  The process cannot allocation the
 *                  sufficient amount of memory.
 * 
 * @since  Always.
 */
int vbprintf(char** restrict buffer, size_t* restrict size, size_t offset,
	     int secure, const char* restrict format, va_list args)
{
  struct buffer buf =
    {
      .buf.str = *buffer,
      .size = size,
      .off = offset,
      .secure = secure,
      .free_on_error = buffer == NULL,
    };
  P_CHAR(write_buffer, 0, 0, 1, &buf);
}


/**
 * This function is identical to `printf` except
 * it uses wide characters.
 * 
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written characters.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` characters are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws          Any error specified for `fwrite`.
 * 
 * @since  Always.
 */
int wprintf(const wchar_t* restrict format, ...)
{
  V(wprintf(format, args));
}


/**
 * This function is identical to `fprintf` except
 * it uses wide characters.
 * 
 * @param   stream  The output stream.
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written characters.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` characters are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws           Any error specified for `fwrite`.
 * 
 * @since  Always.
 */
int fwprintf(FILE* restrict stream, const wchar_t* restrict format, ...)
{
  V(fwprintf(stream, format, args));
}


/**
 * This function is identical to `fprintf_unlocked` except
 * it uses wide characters.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   stream  The output stream.
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written characters.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` characters are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws          Any error specified for `fwrite_unlocked`.
 * 
 * @since  Always.
 */
int fwprintf_unlocked(FILE* restrict stream, const wchar_t* restrict format, ...)
{
  V(fwprintf_unlocked(stream, format, args));
}


/**
 * This function is identical to `dprintf` except
 * it uses wide characters.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   fd      The file descriptor.
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written characters.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` characters are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws           Any error specified for `write`.
 * 
 * @since  Always.
 */
int dwprintf(int fd, const wchar_t* restrict format, ...)
{
  V(dwprintf(fd, format, args));
}


/**
 * This function is identical to `sockprintf`
 * except it uses wide characters.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   fd      The file descriptor.
 * @param   flags   Flags to pass to `send`, see `send`
 *                  for more information.
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written bytes.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` bytes are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws           Any error specified for `write`.
 * 
 * @since  Always.
 */
int sockwprintf(int fd, int flags, const wchar_t* restrict format, ...)
{
  V(sockwprintf(fd, flags, format, args));
}


/**
 * This function is identical to `snprintf`
 * (not `sprintf`) except it uses wide characters.
 * 
 * @param   buffer  The output buffer.
 * @param   size    The allocation size of `buffer`.
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written characters, excluding
 *                  the NUL character, that would have been written
 *                  if `size` was ignored. On error, a negative
 *                  value (namely -1 in this implementation) is
 *                  returned. It is unspecified what shall
 *                  happen if more than `INT_MAX` non-NUL
 *                  characters would have been written; in slibc,
 *                  `INT_MAX` is returned if more would have
 *                  been written, you can use "%zn" to find the
 *                  actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * 
 * @since  Always.
 */
int swprintf(wchar_t* restrict buffer, size_t size, const wchar_t* restrict format, ...)
{
  V(swprintf(buffer, size, format, args));
}


/**
 * This function is identical to `aswprintf` except
 * it uses wide characters.
 * 
 * This is a slibc extension added for completeness.
 * This is only available if GNU extensions are enabled.
 * 
 * @param   buffer  Output parameter for the output buffer.
 *                  On error the content of this pointer is undefined.
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written characters, excluding
 *                  the NUL character. On error, a negative value
 *                  (namely -1 in this implementation) is
 *                  returned. It is unspecified what shall
 *                  happen if more than `INT_MAX` non-NUL
 *                  characters are written; in slibc, `INT_MAX`
 *                  is returned if more is written, you can
 *                  use "%zn" to find the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws  ENOMEM  The process cannot allocation the
 *                  sufficient amount of memory.
 * 
 * @since  Always.
 */
int aswprintf(wchar_t** restrict buffer, const wchar_t* restrict format, ...)
{
  V(aswprintf(buffer, format, args));
}


/**
 * This function is identical to `bprintf` except
 * it uses wide characters.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   buffer  Reference parameter for the output buffer.
 *                  It should point to the buffer than shall
 *                  be used, or point to `NULL` if a new buffer
 *                  shall be allocated. It will be updated with
 *                  a new buffer if it points to `NULL`, or the
 *                  new pointer if `buffer` needed to be reallocated.
 *                  On error, this pointer will only have been
 *                  updated if the buffer was reallocated during
 *                  the call; if it pointed to `NULL`, it will
 *                  still point to `NULL`.
 * @param   size    Reference parameter for the buffer size,
 *                  in `wchar_t`.
 *                  It shall point to a variable whose value is
 *                  the allocation size of `*buffer`, or point to
 *                  a variable whose value is zero if `*buffer`
 *                  is `NULL`.
 * @param   offset  The offset in the buffer where the function
 *                  shall start the printing.
 * @param   secure  Non-zero if the function must override the
 *                  buffer with zero before freeing it if it
 *                  creates a new allocation.
 * @param   format  The formatting-string.
 * @param   ...     The formatting-arguments.
 * @return          The number of written characters, excluding
 *                  the NUL character. On error, a negative value
 *                  (namely -1 in this implementation) is
 *                  returned. It is unspecified what shall
 *                  happen if more than `INT_MAX` non-NUL
 *                  characters are written; in slibc, `INT_MAX`
 *                  is returned if more is written, you can
 *                  use "%zn" to find the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws  ENOMEM  The process cannot allocation the
 *                  sufficient amount of memory.
 * 
 * @since  Always.
 */
int bwprintf(wchar_t** restrict buffer, size_t* restrict size, size_t offset,
	     int secure, const wchar_t* restrict format, ...)
{
  V(bwprintf(buffer, size, offset, secure, format, args));
}


/**
 * This function is identical to `wprintf`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written characters.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` characters are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws          Any error specified for `fwrite`.
 * 
 * @since  Always.
 */
int vwprintf(const wchar_t* restrict format, va_list args)
{
  return vfwprintf(stdout, format, args);
}


/**
 * This function is identical to `fwprintf`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * @param   stream  The output stream.
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written characters.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` characters are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws          Any error specified for `fwrite`.
 * 
 * @since  Always.
 */
int vfwprintf(FILE* restrict stream, const wchar_t* restrict format, va_list args)
{
  int r, saved_errno;
  FLOCK(stream);
  r = vfwprintf_unlocked(stream, format, args);
  saved_errno = errno;
  FUNLOCK(stream);
  return errno = saved_errno, r;
}


/**
 * This function is identical to `fwprintf_unlocked`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   stream  The output stream.
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written characters.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` characters are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws          Any error specified for `fwrite_unlocked`.
 * 
 * @since  Always.
 */
int vfwprintf_unlocked(FILE* restrict stream, const wchar_t* restrict format, va_list args)
{
  P_WCHAR(wwrite_stream, 0, 0, 0, stream);
}


/**
 * This function is identical to `dwprintf`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   fd      The file descriptor.
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written characters.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` characters are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws           Any error specified for `write`.
 * 
 * @since  Always.
 */
int vdwprintf(int fd, const wchar_t* restrict format, va_list args)
{
  P_WCHAR(wwrite_fd, 0, 0, 0, &fd);
}


/**
 * This function is identical to `sockwprintf`
 * except it uses `va_list` instead of variadic argument.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   fd      The file descriptor.
 * @param   flags   Flags to pass to `send`, see `send`
 *                  for more information.
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written bytes.
 *                  On error, a negative value (namely -1
 *                  in this implementation) is returned.
 *                  It is unspecified what shall happen if
 *                  more than `INT_MAX` bytes are written;
 *                  in slibc, `INT_MAX` is returned if more
 *                  is written, you can use "%zn" to find
 *                  the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws           Any error specified for `write`.
 * 
 * @since  Always.
 */
int vsockwprintf(int fd, int flags, const wchar_t* restrict format, va_list args)
{
  int input[] = {fd, flags};
  P_WCHAR(wsend_fd, 0, 0, 0, input);
}


/**
 * This function is identical to `swprintf`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * @param   buffer  The output buffer.
 * @param   size    The allocation size of `buffer`.
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written characters, excluding
 *                  the NUL character, that would have been written
 *                  if `size` was ignored. On error, a negative
 *                  value (namely -1 in this implementation) is
 *                  returned. It is unspecified what shall
 *                  happen if more than `INT_MAX` non-NUL
 *                  characters would have been written; in slibc,
 *                  `INT_MAX` is returned if more would have
 *                  been written, you can use "%zn" to find the
 *                  actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * 
 * @since  Always.
 */
int vswprintf(wchar_t* restrict buffer, size_t size, const wchar_t* restrict format, va_list args)
{
  wchar_t* buf = buffer;
  P_WCHAR(wwrite_string, size, 1, 1, &buf);
}


/**
 * This function is identical to `aswprintf`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * This is a slibc extension added for completeness.
 * This is only available if GNU extensions are enabled.
 * 
 * @param   buffer  Output parameter for the output buffer.
 *                  On error the content of this pointer is undefined.
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written characters, excluding
 *                  the NUL character. On error, a negative value
 *                  (namely -1 in this implementation) is
 *                  returned. It is unspecified what shall
 *                  happen if more than `INT_MAX` non-NUL
 *                  characters are written; in slibc, `INT_MAX`
 *                  is returned if more is written, you can
 *                  use "%zn" to find the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws  ENOMEM  The process cannot allocation the
 *                  sufficient amount of memory.
 * 
 * @since  Always.
 */
int vaswprintf(wchar_t** restrict buffer, const wchar_t* restrict format, va_list args)
{
  wchar_t* buf = NULL;
  size_t _size = 0;
  int r = vbwprintf(&buf, &_size, 0, 0, format, args);
  return r ? r : (*buffer = buf, 0);
}


/**
 * This function is identical to `bwprintf`,
 * except it uses `va_list` instead of variadic argument.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   buffer  Reference parameter for the output buffer.
 *                  It should point to the buffer than shall
 *                  be used, or point to `NULL` if a new buffer
 *                  shall be allocated. It will be updated with
 *                  a new buffer if it points to `NULL`, or the
 *                  new pointer if `buffer` needed to be reallocated.
 *                  On error, this pointer will only have been
 *                  updated if the buffer was reallocated during
 *                  the call; if it pointed to `NULL`, it will
 *                  still point to `NULL`.
 * @param   size    Reference parameter for the buffer size,
 *                  in `wchar_t`.
 *                  It shall point to a variable whose value is
 *                  the allocation size of `*buffer`, or point to
 *                  a variable whose value is zero if `*buffer`
 *                  is `NULL`.
 * @param   offset  The offset in the buffer where the function
 *                  shall start the printing.
 * @param   secure  Non-zero if the function must override the
 *                  buffer with zero before freeing it if it
 *                  creates a new allocation.
 * @param   format  The formatting-string.
 * @param   args    The formatting-arguments.
 * @return          The number of written characters, excluding
 *                  the NUL character. On error, a negative value
 *                  (namely -1 in this implementation) is
 *                  returned. It is unspecified what shall
 *                  happen if more than `INT_MAX` non-NUL
 *                  characters are written; in slibc, `INT_MAX`
 *                  is returned if more is written, you can
 *                  use "%zn" to find the actual length.
 * 
 * @throws  EINVAL  `format` contained unsupported formatting codes.
 * @throws  ENOMEM  The process cannot allocation the
 *                  sufficient amount of memory.
 * 
 * @since  Always.
 */
int vbwprintf(wchar_t** restrict buffer, size_t* restrict size, size_t offset,
	      int secure, const wchar_t* restrict format, va_list args)
{
  struct buffer buf =
    {
      .buf.wcs = *buffer,
      .size = size,
      .off = offset,
      .secure = secure,
      .free_on_error = buffer == NULL,
    };
  P_WCHAR(wwrite_buffer, 0, 0, 1, &buf);
}

