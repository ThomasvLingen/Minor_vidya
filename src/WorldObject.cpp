#include "WorldObject.hpp"


WorldObject::WorldObject(vector<vector<TileObject*>> field)
: _field(field)
, _point_of_view(Engine::DoubleCoordinate{2 , 10}, Engine::RaycastingVector{-1 , 0}, Engine::RaycastingVector{0 , 0.66})
{
}

WorldObject::~WorldObject()
{
}

/// \brief update all objects of the WorldObject.
void WorldObject::update()
{
	// TODO: Implement this
}

PointOfView & WorldObject::get_pov()
{
	return this->_point_of_view;
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
