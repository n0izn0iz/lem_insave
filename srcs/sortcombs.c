#include "lem_in.h"

static uint	get_distance(t_array *comb)
{
	t_array	*path;
	uint	i;
	uint	distance;

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

static int	sort_func(void *a, void *b)
{
	t_array *acomb;
	t_array *bcomb;

	acomb = a;
	bcomb = b;
	if (acomb->size == bcomb->size)
		return (get_distance(a) < get_distance(b) ? true : false);
	return (acomb->size > bcomb->size ? true : false);
}

void		sort_combs(t_array *combs)
{
	array_sort(combs, sort_func);
}
