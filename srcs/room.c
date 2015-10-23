#include "lem_in.h"

#include <stdlib.h>
#include <libft.h>

t_room	*construct_room(const char *name, uint coord_x, uint coord_y)
{
	t_room *new_room;

	new_room = malloc(sizeof(t_room));
	new_room->name = ft_strdup(name);
	new_room->coord_x = coord_x;
	new_room->coord_y = coord_y;
	new_room->tubes = array_create(5);
	new_room->ant_id = 0;
	return (new_room);
}

void	link_rooms(t_room *a, t_room *b)
{
	array_append(a->tubes, b);
	array_append(b->tubes, a);
}
