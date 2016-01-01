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
#include <wchar.h>



size_t wscclen(const wchar_t* string, wchar_t stop) /* slibc: completeness */
{
  return (size_t)(wscchrnul(string, stop) - string);
}

size_t wsccnlen(const wchar_t* string, wchar_t stop, size_t maxlen) /* slibc: completeness */
{
  const wchar_t* end = wscnchr(string, stop, maxlen);
  return end ? (size_t)(end - string) : maxlen;
}

size_t wscstrlen(const wchar_t* string, const wchar_t* stop) /* slibc: completeness */
{
  const wchar_t* end = wscstr(string, stop);
  return end ? (size_t)(end - string) : wsclen(string);
}

size_t wscstrnlen(const wchar_t* string, const wchar_t* stop, size_t maxlen) /* slibc: completeness */
{
  const wchar_t* end = wscnstr(string, stop, maxlen);
  return end ? (size_t)(end - string) : maxlen;
}

wchar_t* (wcsnchr)(const wchar_t* string, wchar_t c, size_t maxlen) /* slibc: completeness */
{
  for (;;)
    if (*string == c)
      return string;
    else if (!*string++ || !maxlen--)
      return NULL;
}

wchar_t* (wcsnchrnul)(const wchar_t* string, wchar_t c, size_t maxlen) /* slibc: completeness */
{
  for (;; string++)
    if (*string == c)
      return string;
    else if (!*string || !maxlen--)
      return string;
}

wchar_t* (wmemcchr)(const wchar_t* segment, wchar_t c, wchar_t stop, size_t size) /* slibc: completeness */
{
  wchar_t* s = segment;
  for (;;)
    if (*s == c)
      return s;
    else if ((*s++ == stop) || !size--)
      return NULL;
}

wchar_t* (wcscchr)(const wchar_t* string, wchar_t c, wchar_t stop) /* slibc: completeness */
{
  for (;;)
    if (*string == c)
      return string;
    else if (!*string || (*string++ == stop))
      return NULL;
}

wchar_t* (wcscnchr)(const wchar_t* string, wchar_t c, wchar_t stop, size_t maxlen) /* slibc: completeness */
{
  for (;;)
    if (*string == c)
      return string;
    else if (!*string || (*string++ == stop) || !maxlen--)
      return NULL;
}

wchar_t* (wcscchrnul)(const wchar_t* string, wchar_t c, wchar_t stop) /* slibc+gnu: completeness */
{
  for (;; string++)
    if (*string == c)
      return string;
    else if (!*string || (*string == stop))
      return string;
}

wchar_t* (wcscnchrnul)(const wchar_t* string, wchar_t c, wchar_t stop, size_t maxlen) /* slibc+gnu: completeness */
{
  for (;; string++)
    if (*string == c)
      return string;
    else if (!*string || (*string == stop) || !maxlen--)
      return string;
}

wchar_t* (wcsnrchr)(const wchar_t* string, wchar_t c, size_t maxlen) /* slibc: completeness */
{
  wchar_t* r = NULL;
  while (maxlen--)
    if (*string == c)
      r = string;
    else if (!*string++)
      return c ? r : (string - 1);
}

void* (wmemcrchr)(const void* segment, wchar_t c, wchar_t stop, size_t size) /* slibc: completeness */
{
  wchar_t* r = NULL;
  for (;; size--)
    if (*segment == c)
      r = segment;
    else if ((*segment == stop) || !size)
      return r;
}

wchar_t* (wcscrchr)(const wchar_t* string, wchar_t c, wchar_t stop) /* slibc: completeness */
{
  wchar_t* r = NULL;
  for (;;)
    if (*string == c)
      r = string;
    else if (!*string++)
      return c ? r : (string - 1);
    else if (*string == stop)
      return r;
}

wchar_t* (wcscnrchr)(const wchar_t* string, wchar_t c, wchar_t stop, size_t maxlen) /* slibc: completeness */
{
  wchar_t* r = NULL;
  while (maxlen--)
    if (*string == c)
      r = string;
    else if (!*string++)
      return c ? r : (string - 1);
}

