#ifndef LEM_IN_H
#define LEM_IN_H

typedef unsigned int uint;

#ifdef __cplusplus
extern "C" {
#else
 #define true 1
 #define false 0
typedef uint bool;
#endif

#include "array.h"
#define START_COMMAND 1
#define END_COMMAND 2
#define UNDEFINED -42
#define NO_ANT 0

typedef struct	s_room
{
	char		*name;
	uint		coord_x;
	uint		coord_y;
	t_array		*tubes;
	uint		ant_id;
}				t_room;

typedef struct	s_map
{
	t_array* rooms;
	t_room*	start;
	t_room* end;
	uint ant_count;
}				t_map;

// room.c
t_room	*construct_room(const char *name, uint coord_x, uint coord_y);
void	link_rooms(t_room *a, t_room *b);

// map.c
t_map	*construct_map();
t_map	*read_map();
t_room*	get_room_by_name(const char* name, t_map* map);
t_room*	get_room_by_ant_id(uint id, t_map* map);

// paths.c
t_array	*find_paths(t_map *map);
void	sort_paths(t_array *paths);
void	print_path(t_array *path);
bool find_room_in_path(t_room *room, t_array *path);

// combs.c
t_array	*find_path_combs(t_array *paths);
void	sort_combs(t_array *combs);

// ants.c
void move_ants(t_map *map, t_array *comb);

// other
int		get_next_line(int const fd, char **line);
#ifdef __cplusplus
}
#endif
#endif