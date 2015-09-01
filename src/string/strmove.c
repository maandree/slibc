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
#include <string.h>



/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL byte is encountered.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @return           `whither` is returned.
 */
char* strmove(char* whither, const char* whence)
{
  return memmove(whither, whence, strlen(whence) + 1);
}


/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL byte is encountered.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @return           `whither + strlen(whence)` is returned.
 */
char* stpmove(char* whither, const char* whence)
{
  return mempmove(whither, whence, strlen(whence) + 1) - 1;
}


/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL byte or a specified byte is encountered.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   c        The stop byte.
 * @return           `NULL` if `c` was not encountered, otherwise
 *                   the position of `c` translated to `whither`,
 *                   that is, the address of `whither` plus the
 *                   number of copied characters; the address of
 *                   one character passed the last written non-NUL
 *                   character.
 */
char* strcmove(char* whither, const char* whence, int c)
{
  char* r = memcmove(whither, whence, c, strlen(whence) + 1);
  if (r)
    *r = 0;
  return r;
}


/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL byte or a specified substring is encountered.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   str      The substring, ignored if `NULL`.
 * @return           `NULL` if `str` was not encountered, otherwise
 *                   the position of `str` translated to `whither`,
 *                   that is, the address of `whither` plus the
 *                   number of copied characters; the address of
 *                   one character passed the last written non-NUL
 *                   character.
 */
char* strstrmove(char* whither, const char* whence, const char* restrict str)
{
  const char* stop = str == NULL ? NULL : strstr(whence, str);
  size_t n = stop == NULL ? strlen(whence) : (size_t)(stop - whence);
  char* r = stop == NULL ? NULL : (whither + n);
  memmove(whither, whence, n);
  whither[n] = 0;
  return r;
}


/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL byte is encountered.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   maxlen   The maximum number of bytes to copy.
 *                   NOTE that if the resulting string at least this
 *                   long, no NUL byte will be written to `whither'.
 *                   On the otherhand, if the resultnig string is
 *                   shorter, `whither` will be filled with NUL bytes
 *                   until this amount of bytes have been written.
 * @return           `whither` is returned.
 */
char* strnmove(char* whither, const char* whence, size_t maxlen)
{
  size_t n = strnlen(whence, maxlen);
  memmove(whither, whence, n);
  memset(whither, 0, maxlen - n);
  return whither;
}


/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL byte is encountered.
 * 
 * This is a slibc extension added for completeness.
 * It is only available if GNU extensions are available.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   maxlen   The maximum number of bytes to copy.
 *                   NOTE that if the resulting string at least this
 *                   long, no NUL byte will be written to `whither'.
 *                   On the otherhand, if the resultnig string is
 *                   shorter, `whither` will be filled with NUL bytes
 *                   until this amount of bytes have been written.
 * @return           `whither` plus the number of written bytes,
 *                   excluding NUL bytes, is returned.
 */
char* stpnmove(char* whither, const char* whence, size_t maxlen)
{
  size_t n = strnlen(whence, maxlen);
  memmove(whither, whence, n);
  memset(whither, 0, maxlen - n);
  return whither + n;
}


/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL byte or a specified byte is encountered.
 * 
 * This is a slibc extension added for completeness.
 * It is only available if GNU extensions are available.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   c        The stop byte.
 * @param   maxlen   The maximum number of bytes to copy.
 *                   NOTE that if the resulting string at least this
 *                   long, no NUL byte will be written to `whither'.
 *                   On the otherhand, if the resultnig string is
 *                   shorter, `whither` will be filled with NUL bytes
 *                   until this amount of bytes have been written.
 * @return           `NULL` if `c` was not encountered, otherwise
 *                   the position of `c` translated to `whither`,
 *                   that is, the address of `whither` plus the
 *                   number of copied characters; the address of
 *                   one character passed the last written non-NUL
 *                   character.
 */
char* strcnmove(char* whither, const char* whence, int c, size_t maxlen)
{
  const char* stop = memchr(whence, c, maxlen);
  size_t n = stop == NULL ? strnlen(whence, maxlen) : (size_t)(stop - whence);
  char* r = stop == NULL ? NULL : (whither + n);
  memmove(whither, whence, n);
  memset(whither, 0, maxlen - n);
  return r;
}


/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL byte or a specified substring is encountered.
 * 
 * This is a slibc extension added for completeness.
 * It is only available if GNU extensions are available.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   str      The substring, ignored if `NULL`.
 *                   NOTE that if the resulting string at least this
 *                   long, no NUL byte will be written to `whither'.
 *                   On the otherhand, if the resultnig string is
 *                   shorter, `whither` will be filled with NUL bytes
 *                   until this amount of bytes have been written.
 * @param   maxlen   The maximum number of bytes to copy.
 * @return           `NULL` if `str` was not encountered, otherwise
 *                   the position of `str` translated to `whither`,
 *                   that is, the address of `whither` plus the
 *                   number of copied characters; the address of
 *                   one character passed the last written non-NUL
 *                   character.
 */
char* strstrnmove(char* whither, const char* whence, const char* restrict str, size_t maxlen)
{
  const char* stop = strnstr(whence, str, maxlen);
  size_t n = stop == NULL ? strnlen(whence, maxlen) : (size_t)(stop - whence);
  char* r = stop == NULL ? NULL : (whither + n);
  memmove(whither, whence, n);
  memset(whither, 0, maxlen - n);
  return r;
}

