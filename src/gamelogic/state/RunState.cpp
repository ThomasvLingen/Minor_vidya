//
// Created by sander on 11/17/16.
//

#include "RunState.hpp"
#include "PauseState.hpp"
#include "LevelWinState.hpp"
#include "GameOverState.hpp"
#include "MenuState.hpp"

namespace State {

    RunState::RunState(Game& context)
    : IGameState(context)
    , _fps(context.SDL_facade)
    , _hud(context.SDL_facade, context.get_level()->get_player())
    {
        this->_collection.add_drawable(&_fps);
        this->_collection.add_updatable(&_fps);
        this->_collection.add_drawable(&_hud);
        this->_collection.add_updatable(&_hud);
        this->_collection.add_drawable(&context.get_level()->get_player());
        this->_context.get_level()->start_ticks = this->_context.SDL_facade.get_ticks() - this->_context.get_level()->in_game_ticks;
        context.SDL_facade.stop_music();
    }

    void RunState::update(int time_since_last_update) { //TODO: If called again, level has to reload
        if (this->_is_game_over()) {
            this->_context.set_new_state(std::make_shared<GameOverState>(this->_context));
        }
        else if (this->_context.get_level()->is_level_over()) {
            this->_context.set_new_state(std::make_shared<LevelWinState>(this->_context));
        }
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
        try {
            this->_context.get_level()->get_player().get_weapon()->draw();
        }
        catch ( const Exceptions::WeaponIsNullptrException e ) {
            std::cout << e.what() << std::endl;
            std::cout << "Quiting game" << std::endl;
            this->_context.set_new_state(std::make_shared<MenuState>(this->_context));
        }

        this->_context.SDL_facade.render_buffer();
    }

    bool RunState::_is_game_over()
    {
        return
            this->_context.get_level()->get_player().get_health() <= 0;
    }
}
