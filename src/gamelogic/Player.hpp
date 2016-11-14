//
// Created by waseland on 11/7/16.
//

#ifndef MINOR_VIDYA_PLAYER_HPP
#define MINOR_VIDYA_PLAYER_HPP

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

    class Level;

    class Player : public PointOfView {

    public:
        Player(CoordinateDouble position, Level& level); //is this retarted? perhaps use smart pointer for world

        virtual ~Player();

        bool is_at(int x, int y);

        void set_level_ref(Level& level);

    private:
        Level& _level;

        double _MOVE_SPEED = 0.005;
        double _ROT_SPEED = 0.002;
        double _position_x = 2;
        double _position_y = 10;
        double _dir_x = -1;
        double _dir_y = 0;
        double _plane_x = 0;
        double _plane_y = 0.66;

        double _accel = 0;
        double _rotation = 0;

        void handleInput(PressedKeys keys); //TODO: What is Keyboard?
        virtual void update(int timeSinceLastUpdate);

        void mov_stop();

        void mov_forward();

        void mov_backward();

        void rot_stop();

        void rot_right();

        void rot_left();


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
