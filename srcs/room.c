#include "lem_in.h"

#include <stdlib.h>
#include <libft.h>

t_room* construct_room(const char *name, uint coord_x, uint coord_y)
{
	t_room* newRoom;
	newRoom = malloc(sizeof(t_room));
	newRoom->name = ft_strdup(name);
	newRoom->coord_x = coord_x;
	newRoom->coord_y = coord_y;
	newRoom->tubes = array_create(5);
	newRoom->ant_id = 0;
	return (newRoom);
}

void link_rooms(t_room* a, t_room* b)
{
	array_append(a->tubes, b);
	array_append(b->tubes, a);
}