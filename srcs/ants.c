#include "lem_in.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>

static uint push_ant(uint *ants_at_start, t_map *map)
{
	(*ants_at_start)--;
	return (map->ant_count - (*ants_at_start));
}

static void pop_ant(uint *ants_at_end)
{
	(*ants_at_end) += 1;
}

static uint transit_count(uint ants_at_start, uint ants_at_end, uint ant_count)
{
	return (ant_count - ants_at_start - ants_at_end);
}

static void print_move(t_room *room, uint ant_id)
{
	ft_putstr("L");
	ft_putnbr(ant_id);
	ft_putchar('-');
	ft_putstr(room->name);
	ft_putchar(' ');
}

static void try_move_ant(t_room *a, t_room *b, t_map *map, uint *ants_at_start, uint *ants_at_end)
{
	(void)transit_count;
	if ((a->ant_id == NO_ANT && a != map->start) || (b->ant_id != NO_ANT && b != map->end))
		return;
	if (a == map->start)
	{
		if (*ants_at_start == 0)
			return;
		b->ant_id = push_ant(ants_at_start, map);
		print_move(b, b->ant_id);
	}
	else if (b == map->end)
	{	
		pop_ant(ants_at_end);
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

void move_ants(t_map *map, t_array *comb)
{
	uint ants_at_end;
	uint ants_at_start;
	uint i;
	int j;
	t_array *path;
	t_room *room;
	t_room *next_room;

	(void)comb;
	ants_at_end = 0;
	ants_at_start = map->ant_count;
	while (ants_at_end < map->ant_count)
	{
		i = 0;
		while (i < comb->size)
		{
			path = array_get(comb, i);
			j = path->size - 2;
			while (j >= 0)
			{
				room = array_get(path, j);
				next_room = array_get(path, j + 1);
				try_move_ant(room, next_room, map, &ants_at_start, &ants_at_end);
				j--;
			}
			i++;
		}
		ft_putchar('\n');
	}
}