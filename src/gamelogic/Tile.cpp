//
// Created by waseland on 11/7/16.
//

#include "Tile.hpp"

Tile::Tile()
{
    for (size_t i = 0; i < 4; i++) {
        this->_neighbour_tiles.push_back(nullptr);
    }
}


Tile::~Tile()
{

}

void Tile::update()
{
    // TODO: Implement this
}

void Tile::set_wall(bool has_wall)
{
    this->_wall = has_wall;
}

void Tile::set_color(Color color)
{
    this->_color = color;
}

void Tile::set_tile_neighbour(TileObject * tile, Direction direction)
{
    this->_neighbour_tiles[_direction_to_num_map[direction]];
}

TileObject * Tile::get_tile_neighbour(Direction direction)
{
    return this->_neighbour_tiles[_direction_to_num_map[direction]];
}

bool Tile::is_wall()
{
    return this->_wall;
}

Color Tile::get_color()
{
    return this->_color;
}