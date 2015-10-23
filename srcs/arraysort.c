/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraysort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeier <nmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/22 17:58:52 by nmeier            #+#    #+#             */
/*   Updated: 2015/10/22 17:58:53 by nmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

void			array_sort(t_array *array, int (*func)(void*, void*))
{
	unsigned int j;
	unsigned int i;
	unsigned int imin;
	unsigned int n;

	n = array->size;
	if (n < 2)
		return ;
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

t_array			*array_dup(t_array *array)
{
	t_array *dup;

	dup = array_create(array->cap);
	dup->size = array->size;
	ft_memcpy(dup->data, array->data, sizeof(void*) * array->size);
	return (dup);
}
