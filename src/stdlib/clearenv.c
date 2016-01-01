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
#include <stdlib.h>



/**
 * The process's environment variables.
 */
extern char** environ;



/**
 * This function shall in some manner clear the environment.
 * 
 * To minimise the risk of fatal race conditions, this
 * implementation will set the first element in
 * `extern char** environ` to `NULL`, unless `environ`
 * itself is `NULL`. This also reduces that risk that
 * programs stop working when switching to slibc.
 * 
 * The exact behaviour of this function depeneds of the
 * implementations. Depending on the implementation,
 * this may or may not entail setting `environ` to `NULL`.
 * 
 * This function is a very common non-standard extension.
 * 
 * @etymology  (Clear) the (env)ironment!
 * 
 * @returns  This function is always successful, and will
 *           always return zero. However, according to the
 *           specifications, it shall return -1 on failure.
 * 
 * @since  Always.
 */
int clearenv(void)
{
  if (environ != NULL)
    *environ = NULL;
  return 0;
}

