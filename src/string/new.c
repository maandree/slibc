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
#include <string.h>
#include <stdint.h>
#include <ctype.h>
/* TEMPORARY {{ */
#define STATIC static __attribute__((__used__))
# pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"
STATIC size_t strclen(const char* string, int stop);
STATIC size_t strcnlen(const char* string, int stop, size_t maxlen);
STATIC size_t strstrlen(const char* string, const char* stop);
STATIC size_t strstrnlen(const char* string, const char* stop, size_t maxlen);
STATIC char* (strnchr)(const char* string, int c, size_t maxlen);
STATIC char* (strnchrnul)(const char* string, int c, size_t maxlen);
STATIC char* (memcchr)(const char* segment, int c, int stop, size_t size);
STATIC char* (strcchr)(const char* string, int c, int stop);
STATIC char* (strcnchr)(const char* string, int c, int stop, size_t maxlen);
STATIC char* (strcchrnul)(const char* string, int c, int stop);
STATIC char* (strcnchrnul)(const char* string, int c, int stop, size_t maxlen);
STATIC char* (strnrchr)(const char* string, int c, size_t maxlen);
STATIC void* (memcrchr)(const void* segment, int c, int stop, size_t size);
STATIC char* (strcrchr)(const char* string, int c, int stop);
STATIC char* (strcnrchr)(const char* string, int c, int stop, size_t maxlen);
STATIC void* (rawmemrchr)(const void* segment, int c, size_t size);
STATIC void* (rawmemcasemem)(const void* haystack, const void* needle, size_t needle_length);
STATIC void* (rawmemmem)(const void* haystack, const void* needle, size_t needle_length);
STATIC void* (memccasemem)(const void* haystack, size_t haystack_length, const void* needle, size_t needle_length, int stop);
STATIC void* (memcmem)(const void* haystack, size_t haystack_length, const void* needle, size_t needle_length, int stop);
STATIC char* (strccasestr)(const char* haystack, const char* needle, int stop);
STATIC char* (strcstr)(const char* haystack, const char* needle, int stop);
STATIC char* (strcncasestr)(const char* haystack, const char* needle, int stop, size_t maxlen);
STATIC char* (strcnstr)(const char* haystack, const char* needle, int stop, size_t maxlen);
STATIC char* (strpcbrk)(const char* string, const char* skipset);
STATIC char* (strpbrknul)(const char* string, const char* stopset);
STATIC char* (strpcbrknul)(const char* string, const char* skipset);
STATIC char* (strnpbrk)(const char* string, const char* stopset, size_t maxlen);
STATIC char* (strnpcbrk)(const char* string, const char* skipset, size_t maxlen);
STATIC char* (strnpbrknul)(const char* string, const char* stopset, size_t maxlen);
STATIC char* (strnpcbrknul)(const char* string, const char* skipset, size_t maxlen);
STATIC size_t strnspn(const char* string, const char* skipset, size_t maxlen);
STATIC size_t strncspn(const char* string, const char* stopset, size_t maxlen);
STATIC char* strnsep(char** restrict string, const char* restrict delimiters, size_t* restrict maxlen);
STATIC char* strntok(char* restrict string, const char* restrict delimiters, char** restrict state, size_t* restrict maxlen);
STATIC char* (strprbrk)(const char* string, const char* stopset);
STATIC char* (strprcbrk)(const char* string, const char* skipset);
STATIC char* (strnprbrk)(const char* string, const char* stopset, size_t maxlen);
STATIC char* (strnprcbrk)(const char* string, const char* skipset, size_t maxlen);
STATIC char* memmemmove(char* whither, const char* whence, const char* restrict str, size_t strsize, size_t size);
STATIC char* memmemcpy(void* whither, const void* whence, const char* restrict str, size_t strsize, size_t size);
STATIC void* (memcasestarts)(const void* string, const void* desired, size_t size);
STATIC char* (strncasestarts)(const char* string, const char* desired, size_t maxlen);
STATIC void* (memcaseends)(const void* string, size_t string_size, const void* desired, size_t desired_size);
STATIC char* (strncaseends)(const char* string, const char* desired, size_t maxlen);
STATIC void* (memstarts)(const void* string, const void* desired, size_t size);
STATIC char* (strnstarts)(const char* string, const char* desired, size_t maxlen);
STATIC void* (memends)(const void* string, size_t string_size, const void* desired, size_t desired_size);
STATIC char* (strnends)(const char* string, const char* desired, size_t maxlen);
STATIC int memccasecmp(const void* a, const void* b, size_t size, int stop);
STATIC int memccmp(const void* a, const void* b, size_t size, int stop);
STATIC int strccasecmp(const char* a, const char* b, int stop);
STATIC int strccmp(const char* a, const char* b, int stop);
STATIC int strcncasecmp(const char* a, const char* b, int stop, size_t length);
STATIC int strcncmp(const char* a, const char* b, int stop, size_t length);
STATIC void* (memccasestarts)(const void* string, const void* desired, size_t size, int stop);
STATIC void* (memcstarts)(const void* string, const void* desired, size_t size, int stop);
STATIC char* (strccasestarts)(const char* string, const char* desired, int stop);
STATIC char* (strcstarts)(const char* string, const char* desired, int stop);
STATIC char* (strcncasestarts)(const char* string, const char* desired, int stop, size_t maxlen);
STATIC char* (strcnstarts)(const char* string, const char* desired, int stop, size_t maxlen);
STATIC void* (memccaseends)(const void* string, size_t string_size, const void* desired, size_t desired_size, int stop);
STATIC void* (memcends)(const void* string, size_t string_size, const void* desired, size_t desired_size, int stop);
STATIC char* (strccaseends)(const char* string, const char* desired, int stop);
STATIC char* (strcends)(const char* string, const char* desired, int stop);
STATIC char* (strcncaseends)(const char* string, const char* desired, int stop, size_t maxlen);
STATIC char* (strcnends)(const char* string, const char* desired, int stop, size_t maxlen);
STATIC int strlowercmp(const char* a, const char* b);
STATIC int struppercmp(const char* a, const char* b);
STATIC int strnlowercmp(const char* a, const char* b, size_t length);
STATIC int strnuppercmp(const char* a, const char* b, size_t length);
STATIC int memlowercmp(const void* a, const void* b, size_t size);
STATIC int memuppercmp(const void* a, const void* b, size_t size);
/* }} */



