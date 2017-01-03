//
// Created by mafn on 1/2/17.
//

#ifndef MINOR_VIDYA_SOLDIER_HPP
#define MINOR_VIDYA_SOLDIER_HPP

#include "../../engine/domain/Entity.hpp"
#include "../../engine/AssetsManager.hpp"

namespace GameLogic {

    using Engine::Entity;
    using Engine::CoordinateDouble;
    using Engine::AssetsManager;

    class Soldier : public Entity {
    public:
        Soldier(AssetsManager& assets, CoordinateDouble position);
    private:
    };
}


#endif //MINOR_VIDYA_SOLDIER_HPP
