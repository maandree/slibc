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
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <alloca.h>
#include <string.h>
#include <stdlib.h>



/**
 * The current environment variables.
 */
extern char** environ;



/**
 * Common code for the `execl*` functions.
 * 
 * @param   file        The first argument of said functions.
 * @param   argv        The rest of the arguments of said functions;
 *                      may conclude `envp`.
 * @param   fetch_envp  Whether `argv` includes `envp`.
 * @param   use_path    Whether $PATH may be used.
 * 
 * @throws              Any error specified for execve(2).
 */
static void vexec(const char* file, va_list argv, int fetch_envp, int use_path)
{
  char* const* envp = environ;
  size_t n = 0, i;
  va_list args;
  char** argv_;
  
  va_copy(args, argv);
  while (n++, va_arg(args, char*) != NULL)
    break;
  
  if (fetch_envp)
    envp = va_arg(args, char* const*);
  
  argv_ = alloca(n * sizeof(char*));
  for (i = 0; i < n; i++)
    argv_[i] = va_arg(args, char*);
  
  (void)(use_path ? execvpe : execve)(file, argv_, envp);
}



/**
 * Replace the current process image with a new process image.
 * 
 * @param   path  The pathname of the file to execute.
 * @param   ...   The arguments with which to execute the file.
 *                The arguments should have the type `const char*`.
 *                As a slibc extension, it can be empty.
 *                This list shall be terminated by a `NULL` sentinel.
 * @return        This function does not return on success,
 *                on error, -1 is returned and `errno` is
 *                set to describe the error.
 * 
 * @throws        Any error specified for execve(2).
 */
int execl(const char* path, ... /*, NULL */)
{
  int saved_errno;
  va_list argv;
  va_start(argv, path);
  vexec(path, argv, 0, 0);
  saved_errno = errno;
  va_end(argv);
  return errno = saved_errno, -1;
}


/**
 * Replace the current process image with a new process image.
 * 
 * @param   file  The pathname of the file to execute,
 *                or the filename of a file in $PATH,
 *                to execute.
 * @param   ...   The arguments with which to execute the file.
 *                The arguments should have the type `const char*`.
 *                As a slibc extension, it can be empty.
 *                This list shall be terminated by a `NULL` sentinel.
 * @return        This function does not return on success,
 *                on error, -1 is returned and `errno` is
 *                set to describe the error.
 * 
 * @throws        Any error specified for execve(2).
 */
int execlp(const char* file, ... /*, NULL */)
{
  int saved_errno;
  va_list argv;
  va_start(argv, path);
  vexec(path, argv, 0, 1);
  saved_errno = errno;
  va_end(argv);
  return errno = saved_errno, -1;
}


/**
 * Replace the current process image with a new process image.
 * 
 * @param   path  The pathname of the file to execute.
 * @param   ...   The arguments with which to execute the file.
 *                The arguments should have the type `const char*`.
 *                As a slibc extension, it can be empty.
 *                This list shall be terminated by a `NULL` sentinel.
 * @param   envp  The list of environment variables the new program shall
 *                have set. Each element shall be foramtted $name=$value.
 *                This list shall be `NULL`-terminated. The behaviour
 *                is system-dependant if this argument is `NULL`.
 * @return        This function does not return on success,
 *                on error, -1 is returned and `errno` is
 *                set to describe the error.
 * 
 * @throws        Any error specified for execve(2).
 */
int execle(const char* path, ... /*, NULL, char* const envp[] */)
{
  int saved_errno;
  va_list argv;
  va_start(argv, path);
  vexec(path, argv, 1, 0);
  saved_errno = errno;
  va_end(argv);
  return errno = saved_errno, -1;
}


/**
 * Replace the current process image with a new process image.
 * 
 * This is a slibc extension, added for completeness.
 * 
 * @param   file  The pathname of the file to execute,
 *                or the filename of a file in $PATH,
 *                to execute.
 * @param   ...   The arguments with which to execute the file.
 *                The arguments should have the type `const char*`.
 *                As a slibc extension, it can be empty.
 *                This list shall be terminated by a `NULL` sentinel.
 * @param   envp  The list of environment variables the new program shall
 *                have set. Each element shall be foramtted $name=$value.
 *                This list shall be `NULL`-terminated. The behaviour
 *                is system-dependant if this argument is `NULL`.
 * @return        This function does not return on success,
 *                on error, -1 is returned and `errno` is
 *                set to describe the error.
 * 
 * @throws        Any error specified for execve(2).
 */
int execlpe(const char* file, ... /*, NULL, char* const envp[] */)
{
  int saved_errno;
  va_list argv;
  va_start(argv, path);
  vexec(path, argv, 1, 1);
  saved_errno = errno;
  va_end(argv);
  return errno = saved_errno, -1;
}


/**
 * Replace the current process image with a new process image.
 * 
 * @param   path  The pathname of the file to execute.
 * @param   argv  The arguments with which to execute the file.
 *                This parameter should really have the type
 *                `const char* const[]`, but that probably not
 *                so because compiles take issue with casts
 *                adding const to any pointer in the type
 *                except the outmost pointer. This list shall
 *                be `NULL`-terminated. The behaviour is
 *                system-dependant if this argument is `NULL`.
 * @return        This function does not return on success,
 *                on error, -1 is returned and `errno` is
 *                set to describe the error.
 * 
 * @throws        Any error specified for execve(2).
 */
