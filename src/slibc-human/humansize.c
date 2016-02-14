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
#include <slibc-human.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <alloca.h>
#include <errno.h>



#define SPRINTF(...)   do  if (m =  sprintf(__VA_ARGS__), m < 0)  goto fail;  while (0)
#define SNPRINTF(...)  do  if (m = snprintf(__VA_ARGS__), m < 0)  goto fail;  while (0)
#define ADD_PREFIX(prefix, buffer, n)				   \
  do								   \
    if (prefix == 0)						   \
      buffer[n++] = 'B';					   \
    else							   \
      {								   \
	buffer[n++] = prefixes[prefix];				   \
	if (mode & HUMANSIZE_IEC_EXPLICIT)     buffer[n++] = 'i';  \
	if (!(mode & HUMANSIZE_PREFIX_ONLY))   buffer[n++] = 'B';  \
      }								   \
  while (0)



/**
 * Convert a file size of file offset from machine representation to human representation.
 * The representation is exact.
 * 
 * @param   buffer        A buffer than shall be used if it is sufficiently large.
 * @param   bufsize       The allocation size of `buffer`.
 *                        Must be 0 if and only if `buffer` is `NULL`.
 * @param   mode          Representation style, 0 for default.
 * @param   detail        See documentation for the select value on `mode`.
 * @param   intraspacing  Spacing between values and units. `NULL` or empty for none.
 *                        This value should depend on language and context. For English
 *                        this value should be "" or "-", but in for example Swedish it
 *                        should always be " ". Hence this value is a string rather than
 *                        a booleanic integer.
 * @param   interspacing  Spacing between value–unit-pairs. `NULL` for default (" ").
 *                        This value should depend on language and context.
 * @param   prefixes      Prefix characters (including prefixless.)
 * @param   values        Values for prefixes.
 * @param   buf           Create intermediate write buffer.
 * @return                Human representation of the file size/offset, `NULL` on error.
 *                        On success, the caller is responsible for deallocating the
 *                        returned pointer, if and only if it is not `buffer`.
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 */
static char* humansize_exact(char* buffer, size_t bufsize, enum humansize_mode mode, int detail,
			     const char* restrict intraspacing, const char* restrict interspacing, size_t words,
			     const char* restrict prefixes, const size_t* restrict values, char* restrict buf)
{
  size_t i, n = 0;
  void* new = NULL;
  int m = 0, saved_errno;
  
  if (detail == 0)
    detail = 999;
  
  for (i = words; (i-- > 0) && detail--;)
    {
      /* Check non-zero only word. */
      if (!(values[i] || (!i && !n)))
	continue;
      
      /* Add interspacing. */
      if (i != words)
	{
	  memcpy(buffer + n, interspacing, strlen(interspacing) * sizeof(char));
	  n += strlen(interspacing);
	}
      
      /* Construct word (and intraspacing). */
      SPRINTF(buf, "%zu%s", values[i], intraspacing);
      ADD_PREFIX(i, buf, m);
      
      /* Ensure the buffer is large enougth. */
      if (n + (size_t)m > bufsize / sizeof(char))
	{
	  bufsize = 7 * (size_t)detail + strlen(interspacing) * ((size_t)detail - 1) + 1;
	  new = malloc(bufsize *= sizeof(char));
	  if (new == NULL)
	    goto fail;
	  memcpy(new, buffer, n * sizeof(char));
	  buffer = new;
	}
      
      /* Append word. */
      memcpy(buffer + n, buf, (size_t)m * sizeof(char));
      n += (size_t)m;
    }
  
  return buffer[n] = 0, buffer;
 fail:
  saved_errno = errno;
  free(new);
  return errno = saved_errno, NULL;
}


/**
 * Convert a file size of file offset from machine representation to human representation.
 * The representation is rounded.
 * 
 * @param   buffer        A buffer than shall be used if it is sufficiently large.
 * @param   bufsize       The allocation size of `buffer`.
 *                        Must be 0 if and only if `buffer` is `NULL`.
 * @param   mode          Representation style, 0 for default.
 * @param   detail        See documentation for the select value on `mode`.
 * @param   point         The symbol to use for decimal points. `NULL` or empty for default.
 * @param   intraspacing  Spacing between values and units. `NULL` or empty for none.
 *                        This value should depend on language and context. For English
 *                        this value should be "" or "-", but in for example Swedish it
 *                        should always be " ". Hence this value is a string rather than
 *                        a booleanic integer.
 * @param   interspacing  Spacing between value–unit-pairs. `NULL` for default (" ").
 *                        This value should depend on language and context.
 * @param   prefixes      Prefix characters (including prefixless.)
 * @param   values        Values for prefixes.
 * @param   buf           Create intermediate write buffer.
 * @param   div           K-multiple (1000 for SI, 1024 for IEC.)
 * @return                Human representation of the file size/offset, `NULL` on error.
 *                        On success, the caller is responsible for deallocating the
 *                        returned pointer, if and only if it is not `buffer`.
 * 
 * @throws  ENOMEM  The process cannot allocate more memory.
 */
