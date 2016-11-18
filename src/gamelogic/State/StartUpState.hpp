//
// Created by sander on 11/17/16.
//

#ifndef MINOR_VIDYA_STARTUPSTATE_HPP
#define MINOR_VIDYA_STARTUPSTATE_HPP

#include "IGameState.hpp"
#include "../Game.hpp"
#include "../../engine/SDLFacade.hpp"

namespace GameLogic {
    class Game;
}

namespace State {
    using Engine::SDLFacade;
    using Engine::CoordinateDouble;
    using Engine::Color;
    using Engine::FontType;
    using Engine::PressedKeys;
    using Engine::Key;

    class StartUpState : public IGameState {

    public:
        StartUpState();
        ~StartUpState();

        void update(GameLogic::Game& game) override ;
    private:
        int timeSinceLastPress = 0;
    };
}

#endif //MINOR_VIDYA_STARTUPSTATE_HPP
