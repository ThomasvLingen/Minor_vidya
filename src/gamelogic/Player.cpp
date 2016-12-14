//
// Created by waseland on 11/7/16.
//

#include "Player.hpp"
#include "../engine/SDLFacade.hpp"

namespace GameLogic {

    Player::Player(CoordinateDouble position, SDLFacade& SDL_facade, ControlMapper* control_mapper)
    : PointOfView(position, Engine::RaycastingVector{-1, 0}, Engine::RaycastingVector{0, 0.66})
    , Drawable(SDL_facade)
    , _level(nullptr)
    , _health(_total_health)
    , _control_mapper(control_mapper)
    {

    }

    Player::~Player()
    {
        for (auto weapon : this->_weapons) {
            delete weapon;
        }
    }

    /// \brief Handles the keys that were pressed during the last tick
    ///
    /// \param keys is a vector of Key enumerables that were pressed
    void Player::handleInput(Input keys)
    {
        this->_control_mapper->handle_input(keys);
        InputActions* input_actions = this->_control_mapper->get_input_actions();

        for (auto action : input_actions->actions_off) {
            switch (action) {
                case Action::ACTION_INTERACT :
                    this->_action_released = true;
                    break;
                default:
                    break;
            }
        }

        for (auto action : input_actions->actions_on) {
            switch (action) {
                case Action::MOVE_LEFT :
                    this->_move_left();
                    break;
                case Action::MOVE_BACKWARD :
                    this->_mov_backward();
                    break;
                case Action::MOVE_FORWARD :
                    this->_mov_forward();
                    break;
                case Action::MOVE_RIGHT :
                    this->_move_right();
                    break;
                case Action::ROTATE_LEFT :
                    this->_rot_left();
                    break;
                case Action::ROTATE_RIGHT :
                    this->_rot_right();
                    break;
                case Action::ACTION_INTERACT :
                    if (this->_action_released) {
                        this->_action_released = false;
                        this->_do_action();
                    }
                    break;
                case Key::K :
                    this->_hurt_self();
                default:
                    break;
            }
        }
    }

    int Player::get_health() {
        return this->_health;
    }

    int Player::get_total_health() {
        return this->_total_health;
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

    SPTR_Level Player::get_level()
    {
        return this->_level;
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
        Tile* tile = this->_get_facing_tile();
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

    void Player::_shoot()
    {
        CoordinateDouble new_position{this->_position.x + this->_direction.x * (this->_next_tile + 1), this->_position.y + this->_direction.y * (this->_next_tile + 1)};
        if (this->_level->has_entity((int)new_position.x , (int)new_position.y) && !this->_get_facing_tile()->is_wall()) {
            this->_level->kill_entity((int) new_position.x, (int) new_position.y);
        }
        this->get_weapon()->shoot();
    }

    Weapon* Player::get_weapon()
    {
        if (this->_weapons[this->_current_weapon_index] != nullptr) {
            return this->_weapons[this->_current_weapon_index];
        } else {
            throw Exceptions::WeaponIsNullptrException();
        }
    }

    void Player::give_weapon(Weapon* weapon)
    {
        if (weapon != nullptr) {
            this->_weapons.push_back(weapon);
        } else {
            throw Exceptions::WeaponIsNullptrException();
        }
    }

    void Player::_next_weapon()
    {
        if (!(this->get_weapon()->being_shot())) {
            this->_current_weapon_index++;
            this->_current_weapon_index = this->_current_weapon_index % (int) this->_weapons.size();
            this->_current_weapon_index = (this->_current_weapon_index < 0) ? this->_current_weapon_index
              + this->_weapons.size() : this->_current_weapon_index;
        }
    }

    void Player::_previous_weapon()
    {
        if (!(this->get_weapon()->being_shot())) {
            this->_current_weapon_index--;
            this->_current_weapon_index = this->_current_weapon_index % (int) this->_weapons.size();
            this->_current_weapon_index = (this->_current_weapon_index < 0) ? this->_current_weapon_index
              + this->_weapons.size() : this->_current_weapon_index;
        }
    }

    void Player::draw()
    {
        this->_draw_tile_usage();
        this->_draw_punch_usage();
        this->_draw_crosshair_usage();
    }

    Tile* Player::_get_facing_tile()
    {
        CoordinateDouble new_position{this->_position.x + this->_direction.x * this->_next_tile, this->_position.y + this->_direction.y * this->_next_tile};
        return this->_level->get_tile_in_level({(int)new_position.x, (int)new_position.y});
    }

    void Player::_draw_tile_usage()
    {
        if (this->_get_facing_tile()->get_action_tiletriggers().size() > 0) {
            this->_SDL_facade.draw_image(
                this->_action_hand_path,
                {this->_SDL_facade.get_width() / 2 - this->_SDL_facade.get_image_width(this->_action_hand_path) / 2,
                 this->_SDL_facade.get_height() / 2}
            );
        }
    }

    void Player::_draw_punch_usage()
    {
        CoordinateDouble new_position{this->_position.x + this->_direction.x * this->_next_tile, this->_position.y + this->_direction.y * this->_next_tile};
        if (this->_level->has_entity((int)new_position.x , (int)new_position.y)) {
            this->_SDL_facade.draw_image(
                    this->_action_punch_path,
                    {295,
                      200}
            );
        }
    }

    void Player::_draw_crosshair_usage()
    {
        CoordinateDouble new_position{this->_position.x + this->_direction.x * (this->_next_tile + 1), this->_position.y + this->_direction.y * (this->_next_tile + 1)};
        if (this->_level->has_entity((int)new_position.x , (int)new_position.y) && !this->_get_facing_tile()->is_wall()) {
            this->_SDL_facade.draw_image(
                    this->_crosshair_path,
                    {295,
                     200}
            );
        }
    }

    void Player::_melee() {
        CoordinateDouble new_position{this->_position.x + this->_direction.x * this->_next_tile,
                                      this->_position.y + this->_direction.y * this->_next_tile};
        if (this->_level->has_entity((int) new_position.x, (int) new_position.y)) {
            this->_level->kill_entity((int) new_position.x, (int) new_position.y);
            this->_SDL_facade.play_sound_effect("punch");
        } else {
            this->_SDL_facade.play_sound_effect("air");
        }
    }

    void Player::_hurt_self()
    {
        this->_health -= 2;
    }

}
