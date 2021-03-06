//
// Created by sander on 11/17/16.
//

#ifndef MINOR_VIDYA_STARTUPSTATE_HPP
#define MINOR_VIDYA_STARTUPSTATE_HPP

#include "IGameState.hpp"
#include "../Game.hpp"
#include "../../engine/SDLFacade.hpp"
#include "../../engine/PathUtil.hpp"

namespace GameLogic {
    class Game;
}

namespace State {
    using Engine::SDLFacade;
    using Engine::CoordinateDouble;
    using Engine::Color;
    using Engine::FontType;
    using Engine::Keys;
    using Engine::Input;
    using Engine::Key;
    using GameLogic::Game;

    class StartUpState : public IGameState {

    public:
        StartUpState(Game& context);
        void update(int time_since_last_update) override;
        
    };
}

#endif //MINOR_VIDYA_STARTUPSTATE_HPP