wchar_t* (rawwmemrchr)(const wchar_t* segment, wchar_t c, size_t size) /* slibc+gnu: completeness */
{
  for (;;)
    if (segment[--size] == c)
      return segment + size;
}

wchar_t* (rawwmemcasemem)(const wchar_t* haystack, const wchar_t* needle, size_t needle_length) /* slibc: completeness */
{
  return (wmemcasemem)(haystack, SIZE_MAX, needle, needle_length);
}

wchar_t* (rawwmemmem)(const wchar_t* haystack, const wchar_t* needle, size_t needle_length) /* slibc: completeness */
{
  return (wmemmem)(haystack, SIZE_MAX, needle, needle_length);
}

wchar_t* (wmemccasemem)(const wchar_t* haystack, size_t haystack_length, const wchar_t* needle, size_t needle_length, wchar_t stop) /* slibc: completeness */
{
  const wchar_t* p = wmemchr(haystack, stop, haystack_length);
  return (wmemcasemem)(haystack, p ? (size_t)(p - haystack) : haystack_length, needle, needle_length);
}

wchar_t* (wmemcmem)(const wchar_t* haystack, size_t haystack_length, const wchar_t* needle, size_t needle_length, wchar_t stop) /* slibc: completeness */
{
  const wchar_t* p = wmemchr(haystack, stop, haystack_length);
  return (wmemmem)(haystack, p ? (size_t)(p - haystack) : haystack_length, needle, needle_length);
}

wchar_t* (wcsccasestr)(const wchar_t* haystack, const wchar_t* needle, wchar_t stop) /* slibc: completeness */
{
  return (wmemcasemem)(haystack, wscclen(haystack, stop), needle, wsclen(needle));
}

wchar_t* (wcscstr)(const wchar_t* haystack, const wchar_t* needle, wchar_t stop) /* slibc: completeness */
{
  return (wmemmem)(haystack, wscclen(haystack, stop), needle, wsclen(needle));
}

wchar_t* (wcscncasestr)(const wchar_t* haystack, const wchar_t* needle, wchar_t stop, size_t maxlen) /* slibc: completeness */
{
  return (wmemcasemem)(haystack, wsccnlen(haystack, stop, maxlen), needle, wsclen(needle));
}

wchar_t* (wcscnstr)(const wchar_t* haystack, const wchar_t* needle, wchar_t stop, size_t maxlen) /* slibc: completeness */
{
  return (wmemmem)(haystack, wsccnlen(haystack, stop, maxlen), needle, wsclen(needle));
}

wchar_t* (wcspcbrk)(const wchar_t* string, const wchar_t* skipset) /* slibc: completeness */
{
  string += wcsspn(string, skipset);
  return *string ? string : NULL;
}

wchar_t* (wcspbrknul)(const wchar_t* string, const wchar_t* stopset) /* slibc: completeness */
{
  return string + wcscspn(string, stopset);
}

wchar_t* (wcspcbrknul)(const wchar_t* string, const wchar_t* skipset) /* slibc: completeness */
{
  return string + wcsspn(string, skipset);
}

wchar_t* (wcsnpbrk)(const wchar_t* string, const wchar_t* stopset, size_t maxlen) /* slibc: completeness */
{
  wchar_t s = string;
  string += wcsncspn(string, stopset, maxlen);
  return (((size_t)(string - s) < maxlen) && *string) ? string : NULL;
}

wchar_t* (wcsnpcbrk)(const wchar_t* string, const wchar_t* skipset, size_t maxlen) /* slibc: completeness */
{
  wchar_t s = string;
  string += wcsnspn(string, skipset, maxlen);
  return (((size_t)(string - s) < maxlen) && *string) ? string : NULL;
}

wchar_t* (wcsnpbrknul)(const wchar_t* string, const wchar_t* stopset, size_t maxlen) /* slibc: completeness */
{
  return string + wcscspn(string, stopset, maxlen);
}

