//
// Created by sander on 11/17/16.
//

#include "CreditState.hpp"
#include "MenuState.hpp"
#include "../../util/UnusedMacro.hpp"

namespace State {

    CreditState::CreditState(Game& context)
    : IGameState(context)
    {

    }

    void CreditState::update(int time_since_last_update) {
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
        this->_context.SDL_facade.draw_image("res/creditscreen.bmp" , CoordinateInt{0,0});

        int current_y_pos = this->_start_pos_y;
        for (auto& line : this->_text) {
            this->_context.SDL_facade.draw_text(line, this->_font, this->_color, {this->_start_pos_x, current_y_pos});
            current_y_pos += this->_step_size_y;
        }

        this->_context.SDL_facade.render_buffer();
    }
}