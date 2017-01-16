//
// Created by mafn on 1/2/17.
//

#include "Soldier.hpp"

namespace GameLogic {

    Soldier::Soldier(AssetsManager& assets, CoordinateDouble position, vector<CoordinateDouble> idle_route )
    : Enemy(
        new Engine::AnimatedTexture(
            assets.get_animation("soldier_idle"),
            {250, 250, 250, 250},
            16, 16
        ),
        position,
        idle_route
    )
    {

    }
}