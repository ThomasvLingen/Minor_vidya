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
        this->_context.control_mapper.handle_input(keys);
        InputActions input_actions = this->_context.control_mapper.get_input_actions();


        for (auto action : input_actions.actions_off) {
            switch (action) {
                case Action::MENU_BACK:
                    this->_context.set_new_state(std::make_shared<MenuState>(this->_context));
                    break;
                default:
                    break;
            }
        }

        this->_context.SDL_facade.clear_screen();
        this->_context.SDL_facade.draw_image("res/helpscreen.bmp" , {0,0});
        this->_context.SDL_facade.draw_text("Controls for Vidya Game", FontType::alterebro_pixel, this->_color, {120, 50});

        ControlMapper mapper = this->_context.control_mapper;

        int current_y_pos = this->_start_pos_y;
        for (auto& editable_action : mapper.get_all_actions()) {
            this->_context.SDL_facade.draw_text(mapper.get_action_description(editable_action.first), this->_font, this->_color, {this->_action_start_pos_x, current_y_pos});
            this->_context.SDL_facade.draw_text(mapper.get_key_description(editable_action.second), FontType::alterebro_pixel, this->_color, {_key_start_pos_x, current_y_pos});
            current_y_pos += this->_step_size_y;
        }

        this->_context.SDL_facade.render_buffer();
    }
}