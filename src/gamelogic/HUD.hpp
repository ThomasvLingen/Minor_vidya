//
// Created by sander on 12/12/16.
//

#ifndef MINOR_VIDYA_HUD_HPP
#define MINOR_VIDYA_HUD_HPP

#include "../engine/interface/Drawable.hpp"
#include "../engine/interface/Updatable.hpp"
#include "../engine/SDLFacade.hpp"
#include "../engine/PathUtil.hpp"
#include "Player.hpp"
#include <string>

namespace Engine {
    class SDLFacade;
}

namespace GameLogic {
    using std::string;
    using Engine::Drawable;
    using Engine::Updatable;
    using Engine::Color;
    using Engine::SDLFacade;
    using Engine::FontType ;

    class HUD : public Drawable, public Updatable {
    public:
        HUD(SDLFacade& _SDL_facade, Player& player);

        int get_current_time();
        void set_ticks_set_off(int ticks);
        virtual void draw() override;

        virtual void update(int delta_time) override;

    private:
        Player& _player;
        void _draw_health(int health);
        void _draw_face();

        int _health_points;
        int _current_time; // in sec
        int _start_time;

        int _calculate_time(int ticks); // mili seconds to seconds
        string _time_to_string(int current_time); // nice output 1:32


    };
}

#endif //MINOR_VIDYA_HUD_HPP
