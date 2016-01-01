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
#include <fcntl.h>
#include <stdio.h>
#include <termios.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <slibc-alloca.h>


#define t(...)  do { if (__VA_ARGS__) goto fail; } while (0)



/**
 * This function performs the actual password-reading
 * part of `getpass`. It will read into a statically
 * allocated buffer until that buffer is full (8196 bytes,
 * including termination), and switch to a dynamically
 * allocated buffer when the it [the statically allocated
 * buffer] is full.
 * 
 * @prarm   fd  File descriptor to the, already configured,
 *              controlling terminal.
 * @return      The entered line. You should override it with zeroes as
 *              soon as possible to avoid leaving cleartest passphrases
 *              visible in memory, or potentially stored to unencrypted
 *              swap. The returned string is statically allocated, and
 *              should not be deallocated, if the length of the string,
 *              is (strictly) less than 8196, otherwise it is dynamically
 *              allocated, and should be deallocated.
 * 
 * @throws  Any error specified for malloc(3).
 * @throws  Any error specified for read(3).
 */
static char* _getpass(int fd)
{
  static char pass_s[8196];
  char* pass_d = NULL;
  size_t ptr_s = 0, ptr_d = 8196, size_d = (8196 << 1);
  ssize_t got = 1;
  void* new;
  
  /* Read into statically allocated buffer until it is full. */
  while (ptr_s < sizeof(pass_s) / sizeof(char))
    {
      /* Read. */
      t (got = read(fd, pass_s + ptr_s, sizeof(pass_s) - ptr_s * sizeof(char)), got < 0);
      ptr_s += (size_t)got;
      /* End of line? */
      if ((got == 0) || (pass_s[ptr_s - 1] == '\n'))
	{
	  pass_s[ptr_s - !!got] = '\0';
	  return pass_s;
	}
    }
  
  /* Transfer input to dynamically allocated buffer. */
  t (pass_d = secure_realloc(pass_d, size_d * sizeof(char)), pass_d == NULL);
  memcpy(pass_d, pass_s, sizeof(pass_s)), explicit_bzero(pass_s, sizeof(pass_s));
  
  /* Read into dynamically allocated buffer. */
  for (;;)
    {
      /* Do we need to grow the buffer? */
      if (ptr_d + 1 == size_d)
	{
	  t (new = secure_realloc(pass_d, (size_d <<= 1) * sizeof(char)), new == NULL);
	  pass_d = new;
	}
      /* Read. */
      t (got = read(fd, pass_d + ptr_d, (size_d - ptr_d - 1) * sizeof(char)), got < 0);
      ptr_d += (size_t)got;
      /* End of line? */
      if ((got == 0) || (pass_d[ptr_d - 1] == '\n'))
	{
	  pass_d[ptr_d - !!got] = '\0';
	  return pass_d;
	}
    }
  
 fail:
  saved_errno = errno;
  explicit_bzero(pass_s, sizeof(pass_s));
  secure_free(pass_d);
  errno = saved_errno;
  return NULL;
}


/**
 * Get password input from the terminal.
 * 
 * The exact behaviour of this function depends on the implementations.
 * However you can assume that, the controlling terminal (/dev/tty) is
 * opened and used for input and output, and that echoing is disabled.
 * You cannot assume that arbitrary lengths are supported. However, in
 * this implementation, line editing is enabled and arbitrary lengths
 * are supported. If the length of the input (excluding termination) is
 * less than 8192 a statically allocated string is returned, otherwise
 * a dynamically allocated string is returned.
 * 
 * @etymology  (Get) (pass)word from terminal!
 * 
 * @param   prompt  Text to print at the beginning of the line.
 *                  Used to tell the user what is expected of her.
 *                  Must not be `NULL`.
 * @return          The entered line. You should override it with zeroes as
 *                  soon as possible to avoid leaving cleartest passphrases
 *                  visible in memory, or potentially stored to unencrypted
 *                  swap. The returned string is statically allocated, do
 *                  not deallocate it, unless you know that you are using
 *                  slibc and the length of the string is at least 8192.
 *                  `NULL` on error. If a statically allocated string is
 *                  returned, it will be overwritten at the next call.
 * 
 * @throws  Any error specified for open(3).
 * @throws  Any error specified for malloc(3).
 * @throws  Any error specified for read(3).
 * @throws  Any error specified for tcgetattr(3).
 * @throws  Any error specified for tcsetattr(3).
 * @throws  Any error specified for tcdrain(3).
 * 
 * @since  Always.
 */
char* getpass(const char* prompt)
{
  struct termios saved_stty, stty;
  char* pass;
  int fd = -1, stty_saved = 0, saved_errno;
  
  /* Open controlling terminal. */
  t (fd = open("/dev/tty", O_RDWR | O_NOCTTY | O_CLOEXEC), fd < 0);
  
  /* Configure terminal settings. */
  t (tcgetattr(fd, &stty));
  saved_stty = stty;
  stty_saved = 1;
  stty.c_lflag = (stty.c_lflag & (tcflag_t)~(ECHO  | ISIG )) | (tcflag_t)ICANON;
  stty.c_iflag = (stty.c_iflag & (tcflag_t)~(INLCR | IGNCR)) | (tcflag_t)ICRNL;
  t (tcsetattr(fd, TCSAFLUSH, &stty));
  t (tcdrain(fd));
  
  /* Prompt the user. */
  (void) dprintf(fd, "%s", prompt);
  
  /* Get password. */
  pass = _getpass(fd);
  if (pass == NULL)
    goto fail;
  
  /* Move cursor to next line. */
  (void) dprintf(fd, "\n");
  
  /* Restore terminal settings. */
  (void) tcsetattr(fd, TCSAFLUSH, &saved_stty);
  (void) tcdrain(fd);
  
  /* Close controlling terminal. */
  close(fd);
  
  return pass;
  
 fail:
  saved_errno = errno;
  if (fd >= 0)
    close(fd);
  if (stty_saved)
    {
      tcsetattr(fd, TCSAFLUSH, &saved_stty);
      tcdrain(fd);
    }
  errno = saved_errno;
  return NULL;
}

