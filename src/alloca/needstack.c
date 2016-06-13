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
#include <slibc/internals.h>
#include <alloca.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>



/**
 * Unless the stack can grow with `n` bytes
 * without overflowing, the program shall
 * either be killed by the kernel (SIGSEGV)
 * or this function shall indicate that the
 * stack cannot be grown.
 * 
 * @param   n  The number of bytes the stack must be able to grow.
 * @return     0 if the stack can grow, 1 otherwise.
 */
int stack_will_overflow(intptr_t n)
{
  void* prev_brk;
  
  /* TODO an alternative way is to fork and let the child
   *      do the test. */
  
  /* TODO This function shall block calls to brk and sbrk. */
  
  prev_brk = sbrk(n);
  if (prev_brk == (void*)-1)
    return 1;
  if (brk(prev_brk))
    return 1; /* Should not happen. */
  
  {
    /* TODO This function shall block calls to signal.h functions. */
    
    sigset_t old_mask;
    sigset_t new_mask;
    void* old_sigsegv_handler;
    
    if (sigemptyset(&new_mask) || sigaddset(&new_mask, SIGSEGV))
      return 1;
    
    old_sigsegv_handler = signal(SIGSEGV, SIG_DFL);
    /* Sorry, we cannot have a signal handler, the OS kernel
     * will make the CPU halt and catch fire until we die. */
    if (old_sigsegv_handler == SIG_ERR)
      return 1;
    
    if (pthread_sigmask(SIG_UNBLOCK, &new_mask, &old_mask))
      return 1;
    
    (void) alloca((size_t)n);
    
    if (pthread_sigmask(SIG_SETMASK, &old_mask, NULL))
      return 1;
    
    if (signal(SIGSEGV, old_sigsegv_handler) == SIG_ERR)
      return 1;
  }
  
  return 0;
}


/**
 * Check for execution stack overflow. If the stack of
 * overflow, or will overflow, the program shall abort.
 * 
 * It is possible that the process is killed by SIGSEGV
 * instead of aborting.
 * 
 * This is a Plan 9 from Bell Labs extension.
 * 
 * @etymology  I (need) addition (stack) space.
 * 
 * @param  n  The number of bytes the stack will grow by.
 *            0 can be used to check for a current stack
 *            overflow. Must be non-negative.
 * 
 * @since  Always.
 */
void (needstack)(int n)
{
  int tty;
  
  if (stack_will_overflow((intptr_t)n) == 0)
    return;
  
  tty = isatty(STDERR_FILENO);
  fprintf(stderr,
	  _("%(\033[00;01m%)%s%(\033[00m%): "
	    "%(\033[31m%)%s%(\033[00m%)"
	    "%(: %(\033[31m%)hinted stack growth: %i bytes%(\033[00m%)%)\n"),
	  tty, program_invocation_name, tty,
	  tty, (n ? _("imminent stack overflow detected") : _("stack overflow detected")), tty,
	  n != 0, tty, n, tty);
  
  fflush(NULL); /* Flush all streams. */
  abort();
}


/**
 * This function is called if the `needstack` macro is called.
 * It enhances the `needstack` function with detail on where
 * the program failed.
 * 
 * You should not use this function directly.
 * 
 * @param  n     The number of bytes the stack will grow by. 0 can be used
 *               to check for a current stack overflow. Must be non-negative.
 * @param  file  The filename of the source cose whence the check was made.
 * @param  line  The line in the source code whence the check was made.
 * @param  func  The function in the source code whence the check was made,
 *               `NULL` if unknown (C99 is required.)
 */
void __needstack(int n, const char* file, int line, const char* func)
{
  int tty;
  
  if (stack_will_overflow((intptr_t)n) == 0)
    return;
  
  tty = isatty(STDERR_FILENO);
  fprintf(stderr,
	  _("%(\033[00;01m%)%s%(\033[00m%): "
	    "%(\033[31m%)%s%(\033[00m%) "
	    "at line %(\033[33m%)%i%(\033[00m%) "
	    "of file %(\033[35m%)%s%(\033[00m%)"
	    "%(, function %(\033[1;34m%)%s%(\033[00m%)%)"
	    "%(: %(\033[31m%)hinted stack growth: %i bytes%(\033[00m%)%)\n"),
	  tty, program_invocation_name, tty,
	  tty, (n ? _("imminent stack overflow detected") : _("stack overflow detected")), tty,
	  tty, line, tty,
	  tty, file, tty,
	  func != NULL, tty, func, tty,
	  n != 0, tty, n, tty);
  
  fflush(NULL); /* Flush all streams. */
  abort();
}

