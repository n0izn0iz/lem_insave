#include "lem_in.h"

#include <libft.h>
#include <stdlib.h>

int main()
{
	t_map* map;
	t_array* paths;

	map = read_map();
	paths = find_paths(map);
}