/**
 * Variant of `strlen` that treats both NUL and a
 * selected byte as the termination-byte.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   str   The string.
 * @param   stop  The additional termination-byte.
 * @return        The number of bytes before, the first termination-byte.
 * 
 * @since  Always.
 */
size_t strclen(const char* string, int stop)
{
  return (size_t)(strchrnul(string, stop) - string);
}

/**
 * Variant of `strclen` that only inspects the
 * beginning of a string.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   str     The string.
 * @param   stop    The additional termination-byte.
 * @param   maxlen  The number of bytes to inspect, at most.
 * @return          The number of bytes before, the first termination-byte.
 *                  `maxlen` if no termination-byte was found.
 * 
 * @since  Always.
 */
size_t strcnlen(const char* string, int stop, size_t maxlen)
{
  const char* end = strnchr(string, stop, maxlen);
  return end ? (size_t)(end - string) : maxlen;
}

/**
 * Variant of `strlen` that treats both NUL and a
 * selected string as the termination-mark.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   str   The string.
 * @param   stop  The additional termination-mark.
 * @return        The number of bytes before, the first termination-mark.
 * 
 * @since  Always.
 */
size_t strstrlen(const char* string, const char* stop)
{
  const char* end = strstr(string, stop);
  return end ? (size_t)(end - string) : strlen(string);
}

/**
 * Variant of `strstrlen` that only inspects the
 * beginning of a string.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   str     The string.
 * @param   stop    The additional termination-mark.
 * @param   maxlen  The number of bytes to inspect, at most.
 * @return          The number of bytes before, the first termination-mark.
 *                  `maxlen` if no termination-byte was found.
 * 
 * @since  Always.
 */
