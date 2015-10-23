#include "lem_in.h"

#include <libft.h>
#include <stdlib.h>
#include <fcntl.h>

static void	error(void)
{
	ft_putstr_fd("ERROR\n", 2);
	exit(-1);
}

t_map		*construct_map(void)
{
	t_map *new_map;

	new_map = malloc(sizeof(t_map));
	new_map->rooms = array_create(5);
	new_map->ant_count = 16;
	new_map->start = NULL;
	new_map->end = NULL;
	return (new_map);
}

bool		handle_comment(const char *line)
{
	if (line[0] == '#' && line[1] != '#')
		return (true);
	return (false);
}

uint		handle_command(const char *line)
{
	if (line[0] != '#' || line[1] != '#')
		return (false);
	if (ft_strcmp("start", line + 2) == 0)
	{
		ft_putendl("##start");
		return (START_COMMAND);
	}
	if (ft_strcmp("end", line + 2) == 0)
	{
		ft_putendl("##end");
		return (END_COMMAND);
	}
	error();
	return (UNDEFINED);
}

static uint	splitsize(char **split)
{
	uint size;

	size = 0;
	while (*split != NULL)
	{
		size++;
		split++;
	}
	return (size);
}

static void	printroom(t_room *room)
{
	ft_putstr(room->name);
	ft_putstr(" ");
	ft_putnbr(room->coord_x);
	ft_putstr(" ");
	ft_putnbr(room->coord_y);
	ft_putendl("");
}

bool		handle_room(const char *line, uint command, t_map *map)
{
	char	**split;
	char	*name;
	uint	coord_x;
	uint	coord_y;
	t_room	*room;

	split = ft_strsplit(line, ' ');
	if (splitsize(split) != 3)
	{
		if (command != false)
			error();
		return (false);
	}
	name = split[0];
	coord_x = ft_atoi(split[1]);
	coord_y = ft_atoi(split[2]);
	if (get_room_by_name(name, map) != NULL)
		error();
	room = construct_room(name, coord_x, coord_y);
	ft_freeptrarray(split);
	array_append(map->rooms, room);
	if (command == START_COMMAND)
		map->start = room;
	else if (command == END_COMMAND)
		map->end = room;
	printroom(room);
	return (true);
}

t_room		*get_room_by_name(const char *name, t_map *map)
{
	uint	i;
	t_room	*room;

	i = 0;
	while (i < map->rooms->size)
	{
		room = array_get(map->rooms, i);
		if (ft_strcmp(room->name, name) == 0)
			return (room);
		i++;
	}
	return (NULL);
}

t_room		*get_room_by_ant_id(uint id, t_map *map)
{
	uint	i;
	t_room	*room;

	i = 0;
	while (i < map->rooms->size)
	{
		room = array_get(map->rooms, i);
		if (room->ant_id == id)
			return (room);
		i++;
	}
	error();
	return ((t_room*)UNDEFINED);
}

static void	link_rooms_by_name(const char *aname, const char *bname, t_map *m)
{
	t_room *room_a;
	t_room *room_b;

	room_a = get_room_by_name(aname, m);
	room_b = get_room_by_name(bname, m);
	if (!room_a || !room_b)
		error();
	link_rooms(room_a, room_b);
}

bool		handle_tube(const char *line, t_map *map)
{
	char	**split;

	split = ft_strsplit(line, '-');
	if (splitsize(split) != 2)
		return (false);
	link_rooms_by_name(split[0], split[1], map);
	ft_putstr(split[0]);
	ft_putstr("-");
	ft_putendl(split[1]);
	ft_freeptrarray(split);
	return (true);
}

bool		handle_antcount(t_map *map)
{
	char	*line;
	int		ret;

	while ((ret = get_next_line(0, &line)) > 0 && handle_comment(line))
		free(line);
	if (ret <= 0)
		error();
	map->ant_count = ft_atoi(line);
	free(line);
	if (map->ant_count == 0)
		return (false);
	return (true);
}

t_map		*read_map(bool visualizer)
{
	t_map	*map;
	char	*buf;
	uint	command;
	bool	notubes;

	notubes = true;
	map = construct_map();
	if (!handle_antcount(map))
		error();
	ft_putnbr(map->ant_count);
	ft_putchar('\n');
	command = 0;
	while (get_next_line(0, &buf) > 0)
	{
		if (handle_comment(buf))
			continue;
		if (handle_room(buf, command, map))
		{
			command = false;
			continue;
		}
		if ((command = handle_command(buf)))
			continue;
		if (handle_tube(buf, map))
		{
			notubes = false;
			continue;
		}
		if (visualizer)
			return (map);
		error();
	}
	if (map->start == NULL || map->end == NULL || notubes)
		error();
	return (map);
}
