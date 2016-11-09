//
// Created by waseland on 11/7/16.
//

#include "Level.hpp"
#include "Tile.hpp"

using std::vector;

Level::Level(vector<vector<TileObject*>> field)
: WorldObject(field)
, _point_of_view(Engine::CoordinateDouble{2 , 10}, Engine::RaycastingVector{-1 , 0}, Engine::RaycastingVector{0 , 0.66})
{

}

Level::~Level()
{

}

void Level::update()
{
    // TODO: Implement this
}

PointOfView & Level::get_pov()
{
    return this->_point_of_view;
}

TileObject * Level::get_tile(int x, int y)
{
    try {
        return this->_field[y][x];
    }
    catch (const std::exception&) {
        return nullptr;
    }
}

CoordinateDouble Level::get_spawnpoint()
{
    return this->_spawnpoint;
}