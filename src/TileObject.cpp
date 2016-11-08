#include "TileObject.hpp"


TileObject::TileObject()
{
	for (size_t i = 0; i < 4; i++) {
		this->_neighbour_tiles.push_back(nullptr);
	}
}


TileObject::~TileObject()
{

}

/// \brief update all objects in this particular tile.
///
///
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
	this->_neighbour_tiles[_direction_to_num_map[direction]] = tile;
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
