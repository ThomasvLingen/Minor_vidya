//
// Created by sander on 11/17/16.
//

#ifndef MINOR_VIDYA_LOADSTATE_HPP
#define MINOR_VIDYA_LOADSTATE_HPP

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
    using Engine::PressedKeys;
    using Engine::Key;
    using GameLogic::Game;
    using Engine::PathUtil;

    class LoadState : public IGameState {

    public:
        LoadState(Game& context);
        void update(int time_since_last_update) override ;

    private:
        int _loading_screen_time = 0;
        Color _color{255,255,255};
    };
}
#endif //MINOR_VIDYA_LOADSTATE_HPP
