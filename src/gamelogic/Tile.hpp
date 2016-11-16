//
// Created by waseland on 11/7/16.
//

#ifndef MINOR_VIDYA_TILE_HPP
#define MINOR_VIDYA_TILE_HPP

#include "../engine/domain/TileObject.hpp"

namespace GameLogic {

    class Tile : public Engine::TileObject {

    public:
        Tile();

        void update(int delta_time) override;

    };
}


#endif //MINOR_VIDYA_TILE_HPP
