//
// Created by sander on 11/17/16.
//

#ifndef MINOR_VIDYA_PAUSESTATE_HPP
#define MINOR_VIDYA_PAUSESTATE_HPP

#include "IGameState.hpp"

namespace GameLogic {
    class Game;
}

namespace State {

    class PauseState : public IGameState {

    public:
        PauseState();
        ~PauseState();

        void update(GameLogic::Game& game) override ;
    };
}

#endif //MINOR_VIDYA_PAUSESTATE_HPP
