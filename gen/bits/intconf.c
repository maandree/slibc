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
#include <stdio.h>
#include <string.h>
#include <time.h>



volatile char nul = 0;
volatile typeof(L'\0') wnul = 0;



/**
 * On my amd64 machine, the usual result is:
 *   int_fast8_t  = int32_t
 *   int_fast16_t = int32_t
 *   int_fast32_t = int32_t
 *   int_fast64_t = int64_t
 */


#define FAST_TEST(VAR)  \
  n = 0, *VAR##p = 0; \
  if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start)) \
    return perror(""), -1; \
  for (;;) \
    { \
      for (m = 1000; m--;) \
	VAR = 50, VAR += 50, VAR -= 50, VAR *= 50, VAR /= 50, VAR <<= 1, VAR >>= 1, *VAR##p |= 1; \
      n++; \
      if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end)) \
	return perror(""), -1; \
      if (end.tv_sec > start.tv_sec + 2) \
	break; \
      if (end.tv_sec > start.tv_sec + 1) \
	if (end.tv_nsec >= start.tv_nsec) \
	  break; \
    } \
  time_elapsed = (long long int)(end.tv_sec) * 1000000000LL; \
  time_elapsed += (long long int)(end.tv_nsec); \
  time_elapsed -= (long long int)(start.tv_sec) * 1000000000LL; \
  time_elapsed -= (long long int)(start.tv_nsec); \
  adjn = (double)n, adjn /= (double)time_elapsed / 1000000000.; \
  fprintf(stderr, "int%zu_t:%s %i000 op:s in %lli.%09lli s = %lf op:s/s\n", \
	  8 * sizeof(VAR), 8 * sizeof(VAR) < 10 ? " " : "", 8 * n, \
	  time_elapsed / 1000000000LL, time_elapsed % 1000000000LL, adjn * 8000.); \
  if ((!best) || (adjn > bestn)) \
    bestn = adjn, best = 8 * sizeof(VAR); \
  last = this


#define TEST(VAR)  (this = 8 * (int)sizeof(VAR), ((this >= bits) && (this > last)))
#if defined(__GNUC__)
__attribute__((optimize("-O0")))
#endif
static int fast(int bits)
{
  int last = 0, this = 0, best = 0, n, m;
  float bestn = 0;
  float adjn;
  struct timespec start, end;
  long long int time_elapsed;
  
  register volatile char hhi;
  register volatile short int hi;
  register volatile int i;
  register volatile long int li;
  register volatile long long int lli;
  volatile char hhip[1];
  volatile short int hip[1];
  volatile int ip[1];
  volatile long int lip[1];
  volatile long long int llip[1];
  
  if (TEST(hhi))    { FAST_TEST(hhi); }
  if (TEST(hi))     { FAST_TEST(hi);  }
  if (TEST(i))      { FAST_TEST(i);   }
  if (TEST(li))     { FAST_TEST(li);  }
  if (best) {
    if (TEST(lli))  { FAST_TEST(lli); }
  } else
    best = 64;
  fprintf(stderr, "int_fast%i_t = int%i_t\n\n", bits, best);
  
  return best;
}
#undef TEST


int main(int argc, char* argv[])
{
  int r = 0;
  if (argc < 2)
    {
      r |= printf("CHAR_BIT %zu\n",      8 * sizeof(char));
      r |= printf("SHORT_BIT %zu\n",     8 * sizeof(short int));
      r |= printf("INT_BIT %zu\n",       8 * sizeof(int));
      r |= printf("LONG_BIT %zu\n",      8 * sizeof(long int));
      r |= printf("LONG_LONG_BIT %zu\n", 8 * sizeof(long long int));
      r |= printf("PTR_BIT %zu\n",       8 * sizeof(void*));
      r |= printf("WCHAR_BIT %zu\n",     8 * sizeof(L'\0'));
      
      r |= printf("INT%zu %s\n", 8 * sizeof(char), "char");
      r |= printf("INT%zu %s\n", 8 * sizeof(short int), "short int");
      r |= printf("INT%zu %s\n", 8 * sizeof(int), "int");
      r |= printf("INT%zu %s\n", 8 * sizeof(long int), "long int");
      r |= printf("INT%zu %s\n", 8 * sizeof(long long int), "long long int");
      return r < 0 ? 1 : 0;
    }
  else if (argc == 2)
    {
      if      (!strcmp(argv[1], "fast8"))   r = fast(8);
      else if (!strcmp(argv[1], "fast16"))  r = fast(16);
      else if (!strcmp(argv[1], "fast32"))  r = fast(32);
      else if (!strcmp(argv[1], "fast64"))  r = fast(64);
      else if (!strcmp(argv[1], "char-signed"))
	{
	  nul = ~nul;
	  r = !(nul > 0);
	  return printf("%i\n", r) < 0 ? 1 : 0;
	}
      else if (!strcmp(argv[1], "wchar-signed"))
	{
	  wnul = ~wnul;
	  r = !(wnul > 0);
	  return printf("%i\n", r) < 0 ? 1 : 0;
	}
      
      if (r <= 0)
	return 1;
      return printf("%i\n", r) < 0 ? 1 : 0;
    }
  
  return 1;
}

