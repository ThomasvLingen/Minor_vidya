//
// Created by waseland on 11/7/16.
//

#include "Player.hpp"

namespace GameLogic {

    Player::Player(CoordinateDouble position)
    : PointOfView(position, Engine::RaycastingVector{-1, 0}, Engine::RaycastingVector{0, 0.66})
    , _level(nullptr)
    {
    }

    /// \brief Handles the keys that were pressed during the last tick
    ///
    /// \param keys is a vector of Key enumerables that were pressed
    void Player::handleInput(Input keys)
    {
        for (auto key : keys.keys_down) {
            switch (key) {
                case Key::A :
                    this->_move_left();
                    break;
                case Key::DOWN :
                    this->_mov_backward();
                    break;
                case Key::UP :
                    this->_mov_forward();
                    break;
                case Key::D :
                    this->_move_right();
                    break;
                case Key::LEFT :
                    this->_rot_left();
                    break;
                case Key::RIGHT :
                    this->_rot_right();
                    break;
                case Key::E :
                    this->_do_action();
                    break;
                default:
                    break;
            }
        }
    }

    void Player::update(int timeSinceLastUpdate)
    {
        if (this->_level != nullptr) {
            this->_move_player(timeSinceLastUpdate);
            this->_rotate_player(timeSinceLastUpdate);
        }
    }


    /// \brief Moves the player to the new x and y position
    ///
    /// \param timeSinceLastUpdate
    void Player::_move_player(int timeSinceLastUpdate){
        double moveSpeedY = this->_yAccel * timeSinceLastUpdate;
        double moveSpeedX = this->_xAccel * timeSinceLastUpdate;
        double new_x = this->_position.x + this->_direction.x * moveSpeedY;
        double new_y = this->_position.y + this->_direction.y * moveSpeedY;

        double newDirectionX = this->_direction.x;
        double newDirectionY = this->_direction.y;

        VectorUtil::rotate_vector(newDirectionX, newDirectionY, 1.5);

        new_x = new_x + newDirectionX * moveSpeedX;
        new_y = new_y + newDirectionY * moveSpeedX;

        if (!this->_level->get_tile(CoordinateInt{(int) new_x, (int) this->_position.y})->is_wall()) {
            this->_position.x = new_x;
        }
        if (!this->_level->get_tile(CoordinateInt{(int) this->_position.x, (int) new_y})->is_wall()) {
            this->_position.y = new_y;
        }
        
        this->_yAccel = 0;
        this->_xAccel = 0;
    }

    void Player::_rotate_player(int timeSinceLastUpdate)
    {
        double rotSpeed = this->_rotation * timeSinceLastUpdate;
        
        VectorUtil::rotate_vector(this->_direction.x, this->_direction.y, rotSpeed);
        VectorUtil::rotate_vector(this->_camera_plane.x, this->_camera_plane.y, rotSpeed);
        
        this->_rotation = 0;
    }

    bool Player::is_at(int x, int y)
    {
        return (int) this->_position.x == x && (int) this->_position.y == y;
    }

    //TODO: rethink this, it is actually code dupplication, but readability increases by it
    // Should these functions be declared seperately or do we want one _move function?
    void Player::_mov_forward()
    {
        this->_yAccel = this->_MOVE_SPEED;
    }

    void Player::_mov_backward()
    {
        this->_yAccel = -this->_MOVE_SPEED;
    }

    void Player::_move_left()
    {
        this->_xAccel = this->_STRAFE_SPEED;
    }

    void Player::_move_right()
    {
        this->_xAccel = -this->_STRAFE_SPEED;
    }

    void Player::_rot_right()
    {
        this->_rotation = -this->_ROT_SPEED;
    }

    void Player::_rot_left()
    {
        this->_rotation = this->_ROT_SPEED;
    }

    void Player::set_level(SPTR_Level level)
    {
        this->_level = level;
        this->_position = level->get_spawnpoint();
    }

    void Player::_do_action()
    {
        double new_x = this->_position.x + this->_direction.x * 0.5;
        double new_y = this->_position.y + this->_direction.y * 0.5;
        TileObject* tile = this->_level->get_tile({(int)new_x, (int)new_y});
        std::cout << ", tile: " <<  (int)new_x << " : "  << (int)new_y << " is: " << ((tile->is_wall()) ? "true" : "false") << std::endl;
        std::cout << tile->_tiletrigger;
        if(tile->_tiletrigger != nullptr){
            std::cout << "Triggered" << std::endl;
            tile->_tiletrigger->make_call(*this->_level);
        }
    }
}
