//
// Created by waseland on 11/7/16.
//

#include "Player.hpp"

namespace GameLogic {

    Player::Player(CoordinateDouble position)
    : PointOfView(position, Engine::RaycastingVector{-1, 0}, Engine::RaycastingVector{0, 0.66})
    , _level(nullptr)
    , _health(80)
    {

    }

    /// \brief Handles the keys that were pressed during the last tick
    ///
    /// \param keys is a vector of Key enumerables that were pressed
    void Player::handleInput(Input keys)
    {
        for (auto key : keys.keys_released) {
            switch (key) {
                case Key::E :
                    this->_action_released = true;
                    break;
                default:
                    break;
            }
        }

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
                    if (this->_action_released) {
                        this->_action_released = false;
                        this->_do_action();
                    }
                    break;
                default:
                    break;
            }
        }
    }

    int Player::get_health() {
        return this->_health;
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
        if (this->_new_tile()){
            this->_set_new_current_tile();
            this->_try_trigger();
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
        this->_current_tile = this->_level->get_tile_in_level({(int)this->_position.x, (int)this->_position.y});
    }

    /// \brief Checks if the player stepped in a new tile
    bool Player::_new_tile()
    {
        return this->_level->get_tile({(int)this->_position.x, (int)this->_position.y}) != this->_current_tile;
    }
    void Player::_set_new_current_tile()
    {
        this->_current_tile = this->_level->get_tile_in_level({(int)this->_position.x, (int)this->_position.y});
    }

    /// \brief Applies action to the tile
    void Player::_do_action() //TODO: Expand with maybe checking for items on ground etc.
    {
        CoordinateDouble new_position{this->_position.x + this->_direction.x * this->_next_tile, this->_position.y + this->_direction.y * this->_next_tile};
        Tile* tile = this->_level->get_tile_in_level({(int)new_position.x, (int)new_position.y});
        for(auto tiletrigger : tile->get_action_tiletriggers()) {
            if (tiletrigger != nullptr) {
                tiletrigger->make_call(*this->_level);
            }
        }
    }

    /// \brief Checks if there is a trigger on the tile
    void Player::_try_trigger()
    {
        Tile* tile = this->_current_tile;
        for(auto tiletrigger : tile->get_step_on_tiletriggers()) {
            if (tiletrigger != nullptr) {
                tiletrigger->make_call(*this->_level);
            }
        }
    }
}
