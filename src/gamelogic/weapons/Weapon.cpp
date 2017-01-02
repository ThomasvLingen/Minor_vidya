//
// Created by waseland on 12/19/16.
//

#include "Weapon.hpp"

namespace GameLogic {

    Weapon::Weapon(SDLFacade &SDL_Facade)
    : Drawable(SDL_Facade)
    {
    }

    Weapon::~Weapon()
    {
    }

    void Weapon::draw()
    {
        if (this->_shoot == true) {
            this->_SDL_facade.draw_image(this->_images[this->_current_image], this->_draw_coordinates);
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
        this->_previous_ticks = this->_SDL_facade.get_ticks();

    }

    void Weapon::shoot()
    {
        if(!this->_shoot){
            this->_shoot = true;
            this->_SDL_facade.play_sound_effect(this->_sound_effect);
            this->_ticks_on_shoot = this->_SDL_facade.get_ticks();
        }
    }

    bool Weapon::being_shot()
    {
        return this->_shoot;
    }

    int Weapon::get_bullets_per_shot()
    {
        return this->_bullets_per_shot;
    }

    int Weapon::get_damage_per_shot()
    {
        return this->_damage_per_shot;
    }

}