wchar_t* (wcsnpcbrknul)(const wchar_t* string, const wchar_t* skipset, size_t maxlen) /* slibc: completeness */
{
  return string + wcsspn(string, skipset, maxlen);
}

size_t wcsnspn(const wchar_t* string, const wchar_t* skipset, size_t maxlen) /* slibc: completeness */
{
  wchar_t* s = string;
  wchar_t c;
  for (; maxlen && ((c = *s++)); maxlen--)
    if (wcschr(skipset, c) == NULL)
      break;
  return (size_t)(s - !!maxlen - string);
}

size_t wcsncspn(const wchar_t* string, const wchar_t* stopset, size_t maxlen) /* slibc: completeness */
{
  size_t i, end = wcsnlen(string, maxlen);
  wchar_t* s;
  wchar_t c;
  while ((c = *stopset++))
    for (i = 0, s = string; i < end; i++, s++)
      if (*s == c)
	{
	  end = (size_t)(s - string);
	  break;
	}
  return end;
}

wchar_t* wcsnsep(wchar_t** restrict string, const wchar_t* restrict delimiters,
		 size_t* restrict maxlen) /* slibc: completeness */
{
  wchar_t* r = *string;
  wchar_t* next;
  if (r == NULL)
    return NULL;
  
  next = wcsnpbrk(r, delimiters, *maxlen);
  if (next != NULL)
    *next++ = 0, *maxlen -= (size_t)(next - r);
  *string = next;
  
  return r;
}

wchar_t* wcsntok(wchar_t* restrict string, const wchar_t* restrict delimiters,
		 wchar_t** restrict state, size_t* restrict maxlen) /* slibc: completeness */
{
  wchar_t* r;
  if (string == NULL)
    *state = string;
  for (;;)
    {
      r = wcsnsep(state, delimiters, maxlen);
      if (r == NULL)
	return NULL;
      if (*r)
	return r;
    }
}

wchar_t* (wcsprbrk)(const wchar_t* string, const wchar_t* stopset) /* slibc: completeness */
{
  wchar_t* r;
  int found = 0;
  while (string)
    if ((r = wcspbrk(string + 1, stopset)))
      string = r, found = 1;
  return found ? string : NULL;
}

wchar_t* (wcsprcbrk)(const wchar_t* string, const wchar_t* skipset) /* slibc: completeness */
{
  wchar_t* r;
  int found = 0;
  while (string)
    if ((r = wcspcbrk(string + 1, skipset)))
      string = r, found = 1;
  return found ? string : NULL;
}

wchar_t* (wcsnprbrk)(const wchar_t* string, const wchar_t* stopset, size_t maxlen) /* slibc: completeness */
{
  wchar_t* r;
  int found = 0;
  while (string)
    if ((r = wcsnpbrk(string + 1, stopset, maxlen - 1)))
      maxlen -= (r - string), string = r, found = 1;
  return found ? string : NULL;
}

wchar_t* (wcsnprcbrk)(const wchar_t* string, const wchar_t* skipset, size_t maxlen) /* slibc: completeness */
{
  wchar_t* r;
  int found = 0;
  while (string)
    if ((r = wcsnpcbrk(string + 1, skipset, maxlen - 1)))
      maxlen -= (r - string), string = r, found = 1;
  return found ? string : NULL;
}

wchar_t* wmemmemmove(wchar_t* whither, const wchar_t* whence, const wchar_t* restrict str,
		     size_t strsize, size_t size) /* slibc: completeness */
{
  wchar_t* stop = (wmemmem)(whence, size, str, strsize);
  wchar_t* r = NULL;
  if (stop != NULL)
    size = (size_t)(stop - whence), r = whither + size;
  wmemmove(whither, whence, size);
  return r;
}

