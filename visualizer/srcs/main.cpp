#include <SFML/Graphics.hpp>
#include <lem_in.h>
#include <libft.h>
#include <iostream>
#include <vector>

#define ROOM_SIZE 80
#define ANT_SIZE 16
#define FRAME_COUNT 100
#define window_pos(x) (50 + ((x) * 50))

void static draw_tube(t_room *rooma, t_room *roomb, sf::RenderWindow& window)
{
	const uint room_half = ROOM_SIZE / 2;
	sf::Vertex line[] =
	{
	    sf::Vertex(sf::Vector2f(window_pos(rooma->coord_x) + room_half, window_pos(rooma->coord_y) + room_half)),
	    sf::Vertex(sf::Vector2f(window_pos(roomb->coord_x) + room_half, window_pos(roomb->coord_y) + room_half))
	};
	window.draw(line, 2, sf::Lines);
}

void static draw_room(t_room *room, sf::RenderWindow& window, sf::Font& font, t_map *map)
{
	const uint room_half = ROOM_SIZE / 2;
	(void)font;
	uint xpos, ypos;
	xpos = window_pos(room->coord_x);
	ypos = window_pos(room->coord_y);
	sf::RectangleShape rectangle(sf::Vector2f(ROOM_SIZE, ROOM_SIZE));
	rectangle.setPosition(xpos, ypos);
	window.draw(rectangle);

	sf::Text text;
	text.setFont(font);
	text.setString(room->name);
	text.setCharacterSize(24);
	text.setColor(sf::Color::Black);
	text.setPosition(window_pos(room->coord_x) + 5, window_pos(room->coord_y) + room_half);
	window.draw(text);
	text.setPosition(window_pos(room->coord_x) + 5, window_pos(room->coord_y));
	text.setCharacterSize(12);
	if (room == map->start)
		text.setString("start");
	else if (room == map->end)
		text.setString("end");
	else
		return;
	window.draw(text);
}

static void draw_tubes(t_map *map, sf::RenderWindow& window)
{
	for (uint j = 0; j < map->rooms->size; j++)
	{
		t_room *room = (t_room*)array_get(map->rooms, j);
		for (uint i = 0; i < room->tubes->size; i++)
		{
			draw_tube(room, (t_room*)array_get(room->tubes, i), window);
			i++;
		}
	}
}

static t_map *create_map()
{
	t_map *map;

	map = construct_map();
	map->start = construct_room("0", 1, 2);
	map->end = construct_room("1", 9, 2);
	array_append(map->rooms, construct_room("2", 5, 0));
	array_append(map->rooms, map->start);
	array_append(map->rooms, map->end);
	array_append(map->rooms, construct_room("3", 5, 4));
	link_rooms(get_room_by_name("0", map), get_room_by_name("2", map));
	link_rooms(get_room_by_name("0", map), get_room_by_name("3", map));
	link_rooms(get_room_by_name("2", map), get_room_by_name("1", map));
	link_rooms(get_room_by_name("3", map), get_room_by_name("1", map));
	link_rooms(get_room_by_name("2", map), get_room_by_name("3", map));
	return (map);
}

struct Move
{
	Move(uint id, const std::string& name) : ant_id(id), room_name(name) {}
	uint ant_id;
	std::string room_name;
};

static void create_moves(std::vector<std::vector<Move> >& moves)
{
	std::vector<Move> moveList;
	moveList.push_back(Move(1, "3"));
	moveList.push_back(Move(2, "2"));
	moves.push_back(moveList);
	moveList.clear();
	moveList.push_back(Move(1, "1"));
	moveList.push_back(Move(2, "1"));
	moveList.push_back(Move(3, "3"));
	moves.push_back(moveList);
	moveList.clear();
	moveList.push_back(Move(3, "1"));
	moves.push_back(moveList);
}

static void apply_move_list(std::vector<Move>& move_list, t_map *map, uint& last_ant_id)
{
	for (uint i = 0; i < move_list.size(); i++)
	{
		Move& move = move_list[i];
		//std::cout << "Applying move: ant#" << move.ant_id << " to room \"" << move.room_name << "\"" << std::endl;
		t_room *room_a;
		if (move.ant_id > last_ant_id)
		{
			room_a = map->start;
			last_ant_id++;
			//std::cout << "Spawning ant#" << ++last_ant_id << std::endl;
		}
		else
		{
			//std::cout << "Trying to find room of ant#" << move.ant_id << std::endl;
			room_a = get_room_by_ant_id(move.ant_id, map);
		}
		t_room *room_b = get_room_by_name(move.room_name.c_str(), map);
		if (room_b != map->end)
			room_b->ant_id = move.ant_id;
		if (room_a != map->start)
			room_a->ant_id = NO_ANT;
	}
}

static void draw_move(Move& move, uint frame_index, t_map *map, sf::RenderWindow& window, uint last_ant_id, sf::Font& font)
{
	t_room *room_a;
	if (move.ant_id > last_ant_id)
		room_a = map->start;
	else
		room_a = get_room_by_ant_id(move.ant_id, map);
	t_room *room_b = get_room_by_name(move.room_name.c_str(), map);
	const uint room_half = ROOM_SIZE / 2;
	sf::Vector2f original_pos(window_pos(room_a->coord_x) + room_half - ANT_SIZE, window_pos(room_a->coord_y) + room_half - ANT_SIZE);
	sf::Vector2f dest_pos(window_pos(room_b->coord_x) + room_half - ANT_SIZE, window_pos(room_b->coord_y) + room_half - ANT_SIZE);
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

static void draw_move_list(std::vector<Move>& move_list, uint frame_index, t_map *map, sf::RenderWindow& window, uint last_ant_id, sf::Font& font)
{
	for (uint i = 0; i < move_list.size(); i++)
		draw_move(move_list[i], frame_index, map, window, last_ant_id, font);
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
	t_map *map = create_map();
	std::vector<std::vector<Move> > moves;
	create_moves(moves);
	sf::RenderWindow window(sf::VideoMode(800, 600), "lem_in Visualizer");
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
        draw_tubes(map, window);
        for (uint i = 0; i < map->rooms->size; i++)
        	draw_room((t_room*)array_get(map->rooms, i), window, font, map);
        draw_move_list(moves[move_index], frame_index, map, window, last_ant_id, font);
        if (frame_index < FRAME_COUNT)
        	frame_index++;
        else
        {
        	apply_move_list(moves[move_index], map, last_ant_id);
        	move_index++;
        	frame_index = 0;
        	if (move_index >= moves.size())
        	{
        		last_ant_id = 0;
        		reset_map(map);
        		move_index = 0;
        	}
        }
        window.display();
        sf::sleep(sf::milliseconds(10));
    }
	return (0);
}