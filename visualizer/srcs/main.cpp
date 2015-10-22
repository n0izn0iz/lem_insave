#include <SFML/Graphics.hpp>
extern "C" {
#include <lem_in.h>
#include <libft.h>
}
#include <iostream>
#include <vector>

#define FRAME_COUNT 100
#define WIN_SZ 700
#define BORDER (WIN_SZ / 16)
#define SCALE (WIN_SZ / 16)
#define ROOM_SIZE (WIN_SZ / 8)
#define ANT_SIZE (WIN_SZ / 50)
#define window_pos(x) (BORDER + ((x) * SCALE))

struct Move
{
	Move(char **split) : ant_id(ft_atoi(split[0] + 1)), room_name(split[1]) {}
	uint ant_id;
	std::string room_name;
};

struct Scaler
{
	Scaler(t_map *map)
	{
		t_room *room;
		uint max = 0;
		for (uint i = 0; i < map->rooms->size; i++)
		{
			room = (t_room*)array_get(map->rooms, i);
			if (room->coord_x > max)
				max = room->coord_x;
			if (room->coord_y > max)
				max = room->coord_y;
		}
		dscale = WIN_SZ / max / 1.5;
		border = dscale;
	}
	double scale(double x) const
	{
		return (border + (x * dscale));
	}
	double border;
	double dscale;
};

void static draw_tube(t_room *rooma, t_room *roomb, sf::RenderWindow& window, Scaler& scaler)
{
	const uint room_half = ROOM_SIZE / 2;
	sf::Vertex line[] =
	{
	    sf::Vertex(sf::Vector2f(scaler.scale(rooma->coord_x) + room_half, scaler.scale(rooma->coord_y) + room_half)),
	    sf::Vertex(sf::Vector2f(scaler.scale(roomb->coord_x) + room_half, scaler.scale(roomb->coord_y) + room_half))
	};
	window.draw(line, 2, sf::Lines);
}

void static draw_room(t_room *room, sf::RenderWindow& window, sf::Font& font, t_map *map, uint arrived_count, uint last_ant_id, Scaler& scaler)
{
	const uint room_half = ROOM_SIZE / 2;
	(void)font;
	uint xpos, ypos;
	xpos = scaler.scale(room->coord_x);
	ypos = scaler.scale(room->coord_y);
	sf::RectangleShape rectangle(sf::Vector2f(ROOM_SIZE, ROOM_SIZE));
	rectangle.setPosition(xpos, ypos);
	window.draw(rectangle);

	sf::Text text;
	text.setFont(font);
	text.setString(room->name);
	text.setCharacterSize(24);
	text.setColor(sf::Color::Black);
	text.setPosition(scaler.scale(room->coord_x) + 5, scaler.scale(room->coord_y) + room_half);
	window.draw(text);
	text.setPosition(scaler.scale(room->coord_x) + 5, scaler.scale(room->coord_y));
	text.setCharacterSize(12);
	if (room == map->start)
		text.setString("start " + std::string(ft_itoa(map->ant_count - last_ant_id)));
	else if (room == map->end)
		text.setString("end " + std::string(ft_itoa(arrived_count)));
	else
		return;
	window.draw(text);
}

static void draw_tubes(t_map *map, sf::RenderWindow& window, Scaler& scaler)
{
	for (uint j = 0; j < map->rooms->size; j++)
	{
		t_room *room = (t_room*)array_get(map->rooms, j);
		for (uint i = 0; i < room->tubes->size; i++)
		{
			draw_tube(room, (t_room*)array_get(room->tubes, i), window, scaler);
			i++;
		}
	}
}

static t_map *create_map()
{
	t_map *map;
	map = read_map(true);
	return (map);
}

static void create_moves(std::vector<std::vector<Move> >& moves)
{
	char *line;
	char **split;
	char **it;
	std::vector<Move> moveList;
	while (get_next_line(0, &line) > 0)
	{
		split = ft_strsplit(line, ' ');
		if (split)
		{
			it = split;
			while (*it)
			{
				char **osplit;

				osplit = ft_strsplit(*it, '-');
				if (osplit && (ft_ptrarraysize(osplit) == 2))
					moveList.push_back(Move(osplit));
				if (osplit)
					ft_freeptrarray(osplit);
				it++;
			}
			moves.push_back(moveList);
			moveList.clear();
		}
		if (split)
			ft_freeptrarray(split);
		free(line);
	}
}