size_t strstrnlen(const char* string, const char* stop, size_t maxlen)
{
  const char* end = strnstr(string, stop, maxlen);
  return end ? (size_t)(end - string) : maxlen;
}

/**
 * Variant of `strchr` that only inspects the beginning
 * of a string.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   string  The string to search.
 *                  The terminating NUL character is
 *                  considered a part of the string.
 * @param   c       The sought after character.
 * @param   maxlen  The number of bytes to inspect, at most.
 * @return          Pointer to the first occurrence of `c`,
 *                  `NULL` if none were found.
 * 
 * @since  Always.
 */
char* (strnchr)(const char* string, int c, size_t maxlen)
{
  for (;; string++)
    if (*string == c)
      return string;
    else if (!*string || !maxlen--)
      return NULL;
}

/**
 * Variant of `strchrnul` that only inspects the beginning
 * of a string.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   string  The string to search.
 *                  The terminating NUL character is
 *                  considered a part of the string.
 * @param   c       The sought after character.
 * @param   maxlen  The number of bytes to inspect, at most.
 * @return          The end of the string (or end of inspected
 *                  part of the sring) if non were found. If the
 *                  whole string was inspected, the returned
 *                  pointer will point to a NUL byte.
 * 
 * @since  Always.
 */
char* (strnchrnul)(const char* string, int c, size_t maxlen)
{
  for (;; string++)
    if (*string == c)
      return string;
    else if (!*string || !maxlen--)
      return string;
}

/**
 * Variant of `memchr` that stops searching when it
 * another specified character.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   segment  The memory segment to search.
 * @param   c        The sought after character.
 * @param   stop     Return `NULL` when this character is found.
 * @param   size     The size of the memory segment.
 * @return           Pointer to the first occurrence of `c`,
 *                   `NULL` if none were found.
 * 
 * @since  Always.
 */
char* (memcchr)(const char* segment, int c, int stop, size_t size)
{
  char* s = segment;
  for (;; s++)
    if (*s == c)
      return s;
    else if ((*s == stop) || !size--)
      return NULL;
}

/**
 * Variant of `strchr` that stops searching when it
 * another specified character.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   string  The string to search.
 *                  The terminating NUL character is
 *                  considered a part of the string.
 * @param   c       The sought after character.
 * @param   stop    Return `NULL` when this character is found.
 * @return          Pointer to the first occurrence of `c`,
 *                  `NULL` if none were found.
 * 
 * @since  Always.
 */
char* (strcchr)(const char* string, int c, int stop)
{
  for (;; string++)
    if (*string == c)
      return string;
    else if (!*string || (*string == stop))
      return NULL;
}

/**
 * Variant of `strnchr` that stops searching when it
 * another specified character.
 * 
 * This is a slibc extension added for completeness.
 * 
 * @param   string  The string to search.
 *                  The terminating NUL character is
 *                  considered a part of the string.
 * @param   c       The sought after character.
 * @param   stop    Return `NULL` when this character is found.
 * @param   maxlen  The number of bytes to inspect, at most.
 * @return          Pointer to the first occurrence of `c`,
 *                  `NULL` if none were found.
 * 
 * @since  Always.
 */
char* (strcnchr)(const char* string, int c, int stop, size_t maxlen)
{
  for (;; string++)
    if (*string == c)
      return string;
    else if (!*string || (*string == stop) || !maxlen--)
      return NULL;
}

char* (strcchrnul)(const char* string, int c, int stop) /* slibc+gnu: completeness */
{
  for (;; string++)
    if (*string == c)
      return string;
    else if (!*string || (*string == stop))
      return string;
}

char* (strcnchrnul)(const char* string, int c, int stop, size_t maxlen) /* slibc+gnu: completeness */
{
  for (;; string++)
    if (*string == c)
      return string;
    else if (!*string || (*string == stop) || !maxlen--)
      return string;
}

