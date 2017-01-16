//
// Created by mafn on 1/2/17.
//

#ifndef MINOR_VIDYA_SOLDIER_HPP
#define MINOR_VIDYA_SOLDIER_HPP

#include "enemy.hpp"
#include "../../engine/AssetsManager.hpp"

namespace GameLogic {

    using Engine::CoordinateDouble;
    using Engine::AssetsManager;

    class Soldier : public Enemy {
    public:
        Soldier(AssetsManager& assets, CoordinateDouble position, vector<CoordinateDouble> idle_route );
    private:
    };
}


#endif //MINOR_VIDYA_SOLDIER_HPP
