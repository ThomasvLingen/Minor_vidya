//
// Created by sander on 11/17/16.
//

#ifndef MINOR_VIDYA_RUNSTATE_HPP
#define MINOR_VIDYA_RUNSTATE_HPP

#include "IGameState.hpp"
#include "../Game.hpp"
#include "../../engine/SDLFacade.hpp"

namespace GameLogic {
    class Game;
}

namespace State {
    using Engine::PressedKeys;
    using Engine::Key;

    class RunState : public IGameState {

    public:
        RunState();
        ~RunState();

        void update(GameLogic::Game& game) override ;

    private:
        int timeSinceLastPress = 0;
    };
}

#endif //MINOR_VIDYA_RUNSTATE_HPP
