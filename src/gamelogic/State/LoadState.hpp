//
// Created by sander on 11/17/16.
//

#ifndef MINOR_VIDYA_LOADSTATE_HPP
#define MINOR_VIDYA_LOADSTATE_HPP

#include "IGameState.hpp"

namespace GameLogic {
    class Game;
}

namespace State {

    class LoadState : public IGameState {

    public:
        LoadState();
        ~LoadState();

        void update(GameLogic::Game& game) override ;
    };
}
#endif //MINOR_VIDYA_LOADSTATE_HPP