char* wmemmemcpy(wchar_t* whither, const wchar_t* whence, const wchar_t* restrict str,
		 size_t strsize, size_t size) /* slibc: completeness */
{
  wchar_t* stop = (wmemmem)(whence, size, str, strsize);
  wchar_t* r = NULL;
  if (stop != NULL)
    size = (size_t)(stop - whence), r = whither + size;
  wmemcpy(whither, whence, size);
  return r;
}

wchar_t* (wmemcasestarts)(const wchar_t* string, const wchar_t* desired, size_t size) /* slibc: completeness */
{
  return (wmemcasecmp)(string, desired, size) ? NULL : string;
}

wchar_t* (wcsncasestarts)(const wchar_t* string, const wchar_t* desired, size_t maxlen) /* slibc: completeness */
{
  size_t n = wcsnlen(string, maxlen);
  size_t m = wcsnlen(desired, maxlen);
  if (n < m)
    return NULL;
  return (wmemcasecmp)(string, desired, m) ? NULL : string;
}

wchar_t* (wmemcaseends)(const wchar_t* string, size_t string_size, const wchar_t* desired, size_t desired_size) /* slibc: completeness */
{
  return (wmemcasecmp)(string + (string_size - desired_size), desired, desired_size)
    ? NULL : (string + string_size);
}

wchar_t* (wcsncaseends)(const wchar_t* string, const wchar_t* desired, size_t maxlen) /* slibc: completeness */
{
  size_t n = wcsnlen(string, maxlen);
  size_t m = wcsnlen(desired, maxlen);
  if (n < m)
    return NULL;
  return (wmemcasecmp)(string + (n - m), desired, m) ? NULL : (string + n);
}

wchar_t* (wmemstarts)(const wchar_t* string, const wchar_t* desired, size_t size) /* slibc completeness */
{
  return (wmemcmp)(string, desired, size) ? NULL : string;
}

wchar_t* (wstrnstarts)(const wchar_t* string, const wchar_t* desired, size_t maxlen) /* slibc: completeness */
{
  size_t n = wcsnlen(string, maxlen);
  size_t m = wcsnlen(desired, maxlen);
  if (n < m)
    return NULL;
  return (wmemcmp)(string, desired, m) ? NULL : string;
}

wchar_t* (wmemends)(const wchar_t* string, size_t string_size, const wchar_t* desired, size_t desired_size) /* slibc: completeness */
{
  return (wmemcmp)(string + (string_size - desired_size), desired, desired_size)
    ? NULL : (string + string_size);
}

wchar_t* (wcsnends)(const wchar_t* string, const wchar_t* desired, size_t maxlen) /* slibc: completeness */
{
  size_t n = wcsnlen(string, maxlen);
  size_t m = wcsnlen(desired, maxlen);
  if (n < m)
    return NULL;
  return (wmemcmp)(string + (n - m), desired, m) ? NULL : (string + n);
}

int wmemccasecmp(const wchar_t* a, const wchar_t* b, size_t size, wchar_t stop) /* slibc: completeness */
{
  int c1, c2;
  for (; c1 = *a++, c2 = *b++, (c1 != stop) && (c2 != stop) && size; size--)
    if (c1 != c2)
      {
	c1 = isalpha(c1) ? tolower(c1) : c1;
	c2 = isalpha(c2) ? tolower(c2) : c2;
	if ((c1 -= c2))
	  return c1;
      }
  if (c1 == stop)  c1 = 0;
  if (c2 == stop)  c2 = 0;
  return size ? (c1 < c2 ? -1 : c1 > c2 ? 1 : 0) : 0;
}

int wmemccmp(const wchar_t* a, const wchar_t* b, size_t size, wchar_t stop) /* slibc: completeness */
{
  wchar_t c1, c2;
  for (; c1 = *a++, c2 = *b++, (c1 != stop) && (c2 != stop) && size; size--)
    if (c1 != c2)
      return c1 - c2;
  if (c1 == stop)  c1 = 0;
  if (c2 == stop)  c2 = 0;
  return size ? (c1 < c2 ? -1 : c1 > c2 ? 1 : 0) : 0;
}

