//
// Created by sander on 11/17/16.
//

#ifndef MINOR_VIDYA_PAUSESTATE_HPP
#define MINOR_VIDYA_PAUSESTATE_HPP

#include "IGameState.hpp"
#include "../Game.hpp"
#include "../../engine/SDLFacade.hpp"

namespace GameLogic {
    class Game;
}

namespace State {
    using Engine::SDLFacade;
    using Engine::CoordinateDouble;
    using Engine::Color;
    using Engine::FontType;
    using Engine::PressedKeys;
    using Engine::Key;

    class PauseState : public IGameState {

    public:
        void update(GameLogic::Game& game, int time_since_last_update) override ;

    private:
        int _timeSinceLastPress = 0;
        int _selected = 1;
        Color _color{255,255,255};
    };
}

#endif //MINOR_VIDYA_PAUSESTATE_HPP
