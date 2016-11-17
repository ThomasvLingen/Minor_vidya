//
// Created by sander on 11/17/16.
//

#ifndef MINOR_VIDYA_IGAMESTATE_HPP
#define MINOR_VIDYA_IGAMESTATE_HPP

namespace GameLogic {
    class Game;
}

namespace State{

    class IGameState {

    public:
        IGameState();
        virtual ~IGameState();

        virtual void update(GameLogic::Game & game);
    };
}

#endif //MINOR_VIDYA_IGAMESTATE_HPP
