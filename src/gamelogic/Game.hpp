//
// Created by jazula on 11/9/16.
//

#ifndef MINOR_VIDYA_GAME_HPP
#define MINOR_VIDYA_GAME_HPP

#define FRAME_DURATION 16.666

#include "../engine/SDLFacade.hpp"
#include "../engine/raycasting/Raycasting.hpp"
#include "Level.hpp"
#include "Tile.hpp"


namespace GameLogic {

    using Engine::Raycasting;
    using Engine::SDLFacade;
    using Engine::WorldPTR;

    class Game {
    public:
        Game();
        void run();

    private:
        bool _running;
        SDLFacade _SDL_facade;
        Raycasting _raycasting_engine;
        SPTR_Level _level; //TODO: perhaps change this to a level pointer

    };
}


#endif //MINOR_VIDYA_GAME_HPP
