//
// Created by sander on 11/17/16.
//

#include "RunState.hpp"
#include "PauseState.hpp"

namespace State {

    RunState::RunState(Game& context)
    : IGameState(context)
    , _fps(context.SDL_facade)
    {
        this->_collection.add_drawable(&_fps);
        this->_collection.add_updatable(&_fps);
        context.SDL_facade.stop_music();
    }

    void RunState::update(int time_since_last_update) { //TODO: If called again, level has to reload
        this->_context.SDL_facade.handle_sdl_events();
        this->_context.raycasting_engine.handle_input();

        Input keys = this->_context.SDL_facade.get_input();
        for (auto key : keys.keys_released) {
            switch (key) {
                case Key::ESC:
                    this->_context.set_new_state(std::make_shared<PauseState>(this->_context));
                    break;
                default:
                    break;
            }
        }

        this->_context.raycasting_engine.update(time_since_last_update);
        this->_collection.update(time_since_last_update);

        this->_context.SDL_facade.clear_screen();

        this->_context.raycasting_engine.draw();
        this->_collection.draw();

        this->_context.SDL_facade.render_buffer();
    }
}