//
// Created by sander on 11/17/16.
//

#include "RunState.hpp"
#include "PauseState.hpp"

namespace State {

    RunState::RunState(Game& context)
    : IGameState(context)
    {

    }

    void RunState::update(int time_since_last_update) { //TODO: If called again, level has to reload
        this->_context.SDL_facade.handle_sdl_events();
        this->_context.raycasting_engine.handle_input();
        if(this->_timeSinceLastPress <= 20){ //TODO: TO SDL ticks
            this->_timeSinceLastPress++;
        }
        if(this->_timeSinceLastPress > 20) {
            PressedKeys keys = this->_context.SDL_facade.get_keys();
            for (auto key : keys) {
                switch (key) {
                    case Key::ESC:
                        this->_context.set_new_state(std::make_shared<PauseState>(this->_context));
                        break;
                    default:
                        break;
                }
            }
        }

        this->_context.raycasting_engine.update(time_since_last_update);
        this->_context.SDL_facade.clear_screen();

        this->_context.raycasting_engine.draw();

        this->_context.SDL_facade.render_buffer();
    }
}