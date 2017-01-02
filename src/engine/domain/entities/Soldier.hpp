//
// Created by mafn on 1/2/17.
//

#ifndef MINOR_VIDYA_SOLDIER_HPP
#define MINOR_VIDYA_SOLDIER_HPP

#include "../Entity.hpp"
#include "../../AssetsManager.hpp"

namespace Engine {
    class Soldier : public Entity {
    public:
        Soldier(AssetsManager& assets, CoordinateDouble position);
    private:
    };
}


#endif //MINOR_VIDYA_SOLDIER_HPP
