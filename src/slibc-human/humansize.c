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
#include <slib-human.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>



/**
 * Convert a file size of file offset from machine representation to human representation.
 * 
 * @param   buffer   A buffer than shall be used if it is sufficiently large.
 * @param   bufsize  The allocation size of `buffer`.
 *                   Must be 0 if and only if `buffer` is `NULL`.
 * @param   size     The value to convert.
 * @param   mode     Representation style, 0 for default.
 * @param   detail   See documentation for the select value on `mode`.
 * @param   point    The symbol to use for decimal points. `NULL` or empty for default.
 * @return           Human representation of the file size/offset, `NULL` on error.
 *                   On success, the caller is responsible for deallocating the
 *                   returned pointer, if and only if it is not `buffer`.
 * 
 * @throws  EINVAL  If `mode` is invalid.
 * @throws  ENOMEM  The process cannot allocate more memory.
 */
char* humansize(char* buffer, size_t bufsize, size_t size,
		enum humansize_mode mode, int detail, const char* restrict point)
{
  char prefixes[] = { '\0', 'K', 'M', 'G', 'T', 'P', 'E', 'Z', 'Y' };
  size_t values[sizeof(prefixes) / sizeof(*prefixes)] = { 0 };
  size_t div, i, n = 0, words = 0;
  char* p;
  char* new = NULL;
#if (__LONG_LONG_BIT > 90) && (((__LONG_LONG_BIT - 90) * 3 + 7) / 8 + 3 > 7)
  char buf[((__LONG_LONG_BIT - 90) * 3 + 7) / 8 + 3];
#else
  char buf[7];
#endif
  int m, saved_errno;
  
  switch (mode & 7)
    {
    case 0:
    case HUMANSIZE_SI:
      div = 1000;
      prefixes[1] = 'k'
      break;
      
    case HUMANSIZE_IEC:
    case HUMANSIZE_IEC_EXPLICIT:
      div = 1024;
      break;
      
    default:
      goto invalid;
    }
  
  for (i = 0; size && (i < sizeof(values) / sizeof(*values)); i++)
    values[i] = size % div, size /= div, words++;
  words = words ? words : 1;
  
  switch (mode & 48)
    {
    case HUMANSIZE_EXACT:
      if (detail < 0)   goto invalid;
      if (detail == 0)  detail = 999;
      for (i = words; (i-- > 0) && detail--;)
	{
	  if (!(values[i] || (!i && !n)))
	    break;
	  if (m = sprintf(buf, "%zu", values[i]), m < 0)
	    goto fail;
	  if (i == 0)
	    buf[m++] = 'B';
	  else
	    {
	      buf[m++] = prefixes[i];
	      if (mode & HUMANSIZE_IEC_EXPLICIT)     buf[m++] = 'i';
	      if (!(mode & HUMANSIZE_PREFIX_ONLY))   buf[m++] = 'B';
	    }
	  if (n + (size_t)m > bufsize / sizeof(char))
	    {
	      new = malloc(bufsize = 8 * detail * sizeof(char));
	      if (new == NULL)
		goto fail;
	      memcpy(new, buffer, n * sizeof(char));
	      buffer = new;
	    }
	  memcpy(buffer + n, buf, (size_t)m * sizeof(char));
	  n += (size_t)m;
	  buffer[n++] = ' ';
	}
      buffer[n - 1] = 0;
      break;
      
    case 0:
    case HUMANSIZE_ROUND:
      if (!point || !*point)
	point = ".";
      i = words - 1;
      {
	double total = 0, dividend = 1;
	while (words--)
	  total += ((double)values[words]) / dividend, dividend *= (double)div;
	m = snprintf(NULL, 0, "%.*lf%\zn", (detail < 0 ? 0 : detail), (double)total, (ssize_t*)&n);
	if (m < 0)
	  goto fail;
	if (n + strlen(point) + 3 - (detail < 0 ? 0 : 1) > bufsize / sizeof(char))
	  {
	    bufsize = (size_t)m + strlen(point) + 3 - (detail < 0 ? 0 : 1);
	    new = malloc(bufsize * sizeof(char));
	    if (new == NULL)
		goto fail;
	    buffer = new;
	  }
	m = sprintf(buffer, "%.*lf", (detail < 0 ? 0 : detail), (double)total);
	if (m < 0)
	  goto fail;
	if ((p = strchr(buffer, '.')))
	  {
	    if (detail <= 0)
	      n = (size_t)(p - buffer);
	    else
	      {
		memmove(p + strlen(point), p + 1, (n - 1 - (size_t)(p - buffer)) * sizeof(char));
		memcpy(p, point, strlen(point) * sizeof(char));
	      }
	  }
	if ((detail < 0) && (n > 1))
	  {
	    char c;
	    size_t det = (size_t)-detail;
	    if (det >= n)
	      det = n - 1;
	    c = buffer[n - detail];
	    for (i = n - detail; i < n; i++)
	      buffer[i] = '0';
	    if (c >= '5')
	      {
		buffer[n] = 0;
		i = (size_t)atoll(buffer);
		div = 10;
		while (det--)
		  div *= 10;
		i += div;
		m = sprintf(buffer, "%zu%\zn", i, (ssize_t*)&n);
		if (m < 0)
		  goto fail;
	      }
	  }
      }
      if (i == 0)
	buffer[n++] = 'B';
      else
	{
	  buffer[n++] = prefixes[i];
	  if (mode & HUMANSIZE_IEC_EXPLICIT)     buffer[n++] = 'i';
	  if (!(mode & HUMANSIZE_PREFIX_ONLY))   buffer[n++] = 'B';
	}
      buffer[n] = 0;
      break;
      
    default:
      goto invalid;
    }
  
  return buffer;
 invalid:
  return errno = EINVAL, NULL;
 fail:
  saved_errno = errno;
  free(new);
  return errno = saved_errno, NULL;
}

