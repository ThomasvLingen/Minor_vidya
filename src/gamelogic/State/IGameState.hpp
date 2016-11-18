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
        IGameState();
        virtual ~IGameState();

        virtual void update(GameLogic::Game& game);
    };
    typedef std::shared_ptr<IGameState> SPTR_IGameState;
}

#endif //MINOR_VIDYA_IGAMESTATE_HPP
