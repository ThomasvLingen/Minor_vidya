//
// Created by sander on 11/17/16.
//

#include "RunState.hpp"
#include "../Game.hpp"
using State::RunState;

namespace State {

    RunState::RunState(){

    }

    RunState::~RunState(){

    }

    void RunState::update(GameLogic::Game& game) { //TODO: If called again, level has to reload
        game._SDL_facade.handle_sdl_events();
        game._raycasting_engine.handle_input();
        if(timeSinceLastPress <= 20){ //TODO: TO SDL ticks
            timeSinceLastPress++;
        }
        if(timeSinceLastPress > 20) {
            PressedKeys keys = game._SDL_facade.get_keys();
            for (auto key : keys) {
                switch (key) {
                    case Key::ESC:
                        game.set_new_state(game.get_pause_state());
                        timeSinceLastPress = 0;
                        break;
                    default:
                        break;
                }
            }
        }

        game._raycasting_engine.update(game.get_time_since_last_frame());
        game._SDL_facade.clear_screen();

        game._raycasting_engine.draw();

        game._SDL_facade.render_buffer();
    }
}