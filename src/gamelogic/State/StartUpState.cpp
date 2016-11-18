//
// Created by sander on 11/17/16.
//

#include "StartUpState.hpp"

using State::StartUpState;

namespace State {

    StartUpState::StartUpState(){

    }

    StartUpState::~StartUpState(){

    }

    void StartUpState::update(GameLogic::Game& game) {
        game._SDL_facade.handle_sdl_events();
        game._raycasting_engine.handle_input();
        PressedKeys keys = game._SDL_facade.get_keys();
            for(auto key : keys){
                switch (key) {
                    case Key::ENTER:
                        game.set_new_state(game.get_menu_state());
                        break;
                    default:
                        break;
                }
            }
        game._SDL_facade.clear_screen();
        game._SDL_facade.draw_image("res/startscreen.bmp", CoordinateDouble{0,0});
        game._SDL_facade.render_buffer();
    }
}