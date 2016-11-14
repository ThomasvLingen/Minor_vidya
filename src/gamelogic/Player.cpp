//
// Created by waseland on 11/7/16.
//

#include "Player.hpp"

namespace GameLogic {

    Player::Player(CoordinateDouble position, Level &world)
    : PointOfView(position, Engine::RaycastingVector{-1, 0}, Engine::RaycastingVector{0, 0.66})
    , _level(world)
    {
    }

    Player::~Player()
    {

    }

    void Player::handleInput(PressedKeys keys)
    {
        bool WS_Pressed = false;
        bool AD_Pressed = false;

        for (auto key : keys) {
            switch (key) {
                case Key::A :
                    this->_rot_left();
                    AD_Pressed = true;
                    break;
                case Key::S :
                    this->_mov_backward();
                    WS_Pressed = true;
                    break;
                case Key::W :
                    this->_mov_forward();
                    WS_Pressed = true;
                    break;
                case Key::D :
                    this->_rot_right();
                    AD_Pressed = true;
                    break;
                default:
                    break;
            }
        }

        if (!AD_Pressed) {
            this->_rot_stop();
        }
        if (!WS_Pressed) {
            this->_mov_stop();
        }
    }

    void Player::update(int timeSinceLastUpdate)
    {
        double moveSpeed = this->_accel * timeSinceLastUpdate;
        double new_x = this->_position.x + this->_direction.x * moveSpeed;
        double new_y = this->_position.y + this->_direction.y * moveSpeed;


        if (!this->_level.get_tile((int) new_x, (int) this->_position.y)->is_wall()) {
            this->_position.x = new_x;
        }
        if (!this->_level.get_tile((int) this->_position.x, (int) new_y)->is_wall()) {
            this->_position.y = new_y;
        }


        double rotSpeed = this->_rotation * timeSinceLastUpdate;
        VectorUtil::rotate_vector(&this->_direction.x, &this->_direction.y, rotSpeed);
        VectorUtil::rotate_vector(&this->_camera_plane.x, &this->_camera_plane.y, rotSpeed);
    }


    bool Player::is_at(int x, int y)
    {
        return (int) this->_position.x == x && (int) this->_position.y == y;
    }


    void Player::_mov_stop()
    {
        this->_accel = 0;
    }


    void Player::_mov_forward()
    {
        this->_accel = this->_MOVE_SPEED;
    }


    void Player::_mov_backward()
    {
        this->_accel = -this->_MOVE_SPEED;
    }


    void Player::_rot_stop()
    {
        this->_rotation = 0;
    }


    void Player::_rot_right()
    {
        this->_rotation = -this->_ROT_SPEED;
    }


    void Player::_rot_left()
    {
        this->_rotation = this->_ROT_SPEED;
    }

    void Player::set_level_ref(Level& level)
    {
        this->_level = level;
    }
}
