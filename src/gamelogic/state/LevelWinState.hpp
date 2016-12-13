//
// Created by waseland on 12/7/16.
//

#ifndef MINOR_VIDYA_LEVELWINSTATE_HPP
#define MINOR_VIDYA_LEVELWINSTATE_HPP

#include "IGameState.hpp"
#include "../Game.hpp"
#include "../../engine/SDLFacade.hpp"
#include "Menu.hpp"

namespace GameLogic {
    class Game;
}

namespace State {
    using Engine::SDLFacade;
    using Engine::CoordinateDouble;
    using Engine::Color;
    using Engine::FontType;
    using Engine::Keys;
    using Engine::Key;
    using GameLogic::Game;

    class LevelWinState : public IGameState {

    public:
        LevelWinState(Game& context);

        void update(int time_since_last_update) override;

    private:
        Menu _menu;
        Color _color{255,255,255};
    };
}


#endif //MINOR_VIDYA_LEVELWINSTATE_HPP
