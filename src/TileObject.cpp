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

void TileObject::set_tile_up(TileObject* up_tile)
{
	this->_neighbour_tiles[to_up_neighbour_index] = up_tile
}

void TileObject::set_tile_down(TileObject* down_tile)
{
	this->_neighbour_tiles[to_down_neighbour_index] = down_tile;
}

void TileObject::set_tile_left(TileObject* left_tile)
{
	this->_neighbour_tiles[to_left_neighbour_index] = left_tile;
}

void TileObject::set_tile_right(TileObject* right_tile)
{
	this->_neighbour_tiles[to_right_neighbour_index] = right_tile;
}

TileObject * TileObject::get_tile_up()
{
	return this->_neighbour_tiles[to_up_neighbour_index];
}

TileObject * TileObject::get_tile_down()
{
	return this->_neighbour_tiles[to_down_neighbour_index];
}

TileObject * TileObject::get_tile_left()
{
	return this->_neighbour_tiles[to_left_neighbour_index];
}

TileObject * TileObject::get_tile_right()
{
	return this->_neighbour_tiles[to_right_neighbour_index];
}

bool TileObject::is_wall()
{
	return this->_wall;
}

Color TileObject::get_color()
{
	return this->_color;
}
