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
        void run();

        SDLFacade SDL_facade;
        Raycasting raycasting_engine;

        void set_new_state(SPTR_IGameState state);

    private:
        bool _running;
        SPTR_IGameState _current_state;

        SPTR_Level _level; //TODO: perhaps change this to a level pointer

        void init_states();

    };

    typedef std::shared_ptr<Game> SPTR_Game;
}


#endif //MINOR_VIDYA_GAME_HPP
