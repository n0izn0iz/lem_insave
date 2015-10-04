#include "lem_in.h"

static bool path_conflict(t_array *a, t_array *b)
{
	uint i;
	uint j;
	t_room *iroom;
	t_room *jroom;

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

t_array	*find_path_combs(t_array *paths)
{
	t_array *combs;
	t_array *ipath;
	t_array *jpath;
	t_array *kpath;
	t_array *icomb;
	uint i;
	uint j;
	uint k;
	uint n;
	bool conflict;

	n = paths->size;
	combs = array_create(5);
	i = 0;
	while (i < n)
	{
		ipath = array_get(paths, i);
		icomb = array_create(5);
		array_append(icomb, ipath);
		j = 0;
		while (j < n)
		{
			if (i == j)
			{
				j++;
				continue;
			}
			jpath = array_get(paths, j);
			conflict = false;
			k = 0;
			while (k < icomb->size)
			{
				kpath = array_get(icomb, k);
				if (path_conflict(jpath, kpath))
				{
					conflict = true;
					break;
				}
				k++;
			}
			if (!conflict)
				array_append(icomb, jpath);
			j++;
		}
		sort_paths(icomb);
		if (icomb->size > 0)
			array_append(combs, icomb);
		i++;
	}
	return (combs);	
}

static uint get_distance(t_array *comb)
{
	t_array *path;
	uint i;
	uint distance;

	i = 0;
	distance = 0;
	while (i < comb->size)
	{
		path = array_get(comb, i);
		distance += path->size;
		i++;
	}
	return (distance);
}

static int sort_func(void* a, void* b)
{
	t_array *acomb;
	t_array *bcomb;

	acomb = a;
	bcomb = b;
	if (acomb->size == bcomb->size)
		return (get_distance(a) < get_distance(b) ? true : false);
	return (acomb->size > bcomb->size ? true : false);
}

void	sort_combs(t_array *combs)
{
	array_sort(combs, sort_func);
}