char* (strnrchr)(const char* string, int c, size_t maxlen) /* slibc: completeness */
{
  char* r = NULL;
  for (; maxlen--; string++)
    if (*string == c)
      r = string;
    else if (!*string)
      return c ? r : string;
  return NULL;
}

void* (memcrchr)(const void* segment, int c, int stop, size_t size) /* slibc: completeness */
{
  char* r = NULL;
  char* s = segment;
  for (;; size--)
    if (*s == c)
      r = s;
    else if ((*s == stop) || !size)
      return r;
}

char* (strcrchr)(const char* string, int c, int stop) /* slibc: completeness */
{
  char* r = NULL;
  for (;; string++)
    if (*string == c)
      r = string;
    else if (!*string)
      return c ? r : string;
    else if (*string == stop)
      return r;
}

char* (strcnrchr)(const char* string, int c, int stop, size_t maxlen) /* slibc: completeness */
{
  char* r = NULL;
  for (; maxlen--; string++)
    if (*string == c)
      r = string;
    else if (!*string)
      return c ? r : string;
    else if (*string == stop)
      return r;
  return NULL;
}

void* (rawmemrchr)(const void* segment, int c, size_t size) /* slibc+gnu: completeness */
{
  char* s = segment;
  for (;;)
    if (s[--size] == c)
      return s + size;
}

void* (rawmemcasemem)(const void* haystack, const void* needle, size_t needle_length) /* slibc */
{
  return (memcasemem)(haystack, SIZE_MAX, needle, needle_length);
}

void* (rawmemmem)(const void* haystack, const void* needle, size_t needle_length) /* slibc */
{
  return (memmem)(haystack, SIZE_MAX, needle, needle_length);
}

void* (memccasemem)(const void* haystack, size_t haystack_length, const void* needle, size_t needle_length, int stop) /* slibc: completeness */
{
  const void* p = memchr(haystack, stop, haystack_length);
  return (memcasemem)(haystack, p ? (size_t)(p - haystack) : haystack_length, needle, needle_length);
}

void* (memcmem)(const void* haystack, size_t haystack_length, const void* needle, size_t needle_length, int stop) /* slibc: completeness */
{
  const void* p = memchr(haystack, stop, haystack_length);
  return (memmem)(haystack, p ? (size_t)(p - haystack) : haystack_length, needle, needle_length);
}

char* (strccasestr)(const char* haystack, const char* needle, int stop) /* slibc: completeness */
{
  return (memcasemem)(haystack, strclen(haystack, stop), needle, strlen(needle));
}

char* (strcstr)(const char* haystack, const char* needle, int stop) /* slibc: completeness */
{
  return (memmem)(haystack, strclen(haystack, stop), needle, strlen(needle));
}

char* (strcncasestr)(const char* haystack, const char* needle, int stop, size_t maxlen) /* slibc: completeness */
{
  return (memcasemem)(haystack, strcnlen(haystack, stop, maxlen), needle, strlen(needle));
}

char* (strcnstr)(const char* haystack, const char* needle, int stop, size_t maxlen) /* slibc: completeness */
{
  return (memmem)(haystack, strcnlen(haystack, stop, maxlen), needle, strlen(needle));
}

char* (strpcbrk)(const char* string, const char* skipset) /* slibc: completeness */
{
  char set[256];
  char c;
  const char* s = string;
  memset(set, 0, 256 * sizeof(char));
  while ((c = *skipset++))
    set[(size_t)c] = 1;
  while ((c = *s++))
    if (set[(size_t)c])
      break;
  return c ? (s - 1) : NULL;
}

char* (strpbrknul)(const char* string, const char* stopset) /* slibc */
{
  char set[256];
  char c;
  const char* s = string;
  memset(set, 0, 256 * sizeof(char));
  while ((c = *stopset++))
    set[(size_t)c] = 1;
  while ((c = *s++))
    if (!set[(size_t)c])
      break;
  return s - 1;
}

char* (strpcbrknul)(const char* string, const char* skipset) /* slibc: completeness */
{
  char set[256];
  char c;
  const char* s = string;
  memset(set, 0, 256 * sizeof(char));
  while ((c = *skipset++))
    set[(size_t)c] = 1;
  while ((c = *s++))
    if (set[(size_t)c])
      break;
  return s - 1;
}

