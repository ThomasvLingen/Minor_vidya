//
// Created by waseland on 11/7/16.
//

#include "Tile.hpp"
#include "../util/UnusedMacro.hpp"

namespace GameLogic {

    Tile::Tile(ImageBuffer& texture)
    : TileObject(texture)
    {

    }

    void Tile::update(int delta_time)
    {
        UNUSED(delta_time)
        //TODO implement
    }
}