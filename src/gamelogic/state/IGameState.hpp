//
// Created by sander on 11/17/16.
//

#ifndef MINOR_VIDYA_IGAMESTATE_HPP
#define MINOR_VIDYA_IGAMESTATE_HPP

#include <memory>

namespace GameLogic {
    class Game;
    typedef std::shared_ptr<Game> SPTR_Game;
}

namespace State{

    class IGameState {

    public:
        virtual void update(GameLogic::Game& game, int time_since_last_update) = 0;

    };
    typedef std::shared_ptr<IGameState> SPTR_IGameState;
}

#endif //MINOR_VIDYA_IGAMESTATE_HPP
