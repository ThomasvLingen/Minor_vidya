#include "Enemy.hpp"

namespace GameLogic {

    Enemy::Enemy( ImageBuffer* texture, CoordinateDouble position, int hp, vector<CoordinateDouble> idle_route )
    :Entity( texture, position )
    , _hp(hp)
    , _idle_route(idle_route)
    , _original_position(position)
    {
    }

    Enemy::~Enemy()
    {
    }

    void Enemy::update( int delta_time )
    {
        if ( positionindex == _idle_route.size() ) {
            positionindex = 0;
        }
        if ( ticks > 10 ) {
            this->_position = _original_position + _idle_route[positionindex];
            positionindex++;
            ticks = 0;
        }
        ticks++;
    }

}
