//
// Created by sander on 11/17/16.
//

#include "RunState.hpp"
#include "PauseState.hpp"

namespace State {

    void RunState::update(GameLogic::Game& game, int time_since_last_update) { //TODO: If called again, level has to reload
        game.SDL_facade.handle_sdl_events();;
        if(timeSinceLastPress <= 20){ //TODO: TO SDL ticks
            timeSinceLastPress++;
        }
        if(timeSinceLastPress > 20) {
            PressedKeys keys = game.SDL_facade.get_keys();
            for (auto key : keys) {
                switch (key) {
                    case Key::ESC:
                        game.set_new_state(std::make_shared<PauseState>());
                        break;
                    default:
                        break;
                }
            }
        }

        game.raycasting_engine.update(time_since_last_update);
        game.SDL_facade.clear_screen();

        game.raycasting_engine.draw();

        game.SDL_facade.render_buffer();
    }
}