#include "lem_in.h"
#include <libft.h>
#include <stdlib.h>

static bool find_room_in_path(t_room *room, t_array *path)
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

void print_path(t_array* path)
{
	uint i;

	i = 0;
	while (i < path->size)
	{
		t_room* room = array_get(path, i);
		if (i != 0)
			ft_putstr("->");
		ft_putstr(room->name);
		i++;
	}
	ft_putstr(" len=");
	ft_putnbr(path->size);
}

void recur_paths(t_map* map, t_array* paths, t_room* curr_room, t_array* curr_path, int level)
{
	uint i;
	t_array* path_to_use;
	t_room* other_room;

	if (level > 50)
	{
		ft_putendl("Level overflow");
		exit(-1);
	}

	if (find_room_in_path(curr_room, curr_path))
		return;

	array_append(curr_path, curr_room);

	ft_putstr("Level: ");
	ft_putnbr(level);
	ft_putstr(", CurrPath: ");
	print_path(curr_path);
	ft_putchar('\n');

	if (curr_room == map->end)
	{
		ft_putstr("Found path: ");
		print_path(curr_path);
		ft_putchar('\n');
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

t_array* find_paths(t_map* map)
{
	t_array* paths;
	t_array* curr_path;

	paths = array_create(5);
	curr_path = array_create(5);
	recur_paths(map, paths, map->start, curr_path, 0);
	return (paths);
}

#include <stdio.h>

void	sort_paths(t_array* paths)
{
	uint j;
	uint i;
	uint imin;
	uint n;
	t_array* path;
	t_array* min_path;

	n = paths->size;
	j = 0;
	while (j < n - 1)
	{
		imin = j;
		path = array_get(paths, j);
		i = j + 1;
		while (i < n)
		{
			path = array_get(paths, i);
			min_path = array_get(paths, imin);
			if (path->size <= min_path->size)
				imin = i;
			i++;
		}
		if (imin != j)
			array_swap(paths, imin, j);
		j++;
	}
}