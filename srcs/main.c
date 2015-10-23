#include "lem_in.h"

#include <libft.h>

int	main(void)
{
	t_map	*map;
	t_array	*paths;
	t_array	*combs;
	t_array	*best_comb;

	map = read_map(false);
	ft_putchar('\n');
	paths = find_paths(map);
	sort_paths(paths);
	combs = find_path_combs(paths);
	sort_combs(combs);
	best_comb = array_get(combs, 0);
	move_ants(map, best_comb);
}
