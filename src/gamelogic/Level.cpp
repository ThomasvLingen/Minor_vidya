//
// Created by waseland on 11/7/16.
//

#include "Level.hpp"

using std::vector;

Level::Level(vector<vector<Tile*>> field)
{
    this->_field = field;
}

Level::~Level()
{

}

void Level::update()
{
    // TODO: Implement this
}

CoordinateDouble Level::get_spawnpoint()
{
    return this->_spawnpoint;
}

TileObject* Level::get_tile(int x, int y)
{
    return _field.at(x).at(y); //TODO use at or []?
}

PointOfView& Level::get_pov()
{
    return *(this->_player);
}

void Level::set_player(Player* player)
{
    this->_player = player;
}