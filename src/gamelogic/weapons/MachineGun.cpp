//
// Created by waseland on 12/20/16.
//

#include "MachineGun.hpp"

namespace GameLogic {

    MachineGun::MachineGun(SDLFacade& SDL_Facade)
            : Weapon(SDL_Facade)
    {
        SDL_Facade.load_sound_effect("machinegunshot", "res/sound_effects/machinegunshot.wav");
        this->_draw_coordinates = {120,26};
        this->_animation_start_image = 1;
        this->_current_image = 1;
        this->_sound_effect = "machinegunshot";
        this->_image_interval = 75;
        this->_images = {
                "res/gun/machine_gun1.bmp",
                "res/gun/machine_gun2.bmp",
                "res/gun/machine_gun3.bmp",
                "res/gun/machine_gun4.bmp",
                "res/gun/machine_gun5.bmp",
                "res/gun/machine_gun6.bmp",
                "res/gun/machine_gun7.bmp",
                "res/gun/machine_gun8.bmp",
                "res/gun/machine_gun9.bmp",
                "res/gun/machine_gun10.bmp",
                "res/gun/machine_gun11.bmp",
                "res/gun/machine_gun12.bmp",
                "res/gun/machine_gun13.bmp"
        };
        this->_amount_of_shots = 5;
        this->_damage_per_shot = 3;
    }
}