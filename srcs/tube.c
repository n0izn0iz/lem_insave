#include "lem_in.h"

#include <stdlib.h>

t_tube*	construct_tube(t_room* a, t_room* b)
{
	t_tube* newTube;

	newTube = malloc(sizeof(t_tube));
	newTube->a = a;
	newTube->b = b;
	return (newTube);
}

t_tube* link_rooms(t_room* a, t_room* b)
{
	t_tube* newTube;

	newTube = construct_tube(a, b);
	array_append(a->tubes, newTube);
	array_append(b->tubes, newTube);
	return (newTube);
}