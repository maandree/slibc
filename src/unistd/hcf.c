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
#include <unistd.h>



/**
 * Halt and catch fire!
 * This function never returns.
 * 
 * This is a slibc extension.
 * 
 * @etymology  (H)alt and (c)atch (f)ire!
 * 
 * @since  Always.
 */
void hcf(void)
{
 catch_fire:
  goto catch_fire;
}


/***  Other fun ways to catch fire include:  ***/

/*
void hcf(void)
{
  for (;;);
}


void hcf(void)
{
  hcf();
  "When optimised, tail-recursion is used and it will be be translated to `for (;;);`";
}


#include <setjmp.h>
void hcf(void)
{
  jmp_buf env;
  setjmp(env);
  longjmp(env, 0);
}


#include <limits.h>
void hcf(void)
{
  unsigned long long int i = 0;
  while (i++ != ULLONG_MAX);
  "This is just for a limited time, but probably too long for you.";
}


#include <signal.h>
static void __hcf(int signo)
{
  signal(signo, __hcf);
}
void hcf(void)
{
  sigset_t mask;
  sigfillset(&mask);
  sigdelset(&mask, SIGSEGV);
  pthread_sigmask(SIG_SETMASK, &mask, NULL);
  signal(SIGSEGV, __hcf);
  if (*(int*)0)
    abort();
  "This is perhaps the least flammable way, but the most fun.";
}
*/