char* (strnpbrk)(const char* string, const char* stopset, size_t maxlen) /* slibc: completeness */
{
  char set[256];
  char c;
  const char* s = string;
  memset(set, 0, 256 * sizeof(char));
  while ((c = *stopset++))
    set[(size_t)c] = 1;
  while (maxlen-- && ((c = *s++)))
    if (!set[(size_t)c])
      break;
  return c ? (s - 1) : NULL;
}

char* (strnpcbrk)(const char* string, const char* skipset, size_t maxlen) /* slibc: completeness */
{
  char set[256];
  char c;
  const char* s = string;
  memset(set, 0, 256 * sizeof(char));
  while ((c = *skipset++))
    set[(size_t)c] = 1;
  while (maxlen-- && ((c = *s++)))
    if (set[(size_t)c])
      break;
  return c ? (s - 1) : NULL;
}

char* (strnpbrknul)(const char* string, const char* stopset, size_t maxlen) /* slibc: completeness */
{
  char set[256];
  char c;
  const char* s = string;
  memset(set, 0, 256 * sizeof(char));
  while ((c = *stopset++))
    set[(size_t)c] = 1;
  while (maxlen-- && ((c = *s++)))
    if (!set[(size_t)c])
      break;
  return s - 1;
}

char* (strnpcbrknul)(const char* string, const char* skipset, size_t maxlen) /* slibc: completeness */
{
  char set[256];
  char c;
  const char* s = string;
  memset(set, 0, 256 * sizeof(char));
  while ((c = *skipset++))
    set[(size_t)c] = 1;
  while (maxlen-- && ((c = *s++)))
    if (set[(size_t)c])
      break;
  return s - 1;
}

size_t strnspn(const char* string, const char* skipset, size_t maxlen) /* slibc: completeness */
{
  char set[256];
  char c;
  const char* s = string;
  memset(set, 0, 256);
  while ((c = *skipset++))
    set[(size_t)c] = 1;
  for (; maxlen && ((c = *s++)); maxlen--)
    if (set[(size_t)c])
      break;
  return (size_t)(s - !!maxlen - string);
}

size_t strncspn(const char* string, const char* stopset, size_t maxlen) /* slibc: completeness */
{
  char set[256];
  char c;
  const char* s = string;
  memset(set, 0, 256);
  while ((c = *stopset++))
    set[(size_t)c] = 1;
  for (; maxlen && ((c = *s++)); maxlen--)
    if (!set[(size_t)c])
      break;
  return (size_t)(s - !!maxlen - string);
}

char* strnsep(char** restrict string, const char* restrict delimiters,
	      size_t* restrict maxlen) /* slibc: completeness */
{
  char* r = *string;
  char* next;
  if (r == NULL)
    return NULL;
  
  next = strnpbrk(r, delimiters, *maxlen);
  if (next != NULL)
    *next++ = 0, *maxlen -= (size_t)(next - r);
  *string = next;
  
  return r;
}

char* strntok(char* restrict string, const char* restrict delimiters,
	      char** restrict state, size_t* restrict maxlen) /* slibc: completeness */
{
  char* r;
  if (string == NULL)
    *state = string;
  for (;;)
    {
      r = strnsep(state, delimiters, maxlen);
      if (r == NULL)
	return NULL;
      if (*r)
	return r;
    }
}

char* (strprbrk)(const char* string, const char* stopset) /* slibc: completeness */
{
  char set[256];
  char c;
  const char* s = string;
  const char* r = NULL;
  memset(set, 0, 256);
  while ((c = *stopset++))
    set[(size_t)c] = 1;
  while ((c = *s++))
    if (!set[(size_t)c])
      r = s - 1;
  return r;
}

