//
// Created by waseland on 12/19/16.
//

#ifndef MINOR_VIDYA_GUN_HPP
#define MINOR_VIDYA_GUN_HPP

#include "../engine/interface/Drawable.hpp"

namespace GameLogic {

    using Engine::Drawable;
    using Engine::SDLFacade;
    using Engine::CoordinateInt;

    class Weapon : public Drawable {

    public:
        Weapon(SDLFacade& SDL_Facade, CoordinateInt draw_coordinates
        , int animation_start_image, std::string sound_effect, int image_interval
        , std::vector<std::string> images, int amount_of_shots, int damage_per_shot);
        virtual ~Weapon();

        void draw() override;

        void shoot();
        bool being_shot();

        int get_amount_of_shots();
        int get_damage_per_shot();

    private:
        CoordinateInt _draw_coordinates;
        bool _shoot = false;
        int _previous_ticks;
        int _ticks_on_shoot;
        int _current_image;
        int _animation_start_image;
        std::string _sound_effect;
        int _image_interval;
        std::vector<std::string> _images;
        int _amount_of_shots;
        int _damage_per_shot;

    };
}


#endif //MINOR_VIDYA_GUN_HPP
