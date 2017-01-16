#ifndef MINOR_VIDYA_ENEMY_HPP
#define MINOR_VIDYA_ENEMY_HPP

#include <vector>
#include "../engine/domain/Entity.hpp"
#include "../engine/interface/Updatable.hpp"

namespace GameLogic {
    
    using std::vector;
    using Engine::ImageBuffer;
    using Engine::CoordinateDouble;

    class Enemy : public Engine::Entity{
    public:
        Enemy( ImageBuffer* texture, CoordinateDouble position, int hp, vector<CoordinateDouble> idle_route);
        ~Enemy();

        void update( int delta_time );

    private:
        double _speed = 0.00075;
        int _positionindex = 0;
        int _hp;
        CoordinateDouble _original_position;
        vector<CoordinateDouble> _idle_route;
        void _step_towards( int delta_time );
        CoordinateDouble _get_step( int delta_time );
        void _apply_step(CoordinateDouble to_apply);
    };

}

#endif //MINOR_VIDYA_ENEMY_HPP
