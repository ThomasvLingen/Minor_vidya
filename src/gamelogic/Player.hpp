//
// Created by waseland on 11/7/16.
//

#ifndef MINOR_VIDYA_PLAYER_HPP
#define MINOR_VIDYA_PLAYER_HPP


#include "../engine/domain/PointOfView.hpp"
#include "../engine/domain/CoordinateDouble.hpp"
#include "../engine/raycasting/RaycastingVector.hpp"

namespace GameLogic {

    using Engine::CoordinateDouble;
    using Engine::RaycastingVector;
    using Engine::PointOfView;

    class Player : public PointOfView {

    public:
        Player(CoordinateDouble position);

        virtual ~Player();

    private:
        /*
         * int health
         * obj Inventory -> vector<items>
         * GrabItem();
         * PlaceItem();
         *
         */

    };
}


#endif //MINOR_VIDYA_PLAYER_HPP
