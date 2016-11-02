#include "TileObject.hpp"


TileObject::TileObject()
{
	_direction_to_num_map.insert(std::pair<Direction, int>(up_tile, to_up_neighbour_index));
	_direction_to_num_map.insert(std::pair<Direction, int>(down_tile, to_down_neighbour_index));
	_direction_to_num_map.insert(std::pair<Direction, int>(left_tile, to_left_neighbour_index));
	_direction_to_num_map.insert(std::pair<Direction, int>(right_tile, to_right_neighbour_index));

	for (size_t i = 0; i < 4; i++) {
		this->_neighbour_tiles.push_back(nullptr);
	}
}


TileObject::~TileObject()
{

}

void TileObject::update()
{
	// TODO: Implement this
}

void TileObject::set_wall(bool has_wall)
{
	this->_wall = has_wall;
}

void TileObject::set_color(Color color)
{
	this->_color = color;
}

void TileObject::set_tile_neighbour(TileObject * tile, Direction direction)
{
	this->_neighbour_tiles[_direction_to_num_map[direction]];
}

TileObject * TileObject::get_tile_neighbour(Direction direction)
{
	return this->_neighbour_tiles[_direction_to_num_map[direction]];
}

bool TileObject::is_wall()
{
	return this->_wall;
}

Color TileObject::get_color()
{
	return this->_color;
}
