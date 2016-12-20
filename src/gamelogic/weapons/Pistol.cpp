//
// Created by waseland on 12/20/16.
//

#include "Pistol.hpp"

namespace GameLogic {

    Pistol::Pistol(SDLFacade& SDL_Facade)
    : Weapon(SDL_Facade)
    {
        this->_draw_coordinates = {120,26};
        this->_animation_start_image = 1;
        this->_current_image = 1;
        this->_sound_effect = "pistolshot";
        this->_image_interval = 150;
        this->_images = {
                "res/gun/pistol1.bmp",
                "res/gun/pistol2.bmp",
                "res/gun/pistol3.bmp",
                "res/gun/pistol4.bmp",
                "res/gun/pistol5.bmp"
        };
        this->_amount_of_shots = 1;
        this->_damage_per_shot = 10;
    }
}