#include "Enemy.hpp"
#include <cmath>

namespace GameLogic {

    Enemy::Enemy( AnimatedTexture* animated_texture, CoordinateDouble position, vector<CoordinateDouble> idle_route )
    :Entity( animated_texture, position )
    , _original_position(position)
    , _idle_route(idle_route)
    {
    }

    Enemy::~Enemy()
    {
    }

    void Enemy::update( int delta_time )
    {
        Entity::update(delta_time);
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

        if(length != 0 ){
        CoordinateDouble next_distance = { (next_point.x / length) * this->_speed * delta_time, (next_point.y / length) * this->_speed * delta_time };

        if ( std::abs(next_point.x) >= std::abs(next_distance.x) && std::abs(next_point.y) >= std::abs(next_distance.y) ) {
            return next_distance;
        }
        }
            this->_positionindex++;
            return next_point;
    }

    void Enemy::_apply_step( CoordinateDouble to_apply )
    {
        this->_position = this->_position + to_apply;
    }

}
