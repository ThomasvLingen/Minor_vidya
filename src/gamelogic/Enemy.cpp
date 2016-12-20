#include "Enemy.hpp"

namespace GameLogic {

    Enemy::Enemy( ImageBuffer* texture, CoordinateDouble position )
    :Entity( texture, position )
    {
    }


    Enemy::~Enemy()
    {
    }

}