static uint apply_move_list(std::vector<Move>& move_list, t_map *map, uint& last_ant_id)
{
	uint arrived_offset = 0;
	for (uint i = 0; i < move_list.size(); i++)
	{
		Move& move = move_list[i];
		t_room *room_a;
		if (move.ant_id > last_ant_id)
		{
			room_a = map->start;
			last_ant_id++;
		}
		else
		{
			room_a = get_room_by_ant_id(move.ant_id, map);
		}
		t_room *room_b = get_room_by_name(move.room_name.c_str(), map);
		if (room_b != map->end)
			room_b->ant_id = move.ant_id;
		else
			arrived_offset++;
		if (room_a != map->start)
			room_a->ant_id = NO_ANT;
	}
	return (arrived_offset);
}

static void draw_move(Move& move, uint frame_index, t_map *map, sf::RenderWindow& window, uint last_ant_id, sf::Font& font, Scaler& scaler)
{
	t_room *room_a;
	if (move.ant_id > last_ant_id)
		room_a = map->start;
	else
		room_a = get_room_by_ant_id(move.ant_id, map);
	t_room *room_b = get_room_by_name(move.room_name.c_str(), map);
	const uint room_half = ROOM_SIZE / 2;
	sf::Vector2f original_pos(scaler.scale(room_a->coord_x) + room_half - ANT_SIZE, scaler.scale(room_a->coord_y) + room_half - ANT_SIZE);
	sf::Vector2f dest_pos(scaler.scale(room_b->coord_x) + room_half - ANT_SIZE, scaler.scale(room_b->coord_y) + room_half - ANT_SIZE);
	sf::Vector2f delta_vec = dest_pos - original_pos;
	delta_vec.x *= ((double)frame_index / FRAME_COUNT);
	delta_vec.y *= ((double)frame_index / FRAME_COUNT);
	sf::Vector2f draw_pos = original_pos + delta_vec;
	sf::CircleShape shape(ANT_SIZE);
	shape.setPosition(draw_pos);
	shape.setFillColor(sf::Color::Red);
	window.draw(shape);
	sf::Text text;
	text.setFont(font);
	text.setString(ft_itoa(move.ant_id));
	text.setCharacterSize(16);
	text.setColor(sf::Color::Black);
	text.setPosition(draw_pos.x + 5, draw_pos.y + 5);
	window.draw(text);
}

static void draw_move_list(std::vector<Move>& move_list, uint frame_index, t_map *map, sf::RenderWindow& window, uint last_ant_id, sf::Font& font, Scaler& scaler)
{
	for (uint i = 0; i < move_list.size(); i++)
		draw_move(move_list[i], frame_index, map, window, last_ant_id, font, scaler);
}

static void reset_map(t_map *map)
{
	for (uint i = 0; i < map->rooms->size; i++)
	{
		t_room *room = (t_room*)array_get(map->rooms, i);
		room->ant_id = NO_ANT;
	}
}

int main(void)
{

	uint move_index = 0;
	uint frame_index = 0;
	uint last_ant_id = 0;
	uint arrived_count = 0;
	t_map *map = create_map();
	Scaler scaler(map);
	std::vector<std::vector<Move> > moves;
	create_moves(moves);
	sf::RenderWindow window(sf::VideoMode(WIN_SZ, WIN_SZ), "lem_in Visualizer");
	sf::Font font;

	if (!font.loadFromFile("font.otf"))
		std::cout << "failed to load font!" << std::endl;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        draw_tubes(map, window, scaler);
        for (uint i = 0; i < map->rooms->size; i++)
        	draw_room((t_room*)array_get(map->rooms, i), window, font, map, arrived_count, last_ant_id, scaler);
        draw_move_list(moves[move_index], frame_index, map, window, last_ant_id, font, scaler);
        if (frame_index < FRAME_COUNT)
        	frame_index++;
        else
        {
        	arrived_count += apply_move_list(moves[move_index], map, last_ant_id);
        	move_index++;
        	frame_index = 0;
        	if (move_index >= moves.size())
        	{
        		window.clear(sf::Color::Black);
        		draw_tubes(map, window, scaler);
		        for (uint i = 0; i < map->rooms->size; i++)
		        	draw_room((t_room*)array_get(map->rooms, i), window, font, map, arrived_count, last_ant_id, scaler);
		        window.display();
        		sf::sleep(sf::milliseconds(2000));
        		//
        		arrived_count = 0;
        		last_ant_id = 0;
        		reset_map(map);
        		move_index = 0;
        		//
        		window.clear(sf::Color::Black);
        		draw_tubes(map, window, scaler);
		        for (uint i = 0; i < map->rooms->size; i++)
		        	draw_room((t_room*)array_get(map->rooms, i), window, font, map, arrived_count, last_ant_id, scaler);
		        window.display();
        		sf::sleep(sf::milliseconds(2000));
        	}
        }
        window.display();
        sf::sleep(sf::milliseconds(10));
    }
	return (0);
}