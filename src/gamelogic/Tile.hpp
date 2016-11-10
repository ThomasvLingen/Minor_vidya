//
// Created by waseland on 11/7/16.
//

#ifndef MINOR_VIDYA_TILE_HPP
#define MINOR_VIDYA_TILE_HPP

#include "../TileObject.hpp"
#include <iostream>

using std::vector;
using std::string;
using std::map;

class Tile : public TileObject {

public:

private:

public:
    Tile();
    virtual ~Tile();
    void update() override;
    void test();
    TileObject* getTile();

};


#endif //MINOR_VIDYA_TILE_HPP
