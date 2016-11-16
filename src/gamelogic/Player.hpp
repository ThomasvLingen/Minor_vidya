//
// Created by waseland on 11/7/16.
//

#ifndef MINOR_VIDYA_PLAYER_HPP
#define MINOR_VIDYA_PLAYER_HPP

#include <memory>
#include "../engine/domain/WorldObject.hpp"
#include "../engine/domain/PointOfView.hpp"
#include "../engine/domain/CoordinateDouble.hpp"
#include "../engine/raycasting/RaycastingVector.hpp"
#include "VectorUtil.hpp"
#include "Level.hpp"
#include "../engine/KeyStrokes.hpp"

namespace GameLogic {

    using Engine::CoordinateDouble;
    using Engine::RaycastingVector;
    using Engine::PointOfView;
    using Engine::WorldObject;
    using Engine::PressedKeys;
    using Engine::Key;

    class Level;

    class Player : public PointOfView {

    public:
        Player(CoordinateDouble position, std::shared_ptr<Level> level);

        bool is_at(int x, int y);
        void set_level(std::shared_ptr<Level> level);
        void handleInput(PressedKeys keys);
        virtual void update(int timeSinceLastUpdate);

    private:
        std::shared_ptr<Level> _level;

        const double _MOVE_SPEED = 0.005;
        const double _ROT_SPEED = 0.002;
        double _accel = 0;
        double _rotation = 0;

        void _move_player(int timeSinceLastUpdate);
        void _rotate_player(int timeSinceLastUpdate);
        void _mov_forward();
        void _mov_backward();
        void _rot_right();
        void _rot_left();

        /*
         * int health
         * obj Inventory -> vector<items>
         * GrabItem();
         * PlaceItem();
         *
         */

    };
}

#endif //MINOR_VIDYA_PLAYER_HPP
