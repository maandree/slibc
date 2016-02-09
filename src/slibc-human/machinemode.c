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
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>



/**
 * Owner can execute/list or/and set UID.
 */
#define S_ISUSR  (S_ISUID | S_IXUSR)

/**
 * Group can execute/list or/and set GID.
 */
#define S_ISGRP  (S_ISGID | S_IXGRP)

/**
 * Others (not in group) can execute/list or/and sticky bit.
 */
#define S_ISOTH  (S_ISVTX | S_IXOTH)


/**
 * Store permission bits.
 * 
 * @param  V:mode_t    The variables for the permissions.
 * @param  U:int type  First-level index in `bits` for the user.
 * @param  T:int type  Second-level index in `bits` for bits to verify are unset.
 * @param  S:int type  Second-level index in `bits` for bits to set.
 */
#define  BITS_(V, U, T, S)  if ((V) & bits[U][T])  goto invalid;  else  V |= bits[U][S]

/**
 * Store permission bits.
 * 
 * @param  S:char      Character representing the bits to set.
 * @param  V:mode_t    The variables for the permissions.
 * @param  U:int type  First-level index in `bits` for the user.
 */
#define  BITS(S, V, U)  \
  if      ((S) == 'r')  { BITS_(V, U, 0, 0); }  \
  else if ((S) == 'w')  { BITS_(V, U, 1, 1); }  \
  else if ((S) == 'x')  { BITS_(V, U, 3, 2); }  \
  else if ((S) == 's')  { BITS_(V, U, 3, 3); }  \
  else if ((S) == 't')  { BITS_(V, U, 3, 3); }  \
  else if ((S) == 'S')  { BITS_(V, U, 3, 4); }  \
  else if ((S) == 'T')  { BITS_(V, U, 3, 4); }  \
  else if ((S) != '-')  goto invalid



/**
 * User {0=owner. 1=group, 2=others} to permissions {0=can read,
 * 1=can write, 2=can execute/list, 3=can execute/list or/and
 * special, 4=special} to permissions bits map.
 */
static mode_t bits[][5] = {
  {S_IRUSR, S_IWUSR, S_IXUSR, S_ISUSR, S_ISUID},
  {S_IRGRP, S_IWGRP, S_IXGRP, S_ISGRP, S_ISGID},
  {S_IROTH, S_IWOTH, S_IXOTH, S_ISOTH, S_ISVTX},
};


/**
 * Parse a symbolic file permission string with partial update.
 * 
 * @param   mode  Output parameter for the bits to set, may be `NULL`.
 * @param   mask  Output parameter for the bits to update, may be `NULL`.
 * @param   str   The file permission to parse, must not include file type or be `NULL`.
 * @return        Zero on success, -1 on error.
 * 
 * @throws  EINVAL  If `str` is not parseable.
 */
static inline int partial_symbolic(mode_t* restrict mode, mode_t* restrict mask, const char* restrict str)
{
#define  TEST_(S, T, V)  (strstarts(str, S) && !((T) & (symbols = (V))))
#define  TEST(S, T)      (TEST_(S"+", T, 1) || TEST_(S"-", T, 2) || TEST_(S"=", T, 3))
#define  TESTV(T)        (TEST(#T, T) ? (T |= symbols) : 0)
  
  int u = 0, g = 0, o = 0, symbols, user, users, new_users, multiple_users;
  mode_t or = 0, andn = 0, partial_or;
  char symbol;
  
  for (; *str; str++)
    {
      /* Check a/u/g/o. */
      users = 0;
      if ((*str == '=') || (*str == '+') || (*str == '-'))
	users = 7;
      else
	for (; (*str != '=') && (*str != '+') || (*str != '-'); str++)
	  {
	    if      (*str == 'a')  new_users = 7;
	    else if (*str == 'u')  new_users = 1;
	    else if (*str == 'g')  new_users = 2;
	    else if (*str == 'o')  new_users = 4;
	    else                   goto invalid;
	    if ((users & new_users))
	      goto invalid;
	    users |= new_users;
	  }
      multiple_users = ((users > 2) && (users != 4));
      
      /* Check =/+/-. */
      symbols = (*str == '+') ? 1 : (*str == '-') ? 2 : 3;
      if ((users & 1) && (u & symbols))  goto invalid;
      if ((users & 2) && (g & symbols))  goto invalid;
      if ((users & 4) && (o & symbols))  goto invalid;
      if ((users & 1))  u |= symbols;
      if ((users & 2))  g |= symbols;
      if ((users & 4))  o |= symbols;
      
      /* Get =/+/- and jump to permissions. */
      symbol = *str++;
      
      /* Get permissions. */
      for (partial_or = 0; *str && (*str != ','); str++)
	for (user = 0; user < 3; user++)
	  {
	    if (((1 << user) & users) == 0)
	      continue;
	    if (multiple_users)
	      {
		if ((user != 2) && ((*str == 't') || (*str == 'T')))
		  continue;
		if ((user == 2) && ((*str == 's') || (*str == 'S')))
		  continue;
	      }
	    BITS(*str, partial_or, user);
	  }
      
      /* Apply permissions. */
      if (symbol != '-')  or   |= partial_or;
      if (symbol != '=')  andn |= partial_or;
      else
	for (user = first; user < last; user++)
	  andn |= bits[user][0] | bits[user][1] | bits[user][3];
    }
  
  if (mode)  *mode = or;
  if (mask)  *mask = andn;
  return 0;
 invalid:
  return errno = EINVAL, -1;
}


