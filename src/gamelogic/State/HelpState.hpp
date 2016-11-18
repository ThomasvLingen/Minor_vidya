//
// Created by sander on 11/18/16.
//

#ifndef MINOR_VIDYA_HELPSTATE_HPP
#define MINOR_VIDYA_HELPSTATE_HPP

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

    class HelpState : public IGameState {

    public:
        HelpState();
        ~HelpState();

        void update(GameLogic::Game& game) override ;
    };
}

#endif //MINOR_VIDYA_HELPSTATE_HPP