static char* humansize_round(char* buffer, size_t bufsize, enum humansize_mode mode, int detail,
			     const char* restrict point, const char* restrict intraspacing,
			     const char* restrict interspacing, size_t words, const char* restrict prefixes,
			     const size_t* restrict values, char* restrict buf, size_t div)
{
  double total = 0, dividend = 1;
  size_t prefix = words - 1, i, n, det;
  char* p;
  void* new = NULL;
  char c;
  int m, saved_errno;
  
  /* Get single-unit value. */
  while (words--)
    total += ((double)values[words]) / dividend, dividend *= (double)div;
  
  /* Ensure the buffer is large enougth. */
  SNPRINTF(NULL, 0, "%.*lf%zn", (detail < 0 ? 0 : detail), (double)total, (ssize_t*)&n);
  if (n + strlen(point) + 3 - (detail < 0 ? 0 : 1) > bufsize / sizeof(char))
    {
      bufsize = n + strlen(point) + 3 - (detail < 0 ? 0 : 1);
      new = malloc(bufsize *= sizeof(char));
      if (new == NULL)
	goto fail;
      buffer = new;
    }
  
  /* Construct string. */
  SPRINTF(buffer, "%.*lf", (detail < 0 ? 0 : detail), (double)total);
  
  /* Replace decimal point sign. */
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
  
  /* Round value if detail < 0. */
  if ((detail < 0) && (n > 1))
    {
      det = (size_t)-detail;
      if (det >= n)
	det = n - 1;
      c = buffer[n + (size_t)-detail];
      for (i = n + (size_t)-detail; i < n; i++)
	buffer[i] = '0';
      if (c >= '5')
	{
	  buffer[n] = 0;
	  i = (size_t)atoll(buffer);
	  div = 10;
	  while (det--)
	    div *= 10;
	  i += div;
	  SPRINTF(buffer, "%zu%zn", i, (ssize_t*)&n);
	}
    }
  
  /* Add prefix (and intraspacing). */
  if (*intraspacing)
    {
      memcpy(buffer + n, intraspacing, strlen(intraspacing) * sizeof(char));
      n += strlen(intraspacing);
    }
  ADD_PREFIX(prefix, buffer, n);
  
  return buffer[n] = 0, buffer;
 fail:
  saved_errno = errno;
  free(new);
  return errno = saved_errno, NULL;
}


/**
 * Convert a file size of file offset from machine representation to human representation.
 * 
 * @param   buffer        A buffer than shall be used if it is sufficiently large.
 * @param   bufsize       The allocation size of `buffer`.
 *                        Must be 0 if and only if `buffer` is `NULL`.
 * @param   size          The value to convert.
 * @param   mode          Representation style, 0 for default.
 * @param   detail        See documentation for the select value on `mode`.
 * @param   point         The symbol to use for decimal points. `NULL` or empty for default.
 * @param   intraspacing  Spacing between values and units. `NULL` or empty for none.
 *                        This value should depend on language and context. For English
 *                        this value should be "" or "-", but in for example Swedish it
 *                        should always be " ". Hence this value is a string rather than
 *                        a booleanic integer.
 * @param   interspacing  Spacing between value–unit-pairs. `NULL` for default (" ").
 *                        This value should depend on language and context.
 * @return                Human representation of the file size/offset, `NULL` on error.
 *                        On success, the caller is responsible for deallocating the
 *                        returned pointer, if and only if it is not `buffer`.
 * 
 * @throws  EINVAL  If `mode` is invalid.
 * @throws  ENOMEM  The process cannot allocate more memory.
 * 
 * @since  Always.
 */
char* humansize(char* buffer, size_t bufsize, size_t size, enum humansize_mode mode, int detail,
		const char* restrict point, const char* restrict intraspacing, const char* restrict interspacing)
{
#if (__LONG_LONG_BIT > 90) && (((__LONG_LONG_BIT - 90) * 3 + 7) / 8 + 3 > 7)
# define BUFFER_SIZE  (((__LONG_LONG_BIT - 90) * 3 + 7) / 8 + 3)
#else
# define BUFFER_SIZE  7
#endif
  
  char prefixes[] = { '\0', 'K', 'M', 'G', 'T', 'P', 'E', 'Z', 'Y' };
  size_t values[sizeof(prefixes) / sizeof(*prefixes)] = { 0 };
  size_t div, i, words = 0;
  char* buf;
  
  /* Default parameters. */
  if (intraspacing == NULL)  intraspacing = "";
  if (interspacing == NULL)  interspacing = " ";
  if (!point || !*point)     point = ".";
  
  /* Create intermediate write buffer. */
  buf = alloca((BUFFER_SIZE + strlen(intraspacing)) * sizeof(char));
  
  /* Get K-multiple and case of the kilo-prefix. */
  switch (mode & 7)
    {
    case 0:
    case HUMANSIZE_SI:
      div = 1000;
      prefixes[1] = 'k';
      break;
      
    case HUMANSIZE_IEC:
    case HUMANSIZE_IEC_EXPLICIT:
      div = 1024;
      break;
      
    default:
      goto invalid;
    }
  
  /* Get value on prefixes. */
  for (i = 0; size && (i < sizeof(values) / sizeof(*values)); i++)
    values[i] = size % div, size /= div, words++;
  words = words ? words : 1;
  
  /* Construct string. */
  switch (mode & 48)
    {
    case HUMANSIZE_EXACT:
      if (detail < 0)
	goto invalid;
      return humansize_exact(buffer, bufsize, mode, detail, intraspacing,
			     interspacing, words, prefixes, values, buf);
      
    case 0:
    case HUMANSIZE_ROUND:
      return humansize_round(buffer, bufsize, mode, detail, point, intraspacing,
			     interspacing, words, prefixes, values, buf, div);
      
    default:
      goto invalid;
    }
  
 invalid:
  return errno = EINVAL, NULL;
}

