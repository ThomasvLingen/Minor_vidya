#include "stdafx.h"
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
}

void TileObject::set_tile_up(TileObject* up_tile)
{
	this->_neighbour_tiles.at(up) = up_tile;
}

void TileObject::set_tile_down(TileObject* down_tile)
{
	this->_neighbour_tiles.at(down) = down_tile;
}

void TileObject::set_tile_left(TileObject* left_tile)
{
	this->_neighbour_tiles.at(left) = left_tile;
}

void TileObject::set_tile_right(TileObject* right_tile)
{
	this->_neighbour_tiles.at(right) = right_tile;
}

TileObject * TileObject::get_tile_up()
{
	return this->_neighbour_tiles.at(up);
}

TileObject * TileObject::get_tile_down()
{
	return this->_neighbour_tiles.at(down);
}

TileObject * TileObject::get_tile_left()
{
	return this->_neighbour_tiles.at(left);
}

TileObject * TileObject::get_tile_right()
{
	return this->_neighbour_tiles.at(right);
}

bool TileObject::get_is_wall()
{
	return this->_wall;
}

Color TileObject::get_color()
{
	return this->_color;
}
