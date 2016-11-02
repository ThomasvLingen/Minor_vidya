#include "stdafx.h"
#include "WorldObject.hpp"


WorldObject::WorldObject(vector<vector<TileObject*>> field)
{
	this->_field = field;
}

WorldObject::~WorldObject()
{
}

void WorldObject::update()
{

}

TileObject * WorldObject::get_tile(int x, int y)
{
	try {
		return this->_field[y][x];
	}
	catch (const std::exception&) {
		return nullptr;
	}
}
