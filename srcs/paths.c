#include "lem_in.h"
#include <libft.h>
#include <stdlib.h>

bool	find_room_in_path(t_room *room, t_array *path)
{
	uint i;

	i = 0;
	while (i < path->size)
	{
		if (array_get(path, i) == room)
			return (true);
		i++;
	}
	return (false);
}

void	print_path(t_array *path)
{
	uint	i;
	t_room	*room;

	i = 0;
	while (i < path->size)
	{
		room = array_get(path, i);
		if (i != 0)
			ft_putstr("->");
		ft_putstr(room->name);
		i++;
	}
	ft_putstr(" len=");
	ft_putnbr(path->size);
}

void	recur_paths(t_map *map, t_array *paths, t_room *curr_room, t_array *curr_path, int level)
{
	uint	i;
	t_array	*path_to_use;
	t_room	*other_room;

	if (level > 5000)
	{
		ft_putendl("ERROR");
		exit(-1);
	}
	if (find_room_in_path(curr_room, curr_path))
		return;
	array_append(curr_path, curr_room);
	if (curr_room == map->end)
	{
		array_append(paths, curr_path);
		return ;
	}
	i = 0;
	while (i < curr_room->tubes->size)
	{
		path_to_use = array_dup(curr_path);
		other_room = array_get(curr_room->tubes, i);
		recur_paths(map, paths, other_room, path_to_use, level + 1);
		i++;
	}
}

t_array	*find_paths(t_map* map)
{
	t_array *paths;
	t_array *curr_path;

	paths = array_create(5);
	curr_path = array_create(5);
	recur_paths(map, paths, map->start, curr_path, 0);
	if (paths->size == 0)
	{
		ft_putendl_fd("ERROR", 2);
		exit(1);
	}
	return (paths);
}

#include <stdio.h>

static int	comp_func(void* a, void* b)
{
	t_array* c = a;
	t_array* d = b;
	if (c->size < d->size)
		return (true);
	return (false);
}

void		sort_paths(t_array* paths)
{
	array_sort(paths, comp_func);
}
