#ifndef LEM_IN_H
#define LEM_IN_H

#include "array.h"

typedef unsigned int uint;
#define true 1
#define false 0
typedef uint bool;
#define START_COMMAND 1
#define END_COMMAND 2
#define UNDEFINED -42

typedef struct	s_room
{
	char		*name;
	uint		coord_x;
	uint		coord_y;
	t_array*	tubes;
	bool		has_ant;
}				t_room;

typedef struct	s_map
{
	t_array* rooms;
	t_room*	start;
	t_room* end;
	uint ant_count;
}				t_map;

t_room* construct_room(const char *name, uint coord_x, uint coord_y);
void	link_rooms(t_room* a, t_room* b);
t_map*	construct_map();
t_map*	read_map();

t_array* find_paths(t_map* map);
void	sort_paths(t_array* paths);
void print_path(t_array* path);


int		get_next_line(int const fd, char **line);

#endif