//
// Created by sander on 11/18/16.
//

#include "HelpState.hpp"
#include "MenuState.hpp"
#include "../../util/UnusedMacro.hpp"
#include "../ControlMapper.hpp"

namespace State {
    using GameLogic::ControlMapper;

    HelpState::HelpState(Game& context)
    : IGameState(context)
    {

    }

    void HelpState::update(int time_since_last_update)
    {
        UNUSED(time_since_last_update)
        this->_context.SDL_facade.handle_sdl_events();

        Input keys = this->_context.SDL_facade.get_input();
        this->_context.control_mapper->handle_input(keys);
        InputActions* input_actions = this->_context.control_mapper->get_input_actions();


        for (auto action : input_actions->actions_off) {
            switch (action) {
                case Action::MENU_BACK:
                    this->_context.set_new_state(std::make_shared<MenuState>(this->_context));
                    break;
                default:
                    break;
            }
        }

        this->_context.SDL_facade.clear_screen();
        this->_context.SDL_facade.draw_image(VIDYA_RUNPATH + "res/helpscreen.bmp" , {0,0});
        this->_context.SDL_facade.draw_text("Controls for Vidya Game", FontType::alterebro_pixel, this->_color, {120, 50});

        int current_y_pos = this->_start_pos_y;
        for (auto& line : this->_text) {
            this->_context.SDL_facade.draw_text(line, this->_font, this->_color, {this->_start_pos_x, current_y_pos});
            current_y_pos += this->_step_size_y;
        }

        //TODO: Mapping
        this->_context.SDL_facade.draw_text("Up Arrow", FontType::alterebro_pixel, this->_color, {300, 80});
        this->_context.SDL_facade.draw_text("Down Arrow", FontType::alterebro_pixel, this->_color, {300, 110});
        this->_context.SDL_facade.draw_text("Left Arrow", FontType::alterebro_pixel, this->_color, {300, 140});
        this->_context.SDL_facade.draw_text("Right Arrow", FontType::alterebro_pixel, this->_color, {300, 170});
        this->_context.SDL_facade.draw_text("A", FontType::alterebro_pixel, this->_color, {300, 200});
        this->_context.SDL_facade.draw_text("D", FontType::alterebro_pixel, this->_color, {300, 230});
        this->_context.SDL_facade.draw_text("Enter", FontType::alterebro_pixel, this->_color, {300, 260});
        this->_context.SDL_facade.draw_text("ESC", FontType::alterebro_pixel, this->_color, {300, 290});


        this->_context.SDL_facade.render_buffer();
    }
}