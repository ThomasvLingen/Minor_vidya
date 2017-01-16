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
    , _cheats(context)
    {
        this->_collection.add_drawable(&_fps);
        this->_collection.add_updatable(&_fps);
        this->_collection.add_drawable(&_hud);
        this->_collection.add_updatable(&_hud);
        this->_collection.add_drawable(&context.get_level()->get_player());
        this->_context.get_level()->start_ticks = this->_context.SDL_facade.get_ticks() - this->_context.get_level()->in_game_ticks;
        this->_collection.add_handleable(&_fps);
        this->_collection.add_handleable(&this->_cheats);
        context.SDL_facade.stop_music();
        context.SDL_facade.play_music("res/music/music_basic.wav");
    }

    void RunState::update(int time_since_last_update) { //TODO: If called again, level has to reload
        if (this->_is_game_over()) {
            this->_context.SDL_facade.stop_music();
            this->_context.set_new_state(std::make_shared<GameOverState>(this->_context));
        }
        else if (this->_context.get_level()->is_level_over()) {
            this->_context.SDL_facade.stop_music();
            this->_context.set_new_state(std::make_shared<LevelWinState>(this->_context));
        }
        if (!_is_half_hp && this->_context.get_level()->get_player().get_health() < 50) {
            this->_is_half_hp = true;
            this->_context.SDL_facade.stop_music();
            this->_context.SDL_facade.play_music("res/music/music_spedup.wav");
        } else if (_is_half_hp && this->_context.get_level()->get_player().get_health() >= 50) {
            this->_is_half_hp = false;
            this->_context.SDL_facade.stop_music();
            this->_context.SDL_facade.play_music("res/music/music_basic.wav");
        }
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
