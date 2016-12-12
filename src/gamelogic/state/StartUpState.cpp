//
// Created by sander on 11/17/16.
//

#include "StartUpState.hpp"
#include "MenuState.hpp"
#include "../../util/UnusedMacro.hpp"

namespace State {

    StartUpState::StartUpState(Game& context)
    : IGameState(context)
    {
        context.SDL_facade.play_music("res/music/startup.wav");
    }

    void StartUpState::update(int time_since_last_update) {
        UNUSED(time_since_last_update)
        this->_context.SDL_facade.handle_sdl_events();

        Input keys = this->_context.SDL_facade.get_input();
        this->_context.control_mapper.handle_input(keys);
        InputActions input_actions = this->_context.control_mapper.get_input_actions();

        for (auto action : input_actions.actions_off) {
            switch (action) {
                case Action::MENU_SELECT:
                    this->_context.set_new_state(std::make_shared<MenuState>(this->_context));
                    break;
                default:
                    break;
            }
        }

        this->_context.SDL_facade.clear_screen();
        this->_context.SDL_facade.draw_image("res/startscreen.bmp", {0,0});
        this->_context.SDL_facade.render_buffer();
    }
}