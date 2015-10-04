#include "array.h"

void			array_sort(t_array* array, int (*func)(void*, void*))
{
	unsigned int j;
	unsigned int i;
	unsigned int imin;
	unsigned int n;

	n = array->size;
	j = 0;
	while (j < n - 1)
	{
		imin = j;
		i = j + 1;
		while (i < n)
		{
			if (func(array_get(array, i), array_get(array, imin)))
				imin = i;
			i++;
		}
		if (imin != j)
			array_swap(array, imin, j);
		j++;
	}
}