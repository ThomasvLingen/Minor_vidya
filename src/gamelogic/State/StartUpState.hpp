//
// Created by sander on 11/17/16.
//

#ifndef MINOR_VIDYA_STARTUPSTATE_HPP
#define MINOR_VIDYA_STARTUPSTATE_HPP

#include "IGameState.hpp"

namespace GameLogic {
    class Game;
}

namespace State {

    class StartUpState : public IGameState {

    public:
        StartUpState();
        ~StartUpState();

        void update(GameLogic::Game & game) override ;
    };
}

#endif //MINOR_VIDYA_STARTUPSTATE_HPP
