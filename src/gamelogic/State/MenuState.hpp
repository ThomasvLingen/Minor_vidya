//
// Created by sander on 11/17/16.
//

#ifndef MINOR_VIDYA_MENUSTATE_HPP
#define MINOR_VIDYA_MENUSTATE_HPP

#include "IGameState.hpp"

namespace GameLogic {
    class Game;
}

namespace State {

    class MenuState : public IGameState {

    public:
        MenuState();
        ~MenuState();

        void update(GameLogic::Game& game) override ;
    };
}

#endif //MINOR_VIDYA_MENUSTATE_HPP
