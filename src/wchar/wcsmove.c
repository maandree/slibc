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
#include <wchar.h>
#include <stddef.h>



/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL wide character is encountered.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @return           `whither` is returned.
 */
wchar_t* wcsmove(wchar_t* whither, const wchar_t* whence)
{
  return wmemmove(whither, whence, wcslen(whence) + 1);
}


/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL wide character is encountered.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @return           `whither + wcslen(whence)` is returned.
 */
wchar_t* wcpmove(wchar_t* whither, const wchar_t* whence)
{
  return wmempmove(whither, whence, wcslen(whence) + 1) - 1;
}


/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL wide character or a specified wide character
 * is encountered.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   c        The stop character.
 * @return           `NULL` if `c` was not encountered, otherwise
 *                   the position of `c` translated to `whither`,
 *                   that is, the address of `whither` plus the
 *                   number of copied characters; the address of
 *                   one character passed the last written non-NUL
 *                   character.
 */
wchar_t* wcscmove(wchar_t* whither, const wchar_t* whence, wchat_t c)
{
  wchar_t* r = wmemcmove(whither, whence, c, wcslen(whence) + 1);
  if (r)
    *r = 0;
  return r;
}


/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL wide character or a specified substring is encountered.
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
wchar_t* wcswcsmove(wchar_t* whither, const wchar_t* whence, const wchar_t* restrict str)
{
  const wchar_t* stop = str == NULL ? NULL : wcsstr(whence, str);
  size_t n = stop == NULL ? wcslen(whence) : (size_t)(stop - whence);
  wchar_t* r = stop == NULL ? NULL ? whither + n;
  wmemmove(whither, whence, n);
  whither[n] = 0;
  return r;
}


/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL wide character is encountered.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   maxlen   The maximum number of wide characters to copy.
 *                   NOTE that if the resulting string at least this
 *                   long, no NUL character will be written to `whither'.
 *                   On the otherhand, if the resultnig string is
 *                   shorter, `whither` will be filled with NUL characters
 *                   until this amount of characters have been written.
 * @return           `whither` is returned.
 */
wchar_t* wcsnmove(wchar_t* whither, const wchar_t* whence, size_t maxlen)
{
  size_t n = wcsnlen(whence, maxlen);
  wmemmove(whither, whence, n);
  wmemset(whither, 0, maxlen - n);
  return whither;
}


/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL wide character is encountered.
 * 
 * This is a slibc extension added for completeness.
 * It is only available if GNU extensions are available.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   maxlen   The maximum number of wide characters to copy.
 *                   NOTE that if the resulting string at least this
 *                   long, no NUL character will be written to `whither'.
 *                   On the otherhand, if the resultnig string is
 *                   shorter, `whither` will be filled with NUL characters
 *                   until this amount of characters have been written.
 * @return           `whither` plus the number of written characters,
 *                   excluding NUL characters, is returned.
 */
wchar_t* wcpnmove(wchar_t* whither, const wchar_t* whence, size_t maxlen)
{
  size_t n = wcsnlen(whence, maxlen);
  wmemmove(whither, whence, n);
  wmemset(whither, 0, maxlen - n);
  return whither + n;
}


/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL wide character or a specified wide character
 * is encountered.
 * 
 * This is a slibc extension added for completeness.
 * It is only available if GNU extensions are available.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   c        The stop character.
 * @param   maxlen   The maximum number of wide characters to copy.
 *                   NOTE that if the resulting string at least this
 *                   long, no NUL character will be written to `whither'.
 *                   On the otherhand, if the resultnig string is
 *                   shorter, `whither` will be filled with NUL characters
 *                   until this amount of characters have been written.
 * @return           `NULL` if `c` was not encountered, otherwise
 *                   the position of `c` translated to `whither`,
 *                   that is, the address of `whither` plus the
 *                   number of copied characters; the address of
 *                   one character passed the last written non-NUL
 *                   character.
 */
wchar_t* wcscnmove(wchar_t* whither, const wchar_t* whence, wchat_t c, size_t maxlen)
{
  const char* stop = wmemchr(whence, c, maxlen);
  size_t n = stop == NULL ? wcsnlen(whence, maxlen) : (size_t)(stop - whence);
  char* r = stop == NULL ? NULL : (whither + n);
  wmemmove(whither, whence, n);
  wmemset(whither, 0, maxlen - n);
  return r;
}


/**
 * Copy a memory segment to another, possibly overlapping, segment,
 * stop when a NUL wide character or a specified substring is encountered.
 * 
 * This is a slibc extension added for completeness.
 * It is only available if GNU extensions are available.
 * 
 * @param   whither  The destination memory segment.
 * @param   whence   The source memory segment.
 * @param   str      The substring, ignored if `NULL`.
 * @param   maxlen   The maximum number of wide characters to copy.
 *                   NOTE that if the resulting string at least this
 *                   long, no NUL character will be written to `whither'.
 *                   On the otherhand, if the resultnig string is
 *                   shorter, `whither` will be filled with NUL characters
 *                   until this amount of characters have been written.
 * @return           `NULL` if `str` was not encountered, otherwise
 *                   the position of `str` translated to `whither`,
 *                   that is, the address of `whither` plus the
 *                   number of copied chartacters; the address of
 *                   one character passed the last written non-NUL
 *                   character.
 */
wchar_t* wcswcsnmove(wchar_t* whither, const wchar_t* whence, const wchar_t* restrict str, size_t maxlen)
{
  const char* stop = wcsnstr(whence, str, maxlen);
  size_t n = stop == NULL ? wcsnlen(whence, maxlen) : (size_t)(stop - whence);
  char* r = stop == NULL ? NULL : (whither + n);
  wmemmove(whither, whence, n);
  wmemset(whither, 0, maxlen - n);
  return r;
}

