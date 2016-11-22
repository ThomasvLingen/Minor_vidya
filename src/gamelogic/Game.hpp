//
// Created by jazula on 11/9/16.
//

#ifndef MINOR_VIDYA_GAME_HPP
#define MINOR_VIDYA_GAME_HPP

//TODO: set FPS in config file
#define FPS 60
#define FRAME_DURATION 1000/FPS

#include "../engine/SDLFacade.hpp"
#include "../engine/raycasting/Raycasting.hpp"
#include "Level.hpp"
#include "Tile.hpp"
#include "state/IGameState.hpp"

namespace GameLogic {

    using State::SPTR_IGameState;
    using Engine::Raycasting;
    using Engine::SDLFacade;
    using Engine::WorldPTR;

    class Game {
    public:
        Game();
        void run();

        SDLFacade SDL_facade;

        void init_states();

    private:
        SPTR_IGameState _current_state;
        SPTR_IGameState _new_state;

        bool _running;
        Raycasting _raycasting_engine;
        SPTR_Level _level;

    };
}


#endif //MINOR_VIDYA_GAME_HPP
