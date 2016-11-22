//
// Created by sander on 11/17/16.
//

#ifndef MINOR_VIDYA_IGAMESTATE_HPP
#define MINOR_VIDYA_IGAMESTATE_HPP

#include <memory>
#include "../../engine/interface/Collection.hpp"

namespace GameLogic {
    class Game;
    typedef std::shared_ptr<Game> SPTR_Game;
}

namespace State {

    using GameLogic::Game;

    class IGameState {

    public:
        IGameState(Game& context);
        virtual void update(int time_since_last_update) = 0;

    protected:
        Game& _context;
        Engine::Collection _collection;
    };

    typedef std::shared_ptr<IGameState> SPTR_IGameState;
}

#endif //MINOR_VIDYA_IGAMESTATE_HPP