char* (strprcbrk)(const char* string, const char* skipset) /* slibc: completeness */
{
  char set[256];
  char c;
  const char* s = string;
  const char* r = NULL;
  memset(set, 0, 256 * sizeof(char));
  while ((c = *skipset++))
    set[(size_t)c] = 1;
  while ((c = *s++))
    if (set[(size_t)c])
      r = s - 1;
  return r;
}

char* (strnprbrk)(const char* string, const char* stopset, size_t maxlen) /* slibc: completeness */
{
  char set[256];
  char c;
  const char* s = string;
  const char* r = NULL;
  memset(set, 0, 256 * sizeof(char));
  while ((c = *stopset++))
    set[(size_t)c] = 1;
  while (maxlen-- && ((c = *s++)))
    if (!set[(size_t)c])
      r = s - 1;
  return r;
}

char* (strnprcbrk)(const char* string, const char* skipset, size_t maxlen) /* slibc: completeness */
{
  char set[256];
  char c;
  const char* s = string;
  const char* r = NULL;
  memset(set, 0, 256 * sizeof(char));
  while ((c = *skipset++))
    set[(size_t)c] = 1;
  while (maxlen-- && ((c = *s++)))
    if (set[(size_t)c])
      r = s - 1;
  return r;
}

char* memmemmove(char* whither, const char* whence, const char* restrict str,
		 size_t strsize, size_t size) /* slibc: completeness */
{
  char* stop = (memmem)(whence, size, str, strsize);
  void* r = NULL;
  if (stop != NULL)
    size = (size_t)(stop - (const char*)whence), r = whither + size;
  memmove(whither, whence, size);
  return r;
}

char* memmemcpy(void* whither, const void* whence, const char* restrict str,
		size_t strsize, size_t size) /* slibc: completeness */
{
  char* stop = (memmem)(whence, size, str, strsize);
  void* r = NULL;
  if (stop != NULL)
    size = (size_t)(stop - (const char*)whence), r = whither + size;
  memcpy(whither, whence, size);
  return r;
}

void* (memcasestarts)(const void* string, const void* desired, size_t size) /* slibc: completeness */
{
  return (memcasecmp)(string, desired, size) ? NULL : string;
}

char* (strncasestarts)(const char* string, const char* desired, size_t maxlen) /* slibc: completeness */
{
  size_t n = strnlen(string, maxlen);
  size_t m = strnlen(desired, maxlen);
  if (n < m)
    return NULL;
  return (memcasecmp)(string, desired, m) ? NULL : string;
}

void* (memcaseends)(const void* string, size_t string_size, const void* desired, size_t desired_size) /* slibc: completeness */
{
  return (memcasecmp)(string + (string_size - desired_size), desired, desired_size)
    ? NULL : (string + string_size);
}

char* (strncaseends)(const char* string, const char* desired, size_t maxlen) /* slibc: completeness */
{
  size_t n = strnlen(string, maxlen);
  size_t m = strnlen(desired, maxlen);
  if (n < m)
    return NULL;
  return (memcasecmp)(string + (n - m), desired, m) ? NULL : (string + n);
}

void* (memstarts)(const void* string, const void* desired, size_t size) /* slibc */
{
  return (memcmp)(string, desired, size) ? NULL : string;
}

char* (strnstarts)(const char* string, const char* desired, size_t maxlen) /* slibc: completeness */
{
  size_t n = strnlen(string, maxlen);
  size_t m = strnlen(desired, maxlen);
  if (n < m)
    return NULL;
  return (memcmp)(string, desired, m) ? NULL : string;
}

void* (memends)(const void* string, size_t string_size, const void* desired, size_t desired_size) /* slibc: completeness */
{
  return (memcmp)(string + (string_size - desired_size), desired, desired_size)
    ? NULL : (string + string_size);
}

char* (strnends)(const char* string, const char* desired, size_t maxlen) /* slibc: completeness */
{
  size_t n = strnlen(string, maxlen);
  size_t m = strnlen(desired, maxlen);
  if (n < m)
    return NULL;
  return (memcmp)(string + (n - m), desired, m) ? NULL : (string + n);
}

