//
// Created by jazula on 11/9/16.
//

#ifndef MINOR_VIDYA_GAME_HPP
#define MINOR_VIDYA_GAME_HPP

#define FRAME_DURATION 1000/60

#include "../engine/SDLFacade.hpp"
#include "../engine/raycasting/Raycasting.hpp"
#include "Level.hpp"
#include "Tile.hpp"
#include <memory>

#include "State/IGameState.hpp"

namespace GameLogic {

    using State::SPTR_IGameState;
    using State::IGameState;
    using Engine::Raycasting;
    using Engine::SDLFacade;
    using Engine::WorldPTR;

    class Game {
    public:
        Game();
        ~Game();
        void run();

        SDLFacade _SDL_facade;
        Raycasting _raycasting_engine;

        int get_time_since_last_frame();
        void set_new_state(SPTR_IGameState state);

        SPTR_IGameState get_credit_state();
        SPTR_IGameState get_load_state();
        SPTR_IGameState get_menu_state();
        SPTR_IGameState get_pause_state();
        SPTR_IGameState get_run_state();
        SPTR_IGameState get_start_up_state();
        SPTR_IGameState get_help_state();


    private:
        bool _running;
        SPTR_IGameState _credit_state;
        SPTR_IGameState _load_state;
        SPTR_IGameState _menu_state;
        SPTR_IGameState _pause_state;
        SPTR_IGameState _run_state;
        SPTR_IGameState _start_up_state;
        SPTR_IGameState _current_state;
        SPTR_IGameState _help_state;

        int _time_since_last_frame;

        SPTR_Level _level; //TODO: perhaps change this to a level pointer

    };

    typedef std::shared_ptr<Game> SPTR_Game;
}


#endif //MINOR_VIDYA_GAME_HPP
