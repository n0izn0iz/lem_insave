#include "array.h"

typedef unsigned int uint;
#define true 1
#define false 0
typedef uint bool;
#define START_COMMAND 1
#define END_COMMAND 2
#define UNDEFINED -42

struct s_room;

typedef struct	s_tube
{
	struct s_room	*a;
	struct s_room	*b;
}				t_tube;

typedef struct	s_room
{
	char		*name;
	uint		coord_x;
	uint		coord_y;
	t_array*	tubes;
	uint		ant_count;
}				t_room;

typedef struct	s_map
{
	t_array* rooms;
	t_array* tubes;
	uint ant_count;
}				t_map;

t_room* construct_room(const char *name, uint coord_x, uint coord_y, uint ant_count);
t_tube*	construct_tube(t_room* a, t_room* b);
t_tube*	link_rooms(t_room* a, t_room* b);
t_map*	construct_map();
t_map*	read_map();


int		get_next_line(int const fd, char **line);