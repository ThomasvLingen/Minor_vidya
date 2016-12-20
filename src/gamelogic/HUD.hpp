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
#include <iomanip>
#include <sstream>

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

        int get_current_ticks();
        void set_start_tick(int ticks);
        void set_current_tick(int ticks);
        virtual void draw() override;

        virtual void update(int delta_time) override;

    private:
        Player& _player;
        void _draw_health_blocks();
        void _draw_health_text();
        void _draw_face();
        int _calculate_health_blocks();

        int _current_time; // in sec
        int _current_ticks;
        int _start_ticks;

        int _calculate_time(int ticks); // mili seconds to seconds
        string _time_to_string(int current_time); // nice output 01:32

        //HUD health related
        Color _health_text_color = {255, 38, 70};
        CoordinateInt _health_text_pos = {222, 430};
        int _health_block_width = 12;
        int _health_block_height = 24;
        Color _health_block_full = {255, 38, 70};
        Color _health_block_empty = {121, 41, 52};
        int _amount_health_blocks = 10;
        int _set_off_health_bar = 62;
        int _spacing_blocks = 2;
        int _ypos_draw_block = 433;

        //HUD character related
        CoordinateInt _character_head_pos = {290, 410};
        CoordinateInt _HUD_pos = {0, 410};

        //HUD time related
        Color _time_color = {53, 194, 222};
        CoordinateInt _time_pos = {382, 430};

        string HUD_PATH = "res/HUDv2.bmp";
        string HUD_FACE_FRONT = "res/look_front.bmp";
        string HUD_FACE_LEFT = "res/look_left.bmp";
        string HUD_FACE_RIGHT = "res/look_right.bmp";

    };
}

#endif //MINOR_VIDYA_HUD_HPP
