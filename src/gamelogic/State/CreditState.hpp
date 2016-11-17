//
// Created by sander on 11/17/16.
//

#ifndef MINOR_VIDYA_CREDITSTATE_HPP
#define MINOR_VIDYA_CREDITSTATE_HPP

#include "IGameState.hpp"

namespace GameLogic {
    class Game;
}

namespace State {

    class CreditState : public IGameState {

    public:
        CreditState();
        ~CreditState();

        void update(GameLogic::Game & game) override ;
    };
}

#endif //MINOR_VIDYA_CREDITSTATE_HPP