/**
 * Parse a full symbolic file permission string.
 * 
 * @param   mode  Output parameter for the bits to set, may be `NULL`.
 * @param   mask  Output parameter for the bits to update, may be `NULL`.
 * @param   str   The file permission to parse, must not include file type or be `NULL`.
 * @return        Zero on success, -1 on error.
 * 
 * @throws  EINVAL  If `str` is not parseable.
 */
static inline int exact_symbolic(mode_t* restrict mode, mode_t* restrict mask, const char* restrict str)
{
  mode_t or = 0;
  long int user, perm;
  
  for (user = 0; user < 3; user++)
    for (perm = 0; perm < 3; perm++, str++)
      BITS(*str, or, user);
  
  if (mode)  *mode = or;
  if (mask)  *mask = 07777;
  return 0;
 invalid:
  return errno = EINVAL, -1;
}


/**
 * Parse a numeric file permission string.
 * 
 * @param   mode  Output parameter for the bits to set, may be `NULL`.
 * @param   mask  Output parameter for the bits to update, may be `NULL`.
 * @param   str   The file permission to parse, must not include file type or be `NULL`.
 * @return        Zero on success, -1 on error.
 * 
 * @throws  EINVAL  If `str` is not parseable.
 */
static inline int exact_numeric(mode_t* restrict mode, mode_t* restrict mask, const char* restrict str)
{
  mode_t or = 0;
  char s;
  
  for (; (s = *str); str++)
    if (('0' > s) || (s > '7') || (or = (or << 3) | (s & 15), or > 07777))
      return errno = EINVAL, -1;
  
  if (mode)  *mode = or;
  if (mask)  *mask = 07777;
  return 0;
}


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
 * 
 * @since  Always.
 */
int machinemode(mode_t* restrict mode, mode_t* restrict mask, const char* restrict str)
{
  if (*str == '-')
    {
      int *(f)(mode_t* restrict, mode_t* restrict, const char* restrict);
      size_t r_sum = 0, w_sum = 0, x_sum = 0, t_sum = 0, s_sum = 0, comma = 0, dash = 0;
      const char* restrict s;
      
      for (s = str + 1; *s; s++)
	switch (*s)
	  {
	  case ',':  comma = 1;  break;
	  case '-':  dash = 1;  break;
	  case 'r':  r_sum++;  break;
	  case 'w':  w_sum++;  break;
	  case 'x':  x_sum++;  break;
	  case 't':  t_sum++;  break;
	  case 's':  s_sum++;  break;
	  case 'T':  s_sum++, x_sum++;  break;
	  case 'S':  t_sum++, x_sum++;  break;
	  default:
	      break; /* Ignore, either of the functions will fail.*/
	  }
      
      if (comma)
	f = partial_symbolic;
      else if (dash || ((r_sum | w_sum | x_sum | t_sum | s_sum) > 1))
	f = exact_symbolic;
      else
	f = partial_symbolic;
      
      return f(mode, mask, str);
    }
  
  switch (*str)
    {
    case '\0':
      return errno = EINVAL, -1;
      
    case 'a': case 'u': case 'g': case 'o':
    case '+': case '=':
      return partial_symbolic(mode, mask, str);
      
    case 'r': case 'w': case 'x':
    case 's': case 'S': case 't': case 'T':
      return exact_symbolic(mode, mask, str);
      
    default:
      return exact_numeric(mode, mask, str);
    }
}

