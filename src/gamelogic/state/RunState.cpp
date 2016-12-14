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
        this->_collection.add_handleable(&_fps);
        context.SDL_facade.stop_music();
    }

    void RunState::update(int time_since_last_update) { //TODO: If called again, level has to reload
        this->_context.SDL_facade.handle_sdl_events();
        this->_context.raycasting_engine.handle_input();

        Input keys = this->_context.SDL_facade.get_input();
        this->_collection.handle_input(keys);
        this->_context.control_mapper.handle_input(keys);
        InputActions input_actions = this->_context.control_mapper.get_input_actions();
        for (auto action : input_actions.actions_off) {
            switch (action) {
                case Action::PAUSE_GAME:
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