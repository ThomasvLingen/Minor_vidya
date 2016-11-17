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

#include "State/IGameState.hpp"

namespace GameLogic {

    using State::IGameState;

    using Engine::Raycasting;
    using Engine::SDLFacade;
    using Engine::WorldPTR;

    class Game {
    public:
        Game();
        ~Game();
        void run();

    private:
        IGameState _credit_state;
        IGameState _load_state;
        IGameState _menu_state;
        IGameState _pause_state;
        IGameState _run_state;
        IGameState _start_up_state;
        IGameState _current_state;

        bool _running;
        SDLFacade _SDL_facade;
        Raycasting _raycasting_engine;
        SPTR_Level _level; //TODO: perhaps change this to a level pointer

    };
}


#endif //MINOR_VIDYA_GAME_HPP
