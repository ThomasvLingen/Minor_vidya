//
// Created by mafn on 1/2/17.
//

#include "Soldier.hpp"

namespace GameLogic {

    Soldier::Soldier(AssetsManager& assets, CoordinateDouble position)
    : Entity(
        new Engine::AnimatedTexture(
            assets.get_animation("soldier_idle"),
            {250, 250, 250, 250},
            16, 16
        ),
        position
    )
    {

    }
}