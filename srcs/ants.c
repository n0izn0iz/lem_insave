/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmeier <nmeier@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/22 18:00:22 by nmeier            #+#    #+#             */
/*   Updated: 2015/10/22 18:00:24 by nmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>

static uint	push_ant(uint *ants_at_start, t_map *map)
{
	(*ants_at_start)--;
	return (map->ant_count - (*ants_at_start));
}

static void	pop_ant(uint *ants_at_end)
{
	(*ants_at_end) += 1;
}

static void	print_move(t_room *room, uint ant_id)
{
	ft_putstr("L");
	ft_putnbr(ant_id);
	ft_putchar('-');
	ft_putstr(room->name);
	ft_putchar(' ');
}

static void	try_move_ant(t_room *a, t_room *b, t_map *map, uint *ant_counters)
{
	if ((a->ant_id == NO_ANT && a != map->start) \
		|| (b->ant_id != NO_ANT && b != map->end))
		return ;
	if (a == map->start)
	{
		if (ant_counters[0] == 0)
			return ;
		b->ant_id = push_ant(ant_counters, map);
		print_move(b, b->ant_id);
	}
	else if (b == map->end)
	{
		pop_ant(ant_counters + 1);
		print_move(b, a->ant_id);
		a->ant_id = NO_ANT;
	}
	else
	{
		b->ant_id = a->ant_id;
		a->ant_id = NO_ANT;
		print_move(b, b->ant_id);
	}
}

void		move_ants(t_map *map, t_array *comb)
{
	uint	ant_counters[2];
	uint	i;
	int		j;
	t_array	*path;

	ant_counters[0] = 0;
	ant_counters[1] = map->ant_count;
	while (ant_counters[1] < map->ant_count)
	{
		i = 0;
		while (i < comb->size)
		{
			path = array_get(comb, i);
			j = path->size - 2 + 1;
			while (--j >= 0)
				try_move_ant(array_get(path, j), array_get(path, j + 1), \
					map, ant_counters);
			i++;
		}
		ft_putchar('\n');
	}
}
