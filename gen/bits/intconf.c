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



/**
 * Used to determine the signness of `char`.
 */
volatile char nul = 0;

/**
 * Used to determine the signness of `wchar_t`.
 * 
 * Note that `wchar_t` is set implicitly by the
 * help of the compiler so that our libc does
 * not taint the result.
 */
volatile typeof(L'\0') wnul = 0;



/**
 * On my amd64 machine, the usual result is:
 *   int_fast8_t  = int32_t
 *   int_fast16_t = int32_t
 *   int_fast32_t = int32_t
 *   int_fast64_t = int64_t
 */


/**
 * Measure the performance of a intrinsic integer type,
 * and if it is faster than the previous candidate (or
 * is the first candidate,) store it as the, yet, most
 * performant candidate.
 * 
 * @param  VAR  A volatile register variable of the
 *              type that shall be tested.
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


/**
 * Determine whether the performance of `typeof(VAR)` should be determined,
 * when finding the most performant, compatiable intrinsic type of a `int_fastN_t`.
 * 
 * @param   VAR  An variable of the type (or the type itself) that is a candidate.
 * @return       Determine whether the type shall be tested.
 */
#define TEST(VAR)  (this = 8 * (int)sizeof(VAR), ((this >= bits) && (this > last)))

#if defined(__GNUC__)
__attribute__((optimize("-O0")))
#endif
/**
 * Find the (in general) fastest intrinsic integer type,
 * that has at least a specified number of bits.
 * 
 * @param   bits  The minimum number of bits the type may have.
 * @return        The number of bits the most performance
 *                compatible integer type has.
 */
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


/**
 * For a 16-bit integer with the value 0x0102, print,
 * to a string, the bytes it is constructed by one the
 * host machine, in storage order.
 * 
 * @return  The bytes in the integer juxtaposed.
 */
static char* byteorder_16(void)
{
  static char buf[16 / 4 + 1];
  union
  {
    short int all;
    struct
    {
      char a; char b;
    };
  } test = { .all = 0x0102 };
  
  sprintf(buf, "%02i%02i", test.a, test.b);
  return buf;
}


/**
 * For a 32-bit integer with the value 0x01020304, print,
 * to a string, the bytes it is constructed by one the
 * host machine, in storage order.
 * 
 * @return  The bytes in the integer juxtaposed.
 */
static char* byteorder_32(void)
{
  static char buf[32 / 4 + 1];
  if (8 * sizeof(int) == 32)
    {
      union
      {
	int all;
	struct
	{
	  char a; char b; char c; char d;
	};
      } test = { .all = 0x01020304 };
  
      sprintf(buf, "%02i%02i%02i%02i",
	      test.a, test.b, test.c, test.d);
    }
  else
    {
      union
      {
	long int all;
	struct
	{
	  char a; char b; char c; char d;
	};
      } test = { .all = 0x01020304L };
  
      sprintf(buf, "%02i%02i%02i%02i",
	      test.a, test.b, test.c, test.d);
    }
  return buf;
}


/**
 * For a 16-bit integer with the value 0x0102030405060708,
 * print, to a string, the bytes it is constructed by one
 * the host machine, in storage order.
 * 
 * @return  The bytes in the integer juxtaposed.
 */
static char* byteorder_64(void)
{
  static char buf[64 / 4 + 1];
  union
  {
    long long int all;
    struct
    {
      char a; char b; char c; char d;
      char e; char f; char g; char h;
    };
  } test = { .all = 0x0102030405060708LL };
  
  sprintf(buf, "%02i%02i%02i%02i%02i%02i%02i%02i",
	  test.a, test.b, test.c, test.d,
	  test.e, test.f, test.g, test.h);
  return buf;
}


/**
 * @param   argc  The number of command line arguments, should
 *                be either 1 (print integer width information)
 *                or 2 (otherwise).
 * @param   argv  Command line arguments, if `argc == 2`, `argv[2]`
 *                is interpreted as follows:
 *                - "fast8"         Print the number of bits in `int_fast8_t`  and `uint_fast8_t`.
 *                - "fast16"        Print the number of bits in `int_fast16_t` and `uint_fast16_t`.
 *                - "fast32"        Print the number of bits in `int_fast32_t` and `uint_fast32_t`.
 *                - "fast64"        Print the number of bits in `int_fast64_t` and `uint_fast64_t`.
 *                - "char-signed"   Print 1 if `char`    is signed, and `0` if it is unsigned.
 *                - "wchar-signed"  Print 1 if `wchar_t` is signed, and `0` if it is unsigned.
 * @return        0 on success, 1 on error (including printing error.)
 */
int main(int argc, char* argv[])
{
  int r = 0;
  if (argc < 2)
    {
      /* Print the number of bits in the intrinsic integers types. */
      r |= printf("CHAR_BIT %zu\n",      8 * sizeof(char));
      r |= printf("SHORT_BIT %zu\n",     8 * sizeof(short int));
      r |= printf("INT_BIT %zu\n",       8 * sizeof(int));
      r |= printf("LONG_BIT %zu\n",      8 * sizeof(long int));
      r |= printf("LONG_LONG_BIT %zu\n", 8 * sizeof(long long int));
      r |= printf("PTR_BIT %zu\n",       8 * sizeof(void*));
      r |= printf("WCHAR_BIT %zu\n",     8 * sizeof(L'\0'));
      
      /* Print byte orders. */
      r |= printf("INT16_BYTEORDER 0x%s\n",   byteorder_16());
      r |= printf("INT32_BYTEORDER 0x%sL\n",  byteorder_32());
      r |= printf("INT64_BYTEORDER 0x%sLL\n", byteorder_64());
      
      /* Print the intrinsic type for specific numbers of bits. */
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

