//
// Created by sander on 11/17/16.
//

#include "StartUpState.hpp"
#include "MenuState.hpp"

namespace State {

    StartUpState::StartUpState(Game& context)
    : IGameState(context)
    {

    }

    void StartUpState::update(int time_since_last_update) {
        this->_context.SDL_facade.handle_sdl_events();

        PressedKeys keys = this->_context.SDL_facade.get_keys();

        for(auto key : keys){
            switch (key) {
                case Key::ENTER:
                    this->_context.set_new_state(std::make_shared<MenuState>());
                    break;
                default:
                    break;
            }
        }

        this->_context.SDL_facade.clear_screen();
        this->_context.SDL_facade.draw_image("res/startscreen.bmp", CoordinateDouble{0,0});
        this->_context.SDL_facade.render_buffer();
    }
}