//
// Created by sander on 11/17/16.
//

#include "StartUpState.hpp"
#include "MenuState.hpp"

namespace State {

    void StartUpState::update(Game& game, int time_since_last_update) {
        game.SDL_facade.handle_sdl_events();

        PressedKeys keys = game.SDL_facade.get_keys();

        for(auto key : keys){
            switch (key) {
                case Key::ENTER:
                    game.set_new_state(std::make_shared<MenuState>());
                    break;
                default:
                    break;
            }
        }

        game.SDL_facade.clear_screen();
        game.SDL_facade.draw_image("res/startscreen.bmp", CoordinateDouble{0,0});
        game.SDL_facade.render_buffer();
    }
}