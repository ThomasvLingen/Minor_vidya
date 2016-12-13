//
// Created by sander on 11/17/16.
//

#include "RunState.hpp"
#include "PauseState.hpp"

namespace State {

    RunState::RunState(Game& context)
    : IGameState(context)
    , _fps(context.SDL_facade)
    , _hud(context.SDL_facade, *context.get_player())
    {
        this->_collection.add_drawable(&_fps);
        this->_collection.add_updatable(&_fps);
        this->_collection.add_drawable(&_hud);
        this->_collection.add_updatable(&_hud);
        context.SDL_facade.stop_music();
    }

    void RunState::set_ticks_set_off(int ticks) {
        _hud.set_ticks_set_off(ticks);
    }

    void RunState::update(int time_since_last_update) { //TODO: If called again, level has to reload
        this->_context.SDL_facade.handle_sdl_events();
        this->_context.raycasting_engine.handle_input();

        Input keys = this->_context.SDL_facade.get_input();
        for (auto key : keys.keys_released) {
            switch (key) {
                case Key::ESC: {
                    std::shared_ptr<PauseState> state = std::make_shared<PauseState>(this->_context);
                    state->set_ticks_in_game(this->_hud.get_current_time());
                    this->_context.set_new_state(state);
                }
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