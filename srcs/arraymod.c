/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeier <nmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 14:03:33 by nmeier            #+#    #+#             */
/*   Updated: 2015/02/03 14:35:55 by nmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"

#include <stdlib.h>
#include "libft.h"
#include "ft_realloc.h"

static void		ft_assert(int value)
{
	if (!value)
	{
		ft_putendl_fd("assert failed!", 2);
		exit(-1);
	}
}

void			array_append(t_array *array, void *value)
{
	ft_assert(array != NULL);
	if (array->size >= array->cap)
	{
		array->cap *= 2;
		array->data = ft_realloc(array->data, sizeof(void*) * array->size, \
				sizeof(void*) * array->cap);
		ft_assert(array->data != NULL);
	}
	array->data[array->size] = value;
	array->size++;
}

void			array_merge(t_array *dest, t_array *src)
{
	unsigned int	i;

	ft_assert(src != NULL);
	ft_assert(dest != NULL);
	i = 0;
	while (i < src->size)
	{
		array_append(dest, src->data[i]);
		i++;
	}
	array_destroy(src);
}

void			array_swap(t_array *array, unsigned int i1, unsigned int i2)
{
	void *tmptr;

	ft_assert(i1 < array->size);
	ft_assert(i2 < array->size);
	tmptr = array->data[i1];
	array->data[i1] = array->data[i2];
	array->data[i2] = tmptr;
}

void			*array_remove(t_array *array, unsigned int index)
{
	void *tmp;

	ft_assert(array->size > 0);
	tmp = array_get(array, index);
	array->size -= 1;
	array_set(array, index, array_get(array, array->size));
	return (tmp);
}
