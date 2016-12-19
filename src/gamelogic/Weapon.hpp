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
        Weapon(SDLFacade& SDL_Facade, CoordinateInt draw_coordinates, int animation_start_image, std::string sound_effect, int image_interval, std::vector<std::string> images);

        void draw() override;

        void shoot();

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
    };
}


#endif //MINOR_VIDYA_GUN_HPP
