//
// Created by waseland on 11/7/16.
//

#include "Tile.hpp"

Tile::Tile() : TileObject()
{

}


Tile::~Tile()
{

}

void Tile::update()
{
    std::cout << "I am here!" << std::endl;
}

void Tile::test()
{
    std::cout << "Test" << std::endl;
}

TileObject* Tile::getTile()
{
    return this;
};