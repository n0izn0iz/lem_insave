/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeier <nmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 14:03:33 by nmeier            #+#    #+#             */
/*   Updated: 2015/02/03 14:36:01 by nmeier           ###   ########.fr       */
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

void			*array_get(t_array *array, unsigned int index)
{
	ft_assert(index < array->size);
	return (array->data[index]);
}

void			array_set(t_array *array, unsigned int index, void *value)
{
	ft_assert(index < array->size);
	array->data[index] = value;
}

t_array			*array_create(unsigned int cap)
{
	t_array *array;

	array = (t_array*)malloc(sizeof(t_array));
	if (array)
	{
		array->size = 0;
		array->cap = cap;
		array->data = malloc(sizeof(void*) * cap);
		if (!array->data)
		{
			free(array);
			array = NULL;
		}
	}
	return (array);
}

void			array_destroy(t_array *array)
{
	if (array != NULL)
	{
		free(array->data);
		free(array);
	}
}

t_array*		array_dup(t_array* array)
{
	t_array* dup;

	dup = array_create(array->cap);
	dup->size = array->size;
	ft_memcpy(dup->data, array->data, sizeof(void*) * array->size);
	return (dup);
}