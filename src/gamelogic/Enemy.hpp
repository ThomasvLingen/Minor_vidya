#ifndef MINOR_VIDYA_ENEMY_HPP
#define MINOR_VIDYA_ENEMY_HPP

#include "..\engine\domain\Entity.hpp"

namespace GameLogic {

    using Engine::ImageBuffer;
    using Engine::CoordinateDouble;

    class Enemy : public Engine::Entity {
    public:
        Enemy( ImageBuffer* texture, CoordinateDouble position );
        ~Enemy();
    };

}

#endif //MINOR_VIDYA_ENEMY_HPP
