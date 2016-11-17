//
// Created by sander on 11/17/16.
//

#ifndef MINOR_VIDYA_RUNSTATE_HPP
#define MINOR_VIDYA_RUNSTATE_HPP

#include "IGameState.hpp"

namespace GameLogic {
    class Game;
}

namespace State {

    class RunState : public IGameState {

    public:
        RunState();
        ~RunState();

        void update(GameLogic::Game & game) override ;
    };
}

#endif //MINOR_VIDYA_RUNSTATE_HPP