int wcsccasecmp(const wchar_t* a, const wchar_t* b, wchar_t stop) /* slibc: completeness */
{
  return wcscncasecmp(a, b, stop, SIZE_MAX);
}

int wcsccmp(const wchar_t* a, const wchar_t* b, wchar_t stop) /* slibc: completeness */
{
  size_t n = wcsclen(a, stop);
  size_t m = wcsclen(b, stop);
  return wmemcmp(a, b, (n < m ? n : m) + 1);
}

int wcscncasecmp(const wchar_t* a, const wchar_t* b, wchar_t stop, size_t length) /* slibc: completeness */
{
  size_t n = wcscnlen(a, stop, length);
  size_t m = wcscnlen(b, stop, length);
  int r = wmemcasecmp(a, b, (n < m ? n : m));
  return r ? r : n == m ? 0 : n < m ? -1 : +1;
}

int wcscncmp(const wchar_t* a, const wchar_t* b, wchar_t stop, size_t length) /* slibc: completeness */
{
  size_t n = wcscnlen(a, stop, length);
  size_t m = wcscnlen(b, stop, length);
  int r = wmemcmp(a, b, (n < m ? n : m));
  return r ? r : n == m ? 0 : n < m ? -1 : +1;
}

wchar_t* (wmemccasestarts)(const wchar_t* string, const wchar_t* desired, size_t size, wchar_t stop) /* slibc: completeness */
{
  return (wmemccasecmp)(string, desired, size, stop) ? NULL : string;
}

wchar_t* (wmemcstarts)(const wchar_t* string, const wchar_t* desired, size_t size, wchar_t stop) /* slibc: completeness */
{
  return (wmemccmp)(string, desired, size, stop) ? NULL : string;
}

wchar_t* (wcsccasestarts)(const wchar_t* string, const wchar_t* desired, wchar_t stop) /* slibc: completeness */
{
  size_t n = wcsclen(string, stop);
  size_t m = wcsclen(desired, stop);
  if (n < m)
    return NULL;
  return (wmemcasecmp)(string, desired, m) ? NULL : string;
}

wchar_t* (wcscstarts)(const wchar_t* string, const wchar_t* desired, wchar_t stop) /* slibc: completeness */
{
  size_t n = wcsclen(string, stop);
  size_t m = wcsclen(desired, stop);
  if (n < m)
    return NULL;
  return (wmemcmp)(string, desired, m) ? NULL : string;
}

wchar_t* (wcscncasestarts)(const wchar_t* string, const wchar_t* desired, wchar_t stop, size_t maxlen) /* slibc: completeness */
{
  size_t n = wcscnlen(string, stop, maxlen);
  size_t m = wcscnlen(desired, stop, maxlen);
  if (n < m)
    return NULL;
  return (wmemcasecmp)(string, desired, m) ? NULL : string;
}

wchar_t* (wcscnstarts)(const wchar_t* string, const wchar_t* desired, wchar_t stop, size_t maxlen) /* slibc: completeness */
{
  size_t n = wcscnlen(string, stop, maxlen);
  size_t m = wcscnlen(desired, stop, maxlen);
  if (n < m)
    return NULL;
  return (wmemcmp)(string, desired, m) ? NULL : string;
}

wchar_t* (wmemccaseends)(const wchar_t* string, size_t string_size, const wchar_t* desired, size_t desired_size, wchar_t stop) /* slibc: completeness */
{
  wchar_t* end = wmemchr(string, stop, string);
  if (end != NULL)
    string_size = (size_t)(end - string);
  return (wmemcasecmp)(string + (string_size - desired_size), desired, desired_size)
    ? NULL : (string + string_size);
}

wchar_t* (wmemcends)(const wchar_t* string, size_t string_size, const wchar_t* desired, size_t desired_size, wchar_t stop) /* slibc: completeness */
{
  wchar_t* end = wmemchr(string, stop, string);
  if (end != NULL)
    string_size = (size_t)(end - string);
  return (wmemcmp)(string + (string_size - desired_size), desired, desired_size)
    ? NULL : (string + string_size);
}

