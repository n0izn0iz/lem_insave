#include "lem_in.h"

#include <libft.h>
#include <stdlib.h>
#include <fcntl.h>

static void error()
{
	ft_putstr_fd("ERROR\n", 2);
	exit(-1);
}

t_map*	construct_map()
{
	t_map* newMap;

	newMap = malloc(sizeof(t_map));
	newMap->rooms = array_create(5);
	newMap->ant_count = 3;
	newMap->start = NULL;
	newMap->end = NULL;
	return (newMap);
}

// untested, debug stuff
bool handle_comment(const char* line)
{
	if (line[0] == '#' && line[1] !=  '#')
	{
		/*ft_putstr("Comment: ");
		ft_putendl(line + 1);*/
		return (true);
	}
	return (false);
}

// untested, debug stuff
uint handle_command(const char* line)
{
	if (line[0] != '#' || line[1] !=  '#')
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

// untested
static uint splitsize(char** split)
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

// debug
static void printroom(t_room* room)
{
	//ft_putstr("Room: \"");
	ft_putstr(room->name);
	ft_putstr(" ");
	ft_putnbr(room->coord_x);
	ft_putstr(" ");
	ft_putnbr(room->coord_y);
	ft_putendl("");
}

// untested, debug stuff, memleak
bool handle_room(const char* line, uint command, t_map* map)
{
	char	**split;
	char	*name;
	uint	coord_x;
	uint	coord_y;

	split = ft_strsplit(line, ' ');
	if (splitsize(split) < 3)
	{
		if (command != false)
			error();
		return (false);
	}
	name = split[0];
	coord_x = ft_atoi(split[1]);
	coord_y = ft_atoi(split[2]);
	t_room* room = construct_room(name, coord_x, coord_y);
	array_append(map->rooms, room);
	if (command == START_COMMAND)
		map->start = room;
	else if (command == END_COMMAND)
		map->end = room;
	printroom(room);
	return (true);
}

// untested
t_room*	get_room_by_name(const char* name, t_map* map)
{
	uint i;

	i = 0;
	while (i < map->rooms->size)
	{
		t_room* room = array_get(map->rooms, i);
		if (ft_strcmp(room->name, name) == 0)
			return (room);
		i++;
	}
	error();
	return ((t_room*)UNDEFINED);
}

t_room*	get_room_by_ant_id(uint id, t_map* map)
{
	uint i;

	i = 0;
	while (i < map->rooms->size)
	{
		t_room* room = array_get(map->rooms, i);
		if (room->ant_id == id)
			return (room);
		i++;
	}
	error();
	return ((t_room*)UNDEFINED);
}

// untested
static void link_rooms_by_name(const char* a_name, const char* b_name, t_map* map)
{
	t_room* room_a;
	t_room* room_b;

	room_a = get_room_by_name(a_name, map);
	room_b = get_room_by_name(b_name, map);
	link_rooms(room_a, room_b);
}

// untested, debug stuff, memleak
bool handle_tube(const char* line, t_map* map)
{
	char	**split;

	split = ft_strsplit(line, '-');
	if (splitsize(split) != 2)
		return (false);
	link_rooms_by_name(split[0], split[1], map);
	//ft_putstr("Tube: ");
	ft_putstr(split[0]);
	ft_putstr("-");
	ft_putendl(split[1]);
	return (true);
}

// untested, debug stuff
t_map*	read_map()
{
	t_map* map;
	char* buf;
	uint command;

	map = construct_map();
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
			continue;
		ft_putstr("Unhandled line: ");
		ft_putendl(buf);
		error();
	}
	return (map);
}