int memccasecmp(const void* a, const void* b, size_t size, int stop) /* slibc: completeness */
{
  const signed char* s1 = a;
  const signed char* s2 = b;
  int c1, c2;
  for (; c1 = (int)*s1++, c2 = (int)*s2++, (c1 != stop) && (c2 != stop) && size; size--)
    if (c1 != c2)
      {
	c1 = isalpha(c1) ? tolower(c1) : c1;
	c2 = isalpha(c2) ? tolower(c2) : c2;
	if ((c1 -= c2))
	  return c1;
      }
  if (c1 == stop)  c1 = 0;
  if (c2 == stop)  c2 = 0;
  return size ? (c1 - c2) : 0;
}

int memccmp(const void* a, const void* b, size_t size, int stop) /* slibc: completeness */
{
  const signed char* s1 = a;
  const signed char* s2 = b;
  int c1, c2;
  for (; c1 = (int)*s1++, c2 = (int)*s2++, (c1 != stop) && (c2 != stop) && size; size--)
    if (c1 != c2)
      return c1 - c2;
  if (c1 == stop)  c1 = 0;
  if (c2 == stop)  c2 = 0;
  return size ? (c1 - c2) : 0;
}

int strccasecmp(const char* a, const char* b, int stop) /* slibc: completeness */
{
  return strcncasecmp(a, b, stop, SIZE_MAX);
}

int strccmp(const char* a, const char* b, int stop) /* slibc */
{
  size_t n = strclen(a, stop);
  size_t m = strclen(b, stop);
  return memcmp(a, b, (n < m ? n : m) + 1);
}

int strcncasecmp(const char* a, const char* b, int stop, size_t length) /* slibc: completeness */
{
  size_t n = strcnlen(a, stop, length);
  size_t m = strcnlen(b, stop, length);
  int r = memcasecmp(a, b, (n < m ? n : m));
  return r ? r : n == m ? 0 : n < m ? -1 : +1;
}

int strcncmp(const char* a, const char* b, int stop, size_t length) /* slibc: completeness */
{
  size_t n = strcnlen(a, stop, length);
  size_t m = strcnlen(b, stop, length);
  int r = memcmp(a, b, (n < m ? n : m));
  return r ? r : n == m ? 0 : n < m ? -1 : +1;
}

void* (memccasestarts)(const void* string, const void* desired, size_t size, int stop) /* slibc: completeness */
{
  return (memccasecmp)(string, desired, size, stop) ? NULL : string;
}

void* (memcstarts)(const void* string, const void* desired, size_t size, int stop) /* slibc: completeness */
{
  return (memccmp)(string, desired, size, stop) ? NULL : string;
}

char* (strccasestarts)(const char* string, const char* desired, int stop) /* slibc: completeness */
{
  size_t n = strclen(string, stop);
  size_t m = strclen(desired, stop);
  if (n < m)
    return NULL;
  return (memcasecmp)(string, desired, m) ? NULL : string;
}

char* (strcstarts)(const char* string, const char* desired, int stop) /* slibc: completeness */
{
  size_t n = strclen(string, stop);
  size_t m = strclen(desired, stop);
  if (n < m)
    return NULL;
  return (memcmp)(string, desired, m) ? NULL : string;
}

char* (strcncasestarts)(const char* string, const char* desired, int stop, size_t maxlen) /* slibc: completeness */
{
  size_t n = strcnlen(string, stop, maxlen);
  size_t m = strcnlen(desired, stop, maxlen);
  if (n < m)
    return NULL;
  return (memcasecmp)(string, desired, m) ? NULL : string;
}

char* (strcnstarts)(const char* string, const char* desired, int stop, size_t maxlen) /* slibc: completeness */
{
  size_t n = strcnlen(string, stop, maxlen);
  size_t m = strcnlen(desired, stop, maxlen);
  if (n < m)
    return NULL;
  return (memcmp)(string, desired, m) ? NULL : string;
}