wchar_t* (wcsccaseends)(const wchar_t* string, const wchar_t* desired, wchar_t stop) /* slibc: completeness */
{
  size_t n = wcsclen(string, stop);
  size_t m = wcsclen(desired, stop);
  if (n < m)
    return NULL;
  return (wmemcasecmp)(string + (n - m), desired, m) ? NULL : (string + n);
}

wchar_t* (wcscends)(const wchar_t* string, const wchar_t* desired, wchar_t stop) /* slibc: completeness */
{
  size_t n = wcsclen(string, stop);
  size_t m = wcsclen(desired, stop);
  if (n < m)
    return NULL;
  return (wmemcmp)(string + (n - m), desired, m) ? NULL : (string + n);
}

wchar_t* (wcscncaseends)(const wchar_t* string, const wchar_t* desired, wchar_t stop, size_t maxlen) /* slibc: completeness */
{
  size_t n = wcscnlen(string, stop, maxlen);
  size_t m = wcscnlen(desired, stop, maxlen);
  if (n < m)
    return NULL;
  return (wmemcasecmp)(string + (n - m), desired, m) ? NULL : (string + n);
}

wchar_t* (wcscnends)(const wchar_t* string, const wchar_t* desired, wchar_t stop, size_t maxlen) /* slibc: completeness */
{
  size_t n = wcscnlen(string, stop, maxlen);
  size_t m = wcscnlen(desired, stop, maxlen);
  if (n < m)
    return NULL;
  return (wmemcmp)(string + (n - m), desired, m) ? NULL : (string + n);
}

int wcslowercmp(const wchar_t* a, const wchar_t* b) /* slibc: completeness */
{
  return wcsnlowercmp(a, b, SIZE_MAX);
}

int wcsuppercmp(const wchar_t* a, const wchar_t* b) /* slibc: completeness */
{
  return wcsnuppercmp(a, b, SIZE_MAX);
}

int wcsnlowercmp(const wchar_t* a, const wchar_t* b, size_t length) /* slibc: completeness */
{
  wchar_t c1, c2;
  for (; length--; a++, b++)
    if (*a != *b)
      {
	c1 = iswalpha(*a) ? towlower(*a) : *a;
	c2 = *b;
	if (c1 < c2)  return -1;
	if (c1 > c2)  return +1;
      }
    else if (!*a && !*b)  return 0;
    else if (!*a)         return -1;
    else if (!*b)         return +1;
  return 0;
}

int wcsnuppercmp(const wchar_t* a, const wchar_t* b, size_t length) /* slibc: completeness */
{
  wchar_t c1, c2;
  for (; length--; a++, b++)
    if (*a != *b)
      {
	c1 = iswalpha(*a) ? towupper(*a) : *a;
	c2 = *b;
	if (c1 < c2)  return -1;
	if (c1 > c2)  return +1;
      }
    else if (!*a && !*b)  return 0;
    else if (!*a)         return -1;
    else if (!*b)         return +1;
  return 0;
}

int wmemlowercmp(const wchar_t* a, const wchar_t* b, size_t size) /* slibc: completeness */
{
  wchar_t c1, c2;
  for (; size--; a++, b++)
    if (*a != *b)
      {
	c1 = iswalpha(*a) ? towlower(*a) : *a;
	c2 = *b;
	if (c1 != c2)
	  return c1 < c2 ? -1 : +1;
      }
  return 0;
}

int wmemuppercmp(const wchar_t* a, const wchar_t* b, size_t size) /* slibc: completeness */
{
  wchar_t c1, c2;
  for (; size--; a++, b++)
    if (*a != *b)
      {
	c1 = iswalpha(*a) ? towupper(*a) : *a;
	c2 = *b;
	if (c1 != c2)
	  return c1 < c2 ? -1 : +1;
      }
  return 0;
}

