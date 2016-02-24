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


# pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"



/**
 * Search for an item in a sorted list of comparable
 * elements. The list must be sorted in ascending order.
 * The function usually implements binary search,
 * as is done in this implementation.
 * 
 * @etymology  (B)inary (search).
 * 
 * @param   sought  The sought item.
 * @param   list    The beginning of the list to search.
 * @param   n       The number of elements in the list.
 * @param   width   The width, in bytes, of each element in the list.
 * @param   compar  A function that shall compare two items, and return
 *                  a value less than, equal to, or greater than zero
 *                  if the first argument is less than, equal to, or
 *                  greater than the second argument, respectively.
 * @return          The address of an arbritrart element in `list` that
 *                  is equal to `sought`, or `NULL` if no such element
 *                  can be found (does not exist, or because `list`
 *                  is not properly sorted.)
 * 
 * @since  Always.
 */
void* (bsearch)(const void* sought, const void* list, size_t n, size_t width,
		int (*compar)(const void*, const void*))
{
  int cmp;
  size_t i;
  char* test;
  if (n == 0)
    return NULL;
  for (;;)
    {
      i = n >> 1;
      test = (char*)list + i * width;
      cmp = compar(sought, test);
      if (!i)
	return cmp ? NULL : test;
      else if (cmp < 0)
	n = i;
      else if (cmp > 0)
	n -= i, list = test;
      else
	return test;
    }
}

