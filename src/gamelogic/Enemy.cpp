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
        if ( _positionindex == _idle_route.size() ) {
            _positionindex = 0;
        }
        this->_step_towards(delta_time);
    }

    void Enemy::_step_towards( int delta_time )
    {
        CoordinateDouble step = this->_get_step(delta_time);
        CoordinateDouble to_apply = step;
        this->_apply_step(to_apply);
    }

    CoordinateDouble Enemy::_get_step( int delta_time )
    {
        CoordinateDouble next_point((_idle_route[_positionindex] + this->_original_position) - this->_position);
        double length = sqrt( pow( next_point.x, 2 ) + pow( next_point.y, 2 ) );
        CoordinateDouble next_distance = { (next_point.x / length) * this->_speed * delta_time, (next_point.y / length) * this->_speed * delta_time };

        if ( next_point.x >= next_distance.x && next_point.y >= next_distance.y ) {
            return next_distance;
        }
        else {
            this->_positionindex++;
            return next_point;
        }
    }

    void Enemy::_apply_step( CoordinateDouble to_apply )
    {
        this->_position = this->_position + to_apply;
    }

}
