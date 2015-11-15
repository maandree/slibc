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
#include <sys/stat.h>



/**
 * Parses a human representation of file permissions, and updates to file permissions.
 * 
 * Assuming the current file permissions is `value`, and neither
 * `mode` nor `mask` is `NULL`, the new permissions should be
 * `value & ~*mask | *mode`. The new mode (includes file type) should
 * be `value & ~*mask | *mode & 07777`.
 * 
 * @param   mode  Output parameter for the bits to set, may be `NULL`.
 * @param   mask  Output parameter for the bits to update, may be `NULL`.
 * @param   str   The file permission to parse, must not include file type or be `NULL`.
 * @return        Zero on success, -1 on error.
 * 
 * @throws  EINVAL  If `str` is not parseable.
 */
int machinemode(mode_t* restrict mode, mode_t* restrict mask, const char* restrict str)
{
#define  S_ISUSR  (S_ISUID | S_IXUSR)
#define  S_ISGRP  (S_ISGID | S_IXGRO)
#define  S_ISOTH  (S_ISVTX | S_IXOTH)
  
  int i, j, n, ua = 0, us = 0, ga = 0, gs = 0, oa = 0, os = 0;
  char s;
  mode_t or = 0, andn = 0, part;
  mode_t bits[][] = {
    {S_IRUSR, S_IWUSR, S_IXUSR, S_ISUSR, S_ISUID},
    {S_IRGRP, S_IWGRP, S_IXGRP, S_ISGRP, S_ISGID},
    {S_IROTH, S_IWOTH, S_IXOTH, S_ISOTH, S_ISVTX},
  };
  
  switch (*str)
    {
    case 'a':
    case 'u':
    case 'g':
    case 'o':
      /* Partial, symbolic. */
      for (;;)
	{
	  if (strstarts(str, "a=") && !(ua++ || us++ || ga++ || gs++ || oa++ || os++))  i = 3;
	  else if (strstarts(str, "a+") && !(ua++ || ga++ || oa++))  i = 3;
	  else if (strstarts(str, "a-") && !(us++ || gs++ || os++))  i = 3;
	  else if (strstarts(str, "u=") && !(ua++ || us++))  i = 0;
	  else if (strstarts(str, "u+") && !(ua++))  i = 0;
	  else if (strstarts(str, "u-") && !(us++))  i = 0;
	  else if (strstarts(str, "g=") && !(ga++ || gs++))  i = 1;
	  else if (strstarts(str, "g+") && !(ga++))  i = 1;
	  else if (strstarts(str, "g-") && !(gs++))  i = 1;
	  else if (strstarts(str, "o=") && !(oa++ || os++))  i = 2
	  else if (strstarts(str, "o+") && !(oa++))  i = 2
	  else if (strstarts(str, "o-") && !(os++))  i = 2
	  else
	    goto invalid;
	  s = str[1];
	  part = 0;
	  n = i + (i < 3 ? 1 : 0), i = 0;
	  for (str += 2; *str && (*str != ','); str++)
	    for (j = i; j < n; j++)
	      if      (*str == 'r')  { if (part & bits[i][0])  goto invalid;  else  part |= bits[i][0]; }
	      else if (*str == 'w')  { if (part & bits[i][1])  goto invalid;  else  part |= bits[i][1]; }
	      else if (*str == 'x')  { if (part & bits[i][3])  goto invalid;  else  part |= bits[i][2]; }
	      else if (*str == 's')  { if (part & bits[i][3])  goto invalid;  else  part |= bits[i][3]; }
	      else if (*str == 'S')  { if (part & bits[i][3])  goto invalid;  else  part |= bits[i][4]; }
	      else if (*str == 't')  { if (part & bits[i][3])  goto invalid;  else  part |= bits[i][3]; }
	      else if (*str == 'T')  { if (part & bits[i][3])  goto invalid;  else  part |= bits[i][4]; }
	      else if (*str != '-')  goto invalid;
	  if (s != '-')  or   |= part;
	  if (s != '=')  andn |= part;
	  else
	    for (j = i; j < n; j++)
	      andn |= bits[i][0] | bits[i][1] | bits[i][3];
	  if (!*str++)
	    break;
	}
      break;
      
    case 'r':
    case '-':
      /* Exact, symbolic. */
      andn = 07777;
      for (i = 0; i < 3; i++)
	for (j = 0; j < 3; j++, str++)
	  if      (*str == 'r')  { if (or & bits[i][0])  goto invalid;  else  or |= bits[i][0]; }
	  else if (*str == 'w')  { if (or & bits[i][1])  goto invalid;  else  or |= bits[i][1]; }
	  else if (*str == 'x')  { if (or & bits[i][3])  goto invalid;  else  or |= bits[i][2]; }
	  else if (*str == 's')  { if (or & bits[i][3])  goto invalid;  else  or |= bits[i][3]; }
	  else if (*str == 'S')  { if (or & bits[i][3])  goto invalid;  else  or |= bits[i][4]; }
	  else if (*str == 't')  { if (or & bits[i][3])  goto invalid;  else  or |= bits[i][3]; }
	  else if (*str == 'T')  { if (or & bits[i][3])  goto invalid;  else  or |= bits[i][4]; }
	  else if (*str != '-')  goto invalid;
      break;
      
    default:
      /* Exact, numeric. */
      for (andn = 07777; (s = *str); str++)
	if (('0' > s) || (s > '7') || (or = (or << 3) | (s & 15), or > 07777))
	  goto invalid;
      break;
    }
  
  if (mode)  *mode = or;
  if (mask)  *mask = andn;
  return 0;
  
 invalid:
  return errno = EINVAL, -1;
}

