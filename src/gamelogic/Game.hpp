//
// Created by jazula on 11/9/16.
//

#ifndef MINOR_VIDYA_GAME_HPP
#define MINOR_VIDYA_GAME_HPP

#define FRAME_DURATION 1000/60

#include "../engine/SDLFacade.hpp"
#include "../engine/raycasting/Raycasting.hpp"

namespace GameLogic {

    using Engine::Raycasting;
    using Engine::SDLFacade;

    class Game {
    public:
        Game();
        void run();

    private:
        bool _running;
        SDLFacade _SDL_facade;
        Raycasting _raycasting_engine;

    };
}


#endif //MINOR_VIDYA_GAME_HPP
