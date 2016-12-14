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
        void set_start_tick(int ticks);
        virtual void draw() override;

        virtual void update(int delta_time) override;

    private:
        Player& _player;
        void _draw_health_blocks(int health);
        void _draw_health_text(int health);
        void _draw_face();
        int _calculate_health_blocks(int health);

        int _current_time; // in sec
        int _start_time;

        int _calculate_time(int ticks); // mili seconds to seconds
        string _time_to_string(int current_time); // nice output 1:32

        //HUD health related
        Color _health_text_color = {255, 38, 70};
        CoordinateInt _health_text_pos = {222, 430};
        int _health_block_width = 12;
        int _health_block_height = 24;
        Color _health_block_full = {255, 38, 70};
        Color _health_block_empty = {121, 41, 52};
        int _amount_health_blocks = 10;
        int _total_health = 80;

        //HUD character related
        CoordinateInt _character_head_pos = {290, 410};
        CoordinateInt _HUD_pos = {0, 410};

        //HUD time related
        Color _time_color = {53, 194, 222};
        CoordinateInt _time_pos = {390, 430};

    };
}

#endif //MINOR_VIDYA_HUD_HPP
