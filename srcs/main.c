#include "lem_in.h"

#include <libft.h>
#include <stdlib.h>

static void print_combs(t_array *combs)
{
	uint i;
	uint j;
	t_array *comb;
	t_array *path;

	i = 0;
	while (i < combs->size)
	{
		ft_putendl("COMB:");
		comb = array_get(combs, i);
		j = 0;
		while (j < comb->size)
		{
			path = array_get(comb, j);
			print_path(path);
			ft_putchar('\n');
			j++;
		}
		i++;
	}
}

static void print_paths(t_array *paths)
{
	ft_putendl("PATHS:");
	uint i;
	i = 0;
	while (i < paths->size)
	{
		t_array* path = array_get(paths, i);
		print_path(path);
		ft_putchar('\n');
		i++;
	}
}

int main()
{
	t_map* map;
	t_array* paths;
	t_array* combs;
	t_array *best_comb;
	
	map = read_map();
	ft_putchar('\n');
	paths = find_paths(map);
	sort_paths(paths);
	(void)print_paths;
	//print_paths(paths);
	combs = find_path_combs(paths);
	sort_combs(combs);
	(void)print_combs;
	//print_combs(combs);
	best_comb = array_get(combs, 0);
	move_ants(map, best_comb);
}