void* (memccaseends)(const void* string, size_t string_size, const void* desired, size_t desired_size, int stop) /* slibc: completeness */
{
  void* end = memchr(string, stop, string_size);
  if (end != NULL)
    string_size = (size_t)(end - string);
  return (memcasecmp)(string + (string_size - desired_size), desired, desired_size)
    ? NULL : (string + string_size);
}

void* (memcends)(const void* string, size_t string_size, const void* desired, size_t desired_size, int stop) /* slibc: completeness */
{
  void* end = memchr(string, stop, string_size);
  if (end != NULL)
    string_size = (size_t)(end - string);
  return (memcmp)(string + (string_size - desired_size), desired, desired_size)
    ? NULL : (string + string_size);
}

char* (strccaseends)(const char* string, const char* desired, int stop) /* slibc: completeness */
{
  size_t n = strclen(string, stop);
  size_t m = strclen(desired, stop);
  if (n < m)
    return NULL;
  return (memcasecmp)(string + (n - m), desired, m) ? NULL : (string + n);
}

char* (strcends)(const char* string, const char* desired, int stop) /* slibc: completeness */
{
  size_t n = strclen(string, stop);
  size_t m = strclen(desired, stop);
  if (n < m)
    return NULL;
  return (memcmp)(string + (n - m), desired, m) ? NULL : (string + n);
}

char* (strcncaseends)(const char* string, const char* desired, int stop, size_t maxlen) /* slibc: completeness */
{
  size_t n = strcnlen(string, stop, maxlen);
  size_t m = strcnlen(desired, stop, maxlen);
  if (n < m)
    return NULL;
  return (memcasecmp)(string + (n - m), desired, m) ? NULL : (string + n);
}

char* (strcnends)(const char* string, const char* desired, int stop, size_t maxlen) /* slibc: completeness */
{
  size_t n = strcnlen(string, stop, maxlen);
  size_t m = strcnlen(desired, stop, maxlen);
  if (n < m)
    return NULL;
  return (memcmp)(string + (n - m), desired, m) ? NULL : (string + n);
}

int strlowercmp(const char* a, const char* b) /* slibc */
{
  return strnlowercmp(a, b, SIZE_MAX);
}

int struppercmp(const char* a, const char* b) /* slibc: completeness */
{
  return strnuppercmp(a, b, SIZE_MAX);
}

int strnlowercmp(const char* a, const char* b, size_t length) /* slibc: completeness */
{
  int c1, c2;
  for (; length--; a++, b++)
    if (*a != *b)
      {
	c1 = isalpha(*a) ? tolower(*a) : (int)*a;
	c2 = *b;
	if ((c1 -= c2))
	  return c1;
      }
    else if (!*a && !*b)  return 0;
    else if (!*a)         return -1;
    else if (!*b)         return +1;
  return 0;
}

int strnuppercmp(const char* a, const char* b, size_t length) /* slibc: completeness */
{
  int c1, c2;
  for (; length--; a++, b++)
    if (*a != *b)
      {
	c1 = isalpha(*a) ? toupper(*a) : (int)*a;
	c2 = *b;
	if ((c1 -= c2))
	  return c1;
      }
    else if (!*a && !*b)  return 0;
    else if (!*a)         return -1;
    else if (!*b)         return +1;
  return 0;
}

int memlowercmp(const void* a, const void* b, size_t size) /* slibc: completeness */
{
  const signed char* s1 = a;
  const signed char* s2 = b;
  int c1, c2;
  for (; size--; s1++, s2++)
    if (*s1 != *s2)
      {
	c1 = isalpha(*s1) ? tolower(*s1) : (int)*s1;
	c2 = *s2;
	if ((c1 -= c2))
	  return c1;
      }
  return 0;
}

int memuppercmp(const void* a, const void* b, size_t size) /* slibc: completeness */
{
  const signed char* s1 = a;
  const signed char* s2 = b;
  int c1, c2;
  for (; size--; s1++, s2++)
    if (*s1 != *s2)
      {
	c1 = isalpha(*s1) ? toupper(*s1) : (int)*s1;
	c2 = *s2;
	if ((c1 -= c2))
	  return c1;
      }
  return 0;
}

