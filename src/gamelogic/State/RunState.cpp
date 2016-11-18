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

    void RunState::update(GameLogic::Game& game) {
        game._SDL_facade.handle_sdl_events();
        game._raycasting_engine.handle_input();
        game._raycasting_engine.update(game.get_time_since_last_frame());
        game._SDL_facade.clear_screen();

        game._raycasting_engine.draw();

        game._SDL_facade.render_buffer();
    }
}