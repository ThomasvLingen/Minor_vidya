//
// Created by jazula on 1/16/17.
//

#ifndef MINOR_VIDYA_GAMEOVERSTATE_HPP
#define MINOR_VIDYA_GAMEOVERSTATE_HPP

#include "IGameState.hpp"
#include "Menu.hpp"

namespace GameLogic {
    class Game;
}

namespace State {
    class GameOverState : public IGameState {
    public:
        GameOverState(Game& context);

        virtual void update(int time_since_last_update) override;

    private:
        Menu _menu;
        Color _color{255,255,255};
    };
}


#endif //MINOR_VIDYA_GAMEOVERSTATE_HPP
