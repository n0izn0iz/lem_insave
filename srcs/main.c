#include "lem_in.h"

#include <libft.h>
#include <stdlib.h>

int main()
{
	t_map* map;
	t_array* paths;
	uint i;

	map = read_map();
	paths = find_paths(map);
	sort_paths(paths);
	i = 0;
	while (i < paths->size)
	{
		t_array* path = array_get(paths, i);
		print_path(path);
		ft_putchar('\n');
		i++;
	}
}