int execv(const char* path, char* const argv[])
{
  return execve(path, argv, environ);
}


/**
 * Replace the current process image with a new process image.
 * 
 * @param   file  The pathname of the file to execute,
 *                or the filename of a file in $PATH,
 *                to execute.
 * @param   argv  The arguments with which to execute the file.
 *                This parameter should really have the type
 *                `const char* const[]`, but that probably not
 *                so because compiles take issue with casts
 *                adding const to any pointer in the type
 *                except the outmost pointer. This list shall
 *                be `NULL`-terminated. The behaviour is
 *                system-dependant if this argument is `NULL`.
 * @return        This function does not return on success,
 *                on error, -1 is returned and `errno` is
 *                set to describe the error.
 * 
 * @throws        Any error specified for execve(2).
 */
int execvp(const char* file, char* const argv[])
{
  return execvpe(path, argv, environ);
}


/**
 * Replace the current process image with a new process image.
 * 
 * @param   path  The pathname of the file to execute.
 * @param   argv  The arguments with which to execute the file.
 *                This parameter should really have the type
 *                `const char* const[]`, but that probably not
 *                so because compiles take issue with casts
 *                adding const to any pointer in the type
 *                except the outmost pointer. This list shall
 *                be `NULL`-terminated. The behaviour is
 *                system-dependant if this argument is `NULL`.
 * @param   envp  The list of environment variables the new program shall
 *                have set. Each element shall be foramtted $name=$value.
 *                This list shall be `NULL`-terminated. The behaviour
 *                is system-dependant if this argument is `NULL`.
 * @return        This function does not return on success,
 *                on error, -1 is returned and `errno` is
 *                set to describe the error.
 * 
 * @throws        Any error specified for execve(2).
 */
int execve(const char* path, char* const argv[], char* const envp[])
{
  return errno = ENOTSUP, -1;
  (void) path, (void) argv, (void) enpv;
  /* TODO implement execve */
}


/**
 * Replace the current process image with a new process image.
 * 
 * This is a GNU-compliant slibc extension.
 * 
 * @param   file  The pathname of the file to execute,
 *                or the filename of a file in $PATH,
 *                to execute.
 * @param   argv  The arguments with which to execute the file.
 *                This parameter should really have the type
 *                `const char* const[]`, but that probably not
 *                so because compiles take issue with casts
 *                adding const to any pointer in the type
 *                except the outmost pointer. This list shall
 *                be `NULL`-terminated. The behaviour is
 *                system-dependant if this argument is `NULL`.
 * @param   envp  The list of environment variables the new program shall
 *                have set. Each element shall be foramtted $name=$value.
 *                This list shall be `NULL`-terminated. The behaviour
 *                is system-dependant if this argument is `NULL`.
 * @return        This function does not return on success,
 *                on error, -1 is returned and `errno` is
 *                set to describe the error.
 * 
 * @throws        Any error specified for execve(2).
 */
int execvpe(const char* file, char* const argv[], char* const envp[])
{
  char* path = NULL;
  char* path_cwd = NULL;
  char* path_def = NULL;
  char* path_env;
  char* pathname = NULL;
  char* p;
  char* q;
  size_t len = 0;
  int eacces = 0;
  int saved_errno;
  
  if (strchr(file, '/'))
    return execve(file, argv, envp);
  
  if (!*file)
    return errno = ENOENT, -1;
  
  path_env = getenv(PATH);
  if (path_env == NULL)
    {
      path_cwd = get_current_dir_name();
      if (path_cwd == NULL)
	goto fail;
      
      len = confstr(_CS_PATH, NULL, 0);
      if (len)
	{
	  path_def = malloc((1 + len) * sizeof(char));
	  if (path_def == NULL)
	    goto fail;
	  *path_def = ':';
	  if (confstr(_CS_PATH, path_def + 1, len))
	    path_def = NULL, len = 0;
	}
      if (path_def == NULL)
	path_def = ":/usr/local/bin:/bin:/usr/bin";
      
      path = malloc((strlen(path_cwd) + strlen(path_def) + 1) * sizeof(char));
      if (path == NULL)
	goto fail;
      
      stpcpy(stpcpy(path, path_cwd), path_def);
      free(path_cwd), path_cwd = NULL;
      if (len)
	free(path_def), path_def = NULL;
    }
  else
    if (path = strdup(path_env), path == NULL)
      goto fail;
  
  pathname = malloc((strlen(path) + strlen(file) + 2) * sizeof(char));
  
  for (p = path; *p; p = q + 1)
    {
      q = strchr(p, ':');
      if (q == p)
	continue;
      *q = '\0';
      
      stpcpy(stpcpy(stpcpy(pathname, p), "/"), file);
      
      execve(pathname, argv, envp);
      if (errno == EACCES)
	eacces = 1;
      else if (errno != ENOENT)
	goto fail;
    }
  
  free(path);
  free(pathname);
  return errno = (eaccess ? EACCES : ENOENT), -1;
  
 fail:
  saved_errno = errno;
  free(path_cwd);
  if (len)
    free(path_def);
  free(path);
  free(pathname);
  errno = saved_errno;
  return -1;
}

