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



int main(void)
{
  printf("CHAR_BIT %zu\n",      8 * sizeof(char));
  printf("SHORT_BIT %zu\n",     8 * sizeof(short int));
  printf("INT_BIT %zu\n",       8 * sizeof(int));
  printf("LONG_BIT %zu\n",      8 * sizeof(long int));
  printf("LONG_LONG_BIT %zu\n", 8 * sizeof(long long int));
  printf("PTR_BIT %zu\n",       8 * sizeof(void*));
  
  printf("INT%zu %s\n", 8 * sizeof(char), "char");
  printf("INT%zu %s\n", 8 * sizeof(short int), "short int");
  printf("INT%zu %s\n", 8 * sizeof(int), "int");
  printf("INT%zu %s\n", 8 * sizeof(long int), "long int");
  printf("INT%zu %s\n", 8 * sizeof(long long int), "long long int");
  
  return 0;
}

