/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeier <nmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/23 13:22:39 by nmeier            #+#    #+#             */
/*   Updated: 2015/10/23 13:22:40 by nmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static bool	path_conflict(t_array *a, t_array *b)
{
	uint	i;
	uint	j;
	t_room	*iroom;
	t_room	*jroom;

	i = 1;
	while (i < a->size - 1)
	{
		iroom = array_get(a, i);
		j = 1;
		while (j < b->size - 1)
		{
			jroom = array_get(b, j);
			if (iroom == jroom)
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

static bool	find_conflicts(t_array *icomb, t_array *jpath)
{
	t_array	*kpath;
	uint	k;

	k = 0;
	while (k < icomb->size)
	{
		kpath = array_get(icomb, k);
		if (path_conflict(jpath, kpath))
			return (true);
		k++;
	}
	return (false);
}

t_array		*find_path_combs(t_array *paths)
{
	t_array		*combs;
	t_array		*icomb;
	uint		i;
	long long	j;

	combs = array_create(5);
	i = 0;
	while (i < paths->size)
	{
		icomb = array_create(5);
		array_append(icomb, array_get(paths, i));
		j = -1;
		while (++j < paths->size)
		{
			if (i == j)
				continue;
			if (!find_conflicts(icomb, array_get(paths, j)))
				array_append(icomb, array_get(paths, j));
		}
		sort_paths(icomb);
		if (icomb->size > 0)
			array_append(combs, icomb);
		i++;
	}
	return (combs);
}
