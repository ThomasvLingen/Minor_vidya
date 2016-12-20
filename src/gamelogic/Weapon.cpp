//
// Created by waseland on 12/19/16.
//

#include "Weapon.hpp"

namespace GameLogic {

    Weapon::Weapon(SDLFacade& SDL_Facade, CoordinateInt draw_coordinates
    , int animation_start_image, std::string sound_effect, int image_interval
    , std::vector<std::string> images, int amount_of_shots, int damage_per_shot)
    : Drawable(SDL_Facade)
    , _draw_coordinates(draw_coordinates)
    , _current_image(animation_start_image)
    , _animation_start_image(animation_start_image)
    , _sound_effect(sound_effect)
    , _image_interval(image_interval)
    , _images(images)
    , _amount_of_shots(amount_of_shots)
    , _damage_per_shot(damage_per_shot)
    {
    }

    void Weapon::draw()
    {
        if (_shoot == true) {
            this->_SDL_facade.draw_image(this->_images[this->_current_image], _draw_coordinates);
            if (this->_previous_ticks - this->_ticks_on_shoot >= this->_image_interval) {
                this->_current_image++;
                this->_ticks_on_shoot = this->_previous_ticks;
            }
            if (this->_current_image >= (int)this->_images.size()) {
                this->_shoot = false;
                this->_current_image = this->_animation_start_image;
            }
        } else {
            this->_SDL_facade.draw_image(this->_images[0], this->_draw_coordinates);
        }
        _previous_ticks = this->_SDL_facade.get_ticks();

    }

    void Weapon::shoot()
    {
        if(!this->_shoot){
            this->_shoot = true;
            this->_SDL_facade.play_sound_effect(this->_sound_effect);
            this->_ticks_on_shoot = _SDL_facade.get_ticks();
        }
    }

    bool Weapon::being_shot()
    {
        return this->_shoot;
    }

    int Weapon::get_amount_of_shots()
    {
        return this->_amount_of_shots;
    }

    int Weapon::get_damage_per_shot()
    {
        return this->_damage_per_shot;
    }

}