//
// Created by waseland on 12/20/16.
//

#include "ChainGun.hpp"

namespace GameLogic {

    ChainGun::ChainGun(SDLFacade& SDL_Facade)
    : Weapon(SDL_Facade)
    {
        SDL_Facade.load_sound_effect("chaingunshot", "res/sound_effects/chaingunshot.wav");
        this->_draw_coordinates = {120,26};
        this->_animation_start_image = 1;
        this->_current_image = 1;
        this->_sound_effect = "chaingunshot";
        this->_image_interval = 70;
        this->_images = {
                "res/gun/chain_gun1.bmp",
                "res/gun/chain_gun2.bmp",
                "res/gun/chain_gun3.bmp",
                "res/gun/chain_gun4.bmp",
                "res/gun/chain_gun5.bmp",
                "res/gun/chain_gun6.bmp",
                "res/gun/chain_gun7.bmp",
                "res/gun/chain_gun8.bmp",
                "res/gun/chain_gun9.bmp",
                "res/gun/chain_gun10.bmp",
                "res/gun/chain_gun11.bmp",
                "res/gun/chain_gun12.bmp",
                "res/gun/chain_gun13.bmp",
                "res/gun/chain_gun14.bmp"
        };
        this->_bullets_per_shot = 2;
        this->_damage_per_shot = 8;
    }
}
